#!/bin/bash
echo "Running sortmate tests..."\n
echo "-----------------------------------------"

cd data/

# Function to run a test
test_sortmate() {
    local test_num="$1"
    local test_name="$2"
    local command="$3"
    local sort_command="$4"
    
    printf "Test case %d: %s... " "$test_num" "$test_name"
    eval "$command" > output.txt
    eval "$sort_command" > expected.txt
    if diff -q output.txt expected.txt > /dev/null; then
        echo -e "\e[32mPASSED\e[0m"
    else
        echo -e "\e[31mFAILED\e[0m"
        echo "Expected:" && cat expected.txt
        echo "Got:" && cat output.txt
    fi
}

test_sortmate 0 "/etc/passwd" "sortmate /etc/passwd" "LC_ALL=C sort /etc/passwd"
test_sortmate 1 "Basic Sort" "sortmate phonebook" "LC_ALL=C sort phonebook"
test_sortmate 2 "Reverse Sort (-r)" "sortmate -r phonebook" "LC_ALL=C sort -r phonebook"
test_sortmate 3 "Numeric Sort (-n)" "sortmate -n numeric" "LC_ALL=C sort -n numeric"
test_sortmate 4 "Ignore Leading Blanks (-b)" "sortmate -b sample" "LC_ALL=C sort -b sample"
test_sortmate 5 "Dictionary Order (-d)" "sortmate -d symbols" "LC_ALL=C sort -d symbols"
test_sortmate 6 "Fold Case (-f)" "sortmate -f mini.txt" "LC_ALL=C sort -f mini.txt"
test_sortmate 7 "Disable Last Resort Comparison (-s)" "sortmate -k2 -s keystable" "LC_ALL=C sort -k2 -s keystable" 

rm output.txt expected.txt
