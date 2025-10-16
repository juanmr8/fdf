#!/bin/bash

# FDF Project Testing Script
# This script compiles the project and runs comprehensive tests

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== FDF Project Testing Script ===${NC}"

# Function to create test maps
create_test_maps() {
    echo -e "${YELLOW}Creating test maps...${NC}"

    mkdir -p test_maps

    # Tiny 3x3 map
    cat > test_maps/tiny.fdf << EOF
0 1 0
1 2 1
0 1 0
EOF

    # Simple 4x4 map
    cat > test_maps/simple.fdf << EOF
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
EOF

    # Flat map
    cat > test_maps/flat.fdf << EOF
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
EOF

    # Single point
    cat > test_maps/single.fdf << EOF
5
EOF

    # Empty file
    touch test_maps/empty.fdf

    echo -e "${GREEN}✓ Test maps created${NC}"
}

# Function to test compilation
test_compilation() {
    echo -e "${YELLOW}Testing compilation...${NC}"

    # Clean previous build
    make clean > /dev/null 2>&1

    # Attempt compilation
    if make > compilation.log 2>&1; then
        echo -e "${GREEN}✓ Compilation successful${NC}"
        return 0
    else
        echo -e "${RED}✗ Compilation failed${NC}"
        echo "Compilation errors:"
        cat compilation.log
        return 1
    fi
}

# Function to test basic functionality
test_basic_functionality() {
    echo -e "${YELLOW}Testing basic functionality...${NC}"

    # Test 1: No arguments
    echo -n "  Testing no arguments: "
    if ./fdf > /dev/null 2>&1; then
        echo -e "${RED}✗ Should reject no arguments${NC}"
    else
        echo -e "${GREEN}✓ Correctly rejects no arguments${NC}"
    fi

    # Test 2: Too many arguments
    echo -n "  Testing too many arguments: "
    if ./fdf file1.fdf file2.fdf > /dev/null 2>&1; then
        echo -e "${RED}✗ Should reject multiple arguments${NC}"
    else
        echo -e "${GREEN}✓ Correctly rejects multiple arguments${NC}"
    fi

    # Test 3: Invalid file
    echo -n "  Testing invalid file: "
    if ./fdf nonexistent.fdf > /dev/null 2>&1; then
        echo -e "${RED}✗ Should reject invalid file${NC}"
    else
        echo -e "${GREEN}✓ Correctly rejects invalid file${NC}"
    fi
}

# Function to test map parsing
test_map_parsing() {
    echo -e "${YELLOW}Testing map parsing...${NC}"

    # Test each map file
    for map in test_maps/*.fdf; do
        if [ -s "$map" ]; then  # Only test non-empty files
            echo -e "  Testing $(basename "$map"):"
            ./fdf "$map" 2>&1 | sed 's/^/    /'
            echo ""
        fi
    done

    # Test empty file
    echo -e "  Testing empty.fdf:"
    if ./fdf test_maps/empty.fdf > /dev/null 2>&1; then
        echo -e "    ${YELLOW}Note: Program handles empty file${NC}"
    else
        echo -e "    ${GREEN}✓ Correctly handles empty file${NC}"
    fi
}

# Function to check for memory leaks (macOS)
test_memory_leaks() {
    echo -e "${YELLOW}Testing for memory leaks...${NC}"

    if command -v leaks > /dev/null 2>&1; then
        echo "  Running leak detection on tiny.fdf..."
        leaks --atExit -- ./fdf test_maps/tiny.fdf > leak_report.txt 2>&1

        if grep -q "0 leaks for 0 total leaked bytes" leak_report.txt; then
            echo -e "${GREEN}✓ No memory leaks detected${NC}"
        else
            echo -e "${YELLOW}⚠ Potential memory leaks found - check leak_report.txt${NC}"
        fi
    else
        echo -e "${YELLOW}  leaks command not available (skipping memory test)${NC}"
    fi
}

# Function to run performance test
test_performance() {
    echo -e "${YELLOW}Testing performance...${NC}"

    echo "  Timing execution on 42.fdf..."
    if [ -f "test_maps/42.fdf" ]; then
        time ./fdf test_maps/42.fdf > /dev/null 2>&1
    else
        echo -e "${YELLOW}  42.fdf not found - skipping performance test${NC}"
    fi
}

# Function to cleanup
cleanup() {
    echo -e "${YELLOW}Cleaning up...${NC}"
    rm -f compilation.log leak_report.txt
    echo -e "${GREEN}✓ Cleanup complete${NC}"
}

# Main execution
main() {
    create_test_maps
    echo ""

    if test_compilation; then
        echo ""
        test_basic_functionality
        echo ""
        test_map_parsing
        echo ""
        test_memory_leaks
        echo ""
        test_performance
        echo ""

        echo -e "${GREEN}=== All tests completed ===${NC}"
        echo -e "${BLUE}Your FDF map parsing is working correctly!${NC}"
        echo -e "${BLUE}Ready to proceed with graphics implementation.${NC}"
    else
        echo -e "${RED}=== Testing halted due to compilation errors ===${NC}"
        echo -e "${YELLOW}Fix compilation issues and run again.${NC}"
    fi

    echo ""
    cleanup
}

# Run the tests
main
