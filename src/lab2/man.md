# Què és el Manual?

El manual ```man``` ens dona informació sobre la sintaxi de les comandes, el seu funcionament, opcions, arguments i exemples d'ús.

- Pots desplaçar-te pel manual utilitzant les fletxes de navegació (amunt i avall) o prement la tecla Enter.
- Per sortir del manual, pots simplement premer la tecla 'q'.
- Si vols cercar una paraula clau dins del manual, pots utilitzar la tecla '\/' seguida del text que vols cercar. Pots desplaçar-te pels resultats de cerca prement *Enter*.

A través de la comanda `man cat`, pots veure com el manual proporciona una explicació detallada de la comanda `cat`, la seva sintaxi, opcions, arguments i exemples d'ús.

El manual està organitzat en seccions temàtiques, cadascuna centrada en un tema específic:

  - **Secció 1**: Comandes executables o programes de l'usuari (e.g., `cat`, `ls`).
  - **Secció 2**: Crides de sistema (system calls) i funcions del nucli del sistema operatiu.
  - **Secció 3**: Funcions de biblioteca de programació.
  - **Secció 4**: Arxius especials del sistema i dispositius (e.g., `/dev/null`, `/dev/sda`).
  - **Secció 5**: Arxius de configuració del sistema (e.g., `/etc/passwd`, `/etc/fstab`).
  - **Secció 6**: Jocs (e.g., `nethack`, `snake`).
  - **Secció 7**: Diversos documents, com ara convencions de fitxers i protocols de xarxa.
  - **Secció 8**: Ordres per a administradors de sistema (e.g., `mount`, `ifconfig`).

Com en aquest curs ens centrarem en desenvolupar aplicacions per a usuaris utilitzant la biblioteca estàndard de C, instal·larem el paquet `manpages-dev` per a tenir accés a la secció 3 del manual.

```sh
jordi@debianlab:~$ su -c "apt install manpages-dev -y"
```

