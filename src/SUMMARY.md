# Índex

# Laboratoris generals

- [Laboratori 0](./lab0/main.md)
  - [Instal·lació de la màquina virtual](./lab0/vm-install.md)
  - [Conexió remota a la màquina virtual](./lab0/ssh.md)
  - [Configuració VS Code](./lab0/vscode.md)
  - [Configuració Git/Github](./lab0/git.md)
  - [Configurant entorn de treball](./lab0/dev.md)
  - [Projecte Col·laboratiu: Calculadora](./lab0/project0.md)

# Laboratoris de Programació en C

- [Laboratori 1: DebianBin](./lab1/main.md)# DebianBin

Als sistemes operatius basats en el nucli de Linux, no hi ha una paperera de reciclatge per defecte. Aquesta funcionalitat, habitual en altres sistemes, no està integrada nativament en l'estructura de fitxers de Linux. L'objectiu d'aquest laboratori és implementar una paperera de reciclatge per a Linux i crear una eina que permeti utilitzar-la (**rmsf**).

Per realitzar aquest laboratori, feu servir aquest enllaç per crear un repositori privat a GitHub Classroom: [DebianBin](https://classroom.github.com/a/XwzZXs37). Podeu fer servir els mateixos grups que en el laboratori anterior.

```sh
man rmsf
```

## rmsf(1) - Manual de l'usuari

### NOM

**rmsf** - Eliminació segura de fitxers i carpetes

### SÍNTESI

rmsf file ...

### DESCRIPCIÓ

L'eina **rmsf** mou els fitxers i carpetes especificats a la línia de comandes al directori `.trash/`, situat al directori personal de l'usuari. Aquest procés no suposa l'eliminació definitiva dels fitxers. El programa crea el directori `.trash` si no existeix. Si els fitxers no tenen permisos d'escriptura i el dispositiu d'entrada estàndard és un terminal, l'usuari rebrà una sol·licitud de confirmació (mostrada a la sortida d'error estàndard).

### ESTAT DE SORTIDA

**rmsf** retorna un codi d'èxit *0* en cas d'èxit i *>0* si es produeix algun error.

### EXEMPLES

Els següents exemples mostren l'ús comú:

- `rmsf file1`
- `rmsf file1 dir`
- `rmsf file1 dir/file2 b`
- `rmsf file1 dir/subdir/file2`

## Plantejant una possible solució simple

1. Obtenir la informació (`$HOME`) sobre l'usuari que està executant el programa.
2. Comprovar si existeix el directori `($HOME)/.trash`.
3. Si no existeix, crear-lo.
4. Moure tots els fitxers passats com a arguments al directori `($HOME)/.trash`.

## Aconseguint informació sobre l'usuari

Per obtenir el directori de l'usuari que està executant el programa podem utilitzar la funció ```getpwuid()```que es troba definada al fitxer ```/usr/include/pwd.h```. Per conèixer com puc utilitzar la funció podem consultar el manual d'UNIX. ```man getpwuid```.

```c
struct passwd *getpwuid(uid_t uid);
```

Segons el manual aquesta funció retorna un apuntador a una estructura *passwd* i necessita un paràmetre l'identificador únic de l'usuari (*uid*) que és del tipus *uid_t*.

### struct ```passwd```

La funció **getpwuid** ens permet obtenir informació d'un usuari a partir del *uid* proporcionat, accedint a la base de dades del sistema.

```c
 struct passwd {
    char    *pw_name;       /* user name */
    char    *pw_passwd;     /* encrypted password */
    uid_t   pw_uid;         /* user uid */
    gid_t   pw_gid;         /* user gid */
    time_t  pw_change;      /* password change time */
    char    *pw_class;      /* user login class */
    char    *pw_gecos;      /* general information */
    char    *pw_dir;        /* home directory */
    char    *pw_shell;      /* default shell */
    time_t  pw_expire;      /* account expiration */
};
```

### Activitat: whoami.c

Programeu un codi amb C que utilitzi la funció **getuid** per simular el comportament de whoami. Aquest programa tindrà una variable del tipus **int** que indicarà el uid de l'usuari a cercar i es mostrarà per pantalla el nom de l'usuari si l'hem trobat o un missatge indicant que l'usuari no existeix.

```sh
# uid_t uid = 0;
gcc whoami.c -o mywhoami
./mywhoami
The name of the user with uid 0 is root
# uid_t uid = -1;
 ./mywhoami
The user with uid: -1 is not in the system
```

```c
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int
main(){
     uid_t uid = 0; //uid_t uid = -1;
~    struct passwd *pwd;

~    if ((pwd = getpwuid(uid)) != NULL)
~        printf("The name of the user with uid %d is %s\n", uid, pwd->pw_name);
~    else
~        printf("The user with uid: %d is not in the system.\n", uid);
}
```

### Funció ```getuid```

Ara necessitem aconseguir l'identificador de l'usuari que executa el programa. Ja que si l'executa el jordi el seu home serà **/home/jordi** i si ho fa el pep serà **/home/pep**. Si investiguem la funció  ```getuid()```amb el manual ```man getuid()``` observarem que aquesta funció retorna el **uid** de l'usuari que crida a la funció. Noteu, que aquesta funció necessita ```#include <unistd.h>```.

```c
uid_t getuid(void);
```

Modifiqueu el programa anterior per fer servir aquesta funció.

```c
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

int
main(){
~    uid_t uid = getuid();
~    struct passwd *pwd;

~    if ((pwd = getpwuid(uid)) != NULL)
~        printf("The name of the user with uid %d is %s\n", uid, pwd->pw_name);
~    else
~        printf("The user with uid: %d is not in the system.\n", uid);
}
```

## Comprovant si un directori existeix

Si observem la lliberia ```sys/stat.h``` veurem que té una funció *stat()* i que pot estar relacionada amb els fitxers. Fem un ```man stat``` i ```man 2 stat``` (per veure la informació sobre la crida a sistema).

```sh
 stat $HOME
43009 2337025 drwxr-xr-x 12 jordi users -1 1536 "Sep 29 10:03:02
2022" "Sep 29 10:49:20 2022" "Sep 29 10:49:20 2022" "Sep  9
11:08:56 2022" 16384 4 0 /home/jordi
stat $HOME/.trash/
stat: /home/jordi/.trash/: lstat: No such file or directory
```

```c
int stat(const char *path, struct stat *sb);
```

Aquesta funció retorna un enter (**0**) si tot va bé. En cas contrari, retorna **-1** i la variable **errno** conté l'error que ha causat la fallada. En el nostre cas particular, si el directori no existeix esperem un valor de retorn de **-1** i el missatge *no such file or directory* guardat al **errno**.

Com a paràmetres la funció necessita un apuntador a una cadena de caràcters que conté el *path* a evaluar i un apuntador a una estructura del tipus **stat**. Noteu, que ***sb** és un variable d'entrada sortida, per tant, únicament cal que la definim.

Implementeu un ```mystat.c``` que donat un paràmetre d'entrada  ens indicarà si existeix o no.

```sh
gcc mystat.c -o mystat
```

```sh
./mystat $HOME
stat(/home/jordi,st) works!
```

```sh
./mystat $HOME/.trash
stat(/home/jordi/.trash,st) failed with error
Error: No such file or directory
```

```c
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

extern errno;

int
main(int argc, char* argv[])
{
    if (argc == 2){

~            char *path = argv[1];
~            struct stat st;

~            if ( stat(path,&st) == -1 ){
~                    printf("stat(%s,st) failed with error\n ", path);
~                    perror("Error");

~            }else{
~                    printf("stat(%s,st) works!\n", path);
~            }

    }

    return 0;
}
```

Implementeu un ```mystat2.c``` que donat un paràmetre d'entrada  ens indicarà si existeix o no. Però ara utilitzeu **opendir**.

```c
#include <dirent.h>
DIR *     opendir(const char *filename);
```

```c
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

extern errno;

int
main(int argc, char* argv[])
{
    if (argc == 2){
        char *path = argv[1];
~       DIR* dir = opendir(path);

~        if (dir){
~           printf("El directori: %s existeix.\n", path);
~        } else if (ENOENT == errno) {
~           /* opendir() ha fallat per ENOENT (no existeix) */
~           printf("El directori: %s no existeix.\n",path);
~        } else {
~           /* opendir() ha fallat per un altre motiu. */
~           perror("Error obrint el directori");
~           return -1;
~        }
    }
    return 0;
}
```

## Concatenant paraules amb C

Per poder donar la funcionalitat adequada necessitem cercar un mètode per poder concatenar cadenes en C. Tenim a la variable **path** el directori *home* del usuari i amb una altra variable tindrem la cadana constant *".trash"*. Disposem de moltes maneres per concatenar cadenes en C. En aquesta solució revisarem les que ens ofereix ```string.h``` com *strcpy, strncpy, strcat i strncat*.

```c
#include <string.h>
char * strcat(char * restrict s, const char * restrict append);
char * strncat(char * restrict s, const char * restrict append, size_t count);
```

Implementeu un programa que permeti concatenar cadenes en c. Completeu el codi:

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRASH ".trash"
#define PATH "/home/jordi"

int main(){

    char *trash_path = NULL; 
    // 1byte '\0' i 1byte del separador '\'
    trash_path = malloc( (strlen(PATH) + strlen(TRASH) + 1 + 1) * sizeof(char));

    ~strcpy(trash_path,PATH);
    ~strcat(trash_path,"/"); 
    ~strcat(trash_path,TRASH);

    printf("El valor de la cadena trash_path:%s\n", trash_path );
    free(trash_path);
    return 0;
}
```

## Creant directoris

En aquest punt ja tenim totes les eines per detectar si tenim papelera de reciclatge en el directori de l'usuari. Únicament, necessitem una comanda que ens permeti generar un directori en una ubicació.

```sh
mkdir test
mkdir test
mkdir: test: File exists
```

Per poder veure la informació de la crida a sistema ```mkdir()``` fem ```man 2 mkdir```. Aquesta crida ens permet crear el directori passat com apuntador a cadena a la variable **path** amb els permisos indicats per la variable **mode** del tipus *mode_t*. La funció ens retorna 0 o -1 (en cas d'error).

Implementeu un programa en c, que donat un directori comprovi si existeix i si no el crei amb tots els permisos per l'usuari i sense permisos pel grup i altres.

```sh
gcc mkdir.c -o mkd
./mkd test
El directori: test s'ha pogut crear.
./mkd test
File exists.
```

```c
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
extern errno;

int
main(int argc, char* argv[])
{
    if (argc == 2){
            char *path = argv[1];
            ~if (mkdir(path, 0700) == -1){
            ~    printf("%s.\n", strerror(errno));
            ~ } else{
            ~    printf("El directori: %s s'ha pogut crear.\n", path);
            }
        }
    return 0;
}
```

## Movent fitxers i directoris

Si observem com fer servir la crida a sistema **rename** ('''man rename''') observem que ens permet dur a terme la funcionalitat passant com arguments dos punters a caracters on *from* indica el **fitxer/directori** original que volem moure i **to** el **fitxer/directori** final. La funció ens retorna 0 o -1 (en cas d'error).

```c
#include <stdio.h>
int rename(const char *from, const char *to);
```

Implementeu un programa que mogui un fitxer a **/$HOME/.trash**. Podeu assumir que el directori existeix per aquest exemple.

```sh
touch a.txt
ls -la a.txt
-rw-r--r--  1 jordi  users  0 Sep 30 11:06 a.txt
./mymv a.txt
No such file or directory.
mkdir .trash
./mymv a.txt
S'ha mogut a.txt a .trash de forma satisfactoria.
ls -la a.txt
ls: a.txt: No such file or directory
ls -la .trash/a.txt
-rw-r--r--  1 jordi  users  0 Sep 30 11:06 .trash/a.txt
```

```c
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
extern errno;

#define TO ".trash"

int
main(int argc, char* argv[])
{
    if (argc == 2){

            char *path = argv[1];
            char * to = malloc (strlen(TO) + 1 + strlen(path) + 1 );
            strcpy(to,TO); strcat(to,"/"); strcat(to,path);

            ~if (rename(path, to) == -1){
            ~        printf("%s.\n", strerror(errno));
            ~} else{
            ~    printf("S'ha mogut %s a %s de forma satisfactòria.\n", path, to);
            ~}

            free(to);
        }
    return 0;
}
```

Si executem aquest codi, veurem que en alguns casos funciona i en altres no. 

```sh
touch aaaa.txt
./mymv ./aaaa.txt
S'ha mogut ./aaaa.txt a .trash/./aaaa.txt de forma satisfactòria.
```

Per exemple, aquest codi funciona molt bé sempre que indiquem el nom del fitxer a moure i el fitxer es trobi en el mateix path que l'executable. Però que passa quan intento eliminar fitxers amb un *path*.

```sh
./mymv /home/jordi/aaaa.txt

```

Modifiqueu el codi anterior per acceptar *path* i solucionar aquest escenari.

```c
int main(int argc, char* argv[])
{
    if (argc == 2){
            char *path = argv[1];
            struct stat st;
            char * name = malloc (strlen(path));

            if ( stat(path,&st) == -1 ){
                printf("%s.\n", strerror(errno));
                return -1;
            }
            else
            {
            ~    if (S_ISREG(st.st_mode)){
            ~        name = basename(path);
            ~        printf("It is a file with name: %s\n", name);
            ~    else if (S_ISDIR(st.st_mode)){
            ~    }
            ~        name  = basename(path);
            ~        printf("It is a folder with name: %s\n", name);
            ~    }
            ~    else{
            ~        printf("argv[1]=%s is neither file or directory .\n", path);
            ~        return -1;
            ~    }
            }
        }
    return 0;
}
```

## Implementant rmsf

En aquest punt ja tenim totes les eines necessaries per implementar la funcionalitat bàsica de **rmsf**. Aquesta funcionalitat consisteix en moure els fitxers i directoris passats com a paràmetres a la paperera de reciclatge. En cas de no existir la paperera de reciclatge, la crearem. En cas de no existir el fitxer o directori, informarem a l'usuari. En cas de no poder moure el fitxer o directori, informarem a l'usuari.

```c
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <dirent.h>
#include <pwd.h>
extern errno;

#define TRASH ".trash"

int check_and_create_folder(char * folder)
{
    struct stat st;
    if ( stat(folder,&st) == -1 ){
        if (ENOENT == errno) { 
            int res = mkdir(folder, 0700);
            if (res ==-1) printf("%s.\n", strerror(errno));
            return res;
        }
    }
    return 0;
}

void join_path(char** path, char* begin, char* end){
       *path = malloc(strlen(begin) + 1 +strlen(end) + 1);
       strcpy(*path,begin);
       strcat(*path,"/");
       strcat(*path,end);
}


int main(int argc, char* argv[]){
        uid_t uid = getuid();
        struct passwd *pwd;
    
        if ((pwd = getpwuid(uid)) != NULL){

            char *homedir = pwd->pw_dir;

            char *trash_path = NULL;
            join_path(&trash_path, homedir, TRASH);

            if (check_and_create_folder(trash_path)==0)
            {
                for (int i=1; i<argc; i++) {
                    
                    printf("[%d] ::: sending to the trash: %s \n", i,argv[i]);

                    struct stat st;
                    if ( stat(argv[i],&st) == -1 ){
                         printf("::: ...we cannot find it. Error: %s.\n", strerror(errno));
                    }
                    else
                    {
                        char *name = basename(argv[i]);
                        char *to;
                        join_path(&to, trash_path, name);

                        printf("::: from (original): %s to (final): %s.\n",argv[i], to);

                        if (rename(argv[i], to) == -1){
                            printf("::: ...we cannot send it to the trash. Error: %s.\n", strerror(errno));
                        } 
                        free(to);
                    }

                }
            } 
            else 
            { 
                printf("Exiting... errors with the recyclerbin!\n");
                return -1;
            }
            free(trash_path);
        }
        else {
            printf("Exiting... errors with getting user information!\n");
            return -1;
        }
        return 0;
}
```

## Exercicis opcionals

1. Genereu un repositori a GitHub amb el codi de l'aplicació **rmsf**. Inclou-hi:
    - Un **README.md** amb una descripció de l'aplicació i una captura de pantalla de l'execució de l'aplicació.
    - Un *Makefile* per compilar el codi.
    - Un github action que generi un *release* amb el codi compilat.

2. Actualitzeu el programa utilitzant la llibreria *getopt* per poder passar opcions com:
    - **-h** per mostrar l'ajuda.
    - **-v** per mostrar la versió.
    - **-d** per enviar a la paperera de reciclatge fitxers i directoris.
    - **-r** per recuperar fitxers i directoris de la paperera de reciclatge a la seva ubicació original.
    - **-t** per mostrar la ubicació de la paperera de reciclatge.

3. Afegiu una opció per preguntar a l'usuari si vol enviar a la paperera cada fitxer o directori. I en cas afirmatiu, enviar-lo. En cas negatiu, no fer res. Aquesta opció pot estar activada per defecte i es pot desactivar amb l'opció **-y**.

