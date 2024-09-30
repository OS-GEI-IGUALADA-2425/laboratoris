# Sistema de fitxers

El sistema de fitxers és l'estructura que utilitza un sistema operatiu per *organitzar i emmagatzemar informació en el disc*. Aquest sistema defineix com es guarden i s'accedeixen als fitxers i directoris en el sistema operatiu.

- **Fitxers**: Un fitxer és una col·lecció d'informació que es guarda en el disc. Pot contenir text, dades binàries, codi executable, entre altres tipus d'informació.
- **Directoris**: Els directoris són utilitzats per organitzar els fitxers en grups lògics. Cada fitxer es troba en un directori específic, i els directoris poden contenir altres directoris o fitxers.
- **Fitxers especials**: A més dels fitxers i directoris regulars, hi ha altres tipus de fitxers especials que representen dispositius connectats al sistema. Poden ser de caràcters o de blocs, depenent del tipus de dispositiu.

La comanda ```lsblk``` ens permet veure una llista de tots els dispositius de blocs del sistema, com ara discos i particions. Aquesta comanda ens mostra el nom del dispositiu, la seva mida, el tipus de dispositiu i el punt de muntatge associat. 

```bash
jordi@debianlab:~$ lsblk
NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
sda      8:0    0   20G  0 disk
├─sda1   8:1    0  512M  0 part /boot/efi
├─sda2   8:2    0 18,5G  0 part /
└─sda3   8:3    0  976M  0 part [SWAP]
sr0     11:0    1 1024M  0 rom
```

En el meu cas, es pot observar un disc (**sda**) amb 3 particions (**sda1,sda2,sda3**) i un dispositiu rom (**sr0**). Aquest dispositiu rom és un dispositiu de lectura de CD/DVD.

Cada *disc o partició* té el seu propi sistema de fitxers. Pots utilitzar la comanda `df -h` per veure una llista de les particions i els seus sistemes de fitxers associats, així com la informació d'ús d'espai en disc.

```bash
jordi@debianlab:~$ df -h
S. fitxers      Mida En ús Lliure  %Ús Muntat a
udev            1,9G     0   1,9G   0% /dev
tmpfs           392M  616K   391M   1% /run
/dev/sda2        19G  1,7G    16G  10% /
tmpfs           2,0G     0   2,0G   0% /dev/shm
tmpfs           5,0M     0   5,0M   0% /run/lock
/dev/sda1       511M  5,9M   506M   2% /boot/efi
tmpfs           392M     0   392M   0% /run/user/1000
```

En aquest exemple, podem veure que hi ha dues particions amb sistemes de fitxers associats:

* **/dev/sda2**: Partició del disc que té un sistema de fitxers associat i està muntat com a directori arrel **(/)**. Té una mida total de 19G, amb 1,7G utilitzats i 16G lliures. El % d'ús és del 10%. *Aquesta partició conté el sistema operatiu Debian*.

* **/dev/sda1**: Partició del disc que té un sistema de fitxers associat i està muntat a **/boot/efi**. Té una mida total de 511M, amb 5,9M utilitzats i 506M lliures. El % d'ús és del 2%. *Aquesta partició conté els arxius d'arrencada del sistema operatiu Debian*. Els sistemes **UEFI** requereixen una partició especial per a emmagatzemar arxius d'arrencada.

Podem observar diferents sistemes de fitxers com *udev*, *tmpfs*. Aquestes particions són particions virtuals que no tenen un dispositiu físic associat. Aquestes particions virtuals tenen assignades un espai de memòria i són utilitzades pel sistema operatiu per a emmagatzemar informació temporal.

Anem a veure com esta organitzat el sistema de fitxers de Debian. A través del sistema de fitxers principal, els usuaris poden gestionar i accedir a la informació emmagatzemada en el disc. És important comprendre l'estructura i el funcionament del sistema de fitxers per a una correcta gestió i organització dels fitxers i directoris en el sistema operatiu Debian.

```sh
jordi@debianlab:~$ tree -L 1 -d 
├── bin -> usr/bin
├── boot
├── dev
├── etc
├── home
├── lib -> usr/lib
├── lib32 -> usr/lib32
├── lib64 -> usr/lib64
├── libx32 -> usr/libx32
├── lost+found
├── media
├── mnt
├── opt
├── proc
├── root
├── run
├── sbin -> usr/sbin
├── srv
├── sys
├── tmp
├── usr
└── var
```

| Directori | Contingut                               |
|-----------|-----------------------------------------|
| bin       | Binaris d'ordres essencials              |
| boot      | Fitxers estàtics del carregador de l'arrencada |
| dev       | Fitxers de dispositius                   |
| etc       | Configuració específica de l'amfitrió del sistema |
| home      | Directoris d'inici d'usuari              |
| lib       | Llibreries compartides essencials i mòduls del nucli |
| media     | Punts de muntatge per a mitjans reemplaçables |
| mnt       | Punt de muntatge per muntar un sistema de fitxers temporalment |
| opt       | Paquets de programari addicional         |
| proc      | Directori virtual per a informació del sistema |
| root      | Directori d'inici per a l'usuari root    |
| run       | Dades variables d'execució               |
| sbin      | Binaris essencials del sistema           |
| srv       | Dades per a serveis proporcionats pel sistema |
| sys       | Directori virtual per a informació del sistema |
| tmp       | Fitxers temporals                        |
| usr       | Jerarquia secundària                     |
| var       | Dades variables                          |
| .         | Directori actual                        |
| ..        | Directori anterior                      |

