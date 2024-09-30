# Introducció a Debian

## Kernel de Linux

El kernel és el component central del sistema operatiu Linux, que actua com a intermediari entre les aplicacions i el maquinari del sistema.

Té diverses funcions clau:

- **Gestió de la memòria**: El kernel de Linux controla l'ús i la gestió de la memòria del sistema. Això implica assignar espai de memòria a les aplicacions en execució, garantint un ús eficient i evitant conflictes d'accés a la memòria.

- **Gestió dels processos**: El kernel supervisa i controla l'execució dels processos del sistema. Aquesta tasca implica assignar temps de CPU als diferents processos, gestionar les seves prioritats i coordinar la seva comunicació mitjançant mecanismes com les crides al sistema.

- **Gestió dels dispositius**: El kernel és responsable de la comunicació i la interacció amb els dispositius de maquinari. Això inclou els discs durs, les impressores, les targetes de xarxa i altres dispositius connectats al sistema. El kernel proporciona els controladors de dispositius adequats per a gestionar la seva funcionalitat i permetre la seva utilització per part de les aplicacions.

- **Gestió del sistema de fitxers**: El kernel de Linux ofereix un sistema de fitxers jeràrquic, que organitza i emmagatzema els fitxers i directoris del sistema. Aquesta gestió permet l'emmagatzematge eficient, la cerca i l'accés als fitxers i directoris del sistema.

El kernel de Linux és essencial per al funcionament del sistema operatiu i proporciona les funcions bàsiques necessàries per a l'execució de programes i la interacció amb els dispositius de maquinari. És constantment desenvolupat i millorat per la comunitat de desenvolupadors de Linux per a proporcionar un sistema operatiu eficient, estable i segur.


![Diagrama del Kernel de Linux, obtingut de kernel_linux_costa](https://graphviz.org/Gallery/directed/Linux_kernel_diagram.svg)

La figura anterior  extreta de [https://makelinux.github.io/kernel_map/](https://github.com/makelinux/linux_kernel_map/blob/HEAD/Linux_kernel_diagram) mostra l'estructura i els components principals del kernel de Linux. En aquest diagrama, es representen els components del sistema en rosa, els components relacionats amb el processament en vermell, els components relacionats amb l'accés a la memòria en verd, els components relacionats amb la xarxa en blau-cel i els components relacionats amb les interfícies d'usuari en lila. Aquest diagrama proporciona una visió general de l'estructura i les interaccions del nucli de Linux, mostrant com es divideix en diferents components i com s'interrelacionen per proporcionar les funcionalitats del sistema operatiu.

Algunes de les parts clau que es mostren en el diagrama inclouen:

- **Arquitectura del processador**: Aquesta part està relacionada amb les característiques i les funcionalitats específiques de l'arquitectura del processador en el qual s'està executant el kernel de Linux.
- **Subsistema de gestió de processos**: Aquesta part és responsable de la creació, l'execució i la finalització dels processos en el sistema. Gestiona la planificació de tasques, la gestió de memòria i altres aspectes relacionats amb els processos.
- **Gestió de memòria**: Aquesta part controla l'ús i la gestió de la memòria del sistema. Assigna i gestiona l'espai de memòria per a les aplicacions, realitza la gestió de la memòria compartida i aplica polítiques de gestió de memòria.
- **Gestió de dispositius**: Aquesta part gestiona la comunicació i la interacció amb els dispositius de maquinari connectats al sistema. Proporciona els controladors de dispositius adequats per permetre l'ús dels dispositius per part de les aplicacions.
- **Sistema de fitxers**: Aquesta part del kernel proporciona la gestió del sistema de fitxers, incloent l'emmagatzematge, la cerca i l'accés als fitxers i directoris del sistema.

Aquest diagrama del kernel de Linux ens dóna una visió general de l'estructura complexa i la interconnexió dels components que treballen conjuntament per proporcionar les funcionalitats essencials del sistema operatiu Linux.

Les distribucions Linux són versions específiques que incorporen el **kernel de Linux** juntament amb una *selecció de programari i eines addicionals* per proporcionar una experiència d'ús completa.

| Distribució | Descripció                                                 |
|-------------|------------------------------------------------------------|
| Ubuntu      | Basada en Debian, fàcil d'usar i orientada a l'usuari mitjà |
| Rocky Linux | Una continuació de CentOS enfocada en l'estabilitat         |
| Arch Linux  | Dirigida a usuaris avançats i amants de la personalització  |
| **Debian**  | Centrada en l'estabilitat, la seguretat i el programari lliure |
| Kali Linux  | Distribució especialitzada en seguretat i pentesting         |

Les distribucions Linux es diferencien en diversos aspectes, com el conjunt de programari inclòs, la configuració del sistema i la filosofia de desenvolupament. Aquesta varietat de distribucions Linux ofereix als usuaris diferents opcions per satisfer les seves necessitats i preferències. Cada distribució té els seus propis avantatges i aborda diferents casos d'ús.


## Debian

Debian és un sistema operatiu open-source basat en el kernel de **GNU/Linux**, i, per tant, és gratuït i desenvolupat i mantingut per la comunitat.

[![Debian is 30 this year. Here's why it's still worth using.](https://img.youtube.com/vi/jhFH03t4HUY/mqdefault.jpg)](https://www.youtube.com/watch?v=jhFH03t4HUY)

Es tracta d'un projecte sense ànim de lucre amb molts col·laboradors arreu del mon. **[Veure la Comunitat](https://wiki.debian.org/Community)**.

Alguns dels aspectes clau de Debian són:

* **Compromís amb el programari lliure**: Promou i defensa el programari lliure, garantint que els usuaris tinguin la llibertat de copiar, modificar i distribuir el programari.

* **Desenvolupament comunitari**: Projecte col·laboratiu. El desenvolupament es realitza de manera oberta i transparent, amb la participació de la comunitat en la presa de decisions.

* **Estabilitat i fiabilitat**: Reconegut per la seva estabilitat i fiabilitat. Les versions estables passen per un rigorós procés de prova i són alliberades quan s'assoleixen els estàndards d'estabilitat requerits.

### Versions de Debian

* **Stable (Estable)**: Recomanada per a la majoria dels usuaris. Proporciona un sistema operatiu estable amb versions de programari ben provades i suport a llarg termini.

* **Testing (Proves)**: És una edició en constant desenvolupament, amb versions més recents de programari però amb una menor estabilitat que l'edició estable. És adequada per a usuaris que volen tenir les últimes funcionalitats i estan disposats a assumir un cert grau de risc.

* **Unstable (Inestable)**: És l'edició més avançada i experimental. Conté les últimes versions de programari, però pot tenir problemes de compatibilitat i inestabilitat. És adequada per a desenvolupadors i usuaris avançats que volen contribuir al desenvolupament de Debian.

### Exemples i casos d'ús de Debian

* **Servidors**: Debian és ampliament utilitzat com a sistema operatiu per a servidors web. La seva estabilitat i seguretat en fan una opció ideal per a implementacions de servidors crítics, com ara llocs web d'empreses, botigues en línia, portals de notícies i blogs.

* **Centres de dades i computació en núvol**: Debian és una opció popular per a centres de dades i entorns de computació en núvol. La seva fiabilitat i facilitat d'implementació fan que sigui una elecció adequada per a grans infraestructures i sistemes distribuïts.

* **Sistemes empotrats i IoT**: Debian també s'utilitza en sistemes empotrats i dispositius d'Internet de les coses (IoT). La seva versatilitat i la capacitat de personalitzar la instal·lació la fan ideal per a projectes amb requisits específics.