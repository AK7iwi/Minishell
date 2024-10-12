#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Define the path to your minishell binary
MINISHELL="$SCRIPT_DIR/../minishell"
BASH="bash --posix"

# Define the test case input file
TEST_FILE="$SCRIPT_DIR/test_cases.txt"

# Check if the test file exists
if [[ ! -f $TEST_FILE ]]; then
  echo "Test case file not found: $TEST_FILE"
  exit 1
fi

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Read test cases from the file
while IFS= read -r test_case || [ -n "$test_case" ]; do
  echo "Running test: '${test_case}'"

  # Run the command in bash with --posix and capture the output
  bash_output=$($BASH -c "$test_case" 2>&1)

  # Create a temporary file for input
  {
    echo "$test_case"
    echo "exit"  # Ensure minishell exits after the command
  } > temp_input.txt

  # Run the command in minishell using input redirection
  minishell_output=$($MINISHELL < temp_input.txt 2>&1)

  # Clean up the minishell output by removing the prompt, command lines, and the 'exit' line
  cleaned_minishell_output=$(echo "$minishell_output" | sed -E '/Minishell> /d; /exit/d; s/^ *//; s/ *$//')

  # Compare the outputs
  if [ "$cleaned_minishell_output" == "$bash_output" ]; then
    echo -e "${GREEN}Test passed!${NC}"
	echo "$cleaned_minishell_output"
  else
    echo -e "${RED}Test failed!${NC}"
    echo "Expected (bash): '$bash_output'"
    echo "Got (minishell): '$cleaned_minishell_output'"
  fi

  echo # Add a blank line for readability
done < "$TEST_FILE"

# Clean up the temporary input file
rm temp_input.txt
