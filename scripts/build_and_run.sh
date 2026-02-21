#!/bin/bash

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Build the project
"$SCRIPT_DIR/build.sh" "$@" || exit 1

# Run the executable
echo ""
"$SCRIPT_DIR/run.sh"