#!/bin/bash

# Get project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT" || exit 1

if [ -f "exe/LibSystem" ]; then
    cd exe || exit 1
    echo "Running library system..."
    echo "========================================"
    ./LibSystem
else
    echo "✗ Executable not found. Run ./scripts/build.sh first."
    exit 1
fi