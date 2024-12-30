#!/bin/bash

# Variables to configure line length and number of lines
LINE_LENGTH=100
TOTAL_LINES=20

# Function to generate a random line of specified length and columns
generate_random_line() {
    local cols=${1:-1}
    local chars_per_column=$(( (LINE_LENGTH - (cols - 1)) / cols ))
    local line=""

    for ((col = 0; col < cols; col++)); do
        if [[ $col -gt 0 ]]; then
            line+=" " # Add space between columns
        fi
        line+=$(tr -dc 'a-zA-Z0-9' < /dev/urandom | head -c "$chars_per_column")
    done

    echo "$line"
}

# Check if a filename is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <filename> [columns]"
    echo "Generates $TOTAL_LINES random lines, each with $LINE_LENGTH chars and optionally with [COLUMNS] columns"
    exit 1
fi

FILENAME="$1"
COLUMNS=${2:-1}

# Clear the file if it already exists or create a new one
> "$FILENAME"

# Generate and write the random lines to the file
for ((i = 0; i < TOTAL_LINES; i++)); do
    generate_random_line "$COLUMNS" >> "$FILENAME"
done

echo "Generated $TOTAL_LINES lines of length $LINE_LENGTH with $COLUMNS columns in $FILENAME."
