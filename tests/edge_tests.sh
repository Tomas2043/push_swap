#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NOCOLOR='\033[0m'

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to run a test
run_test() {
    local test_name="$1"
    local test_cmd="$2"
    local expected_result="$3"
    local description="$4"

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    echo -e "${CYAN}Test $TOTAL_TESTS: $test_name${NOCOLOR}"
    if [ -n "$description" ]; then
        echo -e "  ${YELLOW}Description: $description${NOCOLOR}"
    fi

    # Run the command and capture output
    result=$(eval "$test_cmd" 2>&1)
    exit_code=$?

    # Check result
    case "$expected_result" in
        "error")
            if echo "$result" | grep -q "Error" && [ $exit_code -ne 0 ]; then
                echo -e "  ${GREEN}✓ PASS${NOCOLOR} - Error correctly detected"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "  ${RED}✗ FAIL${NOCOLOR} - Expected error, got: '$result' (exit: $exit_code)"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
            ;;
        "empty")
            if [ -z "$result" ] && [ $exit_code -eq 0 ]; then
                echo -e "  ${GREEN}✓ PASS${NOCOLOR} - No output (as expected)"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "  ${RED}✗ FAIL${NOCOLOR} - Expected empty output, got: '$result' (exit: $exit_code)"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
            ;;
        "no_error")
            if ! echo "$result" | grep -q "Error" && [ $exit_code -eq 0 ]; then
                echo -e "  ${GREEN}✓ PASS${NOCOLOR} - Executed successfully"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "  ${RED}✗ FAIL${NOCOLOR} - Unexpected error: '$result' (exit: $exit_code)"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
            ;;
        "sorted")
            if [ -z "$result" ] && [ $exit_code -eq 0 ]; then
                echo -e "  ${GREEN}✓ PASS${NOCOLOR} - Already sorted (no moves)"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "  ${RED}✗ FAIL${NOCOLOR} - Expected no output for sorted list, got: '$result'"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
            ;;
    esac
    echo ""
}

# Check if push_swap exists
if [ ! -f "./push_swap" ]; then
    echo -e "${RED}Error: push_swap executable not found!${NOCOLOR}"
    echo "Run 'make' first."
    exit 1
fi

clear
echo -e "${BLUE}╔════════════════════════════════════════════════╗${NOCOLOR}"
echo -e "${BLUE}║     PUSH_SWAP EDGE CASE & ERROR TESTER         ║${NOCOLOR}"
echo -e "${BLUE}╚════════════════════════════════════════════════╝${NOCOLOR}"
echo ""

# ==================== NO ARGUMENTS ====================
echo -e "${YELLOW}═══ SECTION 1: NO ARGUMENTS ═══${NOCOLOR}"
echo ""

run_test "No arguments" \
    "./push_swap" \
    "empty" \
    "Program should exit with no output"

# ==================== EMPTY/INVALID INPUT ====================
echo -e "${YELLOW}═══ SECTION 2: EMPTY/INVALID INPUT ═══${NOCOLOR}"
echo ""

run_test "Empty string argument" \
    "./push_swap ''" \
    "error" \
    "Empty string should produce error"

run_test "Only spaces" \
    "./push_swap '   '" \
    "empty" \
    "String with only spaces should produce no output (empty array after split)"

run_test "Multiple spaces between numbers" \
    "./push_swap '1    2    3'" \
    "no_error" \
    "Should handle multiple spaces correctly"

run_test "Leading spaces" \
    "./push_swap '  1 2 3'" \
    "no_error" \
    "Should handle leading spaces"

run_test "Trailing spaces" \
    "./push_swap '1 2 3  '" \
    "no_error" \
    "Should handle trailing spaces"

# ==================== INVALID NUMBERS ====================
echo -e "${YELLOW}═══ SECTION 3: INVALID NUMBERS ═══${NOCOLOR}"
echo ""

