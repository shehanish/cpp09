#!/bin/bash

#colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' #No color

#Ensure the program is compiled 
make re > /dev/null

echo "------ My RPN calculator tester!------"

#Function to run a test
#Usage: run_test "expression" "expected_output_or_error"
run_test() {
    local expr="$1"
    local expected="$2"
    
    echo -n "Testing: \"$expr\" -> "
    
    # Run program and capture stdout and stderr
    actual=$(./RPN "$expr" 2>&1)
    
    if [ "$actual" == "$expected" ]; then
        echo -e "${GREEN}PASS${NC}"
    else
        echo -e "${RED}FAIL${NC}"
        echo "   Expected: $expected"
        echo "   Actual:   $actual"
    fi
}

# --- VALID TEST CASES ---
echo -e "\n[VALID CASES]"
run_test "3 4 +" "7"
run_test "8 9 * 9 - 9 - 9 - 4 - 1 +" "42"
run_test "7 7 * 7 -" "42"
run_test "1 2 * 3 + 4 /" "1.25"

# --- ERROR CASES ---
echo -e "\n[ERROR CASES]"
run_test "10 5 +" "Error: Only single digit numbers (0 - 9) are allowed!"
run_test "5 5 + +" "Error: Invalid Input: Not enough operands"
run_test "5 0 /" "Error: Division by zero."
run_test "5" "Error: Invalid Inputs."
run_test "(1 + 2)" "Error: Only single digit numbers (0 - 9) are allowed!"

# --- ARGUMENT CASES ---
echo -e "\n[ARGUMENT CASES]"
echo -n "Testing: No arguments -> "
actual=$(./RPN 2>&1)
if [[ $actual == *"Error"* ]]; then echo -e "${GREEN}PASS${NC}"; else echo -e "${RED}FAIL${NC}"; fi

echo -e "\nDone!"