#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NOCOLOR='\033[0m'

# Function to generate random numbers
generate_numbers() {
    local count=$1
    local numbers=()
    local num

    # Generate unique random numbers
    while [ ${#numbers[@]} -lt $count ]; do
        num=$((RANDOM % 10000 + 1))
        # Check if number already exists
        if [[ ! " ${numbers[@]} " =~ " ${num} " ]]; then
            numbers+=($num)
        fi
    done

    echo "${numbers[@]}"
}

# Function to run a single test
run_test() {
    local numbers=$1
    local result=$(./push_swap $numbers 2>&1)
    local exit_code=$?
    local move_count=$(echo "$result" | wc -l)

    # Check if it's an error
    if echo "$result" | grep -q "Error"; then
        echo "ERROR"
        return 1
    fi

    # Check if sorted correctly
    local checker_result=$(echo "$result" | ./checker_linux $numbers 2>&1)
    if [ "$checker_result" = "OK" ]; then
        echo "$move_count"
        return 0
    elif [ "$checker_result" = "KO" ]; then
        echo "KO"
        return 1
    else
        # If checker doesn't exist, just return move count
        echo "$move_count"
        return 0
    fi
}

# Main script
clear
echo -e "${BLUE}╔════════════════════════════════════╗${NOCOLOR}"
echo -e "${BLUE}║     PUSH_SWAP TESTER - LOOP.SH     ║${NOCOLOR}"
echo -e "${BLUE}╚════════════════════════════════════╝${NOCOLOR}"
echo ""

# Check if push_swap exists
if [ ! -f "./push_swap" ]; then
    echo -e "${RED}Error: push_swap executable not found!${NOCOLOR}"
    echo "Compiling..."
    make
    if [ ! -f "./push_swap" ]; then
        echo -e "${RED}Compilation failed!${NOCOLOR}"
        exit 1
    fi
fi

# Get number of elements
echo -e "${YELLOW}How many numbers do you want to sort?${NOCOLOR}"
read -p "> " num_count

# Validate input
if ! [[ "$num_count" =~ ^[0-9]+$ ]] || [ "$num_count" -lt 1 ]; then
    echo -e "${RED}Invalid number!${NOCOLOR}"
    exit 1
fi

# Get number of iterations
echo -e "${YELLOW}How many times do you want to run the test?${NOCOLOR}"
read -p "> " iterations

# Validate input
if ! [[ "$iterations" =~ ^[0-9]+$ ]] || [ "$iterations" -lt 1 ]; then
    echo -e "${RED}Invalid number!${NOCOLOR}"
    exit 1
fi

echo ""
echo -e "${BLUE}Running $iterations tests with $num_count numbers each...${NOCOLOR}"
echo ""

# Statistics
total=0
min_moves=999999
max_moves=0
sum_moves=0
errors=0
ko_count=0

# Run tests
for i in $(seq 1 $iterations); do
    numbers=$(generate_numbers $num_count)
    result=$(run_test "$numbers")

    if [ "$result" = "ERROR" ]; then
        echo -e "${RED}Test $i/$iterations: ERROR${NOCOLOR}"
        errors=$((errors + 1))
    elif [ "$result" = "KO" ]; then
        echo -e "${RED}Test $i/$iterations: KO (not sorted correctly)${NOCOLOR}"
        ko_count=$((ko_count + 1))
    else
        moves=$result
        sum_moves=$((sum_moves + moves))

        if [ $moves -lt $min_moves ]; then
            min_moves=$moves
        fi

        if [ $moves -gt $max_moves ]; then
            max_moves=$moves
        fi

        echo -e "${GREEN}Test $i/$iterations: OK - $moves moves${NOCOLOR}"
    fi
done

# Calculate statistics
successful=$((iterations - errors - ko_count))
if [ $successful -gt 0 ]; then
    avg_moves=$((sum_moves / successful))
else
    avg_moves=0
fi

# Display results
echo ""
echo -e "${BLUE}╔════════════════════════════════════╗${NOCOLOR}"
echo -e "${BLUE}║            TEST RESULTS            ║${NOCOLOR}"
echo -e "${BLUE}╚════════════════════════════════════╝${NOCOLOR}"
echo -e "${GREEN}Successful tests: $successful/$iterations${NOCOLOR}"
if [ $errors -gt 0 ]; then
    echo -e "${RED}Errors: $errors${NOCOLOR}"
fi
if [ $ko_count -gt 0 ]; then
    echo -e "${RED}KO (wrong sorting): $ko_count${NOCOLOR}"
fi

if [ $successful -gt 0 ]; then
    echo ""
    echo -e "${YELLOW}Move Statistics:${NOCOLOR}"
    echo -e "  Min moves:  $min_moves"
    echo -e "  Max moves:  $max_moves"
    echo -e "  Avg moves:  $avg_moves"

    # Grade estimation for common sizes
    if [ $num_count -eq 3 ]; then
        if [ $max_moves -le 3 ]; then
            echo -e "${GREEN}  Grade: Perfect (≤3 moves)${NOCOLOR}"
        else
            echo -e "${RED}  Grade: Failed (>3 moves)${NOCOLOR}"
        fi
    elif [ $num_count -eq 5 ]; then
        if [ $max_moves -le 12 ]; then
            echo -e "${GREEN}  Grade: Perfect (≤12 moves)${NOCOLOR}"
        else
            echo -e "${RED}  Grade: Failed (>12 moves)${NOCOLOR}"
        fi
    elif [ $num_count -eq 100 ]; then
        if [ $avg_moves -lt 700 ]; then
            echo -e "${GREEN}  Grade: 5/5 points (<700 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 900 ]; then
            echo -e "${YELLOW}  Grade: 4/5 points (<900 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 1100 ]; then
            echo -e "${YELLOW}  Grade: 3/5 points (<1100 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 1300 ]; then
            echo -e "${YELLOW}  Grade: 2/5 points (<1300 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 1500 ]; then
            echo -e "${RED}  Grade: 1/5 points (<1500 moves avg)${NOCOLOR}"
        else
            echo -e "${RED}  Grade: 0/5 points (≥1500 moves avg)${NOCOLOR}"
        fi
    elif [ $num_count -eq 500 ]; then
        if [ $avg_moves -lt 5500 ]; then
            echo -e "${GREEN}  Grade: 5/5 points (<5500 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 7000 ]; then
            echo -e "${YELLOW}  Grade: 4/5 points (<7000 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 8500 ]; then
            echo -e "${YELLOW}  Grade: 3/5 points (<8500 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 10000 ]; then
            echo -e "${YELLOW}  Grade: 2/5 points (<10000 moves avg)${NOCOLOR}"
        elif [ $avg_moves -lt 11500 ]; then
            echo -e "${RED}  Grade: 1/5 points (<11500 moves avg)${NOCOLOR}"
        else
            echo -e "${RED}  Grade: 0/5 points (≥11500 moves avg)${NOCOLOR}"
        fi
    fi
fi

echo ""