run_test "Non-numeric input" \
    "./push_swap 1 2 abc" \
    "error" \
    "Letters should produce error"

run_test "Special characters" \
    "./push_swap 1 @ 3" \
    "error" \
    "Special characters should produce error"

run_test "Float number" \
    "./push_swap 1.5 2 3" \
    "error" \
    "Float numbers should produce error"

run_test "Number with plus sign" \
    "./push_swap +42 1 2" \
    "no_error" \
    "Plus sign should be accepted"

run_test "Number with minus sign" \
    "./push_swap -42 1 2" \
    "no_error" \
    "Minus sign should be accepted"

run_test "Multiple signs" \
    "./push_swap ++42" \
    "error" \
    "Multiple signs should produce error"

run_test "Sign without number" \
    "./push_swap + 42" \
    "error" \
    "Sign without number should produce error"

run_test "Sign at end" \
    "./push_swap 42-" \
    "error" \
    "Sign at end should produce error"

# ==================== INT OVERFLOW ====================
echo -e "${YELLOW}═══ SECTION 4: INTEGER OVERFLOW ═══${NOCOLOR}"
echo ""

run_test "INT_MAX" \
    "./push_swap 2147483647 0 1" \
    "no_error" \
    "INT_MAX should be accepted"

run_test "INT_MIN" \
    "./push_swap -2147483648 0 1" \
    "no_error" \
    "INT_MIN should be accepted"

run_test "Greater than INT_MAX" \
    "./push_swap 2147483648" \
    "error" \
    "Number > INT_MAX should produce error"

run_test "Less than INT_MIN" \
    "./push_swap -2147483649" \
    "error" \
    "Number < INT_MIN should produce error"

run_test "Very large number" \
    "./push_swap 999999999999999999" \
    "error" \
    "Very large number should produce error"

# ==================== DUPLICATES ====================
echo -e "${YELLOW}═══ SECTION 5: DUPLICATE NUMBERS ═══${NOCOLOR}"
echo ""

run_test "Simple duplicate" \
    "./push_swap 1 2 2 3" \
    "error" \
    "Duplicate numbers should produce error"

run_test "Duplicate at start" \
    "./push_swap 1 1 2 3" \
    "error" \
    "Duplicate at start should produce error"

run_test "Duplicate at end" \
    "./push_swap 1 2 3 3" \
    "error" \
    "Duplicate at end should produce error"

run_test "All same numbers" \
    "./push_swap 5 5 5 5" \
    "error" \
    "All same numbers should produce error"

run_test "Duplicate with signs" \
    "./push_swap +42 42" \
    "error" \
    "+42 and 42 are duplicates"

run_test "Duplicate zeros" \
    "./push_swap 0 0" \
    "error" \
    "Duplicate zeros should produce error"

run_test "Duplicate negatives" \
    "./push_swap -5 -5" \
    "error" \
    "Duplicate negatives should produce error"

# ==================== ALREADY SORTED ====================
echo -e "${YELLOW}═══ SECTION 6: ALREADY SORTED ═══${NOCOLOR}"
echo ""

run_test "Single number" \
    "./push_swap 42" \
    "empty" \
    "Single number should produce no output"

run_test "Two sorted numbers" \
    "./push_swap 1 2" \
    "sorted" \
    "Already sorted should produce no output"

run_test "Three sorted numbers" \
    "./push_swap 1 2 3" \
    "sorted" \
    "Already sorted should produce no output"

run_test "Five sorted numbers" \
    "./push_swap 1 2 3 4 5" \
    "sorted" \
    "Already sorted should produce no output"

run_test "Sorted negative numbers" \
    "./push_swap -5 -3 -1 0 2" \
    "sorted" \
    "Sorted negative numbers should produce no output"

run_test "Sorted with gaps" \
    "./push_swap 1 10 100 1000" \
    "sorted" \
    "Sorted with gaps should produce no output"

