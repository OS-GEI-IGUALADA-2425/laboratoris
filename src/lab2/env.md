# Què són les variables d'entorn?

Les variables d'entorn són una part important del sistema operatiu que permet als processos interactuar amb el seu entorn. Una variable d'entorn és bàsicament una etiqueta que conté un valor. Aquests valors poden ser utilitzats pels processos per accedir a informació específica o configurar el seu comportament.

Les variables d'entorn són àmplies i poden contenir tot tipus d'informació, com ara la ruta d'accés als executables (*PATH*), la llengua preferida (*LANG*), el directori personal de l'usuari (*HOME*), entre altres. Aquestes variables poden ser útils per als processos per a personalitzar el seu comportament i accedir a recursos específics en funció del seu entorn.

Algunes de les més habituals són:

* **PATH**: Informació sobre les rutes per cercar ordres/comandes externes.
* **HOME**: Aquesta variable emmagatzema la ruta del directori inicial de l'usuari actual. És útil per a referir-se al directori personal d'un usuari en scripts o comandes. Podem utilitzar `echo $HOME` per visualitzar la ruta del directori inicial de l'usuari actual. És equivalent a **~**.
* **USER**: Usuari actual.
* **PWD**: Directori actual.
* **MAIL**: Fitxer on s'emmagatzema el correu.

Per exemple, podem utilitzar la comanda `printenv` per veure l'entorn d'una sessió. Quan s'inicia una sessió amb un usuari, les variables d'entorn associades a aquest usuari estan disponibles per a tots els processos en aquesta sessió. Si canviem de sessió d'usuari utilitzant su, les variables d'entorn també canviaran per reflectir l'usuari actual.

```sh
jordi@debianlab:~$ whoami
jordi@debianlab:~$ printenv
jordi@debianlab:~$ su 
root@debianlab:/home/jordi# whoami
root@debianlab:/home/jordi# printenv
root@debianlab:/home/jordi# exit
jordi@debianlab:~$ su -
root@debianlab:/home/jordi# whoami
root@debianlab:/home/jordi# printenv
```

Les principals operations que podem realitzar sobre les variables d'entorn són:

* ```set```: Permet inicialitzar la variable en la sessió (*shell*) actual.
* ```export```:  Permet inicialitzar la variable en la sessió actual i totes les sessions que es creïn a partir d'aquesta (**herència**).
* ```unset```: Permet eliminar una variable d'entorn.

```sh
jordi@debianlab:~$ echo $HOME
jordi@debianlab:~$ unset HOME
jordi@debianlab:~$ cd $HOME
jordi@debianlab:~$ export HOME=/home/jordi
jordi@debianlab:~$ cd $HOME
jordi@debianlab:~$ pwd
```

La variable **PATH** conté una llista de rutes on el sistema buscarà ordres o comandes externes quan s'intenti executar un programa. Per exemple, si volem executar un programa com `ls`, el sistema cercarà en les rutes especificades a la variable *PATH* per trobar l'executable `ls`. Si l'executable es troba en una d'aquestes rutes, el programa es podrà executar sense problemes.

Podem comprobar amb `whereis ls` que la ruta on es troba la utilitat `ls`, esta inclosa al *PATH*.

```sh
jordi@debianlab:~$ echo $PATH
/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
jordi@debianlab:~$ whereis ls
ls: /usr/bin/ls /usr/share/man/man1/ls.1.gz
```

Per modificar temporalment el *PATH*, podem assignar-li un nou valor. Per exemple, podem eliminar el contingut de la variable *PATH* amb **PATH=**. En aquest cas, si intentem executar una comanda com ls, el sistema no la trobarà ja que no està especificada en cap de les rutes del *PATH*.

```sh
jordi@debianlab:~$ PATH=
jordi@debianlab:~$ ls
-bash: ls: El fitxer o directori no existeix
jordi@debianlab:~$ /usr/bin/ls
a.txt
```

Per tornar a l'estat inicial:
```sh
jordi@debianlab:~$ PATH="/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games"
```

