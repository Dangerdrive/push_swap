#!/bin/bash

PUSH_SWAP="./push_swap"
CHECKER="./checker_linux"

#Test files

OUTPUT_EXPECTED=tester/expected_output.txt
#OUTPUT_PIPEX=tester/output.txt
OUTPUT_PUSH_SWAP=tester/output.txt
OUTPUT_CHECKER="tester/checker_output.txt"


#Test shortcuts
COMMAND_WITH_PATH=/usr/bin/cat
LEAK_TOGGLE=1           #Set to 1 to run Valgrind, some other value for no check
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"


#Colors
NC="\033[0m"
CYAN="\033[36m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"

cd ..
printf "${YELLOW}${BOLD}\n=========== MAKEFILE =============\n${NC}${PURPLE}"
make
#printf "${YELLOW}${BOLD}\n========== NORMINETTE ============\n${NC}${CYAN}"
#norminette


# Function to check for memory leaks and saves if found
check_leaks() {
    local input=$1
    local description=$2
    local valgrind_output="valgrind_output.txt"

    printf "Leak check:${CYAN}\n"
    $VALGRIND $PUSH_SWAP $input > /dev/null 2> $valgrind_output

    # Check for the statement explicitly stating no leaks are possible
    if grep -q "All heap blocks were freed -- no leaks are possible" $valgrind_output || grep -q "ERROR SUMMARY: 0 errors" $valgrind_output; then
        printf "${GREEN}${BOLD}VALGRIND: NO LEAKS${NC}\n"
    else
        printf "${RED}${BOLD}VALGRIND: LEAK FOUND${NC}\n"
        mkdir -p tester/leaks
        cp $valgrind_output tester/leaks/"$(echo $description | sed 's/ /_/g')_valgrind_output.txt"
        printf "Valgrind output saved to ${BOLD}tester/leaks/$(echo $description | sed 's/ /_/g')_valgrind_output.txt${NC}\n"
    fi
}







printf "${PURPLE}${BOLD}\n==================================\n"
printf                   "|        PARAMETER ERRORS        |"
printf                  "\n==================================\n${NC}"





# Test specific variables
INPUT="a b c"
EXPECTED_OUTPUT="Error"
DESCRIPTION="TEST 1: Non-numeric parameters"

# Clear previous output file
rm -f $OUTPUT_PUSH_SWAP

# Run test
printf "${YELLOW}${BOLD}\n=========== $DESCRIPTION ============\n${NC}"
printf "Testing with non-numeric parameters.\n"
printf "Input: ${INPUT}\n\n"
${PUSH_SWAP} ${INPUT} > ${OUTPUT_PUSH_SWAP}
printf "\n"
printf "${NC}Checking for 'Error' in output: "

# Check output
if grep -q "$EXPECTED_OUTPUT" "$OUTPUT_PUSH_SWAP"; then
    printf "${GREEN}${BOLD}OK!${NC}\n"
else
    printf "${RED}${BOLD}KO: Expected 'Error' but got something else${NC}:\n"
    cat $OUTPUT_PUSH_SWAP
fi

# check for leaks
if [ $LEAK_TOGGLE -eq 1 ]; then
    check_leaks "$INPUT" "$DESCRIPTION"
fi

# remove the output file after the check
rm -f $OUTPUT_PUSH_SWAP


# Test specific variables TEST 2
INPUT="53 6 9 987 972337 9"
EXPECTED_OUTPUT="Error"
DESCRIPTION="TEST 2: duplicates"

printf "${YELLOW}${BOLD}\n=========== $DESCRIPTION ============\n${NC}"
# Test specific variables


# Clear previous output file
rm -f $OUTPUT_PUSH_SWAP

# Run test

printf "Testing with duplicate numeric parameters..\n"
printf "Input: ${INPUT}\n\n"
${PUSH_SWAP} ${INPUT} > ${OUTPUT_PUSH_SWAP}
printf "\n"
printf "${NC}Checking for 'Error' in output: "

# Check output
if grep -q "$EXPECTED_OUTPUT" "$OUTPUT_PUSH_SWAP"; then
    printf "${GREEN}${BOLD}OK!${NC}\n"
else
    printf "${RED}${BOLD}KO: Expected 'Error' but got something else${NC}:\n"
    cat $OUTPUT_PUSH_SWAP
fi

