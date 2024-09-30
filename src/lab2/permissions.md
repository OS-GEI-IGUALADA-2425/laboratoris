
# Sistema de protecció de fitxers

Els sistemes **UNIX/Linux** permet controlar **QUI** pot accedir als fitxers i directoris a través dels permisos. Hi ha tres tipus de permisos: **lectura**, **escriptura** i **execució**. Aquests permisos es poden assignar a tres tipus d'usuaris: **owner**, **group** i **others**.

* **Owner**: Usuari que ha creat el fitxer.
* **Group**: Usuaris dels grups.
* **Other**: Qualsevol usuari del sistema.

* **Lectura [r]**: Dona accés al contingut del fitxer o a llistar fitxers dins del directori
* **Escriptura [w]**: Permet canviar el contingut del fitxer o crear/suprimir fitxers 
* **Execució [x]**: Permet executar el fitxer/ordre o permet cercar un directori


L'usuari *jordi* és owner del fitxer **a.txt** i pot **llegir/escriure** però no **executar**. Els membres del grup *jordi* poden **llegir** el fitxer, però **no escriure ni executar**. Igual que la resta d'usuaris.

```bash
jordi@debianlab:~$ touch a.txt
jordi@debianlab:~$ ls -la a.txt
-rw-r--r-- 1 jordi jordi 0 11 de jul.  11:26 a.txt
```

Per a gestionar els permisos dels fitxers i directoris, utilitzarem la comanda `chmod`. Aquesta comanda ens permet canviar els permisos d'accés dels fitxers i directoris. La sintaxi de la comanda és la següent:

```chmod [qui] operació permisos fitxer```

En el següent exemple, realitzem diverses operacions amb els permisos del fitxer creat anteriorment *a.txt*.

1. Amb `ls -la a.txt`, mostrem els permisos originals del fitxer: *-rw-r--r--*.
2. Amb `chmod +x a.txt`, afegim el permís d'execució per a tots els usuaris (owner, grup i altres).
3. Amb `ls -la a.txt`, podem veure que ara el fitxer té permisos d'execució: *-rwxr-xr-x*.
4. Amb `chmod -x a.txt`, eliminem el permís d'execució per a tots els usuaris.
5. Amb `ls -la a.txt`, podem veure que els permisos d'execució han estat eliminats: *-rw-r--r--*.
6. Amb `chmod o-r a.txt`, eliminem el permís de lectura per a altres usuaris.
7. Amb `ls -la a.txt`, podem veure que ara el fitxer té permisos de lectura només per a l'usuari i el grup, i no per a altres: *-rw-r-----*.
8. Amb `chmod g+w a.txt`, afegim el permís d'escriptura per al grup.
9. Amb `ls -la a.txt`, podem veure que ara el fitxer té permisos de lectura i escriptura per a l'usuari i el grup, però no per a altres: *-rw-rw----*.
10. Finalment, amb `chmod o+w a.txt`, afegim el permís d'escriptura per a altres usuaris.
11. Amb `ls -la a.txt`, podem veure que ara el fitxer té permisos de lectura, escriptura i escriptura per a l'usuari, el grup i altres: *-rw-rw--w-*.
12. Amb la comanda `chmod a-w a.txt`, eliminem el permís d'escriptura per a tots els usuaris (owner, grup i altres). 
13. Amb `ls -la a.txt`, podem veure que el permís d'escriptura (w) ha estat eliminat per a tots els usuaris.
14. Quan intentem afegir contingut a *a.txt* amb `echo "a" >> a.txt`, obtenim un error que indica que **s'ha denegat el permís d'escriptura**.
15. Amb la comanda `chmod +w a.txt`, afegim el permís d'escriptura a tots els usuaris. 
16. Ara podem afegir contingut amb `echo "a" >> a.txt` i veure el contingut amb `cat a.txt`.
17. Finalment, amb `chmod -r a.txt`, eliminem tots els permisos de lectura per a tots els usuaris. Quan intentem llegir el contingut de *a.txt* amb `cat a.txt`, obtenim un error que indica que **s'ha denegat el permís de lectura**.

```bash
jordi@debianlab:~$ chmod +x a.txt
jordi@debianlab:~$ ls -la a.txt
-rwxr-xr-x 1 jordi jordi 0 11 de jul.  11:26 a.txt
jordi@debianlab:~$ chmod -x a.txt
jordi@debianlab:~$ ls -la a.txt
-rw-r--r-- 1 jordi jordi 0 11 de jul.  11:26 a.txt
jordi@debianlab:~$ chmod o-r a.txt
jordi@debianlab:~$ ls -la a.txt
-rw-r----- 1 jordi jordi 0 11 de jul.  11:26 a.txt
jordi@debianlab:~$ chmod g+w a.txt
jordi@debianlab:~$ ls -la a.txt
-rw-rw---- 1 jordi jordi 0 11 de jul.  11:26 a.txt
jordi@debianlab:~$ chmod o+w a.txt
jordi@debianlab:~$ ls -la a.txt
-rw-rw--w- 1 jordi jordi 0 11 de jul.  11:26 a.txt
jordi@debianlab:~$ chmod a-w a.txt
jordi@debianlab:~$ ls -la a.txt
-r--r----- 1 jordi jordi 0 11 de jul.  11:26 a.txt
jordi@debianlab:~$ echo "a" >> a.txt
-bash: a.txt: S’ha denegat el permís
jordi@debianlab:~$ cat a.txt
jordi@debianlab:~$ chmod +w a.txt
jordi@debianlab:~$ echo "a" >> a.txt
jordi@debianlab:~$ cat a.txt
a
jordi@debianlab:~$ chmod -r a.txt
jordi@debianlab:~$ cat a.txt
cat: a.txt: S’ha denegat el permís
```

