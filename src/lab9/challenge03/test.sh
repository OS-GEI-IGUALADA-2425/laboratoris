declare -a inputs=("input1" "input2") 
declare -a expecteds=("SECRET" "ONLY")

for i in ${!inputs[@]}; do
    output=$(bash ch3.sh < ${inputs[$i]})
    if [ "$output" == "${expecteds[$i]}" ]; then
        echo "Test $i passed"
    else
        echo "Test $i failed"
        echo "Expected: ${expecteds[$i]}"
        echo "Got: $output"
    fi
done