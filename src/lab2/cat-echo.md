# Cat \& Echo

La comanda ```cat``` llegeix les dades de l'arxiu i mostra el seu contingut com a sortida (**stdout**). Permet crear, veure i concatenar fitxers. La comanda `echo` s'utilitza per mostrar text com a sortida (**stdout**). És similar a la funció `printf` en C i mostra el seu contingut com a sortida.

Podeu utilitar la comanda ```cat``` per mostrar el contingut del fitxer */etc/shells*  que us mostrarà totes les *shells* disponible al vostre sistema i la comanda ```echo``` per mostrar el contingut (**$**) de la variable d'entorn **SHELL** que us indicarà quina teniu activa en la vostra sessió de treball actual.

```sh
jordi@debianlab:~$ cat /etc/shells
jordi@debianlab:~$ echo $SHELL
```
