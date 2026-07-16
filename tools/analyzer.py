#!/usr/bin/env python3
import os
import re
import json
import sys
import urllib.request

# Common C/C++ keywords to exclude from function detection
EXCLUDED_NAMES = {
    'if', 'while', 'for', 'switch', 'return', 'catch', 'sizeof', 'defined', 
    'else', 'typedef', 'struct', 'union', 'enum', 'volatile', 'register',
    'static', 'const', 'extern', 'inline', 'template', 'class', 'typename',
    'operator', 'sizeof', 'new', 'delete', 'throw', 'goto'
}

def strip_comments(code):
    """
    Strips single-line and multi-line comments from C/C++ source code.
    Preserves string literals to avoid corrupting regex matches.
    """
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " "  # Replace comment with space to preserve line spacing
        else:
            return s
    
    # Match double slash comments, block comments, and single/double-quoted string literals
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, code)

def parse_file(file_path):
    """
    Parses a single source file, extracting includes and function definitions/declarations.
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading file {file_path}: {e}")
        return None

    clean_content = strip_comments(content)

    # 1. Extract includes
    includes = []
    # Match #include "file.h" or #include <file.h>
    include_matches = re.finditer(r'#include\s+(?:"([^"]+)"|<([^>]+)>)', clean_content)
    for m in include_matches:
        header = m.group(1) or m.group(2)
        includes.append(header)

    # 2. Extract functions
    # Matches return types, pointers, names, parameters, and trailing brace/semicolon.
    # Excludes control loops.
    func_regex = re.compile(
        r'\b(?:(?:inline|static|extern|volatile|const|virtual|void|int|char|float|double|bool|uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t)\s+)*' # qualifiers
        r'([\w_]+(?:::[\w_]+)?(?:\s*\*+)?)\s+'  # return type (group 1)
        r'([\w_]+(?:::[\w_]+)?)\s*'             # function name (group 2)
        r'\(([^)]*)\)\s*'                       # arguments (group 3)
        r'(?:const\s*)?'                         # const qualifier (optional)
        r'(\{Base\}|;|\{)'                      # terminator (group 4: semicolon = decl, { = def)
    )

    functions = []
    for m in func_regex.finditer(clean_content):
        ret_type = m.group(1).strip()
        func_name = m.group(2).strip()
        args = m.group(3).strip()
        terminator = m.group(4)

        # Ignore keywords misidentified as functions
        if func_name in EXCLUDED_NAMES or '(' in func_name or ')' in func_name:
            continue
        
        # Also check if it's a common control keyword
        if func_name in ['if', 'while', 'for', 'switch']:
            continue

        is_def = (terminator == '{')
        line_num = content[:m.start()].count('\n') + 1

        body = ""
        if is_def:
            # Simple bracket matcher to extract the function body
            start_idx = m.end() - 1  # Index of '{'
            brace_count = 0
            end_idx = start_idx
            for i in range(start_idx, len(clean_content)):
                if clean_content[i] == '{':
                    brace_count += 1
                elif clean_content[i] == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        end_idx = i + 1
                        break
            body = clean_content[start_idx:end_idx]

        functions.append({
            "name": func_name,
            "return_type": ret_type,
            "args": args,
            "is_definition": is_def,
            "line": line_num,
            "body": body
        })

    return {
        "includes": includes,
        "functions": functions,
        "lines_count": content.count('\n') + 1,
        "size_bytes": len(content),
        "clean_content": clean_content
    }

def analyze_cleanup_terms(file_path):
    """
    Scans the file for mentions of door, spindle, coolant, parking to identify cleanup locations.
    """
    cleanup_terms = ['door', 'spindle', 'coolant', 'parking']
    matches = []
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            for idx, line in enumerate(f, 1):
                clean_line = line.strip().lower()
                for term in cleanup_terms:
                    # Avoid matching standard include guards or unrelated words
                    if term in clean_line and not clean_line.startswith('#ifndef') and not clean_line.startswith('#define'):
                        matches.append({
                            "line": idx,
                            "term": term,
                            "content": line.strip()
                        })
    except Exception as e:
        pass
    return matches

def build_codebase_graph(source_dir):
    """
    Recursively scans the directory and processes C/C++/Arduino files to build the graph.
    """
    graph = {
        "files": {},
        "functions": {},
        "file_edges": [],  # includes
        "call_edges": [],  # calls
        "cleanup_candidates": {}
    }

    supported_extensions = ('.c', '.h', '.cpp', '.hpp', '.ino')
    all_files = []

    for root, dirs, files in os.walk(source_dir):
        # Skip output folder, reference-original git directories, and build artifacts
        if 'analyzer-out' in root or '.git' in root or 'build' in root:
            continue
        for file in files:
            if file.endswith(supported_extensions):
                full_path = os.path.join(root, file)
                rel_path = os.path.relpath(full_path, source_dir).replace('\\', '/')
                all_files.append((full_path, rel_path))

    # Phase 1: Parse all files
    for full_path, rel_path in all_files:
        parsed = parse_file(full_path)
        if parsed:
            graph["files"][rel_path] = {
                "name": os.path.basename(rel_path),
                "path": rel_path,
                "size_bytes": parsed["size_bytes"],
                "lines": parsed["lines_count"],
                "includes": parsed["includes"]
            }
            # Record clean-up candidates
            cleanup_matches = analyze_cleanup_terms(full_path)
            if cleanup_matches:
                graph["cleanup_candidates"][rel_path] = cleanup_matches

            # Register functions
            for f in parsed["functions"]:
                f_key = f"{rel_path}::{f['name']}"
                graph["functions"][f_key] = {
                    "name": f["name"],
                    "file": rel_path,
                    "return_type": f["return_type"],
                    "args": f["args"],
                    "is_definition": f["is_definition"],
                    "line": f["line"],
                    "body": f["body"]
                }

    # Phase 2: Build Include (File-to-File) Edges
    for file_path, file_info in graph["files"].items():
        for inc in file_info["includes"]:
            # Find the file in the workspace that matches this include name
            matched_target = None
            for other_path in graph["files"]:
                if other_path.endswith(inc) or os.path.basename(other_path) == inc:
                    matched_target = other_path
                    break
            
            if matched_target:
                graph["file_edges"].append({
                    "source": file_path,
                    "target": matched_target,
                    "type": "includes"
                })

    # Phase 3: Resolve Call Graph (Function-to-Function Edges)
    # Collect all defined function names (global list)
    defined_funcs = {}
    for f_key, f_info in graph["functions"].items():
        if f_info["is_definition"]:
            defined_funcs[f_info["name"]] = defined_funcs.get(f_info["name"], []) + [f_key]

    for f_key, f_info in graph["functions"].items():
        if f_info["is_definition"] and f_info["body"]:
            body = f_info["body"]
            # Look for function calls in the body of the function
            for callee_name, callee_keys in defined_funcs.items():
                # Avoid calling self recursively or matching within names
                if callee_name == f_info["name"]:
                    continue
                # Match function call: callee_name followed by optional space and open parenthesis
                call_pattern = re.compile(r'\b' + re.escape(callee_name) + r'\s*\(')
                if call_pattern.search(body):
                    for c_key in callee_keys:
                        # Record call edge
                        graph["call_edges"].append({
                            "source": f_key,
                            "target": c_key,
                            "type": "calls"
                        })

    return graph

def generate_html_visualization(graph, output_file):
    """
    Generates an interactive vis.js HTML graph visualization dashboard.
    """
    # Structure nodes and edges for vis.js
    nodes = []
    edges = []

    # Add File Nodes
    for path, info in graph["files"].items():
        nodes.append({
            "id": path,
            "label": info["name"],
            "title": f"File: {path}<br>Lines: {info['lines']}<br>Size: {info['size_bytes']} bytes",
            "group": "file",
            "value": info["lines"],
            "level": 1
        })

    # Add Function Nodes (only definitions to avoid clutter)
    for f_key, info in graph["functions"].items():
        if info["is_definition"]:
            nodes.append({
                "id": f_key,
                "label": f"{info['name']}()",
                "title": f"Function: {info['return_type']} {info['name']}({info['args']})<br>File: {info['file']}<br>Line: {info['line']}",
                "group": "function",
                "value": 1,
                "level": 2
            })

    # Add File Include Edges
    for edge in graph["file_edges"]:
        edges.append({
            "from": edge["source"],
            "to": edge["target"],
            "arrows": "to",
            "color": {"color": "#6366f1", "highlight": "#818cf8"},
            "label": "includes",
            "font": {"size": 10, "color": "#a1a1aa"},
            "dashes": True
        })

    # Add Function Call Edges
    for edge in graph["call_edges"]:
        edges.append({
            "from": edge["source"],
            "to": edge["target"],
            "arrows": "to",
            "color": {"color": "#10b981", "highlight": "#34d399"},
            "label": "calls",
            "font": {"size": 8, "color": "#a1a1aa"}
        })

    # Add parent-child containment edges between files and their defined functions
    for f_key, info in graph["functions"].items():
        if info["is_definition"] and info["file"] in graph["files"]:
            edges.append({
                "from": info["file"],
                "to": f_key,
                "arrows": "none",
                "color": {"color": "#4b5563", "opacity": 0.15},
                "label": "defines",
                "length": 80,
                "hidden": True # Controlled dynamically in JS
            })

    html_content = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Agri3D Codebase Knowledge Graph</title>
    <!-- Local vis.js assets (enables offline usage and bypasses file:// security blocks) -->
    <link rel="stylesheet" href="vis-network.min.css" />
    <script type="text/javascript" src="vis-network.min.js"></script>
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;600;800&family=JetBrains+Mono&display=swap" rel="stylesheet">
    
    <style>
        * {{
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }}
        body {{
            font-family: 'Outfit', sans-serif;
            background-color: #0b0f19;
            color: #f3f4f6;
            display: flex;
            height: 100vh;
            overflow: hidden;
        }}
        #sidebar {{
            width: 380px;
            background-color: #111827;
            border-right: 1px solid #1f2937;
            display: flex;
            flex-direction: column;
            padding: 24px;
            z-index: 10;
            box-shadow: 4px 0 20px rgba(0,0,0,0.4);
        }}
        h1 {{
            font-size: 20px;
            font-weight: 800;
            margin-bottom: 8px;
            background: linear-gradient(135deg, #6366f1, #10b981);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
        }}
        .subtitle {{
            font-size: 12px;
            color: #9ca3af;
            margin-bottom: 24px;
        }}
        .search-box {{
            width: 100%;
            padding: 12px;
            border-radius: 8px;
            border: 1px solid #374151;
            background-color: #1f2937;
            color: #fff;
            margin-bottom: 20px;
            font-family: inherit;
        }}
        .search-box:focus {{
            outline: none;
            border-color: #6366f1;
            box-shadow: 0 0 0 2px rgba(99, 102, 241, 0.2);
        }}
        .filter-section {{
            margin-bottom: 24px;
        }}
        .filter-section h3 {{
            font-size: 14px;
            text-transform: uppercase;
            letter-spacing: 0.05em;
            color: #6b7280;
            margin-bottom: 12px;
        }}
        .filter-group {{
            display: flex;
            flex-direction: column;
            gap: 10px;
        }}
        .checkbox-container {{
            display: flex;
            align-items: center;
            font-size: 14px;
            cursor: pointer;
            user-select: none;
        }}
        .checkbox-container input {{
            margin-right: 8px;
            cursor: pointer;
        }}
        #details-panel {{
            flex-grow: 1;
            border-top: 1px solid #1f2937;
            padding-top: 20px;
            overflow-y: auto;
        }}
        #details-panel h3 {{
            font-size: 16px;
            margin-bottom: 10px;
            color: #10b981;
        }}
        .detail-item {{
            margin-bottom: 12px;
            font-size: 13px;
        }}
        .detail-label {{
            font-weight: 600;
            color: #9ca3af;
            margin-bottom: 4px;
        }}
        .detail-val {{
            background-color: #0b0f19;
            padding: 6px;
            border-radius: 4px;
            border: 1px solid #1f2937;
            word-break: break-all;
            font-family: 'JetBrains Mono', monospace;
        }}
        #network-container {{
            flex-grow: 1;
            position: relative;
            height: 100vh;
        }}
        #mynetwork {{
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
        }}
        .legend {{
            position: absolute;
            bottom: 24px;
            right: 24px;
            background-color: rgba(17, 24, 39, 0.9);
            border: 1px solid #1f2937;
            padding: 12px;
            border-radius: 8px;
            font-size: 12px;
            display: flex;
            gap: 16px;
        }}
        .legend-item {{
            display: flex;
            align-items: center;
            gap: 6px;
        }}
        .legend-dot {{
            width: 12px;
            height: 12px;
            border-radius: 50%;
        }}
        .legend-file {{ background-color: #6366f1; }}
        .legend-function {{ background-color: #10b981; }}
        .btn {{
            padding: 10px 14px;
            border-radius: 6px;
            border: none;
            background-color: #374151;
            color: #f3f4f6;
            cursor: pointer;
            font-family: inherit;
            font-weight: 600;
            transition: all 0.2s;
            margin-top: 10px;
        }}
        .btn:hover {{
            background-color: #4b5563;
        }}
        .btn-primary {{
            background-color: #6366f1;
        }}
        .btn-primary:hover {{
            background-color: #4f46e5;
        }}
    </style>
</head>
<body>
    <div id="sidebar">
        <h1>Agri3D Codebase</h1>
        <div class="subtitle">Interactive Knowledge Graph</div>
        
        <input type="text" id="search-input" class="search-box" placeholder="Search functions or files...">
        
        <div class="filter-section">
            <h3>View Mode</h3>
            <select id="view-mode" class="search-box" style="margin-bottom: 20px;">
                <option value="files-only" selected>File Structure Only (Clean)</option>
                <option value="combined">Combined (Files & Functions)</option>
                <option value="functions-only">Function Call Graph Only</option>
            </select>
        </div>
        
        <div class="filter-section">
            <h3>Highlight Depth (N)</h3>
            <div style="display: flex; align-items: center; gap: 10px; margin-bottom: 20px;">
                <input type="range" id="depth-range" min="1" max="5" value="1" style="flex-grow: 1; cursor: pointer;">
                <span id="depth-val" style="font-weight: 600; color: #10b981; min-width: 15px; text-align: right;">1</span>
            </div>
        </div>

        <div class="filter-section">
            <h3>Configuration</h3>
            <div class="filter-group">
                <label class="checkbox-container">
                    <input type="checkbox" id="physics-enable" checked>
                    Enable Physics Simulation
                </label>
            </div>
            <button id="reset-button" class="btn btn-primary">Reset View / Zoom</button>
        </div>

        <div id="details-panel">
            <h3>Element Details</h3>
            <div id="details-content">
                <p style="color: #6b7280; font-size: 13px;">Click on a node in the graph to display its relationships and structural parameters.</p>
            </div>
        </div>
    </div>

    <div id="network-container">
        <div id="mynetwork">
            <div id="loading-fallback" style="padding: 40px; text-align: center; color: #9ca3af; font-family: 'Outfit', sans-serif; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); width: 80%; z-index: 1;">
                <h2 style="color: #6366f1; margin-bottom: 12px; font-weight: 600; font-size: 20px;">Initializing Knowledge Graph...</h2>
                <p style="margin-bottom: 8px; font-size: 14px;">If this screen remains blank, the browser was unable to fetch the <code>vis.js</code> library from the CDN under the <code>file:///</code> protocol.</p>
                <p style="font-size: 12px; color: #6b7280;">Please check your internet connection or press <b>F12</b> to open Developer Tools and view the Console tab for errors.</p>
            </div>
        </div>
        
        <div class="legend">
            <div class="legend-item">
                <div class="legend-dot legend-file"></div>
                <span>Files</span>
            </div>
            <div class="legend-item">
                <div class="legend-dot legend-function"></div>
                <span>Functions</span>
            </div>
        </div>
    </div>

    <script type="text/javascript">
        // Embed the parsed graph data
        const graphData = {{
            nodes: {json.dumps(nodes)},
            edges: {json.dumps(edges)}
        }};

        if (typeof vis === 'undefined') {{
            document.getElementById('loading-fallback').innerHTML = `
                <h2 style="color: #ef4444; margin-bottom: 12px; font-weight: 600; font-size: 20px;">Library Load Error</h2>
                <p style="margin-bottom: 8px; font-size: 14px; color: #f3f4f6;">The <code>vis-network</code> library failed to load from the CDN.</p>
                <p style="font-size: 12px; color: #9ca3af;">This page requires internet access to fetch the graphing library. Please verify your connection.</p>
            `;
            throw new Error("vis-network library not loaded");
        }}

        const container = document.getElementById('mynetwork');
        
        const nodesDataSet = new vis.DataSet(graphData.nodes);
        const edgesDataSet = new vis.DataSet(graphData.edges);

        const data = {{
            nodes: nodesDataSet,
            edges: edgesDataSet
        }};

        const options = {{
            nodes: {{
                shape: 'dot',
                font: {{
                    color: '#f3f4f6',
                    size: 14,
                    face: 'Outfit'
                }},
                borderWidth: 2,
                shadow: true
            }},
            edges: {{
                width: 1.5,
                smooth: {{
                    type: 'continuous'
                }}
            }},
            physics: {{
                stabilization: true,
                barnesHut: {{
                    gravitationalConstant: -6000,
                    centralGravity: 0.15,
                    springLength: 120,
                    springConstant: 0.04
                }}
            }},
            groups: {{
                file: {{
                    color: {{
                        background: '#1e1b4b',
                        border: '#6366f1',
                        highlight: {{ background: '#312e81', border: '#818cf8' }}
                    }},
                    shape: 'dot'
                }},
                function: {{
                    color: {{
                        background: '#064e3b',
                        border: '#10b981',
                        highlight: {{ background: '#065f46', border: '#34d399' }}
                    }},
                    shape: 'dot'
                }}
            }}
        }};

        const network = new vis.Network(container, data, options);

        // Details Panel and Interaction
        network.on("click", function (params) {{
            if (params.nodes.length > 0) {{
                selectedNodeId = params.nodes[0];
                const node = nodesDataSet.get(selectedNodeId);
                displayDetails(node);
                const depth = parseInt(document.getElementById('depth-range').value);
                highlightNeighbors(selectedNodeId, depth);
            }} else {{
                selectedNodeId = null;
                resetHighlight();
                document.getElementById('details-content').innerHTML = 
                    `<p style="color: #6b7280; font-size: 13px;">Click on a node in the graph to display its relationships and structural parameters.</p>`;
            }}
        }});

        function displayDetails(node) {{
            const detailsDiv = document.getElementById('details-content');
            
            if (node.group === 'file') {{
                // Find all functions in this file
                const funcs = nodesDataSet.get({{
                    filter: function (item) {{
                        return item.group === 'function' && item.id.startsWith(node.id + '::');
                    }}
                }});
                
                let funcListHtml = funcs.map(f => `<li>${{f.label}}</li>`).join('');
                if (funcs.length === 0) funcListHtml = 'None detected';

                detailsDiv.innerHTML = `
                    <div class="detail-item">
                        <div class="detail-label">File Path</div>
                        <div class="detail-val">${{node.id}}</div>
                    </div>
                    <div class="detail-item">
                        <div class="detail-label">File Info</div>
                        <div>${{node.title}}</div>
                    </div>
                    <div class="detail-item">
                        <div class="detail-label">Functions Defined Here (${{funcs.length}})</div>
                        <div class="detail-val" style="max-height: 120px; overflow-y: auto;">
                            <ul style="padding-left: 15px; margin: 0;">${{funcListHtml}}</ul>
                        </div>
                    </div>
                `;
            }} else if (node.group === 'function') {{
                // Find callers and callees
                const callers = [];
                const callees = [];
                const allEdges = edgesDataSet.get();
                
                allEdges.forEach(edge => {{
                    if (edge.to === node.id && edge.label === 'calls') {{
                        callers.push(edge.from.split('::').pop() + '()');
                    }}
                    if (edge.from === node.id && edge.label === 'calls') {{
                        callees.push(edge.to.split('::').pop() + '()');
                    }}
                }});

                detailsDiv.innerHTML = `
                    <div class="detail-item">
                        <div class="detail-label">Function Key</div>
                        <div class="detail-val">${{node.id}}</div>
                    </div>
                    <div class="detail-item">
                        <div class="detail-label">Signature Details</div>
                        <div>${{node.title}}</div>
                    </div>
                    <div class="detail-item">
                        <div class="detail-label">Called By (${{callers.length}})</div>
                        <div class="detail-val">${{callers.join(', ') || 'None'}}</div>
                    </div>
                    <div class="detail-item">
                        <div class="detail-label">Calls Functions (${{callees.length}})</div>
                        <div class="detail-val">${{callees.join(', ') || 'None'}}</div>
                    </div>
                `;
            }}
        }}

        // Neighborhood Highlighting with BFS Depth
        let selectedNodeId = null;
        let allNodes = [];
        let highlightActive = false;

        function highlightNeighbors(selectedId, maxDepth = 1) {{
            highlightActive = true;
            allNodes = nodesDataSet.get();
            const allEdges = edgesDataSet.get();

            // Breadth-First Search (BFS) to find nodes within maxDepth
            const visited = new Set();
            const queue = [{{ id: selectedId, depth: 0 }}];
            visited.add(selectedId);

            const traversedEdges = new Set();

            while (queue.length > 0) {{
                const curr = queue.shift();
                if (curr.depth >= maxDepth) {{
                    continue;
                }}

                // Get immediate connected nodes
                const neighbors = network.getConnectedNodes(curr.id);
                neighbors.forEach(neighborId => {{
                    if (!visited.has(neighborId)) {{
                        visited.add(neighborId);
                        queue.push({{ id: neighborId, depth: curr.depth + 1 }});
                    }}
                    
                    // Identify the edge connecting them
                    allEdges.forEach(edge => {{
                        if ((edge.from === curr.id && edge.to === neighborId) || 
                            (edge.from === neighborId && edge.to === curr.id)) {{
                            traversedEdges.add(edge.id);
                        }}
                    }});
                }});
            }}

            // Dim non-visited nodes
            const nodeUpdates = [];
            allNodes.forEach(node => {{
                const isVisited = visited.has(node.id);
                const opacity = isVisited ? 1.0 : 0.08;
                
                nodeUpdates.push({{
                    id: node.id,
                    color: {{
                        background: node.group === 'file' ? 'rgba(30, 27, 75, ' + opacity + ')' : 'rgba(6, 78, 59, ' + opacity + ')',
                        border: node.group === 'file' ? 'rgba(99, 102, 241, ' + opacity + ')' : 'rgba(16, 185, 129, ' + opacity + ')'
                    }}
                }});
            }});

            // Dim non-traversed edges
            const edgeUpdates = [];
            allEdges.forEach(edge => {{
                const baseColor = edge.label === 'includes' ? '#6366f1' : (edge.label === 'calls' ? '#10b981' : '#4b5563');
                const isTraversed = traversedEdges.has(edge.id);
                const opacity = isTraversed ? 1.0 : 0.05;
                
                edgeUpdates.push({{
                    id: edge.id,
                    color: {{
                        color: baseColor,
                        opacity: opacity
                    }}
                }});
            }});

            nodesDataSet.update(nodeUpdates);
            edgesDataSet.update(edgeUpdates);
        }}

        function resetHighlight() {{
            if (highlightActive) {{
                allNodes = nodesDataSet.get();
                const allEdges = edgesDataSet.get();
                
                const nodeUpdates = [];
                allNodes.forEach(node => {{
                    nodeUpdates.push({{
                        id: node.id,
                        color: null
                    }});
                }});
                
                const edgeUpdates = [];
                allEdges.forEach(edge => {{
                    const baseColor = edge.label === 'includes' ? '#6366f1' : (edge.label === 'calls' ? '#10b981' : '#4b5563');
                    edgeUpdates.push({{
                        id: edge.id,
                        color: {{
                            color: baseColor,
                            opacity: 1.0
                        }}
                    }});
                }});
                
                nodesDataSet.update(nodeUpdates);
                edgesDataSet.update(edgeUpdates);
                highlightActive = false;
            }}
        }}

        // View Mode and Filtering logic
        function applyViewMode(mode) {{
            const allNodes = nodesDataSet.get();
            const allEdges = edgesDataSet.get();
            
            const nodeUpdates = [];
            const edgeUpdates = [];
            
            allNodes.forEach(node => {{
                let hidden = false;
                if (mode === 'files-only' && node.group === 'function') {{
                    hidden = true;
                }} else if (mode === 'functions-only' && node.group === 'file') {{
                    hidden = true;
                }}
                nodeUpdates.push({{ id: node.id, hidden: hidden }});
            }});
            
            allEdges.forEach(edge => {{
                let hidden = false;
                if (mode === 'files-only') {{
                    if (edge.label === 'calls' || edge.label === 'defines') {{
                        hidden = true;
                    }}
                }} else if (mode === 'functions-only') {{
                    if (edge.label === 'includes' || edge.label === 'defines') {{
                        hidden = true;
                    }}
                }} else if (mode === 'combined') {{
                    // Show defines as thin lines in combined view
                    if (edge.label === 'defines') {{
                        hidden = false;
                    }}
                }}
                edgeUpdates.push({{ id: edge.id, hidden: hidden }});
            }});
            
            nodesDataSet.update(nodeUpdates);
            edgesDataSet.update(edgeUpdates);
            network.fit();
        }}

        document.getElementById('view-mode').addEventListener('change', function(e) {{
            applyViewMode(e.target.value);
        }});

        document.getElementById('physics-enable').addEventListener('change', function(e) {{
            network.setOptions({{ physics: {{ enabled: e.target.checked }} }});
        }});

        document.getElementById('reset-button').addEventListener('click', function() {{
            selectedNodeId = null;
            resetHighlight();
            const currentMode = document.getElementById('view-mode').value;
            applyViewMode(currentMode);
            document.getElementById('search-input').value = '';
            document.getElementById('depth-range').value = 1;
            document.getElementById('depth-val').innerText = '1';
        }});

        document.getElementById('depth-range').addEventListener('input', function(e) {{
            const val = parseInt(e.target.value);
            document.getElementById('depth-val').innerText = val;
            if (selectedNodeId) {{
                highlightNeighbors(selectedNodeId, val);
            }}
        }});

        // Initialize with default View Mode (Files-Only)
        applyViewMode('files-only');

        // Search functionality
        document.getElementById('search-input').addEventListener('input', function(e) {{
            const query = e.target.value.toLowerCase();
            if (!query) {{
                resetHighlight();
                return;
            }}

            const matches = nodesDataSet.get({{
                filter: item => item.label.toLowerCase().includes(query) || item.id.toLowerCase().includes(query)
            }});

            if (matches.length > 0) {{
                // Highlight matches and their neighbors
                highlightActive = true;
                const matchIds = matches.map(m => m.id);
                allNodes = nodesDataSet.get();
                const updateArray = [];
                
                allNodes.forEach(node => {{
                    const isMatch = matchIds.includes(node.id);
                    const opacity = isMatch ? 1.0 : 0.15;
                    updateArray.push({{
                        id: node.id,
                        color: {{
                            background: node.group === 'file' ? 'rgba(30, 27, 75, ' + opacity + ')' : 'rgba(6, 78, 59, ' + opacity + ')',
                            border: node.group === 'file' ? 'rgba(99, 102, 241, ' + opacity + ')' : 'rgba(16, 185, 129, ' + opacity + ')'
                        }}
                    }});
                }});
                nodesDataSet.update(updateArray);
                
                // Focus camera on first match
                network.focus(matchIds[0], {{ scale: 1.2, animation: true }});
                displayDetails(matches[0]);
            }}
        }});
    </script>
</body>
</html>
"""
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(html_content)

