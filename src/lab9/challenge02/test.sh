#!/bin/bash

check() {
    expected_output=$1
    output=$2
    
    if [ "$output" == "$expected_output" ]; then
        echo "OK"
    else
        echo "ERROR"
        echo "Expected output: $expected_output"
        echo "Actual output: $output"
    fi
}

declare -a expected_output=(\
    "[Error]: No s'han llegit dos nombres" \
    "[Error]: X no és un nombre enter" \
    "[Error]: Y no és un nombre enter" \
    "X és igual a Y" \
    "X és més gran que Y" \
    "X és més petit que Y" \
    "[Error]: X no és un nombre enter" \
)

declare -a inputs=(\
    "" \
    "e 5" \
    "5 e" \
    "5 5" \
    "10 5" \
    "5 10" \
    "5.5 5" \
)

declare -a tests=( "Test1" "Test2" "Test3" "Test4" "Test5" "Test6" "Test7" )

cmd="bash ./ch2.sh"

for i in "${!tests[@]}"; do
    echo "...Running ${tests[$i]}"
    output=$(echo "${inputs[$i]}" | $cmd)
    check "${expected_output[$i]}" "$output"
done

echo "...Done"