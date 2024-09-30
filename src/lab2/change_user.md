# Canvi de sessió d'usuari

Un cop iniciada la sessió amb un usuari concret, com ara *jordi*, a vegades pot ser necessari canviar a un altre usuari per a realitzar tasques específiques o per accedir a recursos restringits. A Debian, podem canviar de sessió d'usuari utilitzant la comanda ```su```.

Podem utilitzar l'ordre su seguida del nom de l'usuari al qual volem canviar per iniciar una nova sessió amb aquest usuari (`su [usuari]`). La comanda demanarà la contrasenya d'aquest usuari per a la verificació. Un cop s'hagi proporcionat la contrasenya correcta, es canviarà la sessió d'usuari i l'indicador del símbol del sistema **($ o #)** canviarà per reflectir l'usuari actual.

Per exemple, podem canviar a l'usuari *root* utilitzant la comanda `su` sense especificar cap usuari addicional. Això ens demanarà la contrasenya de l'usuari *root* i, un cop verificada, canviarem a la sessió de l'usuari *root*. Podem tornar a canviar a l'usuari original utilitzant la comanda exit.

```sh
jordi@debianlab:~$ whoami
jordi@debianlab:~$ cat /etc/master.passwd 
Permission denied
jordi@debianlab:~$ su
root@debianlab:/home/jordi# whoami
root@debianlab:/home/jordi# cat /etc/passwd
root@debianlab:/home/jordi# su jordi
jordi@debianlab:~$ whoami
jordi@debianlab:~$ exit
root@debianlab:/home/jordi# whoami
jordi@debianlab:~$ exit
jordi@debianlab:~$ exit
```

**Observació**: Si utilitzem `su - [usuari]`, aquesta opció carregarà totes les configuracions d'entorn del nou usuari, incloent variables d'entorn, directori personal i altres configuracions específiques. Això assegurarà que la nova sessió d'usuari tingui les mateixes configuracions que si s'iniciés una sessió nova.

### Pujada de privilegis (sudo)

Però, a més de la comanda `su`, hi ha una altra opció que pot ser útil per a la pujada de privilegis: el paquet `sudo`. Amb sudo, un usuari pot obtenir temporàriament privilegis d'administració per a realitzar tasques específiques sense haver de canviar completament de sessió.

Per utilitzar sudo, primer cal instal·lar el paquet mitjançant la comanda `apt install sudo`. Un cop instal·lat, els usuaris que estiguin en el *grup sudo* podran utilitzar la comanda `sudo` per a executar comandes amb privilegis d'administració. La comanda sudo demanarà la contrasenya de l'usuari actual i, si es verifica correctament, permetrà a l'usuari executar la comanda desitjada amb privilegis temporals.