def generate_markdown_report(graph, output_file):
    """
    Generates a structured codebase analysis report in Markdown format.
    Includes Mermaid diagrams for dependency and key call structures.
    """
    # 1. Base Stats
    total_files = len(graph["files"])
    total_funcs = len([f for f in graph["functions"].values() if f["is_definition"]])
    total_lines = sum(f["lines"] for f in graph["files"].values())

    md = []
    md.append("# Agri3D Codebase Knowledge Graph Report\n")
    md.append("This report lists files, function declarations, call flows, and potential clean-up candidates.\n")
    md.append("## 📊 Core Statistics\n")
    md.append(f"- **Total Files**: {total_files}")
    md.append(f"- **Total Functions**: {total_funcs}")
    md.append(f"- **Total Lines of Code**: {total_lines} LOC\n")

    # 2. File Listing Table
    md.append("## 📁 File Structure Index\n")
    md.append("| File Name | Path | Size (KB) | Lines | Includes |")
    md.append("| --- | --- | --- | --- | --- |")
    for path, info in sorted(graph["files"].items()):
        inc_str = ", ".join(info["includes"]) if info["includes"] else "*None*"
        size_kb = round(info["size_bytes"] / 1024, 2)
        md.append(f"| `{info['name']}` | `reference/{path}` | {size_kb} KB | {info['lines']} | {inc_str} |")
    md.append("\n")

    # 3. Mermaid File Dependency Graph
    md.append("## 🕸️ File Dependency Graph\n")
    md.append("```mermaid")
    md.append("graph TD")
    # Add files as nodes
    for path, info in graph["files"].items():
        node_id = info["name"].replace('.', '_').replace('-', '_')
        md.append(f"    {node_id}[\"{info['name']}\"]")
    # Add edges
    for edge in graph["file_edges"]:
        src_id = os.path.basename(edge["source"]).replace('.', '_').replace('-', '_')
        tgt_id = os.path.basename(edge["target"]).replace('.', '_').replace('-', '_')
        md.append(f"    {src_id} --> {tgt_id}")
    md.append("```\n")

    # 4. Key Call Flow Structures
    md.append("## 🔄 Key Entry Call Flows\n")
    # Identify key functions: main, loop, protocol_process, mc_line, limits_get_state
    keys_of_interest = ['main', 'loop', 'mc_line', 'protocol_process', 'limits_get_state']
    found_keys = []
    for f_name in keys_of_interest:
        for f_key, info in graph["functions"].items():
            if info["name"] == f_name and info["is_definition"]:
                found_keys.append((f_name, f_key))
                break

    for f_name, f_key in found_keys:
        md.append(f"### Call Flow from `{f_name}()`\n")
        md.append("```mermaid")
        md.append("graph TD")
        
        # Breadth-first search for calls up to depth 3
        visited = set()
        queue = [(f_key, 0)]
        edges_to_print = []
        
        while queue:
            curr, depth = queue.pop(0)
            if curr in visited or depth >= 3:
                continue
            visited.add(curr)
            
            # Find all outgoing calls
            for edge in graph["call_edges"]:
                if edge["source"] == curr:
                    src_short = edge["source"].split('::')[-1]
                    tgt_short = edge["target"].split('::')[-1]
                    edges_to_print.append(f"    {src_short} --> {tgt_short}")
                    queue.append((edge["target"], depth + 1))
                    
        if edges_to_print:
            # Print unique lines
            for l in sorted(list(set(edges_to_print))):
                md.append(l)
        else:
            md.append(f"    {f_name}[\"{f_name}()\"] --> None[\"No outgoing calls detected\"]")
            
        md.append("```\n")

    # 5. Clean-up Candidates
    md.append("## 🧼 Clean-up Candidates (door, spindle, coolant, parking)\n")
    md.append("These locations contain code references to legacy CNC systems (like spindle, coolant, safety door, etc.) which should be removed or cleaned up in our restarted clean code:\n")
    
    if graph["cleanup_candidates"]:
        for file_path, matches in sorted(graph["cleanup_candidates"].items()):
            md.append(f"### 📍 `reference/{file_path}`\n")
            md.append("| Line | Term | Match Snippet |")
            md.append("| --- | --- | --- |")
            for m in matches:
                # Escape markdown table characters
                escaped_content = m['content'].replace('|', '\\|')
                md.append(f"| {m['line']} | **{m['term']}** | `{escaped_content}` |")
            md.append("\n")
    else:
        md.append("*No legacy terms found.*")

    with open(output_file, 'w', encoding='utf-8') as f:
        f.write("\n".join(md))

