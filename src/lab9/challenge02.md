# Challenge 02: Comparació de nombres en Bash

Escriviu un programa en Bash que, donats dos nombres enters, determini si:

1. Els dos nombres són iguals.
2. El primer nombre és més gran que el segon.
3. El segon nombre és més gran que el primer.

El programa ha de comprovar que les dues entrades són nombres enters vàlids. Si alguna de les entrades no és un nombre enter, s'ha de mostrar un missatge d'error adequat. També ha de comprovar que s'han llegit dues entrades.

Els missatges d'error han de ser els següents:

- [Error]: No s'han llegit dos nombres
- [Error]: X no és un nombre enter
- [Error]: Y no és un nombre enter

La sortida del programa ha de ser una de les següents frases:

- X és més gran que Y
- X és igual a Y
- X és més petit que Y

**Entrades**: Els nombres s'han d'introduir per l'entrada estàndard (stdin) en el format següent: ```x y```.

On **x** i **y** són els dos nombres a comparar.

Podeu utilitzar el següent esquelet de programa per començar:

```bash
#!/bin/bash

# Llegir els dos nombres
read x y

# Comprova que s'han llegit dos nombres
# @TODO

# Comprovar que els dos nombres són enters
# @TODO

# Comprovar si els dos nombres són iguals
# @TODO

# Comprovar si el primer nombre és més gran que el segon
# @TODO

# Comprovar si el segon nombre és més gran que el primer
# @TODO
```

Per validar la vostra solució, podeu utilitzar el següent test:

- [test.sh](./challenge02/test.sh)

Us presento 4 possibles solucions, cadascuna amb una forma diferent de calcular si un nombre és enter i amb diferents formes d'implementar la comparació de nombres.

<details> 
<summary>Mostra la solució (Versió 1)</summary>

```bash
#!/bin/bash

is_number() {
    if ! [ $1 -eq $1 ] 2>/dev/null; then
        echo "[Error]: $1 no és un nombre enter"
        exit 1
    fi
}

# Llegir els dos nombres
read x y

# Comprova que s'han llegit dos nombres
# -n comprova si la cadena no està buida
if !([ -n "$x" ] && [ -n "$y" ] ); then
    echo "[Error]: No s'han llegit dos nombres"
    exit 1
fi

# Comprovar que els dos nombres són enters
is_number $x
is_number $y


# Comprovar si els dos nombres són iguals
if [ $x -eq $y ]; then
    echo "X és igual a Y"
fi

# Comprovar si el primer nombre és més gran que el segon
if [ $x -gt $y ]; then
    echo "X és més gran que Y"
fi

# Comprovar si el segon nombre és més gran que el primer
if [ $x -lt $y ]; then
    echo "X és més petit que Y"
fi
```

</details>

<details>
<summary>Mostra la solució (Versió 2)</summary>

```bash
#!/bin/bash

is_number() {
    let "temp = $1 + 0" 2>/dev/null
    if (( $? != 0 )); then
        echo "[Error]: $1 no és un nombre enter"
        exit 1
    fi
}
# Intenta fer una operació matemàtica per validar si és un nombre enter

# Llegir els dos nombres
read x y

# Comprova que s'han llegit dos nombres
# -n comprova si la cadena no està buida
if !([ -n "$x" ] && [ -n "$y" ] ); then
    echo "[Error]: No s'han llegit dos nombres"
    exit 1
fi

# Comprovar que els dos nombres són enters
is_number $x
is_number $y


# Comprovar si els dos nombres són iguals
if [ $x -eq $y ]; then
    echo "X és igual a Y"
fi

# Comprovar si el primer nombre és més gran que el segon
if [ $x -gt $y ]; then
    echo "X és més gran que Y"
fi

# Comprovar si el segon nombre és més gran que el primer
if [ $x -lt $y ]; then
    echo "X és més petit que Y"
fi
```

</details>

<details>
<summary>Mostra la solució (Versió 3)</summary>

```bash
#!/bin/bash

is_number() {
    if ! (( $1 + 0 )) 2>/dev/null; then
        echo "[Error]: $1 no és un nombre enter"
        exit 1
    fi
}
# Intenta fer una operació matemàtica per validar si és un nombre enter

# Llegir els dos nombres
read x y

# Comprova que s'han llegit dos nombres
# -n comprova si la cadena no està buida
if !([ -n "$x" ] && [ -n "$y" ] ); then
    echo "[Error]: No s'han llegit dos nombres"
    exit 1
fi

# Comprovar que els dos nombres són enters
is_number $x
is_number $y

case 1 in
    $((x == y)))
        echo "X és igual a Y"
        ;;
    $((x > y)))
        echo "X és més gran que Y"
        ;;
    $((x < y)))
        echo "X és més petit que Y"
        ;;
esac
```

</details>

<details>
<summary>Mostra la solució (Versió 4)</summary>

```bash
#!/bin/bash

is_number() {
    if ! [[ $1 =~ ^-?[0-9]+$ ]]; then
        echo "[Error]: $1 no és un nombre enter"
        exit 1
    fi
}

# Intenta fer una operació matemàtica per validar si és un nombre enter

# Llegir els dos nombres
read x y

# Comprova que s'han llegit dos nombres
# -n comprova si la cadena no està buida
if !([ -n "$x" ] && [ -n "$y" ] ); then
    echo "[Error]: No s'han llegit dos nombres"
    exit 1
fi

# Comprovar que els dos nombres són enters
is_number $x
is_number $y

[ $x -eq $y ] && echo "X és igual a Y" || ([ $x -gt $y ] && echo "X és més gran que Y" || echo "X és més petit que Y")
```

</details>

> **Nota**: Assegureu-vos d'entendre bé la sintaxis i les diferents formes de comprovar si un nombre és enter. La última no l'he explicada a classe, però algun company ha trobat la expressió regular, i m'ha semblat interessant afegir-la com a solució.