# ==================== REVERSE SORTED ====================
echo -e "${YELLOW}═══ SECTION 7: REVERSE SORTED ═══${NOCOLOR}"
echo ""

run_test "Two reverse sorted" \
    "./push_swap 2 1" \
    "no_error" \
    "Should sort reverse order"

run_test "Three reverse sorted" \
    "./push_swap 3 2 1" \
    "no_error" \
    "Should sort reverse order"

run_test "Five reverse sorted" \
    "./push_swap 5 4 3 2 1" \
    "no_error" \
    "Should sort reverse order"

# ==================== EDGE COMBINATIONS ====================
echo -e "${YELLOW}═══ SECTION 8: EDGE COMBINATIONS ═══${NOCOLOR}"
echo ""

run_test "Mix of positive and negative" \
    "./push_swap -10 5 -3 8 0 -1" \
    "no_error" \
    "Should handle mix of positive and negative"

run_test "Only zeros" \
    "./push_swap 0" \
    "empty" \
    "Single zero should produce no output"

run_test "Only negative numbers" \
    "./push_swap -5 -2 -8 -1" \
    "no_error" \
    "Should handle only negative numbers"

run_test "Min and max values" \
    "./push_swap 2147483647 -2147483648 0" \
    "no_error" \
    "Should handle INT_MIN and INT_MAX together"

run_test "String with single number" \
    "./push_swap '42'" \
    "empty" \
    "Single number in string should produce no output"

run_test "Multiple string arguments" \
    "./push_swap '1 2' '3 4'" \
    "no_error" \
    "Should handle multiple string arguments"

run_test "Mixed string and individual args" \
    "./push_swap '1 2' 3 '4 5'" \
    "no_error" \
    "Should handle mixed argument formats"

# ==================== MEMORY LEAK TESTS ====================
echo -e "${YELLOW}═══ SECTION 9: MEMORY LEAK TESTS (with leaks command) ═══${NOCOLOR}"
echo ""

if command -v leaks &> /dev/null; then
    run_test "Memory leak - error case" \
        "leaks -atExit -- ./push_swap 1 2 2 2>&1 | grep -q '0 leaks'" \
        "no_error" \
        "No memory leaks on error"

    run_test "Memory leak - normal case" \
        "leaks -atExit -- ./push_swap 3 2 1 2>&1 | grep -q '0 leaks'" \
        "no_error" \
        "No memory leaks on normal execution"

    run_test "Memory leak - string argument" \
        "leaks -atExit -- ./push_swap '5 4 3 2 1' 2>&1 | grep -q '0 leaks'" \
        "no_error" \
        "No memory leaks with string argument"
else
    echo -e "  ${YELLOW}⚠ Skipping memory leak tests (leaks command not available)${NOCOLOR}"
    echo ""
fi

# ==================== SUMMARY ====================
echo -e "${BLUE}╔════════════════════════════════════════════════╗${NOCOLOR}"
echo -e "${BLUE}║                  TEST SUMMARY                  ║${NOCOLOR}"
echo -e "${BLUE}╚════════════════════════════════════════════════╝${NOCOLOR}"
echo ""
echo -e "Total tests:  ${CYAN}$TOTAL_TESTS${NOCOLOR}"
echo -e "Passed:       ${GREEN}$PASSED_TESTS${NOCOLOR}"
echo -e "Failed:       ${RED}$FAILED_TESTS${NOCOLOR}"
echo ""

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}╔════════════════════════════════════════════════╗${NOCOLOR}"
    echo -e "${GREEN}║     ✓ ALL TESTS PASSED! EXCELLENT WORK!       ║${NOCOLOR}"
    echo -e "${GREEN}╚════════════════════════════════════════════════╝${NOCOLOR}"
    exit 0
else
    PASS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "${YELLOW}Pass rate: $PASS_RATE%${NOCOLOR}"
    echo ""
    echo -e "${RED}Some tests failed. Please review the output above.${NOCOLOR}"
    exit 1
fi