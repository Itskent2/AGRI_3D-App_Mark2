#!/usr/bin/env python3
"""
sync_contracts.py

Reads the central protocol_schema.json and generates:
1. agri3d_protocol.h (C++ header for ESP32-S3)
2. agri3d_protocol.dart (Dart class definitions for Flutter)

This ensures both the master microcontroller and the mobile app use the
exact same MessagePack keys and structures, resolving communication bugs at compile-time.
"""

import os
import json
import sys

SCHEMA_PATH = os.path.join(os.path.dirname(__file__), "protocol_schema.json")

def load_schema():
    if not os.path.exists(SCHEMA_PATH):
        print(f"Error: Schema file not found at {SCHEMA_PATH}", file=sys.stderr)
        sys.exit(1)
    with open(SCHEMA_PATH, "r") as f:
        return json.load(f)

def main():
    print("Reading communication schema from protocol_schema.json...")
    schema = load_schema()
    
    enums = schema.get("enums", {})
    messages = schema.get("messages", {})
    
    print(f"Loaded {len(enums)} enums and {len(messages)} messages.")
    print("Contract compilation code will be implemented here during the build phase.")

if __name__ == "__main__":
    main()