# Check for leaks
if [ $LEAK_TOGGLE -eq 1 ]; then
    check_leaks "$INPUT" "$DESCRIPTION"
fi

# remove the output file after the check
rm -f $OUTPUT_PUSH_SWAP



# Test specific variables TEST 3
INPUT="53 6 9 987 972337 2147483650"
EXPECTED_OUTPUT="Error"
DESCRIPTION="TEST 3: integer overflow"
printf "${YELLOW}${BOLD}\n=========== $DESCRIPTION ============\n${NC}"

# Clear previous output file
rm -f $OUTPUT_PUSH_SWAP

# Run test

printf "Testing numeric parameters including integer overflow.\n"
printf "Input: ${INPUT}\n\n"
${PUSH_SWAP} ${INPUT} > ${OUTPUT_PUSH_SWAP}
printf "\n"
printf "${NC}Checking for 'Error' in output: "

# Check output
if grep -q "$EXPECTED_OUTPUT" "$OUTPUT_PUSH_SWAP"; then
    printf "${GREEN}${BOLD}OK!${NC}\n"
else
    printf "${RED}${BOLD}KO: Expected 'Error' but got something else${NC}:\n"
    cat $OUTPUT_PUSH_SWAP
fi

# check for leaks
if [ $LEAK_TOGGLE -eq 1 ]; then
    check_leaks "$INPUT" "$DESCRIPTION"
fi

# remove the output file after the check
rm -f $OUTPUT_PUSH_SWAP


# Test specific variables TEST 4
INPUT=""
EXPECTED_OUTPUT="Error"
DESCRIPTION="TEST 4: no parameters"
printf "${YELLOW}${BOLD}\n=========== $DESCRIPTION ============\n${NC}"

# Clear previous output file
rm -f $OUTPUT_PUSH_SWAP

# Run test
printf "Testing using no parameters.\n"
${PUSH_SWAP} > ${OUTPUT_PUSH_SWAP}
printf "\n"
printf "${NC}Checking for empty output: "

# Check if the output file is empty
if [ ! -s ${OUTPUT_PUSH_SWAP} ]; then
    printf "${GREEN}${BOLD}OK!${NC}\n"
else
    printf "${RED}${BOLD}KO: Expected nothing but got something else${NC}:\n"
    cat $OUTPUT_PUSH_SWAP
fi

# Check for leaks if enabled
if [ $LEAK_TOGGLE -eq 1 ]; then
    check_leaks "$DESCRIPTION"
fi


# remove the output file after the check
rm -f $OUTPUT_PUSH_SWAP

# Test specific variables TEST 5
INPUT=""
EXPECTED_OUTPUT="Error"
DESCRIPTION="TEST 5: empty string as paramenter"
printf "${YELLOW}${BOLD}\n=========== $DESCRIPTION ============\n${NC}"

# Test specific variables
INPUT=""

# Clear previous output file
rm -f $OUTPUT_PUSH_SWAP

# Run test
printf "Testing empty string as parameters..\n"
${PUSH_SWAP} ${INPUT} > ${OUTPUT_PUSH_SWAP}
printf "\n"
printf "${NC}Checking for '' in output: "

# Check if the output file is empty
if [ ! -s ${OUTPUT_PUSH_SWAP} ]; then
    printf "${GREEN}${BOLD}OK!${NC}\n"
else
    printf "${RED}${BOLD}KO: Expected '' but got something else${NC}:\n"
    cat $OUTPUT_PUSH_SWAP
fi

# Check for leaks if enabled
if [ $LEAK_TOGGLE -eq 1 ]; then
    check_leaks "$DESCRIPTION"
fi

# remove the output file after the check
rm -f $OUTPUT_PUSH_SWAP




