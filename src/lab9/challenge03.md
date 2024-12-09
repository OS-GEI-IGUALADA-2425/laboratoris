# Challenge03: Desxifrant el codi

El vostre objectiu és desxifrar un codi secret analitzant una matriu. La matriu està representada per una sèrie de línies que contenen valors (lletres o números). El codi es genera extreient certs valors únics d'acord amb unes regles específiques.

## Entrada

La informació de la matriu es proporciona a través de l'entrada estàndard (stdin) amb el següent format:

- Primera línia: Un enter n que indica el nombre de files de la matriu.
- Les següents n línies: Cada línia representa una fila de la matriu. Les entrades poden ser lletres (A-Z) o números (0-9).

Per exemple:

```bash
6
S
3 3 T T E C C 2 2
2 2 E E C E 3 3 3
3 3 R T E E T T T
2 2 E 2
T 3 3 E E
```

## Regles

Per desxifrar el codi:

1. Cada fila de la matriu s'analitza per identificar el valor únic que coincideix amb la lletra de la paraula que desxifrem.
2. Cada lletra es col·loca en la posició corresponent de la paraula desxifrada.
3. El codi desxifrat serà la concatenació d'aquests valors únics.

Per exemple, utilitzant la matriu anterior, el codi desxifrat seria:

```bash
SECRET
```

## Sortida

El programa ha d'imprimir el codi desxifrat a través de la sortida estàndard (stdout).

Per validar la vostra solució, podeu utilitzar el següent test:

- [test.sh](./challenge03/test.sh)
- [input1](./challenge03/input1)
- [input2](./challenge03/input2)

<details> 
<summary>Mostra la solució (Versió 1)</summary>

```bash
#!/bin/bash

search_unique_value(){
    declare -A counts

    for i in $@; do
        counts["$i"]=$(( ${counts["$i"]} + 1 ))
    done

    for key in ${!counts[@]}; do
        if [ ${counts["$key"]} -eq 1 ]; then
            ckey=$key
        fi
    done
}


read n

password=""
for (( r=1; r<=$n; r++ )); do
    read row
    search_unique_value $row
    password="$password$ckey"
done

echo $password
```

</details>

<details>
<summary>Mostra la solució (Versió 2)</summary>

```bash
#!/bin/bash

search_unique_value(){
    ckey=$(echo $@ | tr ' ' '\n' | sort | uniq -u)
}

# Llegim el nombre de files
read n

password=""
for (( r=1; r<=$n; r++ )); do
    read row
    search_unique_value $row
    password="$password$ckey"
done

echo $password
```

</details>
