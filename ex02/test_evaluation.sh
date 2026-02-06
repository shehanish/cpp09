#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=====================================${NC}"
echo -e "${BLUE}  PmergeMe Evaluation Test Suite${NC}"
echo -e "${BLUE}=====================================${NC}\n"

# Compile the project
echo -e "${YELLOW}[1] Compiling the project...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Compilation successful${NC}\n"

# Test 1: Basic example from subject
echo -e "${YELLOW}[2] Test: Basic example (5 elements)${NC}"
./PmergeMe 3 5 9 7 4
echo ""

# Test 2: Small odd number of elements
echo -e "${YELLOW}[3] Test: Small odd sequence (7 elements)${NC}"
./PmergeMe 15 8 23 42 16 4 99
echo ""

# Test 3: Small even number of elements
echo -e "${YELLOW}[4] Test: Small even sequence (6 elements)${NC}"
./PmergeMe 10 20 30 5 15 25
echo ""

# Test 4: Already sorted
echo -e "${YELLOW}[5] Test: Already sorted sequence${NC}"
./PmergeMe 1 2 3 4 5 6 7 8 9 10
echo ""

# Test 5: Reverse sorted
echo -e "${YELLOW}[6] Test: Reverse sorted sequence${NC}"
./PmergeMe 10 9 8 7 6 5 4 3 2 1
echo ""

# Test 6: Large sequence (100 elements)
echo -e "${YELLOW}[7] Test: 100 random elements${NC}"
./PmergeMe $(shuf -i 1-100000 -n 100 | tr "\n" " ")
echo ""

# Test 7: 3000 elements (required by subject)
echo -e "${YELLOW}[8] Test: 3000 elements (requirement check)${NC}"
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")
echo ""

# Error tests
echo -e "${BLUE}=====================================${NC}"
echo -e "${BLUE}  Error Handling Tests${NC}"
echo -e "${BLUE}=====================================${NC}\n"

echo -e "${YELLOW}[9] Error: No arguments${NC}"
./PmergeMe
echo ""

echo -e "${YELLOW}[10] Error: Negative number${NC}"
./PmergeMe "-1" 2
echo ""

echo -e "${YELLOW}[11] Error: Invalid input (letters)${NC}"
./PmergeMe abc 123
echo ""

echo -e "${YELLOW}[12] Error: Duplicate numbers${NC}"
./PmergeMe 5 3 8 5 1
echo ""

echo -e "${YELLOW}[13] Error: Mixed valid and invalid${NC}"
./PmergeMe 3 5 9a 7 4
echo ""

# Final summary
echo -e "${BLUE}=====================================${NC}"
echo -e "${GREEN}All tests completed!${NC}"
echo -e "${BLUE}=====================================${NC}"