def download_local_dependencies(output_dir):
    """
    Downloads vis-network.min.js and vis-network.min.css locally to the output folder.
    This enables offline loading and bypasses local browser file security policies.
    """
    js_url = "https://unpkg.com/vis-network/standalone/umd/vis-network.min.js"
    css_url = "https://unpkg.com/vis-network/styles/vis-network.min.css"
    
    js_path = os.path.join(output_dir, "vis-network.min.js")
    css_path = os.path.join(output_dir, "vis-network.min.css")
    
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
    }
    
    try:
        if not os.path.exists(js_path):
            print("Downloading local vis-network JS asset...")
            req = urllib.request.Request(js_url, headers=headers)
            with urllib.request.urlopen(req) as response:
                with open(js_path, 'wb') as f:
                    f.write(response.read())
            print("Successfully downloaded vis-network.min.js")
    except Exception as e:
        print(f"Warning: Failed to download JS asset: {e}")
        
    try:
        if not os.path.exists(css_path):
            print("Downloading local vis-network CSS asset...")
            req = urllib.request.Request(css_url, headers=headers)
            with urllib.request.urlopen(req) as response:
                with open(css_path, 'wb') as f:
                    f.write(response.read())
            print("Successfully downloaded vis-network.min.css")
    except Exception as e:
        print(f"Warning: Failed to download CSS asset: {e}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python analyzer.py <source_directory> [output_directory]")
        sys.exit(1)

    source_dir = os.path.abspath(sys.argv[1])
    
    if len(sys.argv) >= 3:
        output_dir = os.path.abspath(sys.argv[2])
    else:
        output_dir = os.path.join(source_dir, "analyzer-out")

    print(f"Scanning source directory: {source_dir}")
    if not os.path.exists(source_dir):
        print(f"Error: Directory {source_dir} does not exist.")
        sys.exit(1)

    print("Building codebase knowledge graph (files, functions, call edges)...")
    graph = build_codebase_graph(source_dir)

    # Ensure output directory exists
    os.makedirs(output_dir, exist_ok=True)
    print(f"Output directory established: {output_dir}")
    
    # Download vis.js locally to make it offline-friendly
    download_local_dependencies(output_dir)

    # 1. Output graph.json
    json_path = os.path.join(output_dir, "graph.json")
    with open(json_path, 'w', encoding='utf-8') as f:
        # Avoid dumping the huge function bodies into the raw JSON to keep it compact
        clean_graph = {
            "files": graph["files"],
            "file_edges": graph["file_edges"],
            "call_edges": graph["call_edges"],
            "functions": {
                k: {s: v for s, v in info.items() if s != "body"}
                for k, info in graph["functions"].items()
            }
        }
        json.dump(clean_graph, f, indent=2)
    print(f"Generated raw JSON graph: {json_path}")

    # 2. Output graph.html (vis.js)
    html_path = os.path.join(output_dir, "graph.html")
    generate_html_visualization(graph, html_path)
    print(f"Generated interactive HTML visualization: {html_path}")

    # 3. Output GRAPH_REPORT.md
    report_path = os.path.join(output_dir, "GRAPH_REPORT.md")
    generate_markdown_report(graph, report_path)
    print(f"Generated markdown report: {report_path}")

    print("Codebase analysis completed successfully.")

if __name__ == "__main__":
    main()