run_test() {
    local description=$1
    local input=$2
    local min_commands=$3
    local max_commands=$4


    printf "${YELLOW}${BOLD}\n============ TEST: $description ==============\n${NC}"
    #printf "Testing with input: ${BOLD}$input${NC}\n"

    # Run push_swap with input and capture output
    echo $input | xargs ${PUSH_SWAP} > ${OUTPUT_PUSH_SWAP}

    # Additionally, use the output of push_swap as input for checker
    echo $input | xargs ${PUSH_SWAP} | ${CHECKER} $input > ${OUTPUT_CHECKER}
    # Check checker's output for "OK"
    if grep -q "OK" ${OUTPUT_CHECKER}; then
        printf "${GREEN}${BOLD}OK!${NC} Checker reported OK status.\n"
    else
        printf "${RED}${BOLD}KO${NC}: Checker did not report OK status:\n"
        cat $OUTPUT_CHECKER
    fi

    # Count the number of commands output by push_swap
    local num_commands=$(wc -l < ${OUTPUT_PUSH_SWAP})

    # Check if the number of commands falls within the expected range
    if [ "$num_commands" -ge "$min_commands" ] && [ "$num_commands" -le "$max_commands" ]; then
        printf "${GREEN}${BOLD}OK!${NC} The number of commands ($num_commands) is within the expected range ($min_commands to $max_commands).\n"
    else
        printf "${RED}${BOLD}KO${NC}: The number of commands ($num_commands) is outside the expected range ($min_commands to $max_commands).\n"
    fi

    # Check for leaks if enabled
    if [ $LEAK_TOGGLE -eq 1 ]; then
        #printf "Leak check:${CYAN}\n"
        $VALGRIND $PUSH_SWAP $input > /dev/null 2> valgrind_output.txt
        
        # Check for the presence of "definitely lost" and "in use at exit" in the Valgrind report
        if grep -q "definitely lost: 0 bytes in 0 blocks" valgrind_output.txt && grep -q "in use at exit: 0 bytes in 0 blocks" valgrind_output.txt; then
            printf "${GREEN}${BOLD}VALGRIND: NO LEAKS${NC}\n"
        else
            printf "${RED}${BOLD}VALGRIND: LEAK FOUND${NC}\n"
            # Create leaks/ directory if it doesn't exist
            mkdir -p leaks
            # Copy valgrind_output.txt to leaks/ folder with a descriptive name
            cp valgrind_output.txt tester/leaks/"$(echo $description | sed 's/ /_/g')_valgrind_output.txt"
            printf "Valgrind output saved to ${BOLD}leaks/$(echo $description | sed 's/ /_/g')_valgrind_output.txt${NC}\n"
        fi
    fi

    # Optionally, remove the output files after the checks
    rm -f $OUTPUT_PUSH_SWAP $OUTPUT_CHECKER
}


printf "${PURPLE}${BOLD}\n==================================\n"
printf                   "|       SORTED PARAMETERS        |"
printf                  "\n==================================\n${NC}"


run_test "Single value (42)" "42" "0" "0" 
run_test "Two values in order (2 3)" "2 3" "0" "0"
run_test "Four values in order (0 1 2 3)" "0 1 2 3" "0" "0"
run_test "Ten values in order (0 1 2 3 4 5 6 7 8 9)" "0 1 2 3 4 5 6 7 8 9" "0" "0"
run_test "Four random values in order (2 5 8 9)" "2 5 8 9" "0" "0"



printf "${PURPLE}${BOLD}\n==================================\n"
printf                   "|       UNSORTED PARAMETERS        |"
printf                  "\n==================================\n${NC}"

run_test "3 values out of order (2 1 0)" "2 1 0" "2" "3"

# Generate a random amount between 0 and 3
random_amount=$((RANDOM % 4))
# Use the random amount to shuffle that number of values between 0 and 9
random_sequence=$(shuf -i 0-5000 -n $random_amount | xargs)
# Run the test with the generated random sequence
run_test "Between 0 and 3 random values" "$random_sequence" "0" "3"

run_test "Five values (1 5 2 4 3)" "1 5 2 4 3" "8" "12"
random_sequence=$(shuf -i 0-2147483647 -n 5 | xargs)
run_test "Five random values" "$random_sequence" "0" "12"
random_sequence=$(shuf -i 0-2147483647 -n 5 | xargs)
run_test "Five random values²" "$random_sequence" "0" "12"
random_sequence=$(shuf -i 0-2147483647 -n 5 | xargs)
run_test "Five random values³" "$random_sequence" "0" "12"

for i in {1..5}; do
    random_sequence=$(shuf -i 0-2147483647 -n 100 | xargs)
    run_test "100 random values, Test #$i" "$random_sequence" "500" "1500"
done

for i in {1..5}; do
    random_sequence=$(awk 'BEGIN{srand(); for(i=1;i<=500;i++) print int(rand()*(2147483647-(-2147483648))+(-2147483648))}' | xargs)
    run_test "500 random values, Test #$i" "$random_sequence" "3000" "11500"
done

