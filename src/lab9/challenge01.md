# Challenge 01: Calcula la mitjana d'una llista de nombres enters

En aquest repte, es demana calcular la mitjana d'una llista de nombres enters utilitzant Bash. Heu de considerar les següents restriccions:

- Tots els valors s'entren per la entrada estàndard (stdin).
- La primera línia conté un enter, indicant el nombre de nombres enters que es volen calcular.
- Les següents `n` línies contenen un enter cada una.
- La sortida ha de mostrar la mitjana dels `n` nombres enters, arrodonida a tres decimals.
- La mitjana s'ha de mostrar sempre amb tres decimals, encara que siguin redundants (p. ex., 0.000 en lloc de 0).
- La sortida ha de ser mostrada per la sortida estàndard (stdout).
- S'ha de verificar que el nombre d'enters estiguin entre 1 i 500. En cas contrari, no es mostrarà cap sortida.
- S'ha de verificar que els enters estiguin entre -10000 i 10000. En cas contrari, no es mostrarà cap sortida.

Per crear la vostra solució, heu de crear un fitxer anomenat `ch1.sh` amb el següent contingut:

```bash
#!/bin/bash
// Your code here
```

Per validar la vostra solució, podeu utilitzar el següent test:

```bash
!#/bin/bash
declare -a inputs=("input1" "input2" "input3" "input4" "input5")
declare -a expecteds=("5.000" "5175.240" "4696.947" "" "")

for i in ${!inputs[@]}; do
    output=$(bash ch1.sh < ${inputs[$i]})
    if [ "$output" == "${expecteds[$i]}" ]; then
        echo "Test $i passed"
    else
        echo "Test $i failed"
        echo "Expected: ${expecteds[$i]}"
        echo "Got: $output"
    fi
done
```

Els inputs són fitxers de text que us podeu baixar:

- [input1](./challenge01/input1)
- [input2](./challenge01/input2)
- [input3](./challenge01/input3)
- [input4](./challenge01/input4)
- [input5](./challenge01/input5)
- [test.sh](./challenge01/test.sh)

<details>
<summary>Mostra la solució (Versió Elizabeth) </summary>

```bash
#!/bin/bash
export LC_NUMERIC="C" # Set the locale to C to avoid problems with the decimal separator

total=0
avg () { 
    total=$(($total + $1))
}

val(){
if [ $1 -lt -10000 ] || [ $1 -gt 10000 ]; then
        exit 1
    fi
}


read nr
if [ $nr -lt 1 ] || [ $nr -gt 500 ]; then
    exit 1
fi

for i in $(seq 1 $nr); do
    read x
    val $x
    avg $x
done

echo "scale=3; $total / $nr" | bc
```
</details>

<details>
<summary>Mostra la solució (Versió Asier) </summary>

```bash
#!/bin/bash

total=0
avg () { 
    total=$(($total + $1))
}

val(){
if [ $1 -lt -10000 ] || [ $1 -gt 10000 ]; then
        exit 1
    fi
}


read nr
if [ $nr -lt 1 ] || [ $nr -gt 500 ]; then
    exit 1
fi

for i in $(seq 1 $nr); do
    read x
    val $x
    avg $x
done

digit=$(($total / $nr))
decimal=$((($total * 1000 / $nr) % 1000))

printf "%d.%03d\n" $digit $decimal
```
</details>

<details>
<summary>Mostra la solució (Versió Alex) </summary>

```bash
#!/bin/bash
function ex1 {
    read long
    if [ -z "$long" ] || [ "$long" -lt 1 ] || [ "$long" -gt 500 ]; then
        return
    fi

    sum=0
    for ((i = 0; i < long; i++)); do
        read num
        if [ -z "$num" ] || [ "$num" -lt -10000 ] || [ "$num" -gt 10000 ]; then
            return
        fi
        ((sum += num))
    done

    res=$(echo "scale=3; $sum / $long" | bc)
    res=$(echo $res | sed 's/\./,/g')
    printf "%.3f" $res | tr , .
}

ex1
```

</details>
