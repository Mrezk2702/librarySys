#!/bin/bash
# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get the project root directory (parent of scripts folder)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Change to project root
cd "$PROJECT_ROOT" || exit 1
# Project directories (relative to project root)
BUILD_DIR="build"
EXE_DIR="exe"
EXECUTABLE_NAME="LibSystem"  # Change this to your executable name


echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Building Library System Project${NC}"
echo -e "${BLUE}Project Root: $PROJECT_ROOT${NC}"
echo -e "${BLUE}========================================${NC}"

# Step 1: Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${GREEN}Creating build directory...${NC}"
    mkdir -p "$BUILD_DIR"
else
    echo -e "${GREEN}Build directory exists.${NC}"
fi

# Step 2: Navigate to build directory and run CMake
echo -e "${GREEN}Running CMake...${NC}"
cd "$BUILD_DIR" || exit 1

cmake .. || {
    echo -e "${RED}✗ CMake configuration failed!${NC}"
    exit 1
}

# Step 3: Build the project
echo -e "${GREEN}Building project...${NC}"
cmake --build . || {  # Use all CPU cores for faster build
    echo -e "${RED}✗ Build failed!${NC}"
    exit 1
}

# Step 4: Go back to project root
cd "$PROJECT_ROOT"

# Step 5: Create exe directory if it doesn't exist
if [ ! -d "$EXE_DIR" ]; then
    echo -e "${GREEN}Creating exe directory...${NC}"
    mkdir -p "$EXE_DIR"
else
    echo -e "${GREEN}exe directory exists.${NC}"
fi

# Step 6: Copy executable to exe directory
if [ -f "$BUILD_DIR/$EXECUTABLE_NAME" ]; then
    echo -e "${GREEN}Copying executable to exe directory...${NC}"
    cp "$BUILD_DIR/$EXECUTABLE_NAME" "$EXE_DIR/" || {
        echo -e "${RED}✗ Failed to copy executable!${NC}"
        exit 1
    }
    
    # Make sure it's executable
    chmod +x "$EXE_DIR/$EXECUTABLE_NAME"
    
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}✓ Build Successful!${NC}"
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}Executable: $EXE_DIR/$EXECUTABLE_NAME${NC}"
    
    # Show size
    SIZE=$(du -h "$EXE_DIR/$EXECUTABLE_NAME" | cut -f1)
    echo -e "${GREEN}Size: $SIZE${NC}"
else
    echo -e "${RED}✗ Executable not found in build directory!${NC}"
    exit 1
fi
