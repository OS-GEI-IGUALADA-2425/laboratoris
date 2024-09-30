# Cheat Sheet

Us podeu descàrregar i consultar la targeta de referència per a Debian 12.0 *Bookworm* en format PDF en el següent enllaç: [https://www.debian.org/doc/manuals/refcard/refcard](https://www.debian.org/doc/manuals/refcard/refcard)

![](./figures/targeta1.png)

![](./figures/targeta2.png)

Resum de comandes per a fitxers:

* ```ls -la```: Llista amb format de tots els fitxers (normals i ocults).
* ```cd```: Navegar a un directori. 
* ```pwd```: Mostra el directori actual.
* ```mkdir```: Crear un directori.
* ```rm -rf```: Eliminar de forma recursiva (fitxers i directoris).
* ```cp f1 f2```: Copia el fitxer f1 al fitxer f2.
* ```mv f1 f2```: Moure o reanomenar el fitxer f1 a f2.
* ```more f1```: Mostra el contingut del fitxer f1.
* ```less f1```: Mostra el contingut del fitxer f1.
* ```head f1```: Mostra les primeres 10 línies del fitxer f1.
* ```tail f1```: Mostra les últimes 10 línies del fitxer f1.

Resum de comandes per a consultar informació del sistema:

* ```date```: Mostra la data i el temps actuals.
* ```cal```: Mostra el calendari.
* ```uptime```: Mostra el temps que el servidor porta actiu.
* ```w```: Mostra quins usuaris estan actius online.
* ```whoami```: Mostra el nom de l'usuari actual.
* ```finger user```: Mostra informació de l'usuari.
* ```uname -a```: Mostra informació sobre el kernel.
* ```cat /proc/cpuinfo```: Mostra informació sobre la cpu.
* ```cat /proc/meminfo```: Mostra informació sobre la memòria.
* ```df```: Mostra informació sobre l'utiltizació del disc.
* ```du```: Mostra informació sobre l'espai utilitzat al directori.
* ```whereis app```: Mostra les localitzacions de app.
* ```which app```: Mostra quina app s'executarà per defecte.

Resum de comandes per a la compressió de fitxers:

* ```tar cf f.tar files```: Comprimeix files en un fitxer f.tar.
* ```tar xf file.tar```: Extreu els fitxers de file.tar al directori actual.
* ```tar czf file.tar.gz files```: Comprimeix amb Gzip.
* ```tar xzf file.tar.gz```: Extreu els fitxers comprimits amb Gzip.
* ```tar cjf file.tar.bz2 files```: Comprimeix amb Bzip2.
* ```tar xjf file.tar.bz2```: Extreu els fitxers comprimits amb Bzip2.
* ```gzip file```: Comprimeix el fitxer file i l'anomena file.gz.
* ```gzip -d file.gz```: Descomprimeix el fitxer file.gz.

Resum de comandes per consultar informació de la xarxa:

* ```ping``` host: Ping a una ip i mostra els resultats.
* ```whois``` domain: Aconsegueix informació sobre el domini.
* ```dig``` domain: Obté informació sobre els dns del domini.
* ```wget``` file: Descarrega un fitxer.
  