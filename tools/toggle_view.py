import os
import json
import argparse

SETTINGS_PATH = '.vscode/settings.json'

# Folders and patterns to permanently exclude from the VSCode sidebar
PERMANENT_EXCLUDES = {
    "**/.git": True,
    "**/__pycache__": True,
    "**/*.pyc": True,
    "**/node_modules": True,
    "**/.dart_tool": True,
    "**/build": True,
    "**/.flutter-plugins": True,
    "**/.flutter-plugins-dependencies": True,
    "**/agri3d_flutter/android": True,
    "**/agri3d_flutter/ios": True,
    "**/agri3d_flutter/linux": True,
    "**/agri3d_flutter/macos": True,
    "**/agri3d_flutter/web": True,
    "**/agri3d_flutter/windows": True,
    "**/agri3d_flutter/pubspec.lock": True,
    "**/.vscode": True,
    "**/.agents": True
}

def main():
    parser = argparse.ArgumentParser(description='Toggle workspace visibility in VSCode')
    parser.add_argument('--focus', nargs='+', help='Root folders to keep visible (e.g. GRBL-AGRI3D, AI-Agri3D, agri3d_flutter, reference)')
    parser.add_argument('--reset', action='store_true', help='Show all root folders')
    args = parser.parse_args()

    if not os.path.exists(SETTINGS_PATH):
        # Create it if it doesn't exist
        os.makedirs(os.path.dirname(SETTINGS_PATH), exist_ok=True)
        with open(SETTINGS_PATH, 'w') as f:
            json.dump({}, f)

    with open(SETTINGS_PATH, 'r') as f:
        try:
            settings = json.load(f)
        except json.JSONDecodeError:
            settings = {}

    # Always enforce the permanent excludes
    new_excludes = dict(PERMANENT_EXCLUDES)

    if args.focus:
        # Core folders that should never be dynamically hidden
        always_visible = ['masterplan', 'tools', 'communication']
        
        visible_roots = set(always_visible)
        nested_focus = {}
        
        # Parse focus paths
        for path in args.focus:
            parts = path.replace('\\', '/').strip('/').split('/')
            root = parts[0]
            visible_roots.add(root)
            if len(parts) > 1:
                if root not in nested_focus:
                    nested_focus[root] = set()
                nested_focus[root].add(parts[1])
            else:
                # If they requested the entire root, clear any nested constraints
                if root in nested_focus:
                    del nested_focus[root]

        root_items = os.listdir('.')
        for item in root_items:
            # Skip dotfiles/dotfolders
            if item.startswith('.'):
                continue
                
            if item not in visible_roots:
                # Hide the entire root folder
                new_excludes[item] = True
            elif item in nested_focus and os.path.isdir(item):
                # Hide only the un-focused subfolders
                allowed_subdirs = nested_focus[item]
                for sub in os.listdir(item):
                    if sub not in allowed_subdirs:
                        new_excludes[f"{item}/{sub}"] = True
        
        print(f"[Workspace Toggler] Focusing on: {', '.join(args.focus)}")
    elif args.reset:
        print("[Workspace Toggler] Resetting workspace view. All modules visible.")
    else:
        print("Please provide --focus [folders...] or --reset")
        return

    settings['files.exclude'] = new_excludes

    with open(SETTINGS_PATH, 'w') as f:
        json.dump(settings, f, indent=2)
    
    print("[Workspace Toggler] .vscode/settings.json updated successfully.")

if __name__ == '__main__':
    main()
