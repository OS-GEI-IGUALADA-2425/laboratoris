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
