# Pràctica 1: Pokemon GamePlay

## TroubleShooting

### Execució de programes

Els programes estan preparats per ser executats des del directori arrel, on es troba el `Makefile` principal. Aquest `Makefile` s'encarrega de compilar tant el programa **game** com el programa **pokedex** (*situat a src/pokedex*).

No obstant això, si intenteu executar el programa **pokedex** des del directori *src/pokedex*, aquest no funcionarà correctament a causa dels *path* dels fitxers CSV. Per tant, per executar correctament:

- Mode **pipe**: des del directori arrel, executar `./game` o `make run`.
- Mode **standalone**: `.src/pokedex/pokedex`.

Una millora que es podria implementar és fer que el programa sigui capaç d'executar-se correctament des de qualsevol directori.

### Lectura d'entrada estàndar amb `read`

La crida a sistema `read` en c, es defineix com `int nbytes=read(int fd, void *buf, int count)`. Aquesta crida llegeix `count` bytes del fitxer `fd` i els guarda a la memòria apuntada per `buf`. La crida retorna el nombre de bytes llegits o -1 en cas d'error.

És important tenir en compte que si es llegeixen menys bytes dels sol·licitats (per exemple, en llegir d'entrada estàndard), els bytes restants queden pendents per a la següent crida a read, la qual continuarà llegint des del mateix lloc. Això pot causar comportaments inesperats si no es gestiona adequadament el buffer.

Un exemple bàsic d'ús seria el següent:

```c
char buffer[2];
int nbytes = read(0, buffer, sizeof(buffer) - 1);
```

En aquest cas `sizeof(buffer)` retorna la mida del buffer en bytes (2), i es resta 1 per tant, únicament es llegeix un byte de l'entrada estàndard.

En aquest cas, si l'usuari introdueix **0\n** a través de l'entrada estàndard (**stdin**), el caràcter de nova línia **(\n)** romandrà al buffer, i serà llegit a la següent crida a `read`, fet que pot provocar comportaments imprevistos. Imagina que més endavant es torna a fer servir read(0) per llegir de l'entrada estàndard, el buffer contindrà el caràcter de nova línia, i la crida a `read` retornarà immediatament, ja que el buffer ja conté dades.

La recomanció es llegir la totalitat del buffer per evitar problemes, o bé, assegurar-se de netejar el buffer abans de fer una nova crida a `read`. Per exemple:

```c
size_t buffer_size = 8;  
char *buffer = malloc(buffer_size * sizeof(char));

int nbytes = read(0, buffer, buffer_size);
char* ptr = malloc(sizeof(char));
 
while ( ( read(0, ptr, 1)) > 0 && ptr[0] != '\n') {
    // Descartem tots els bytes que superen la mida del buffer
    // Fins que trobem un salt de línia
}
free(ptr);
```

### Optimització de memòria amb `realloc`

Quan es vol llegir una quantitat indeterminada de dades, és comú fer servir *malloc* per reservar una quantitat inicial de memòria i després utilitzar **realloc** per ajustar-ne la mida a mesura que es llegeixen més dades. Per exemple, els noms dels Pokémon són de longitud variable (*Mewtwo* té 6 caràcters, *Charizard* en té 9, etc.), així que no es pot reservar una quantitat fixa de memòria per a aquests noms.

Per exemple, si es vol llegir un nom de Pokémon de l'entrada estàndard, es podria fer servir el següent codi:

```c
size_t buffer_size = 8;  
char *buffer = malloc(buffer_size * sizeof(char));

int nbytes = read(0, buffer, buffer_size);
char* ptr = malloc(sizeof(char));
while ( ( read(0, ptr, 1)) > 0 && ptr[0] != '\n') {}
free(ptr);
        
char *buff = realloc(buffer, (nbytes + 1) * sizeof(char));
buff[nbytes] = '\0'; 
```

En aquest exemple, es reserven inicialment 8 bytes, es llegeixen dades de l'entrada, i si el nombre de bytes llegits és inferior a 8, es fa un *realloc* per ajustar el buffer a la mida exacta necessària. Finalment, es col·loca el **caràcter (\0)** per indicar el final de la cadena.

També cal tenir en compte el cas en què el nombre de caràcters llegits sigui superior a la mida inicial del buffer. En aquest cas, seria necessari utilitzar *realloc* per augmentar la memòria de forma dinàmica a mesura que es rebin més dades.

Una recomanació per evitar problemes és reservar una mida inicial basada en el nom del Pokémon més llarg conegut, i gestionar entrades que superin aquesta mida amb un avís o error. Com fem en l'exemple, que descartem els caràcters que superen la mida del buffer fins que trobem un salt de línia.

Us deixo un exemple per jugar:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    size_t buffer_size = 8;  
    char *buffer = malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        perror("malloc failed");
        return 1;
    }


    int nbytes = read(0, buffer, buffer_size);

    char* ptr = malloc(sizeof(char));
 
    while ( ( read(0, ptr, 1)) > 0 && ptr[0] != '\n') {
        // Descartem tots els bytes que superen la mida del buffer
        // Fins que trobem un salt de línia
    }
    free(ptr);
        

    if (nbytes < 0) {
        perror("read failed");
        free(buffer);
        return 1;
    }

    char *buff = realloc(buffer, (nbytes + 1) * sizeof(char));

    if (buff == NULL) {
        perror("realloc failed");
        free(buffer);
        return 1;
    }

    buff[nbytes] = '\0'; 

    printf("Buffer: %s\n", buff);
    printf("nb: %d\n", nbytes);
    printf("Mida del buffer: %d\n", nbytes + 1); 

    free(buff);
    return 0;
}
```

### Gestió de memòria amb `free`

Un altre aspecte important a tenir en compte és la gestió de la memòria amb `free`. Quan es fa servir `malloc`, `calloc` o `realloc` per reservar memòria, és responsabilitat del programador alliberar aquesta memòria un cop ja no sigui necessària. Si no es fa, es produeixen fuites de memòria, que poden causar problemes de rendiment i estabilitat en el programa.

Per exemple, si es reserva memòria per a un buffer de noms de Pokémon, s'ha de garantir que aquesta memòria es lliberi quan ja no sigui necessària. Un exemple senzill seria:

```c
char *buffer = malloc(10);
// fer servir buffer
free(buffer);
```

En aquest cas, un cop s'ha acabat de fer servir el buffer, s'allibera la memòria amb `free`. Això és especialment important en programes que fan servir molta memòria o que s'executen durant períodes llargs de temps, ja que les fuites de memòria poden acumular-se i causar problemes greus.

### Mode `pipe` vs. Mode `standalone`

El programa pokedex es pot executar en dos modes diferents: mode `pipe` i mode `standalone`. Els dos modes utilitzen el mateix codi font, però la diferencia rau en per on llegeixn i escriuen les dades.

- **Mode `pipe`**: En aquest mode, el programa Pokedex llegeix les dades d'una pipe i les escriu a una altra pipe, redirigint l'entrada i sortida estàndard de forma adequada. Tots els missatges de log, depuració, errors o informació es poden mostrar per la sortida d'error estàndard (stderr), ja que en tots dos modes es redirigeixen cap al terminal de l'usuari.

- **Mode `standalone`**: En aquest mode, el programa Pokedex llegeix les dades directament de l'entrada estàndard i escriu els resultats a la sortida estàndard. Això permet executar el programa de manera independent, sense necessitat de redirigir les dades, i facilita una interacció més directa amb l'usuari.

Pel que fa als missatges de sincronització que el programa **Pokedex** envia al **Game**, aquests es poden mostrar per la sortida estàndard en mode `standalone`, ja que no hi ha cap requeriment que indiqui el contrari. Tot i això, si preferiu que no es mostrin, podeu idear una solució creativa per evitar-ho, i es valorarà durant l'avaluació.

### Operacions `read` de tipus `char` vs. `int`

La crida de sistema `read`, per defecte, llegeix dades en forma de bytes (generalment interpretats com a caràcters de tipus **char**), però com que accepta un punter a `void`, es pot utilitzar per llegir qualsevol tipus de dades. Això vol dir que és possible llegir un enter, un flotant, un caràcter, etc.

- Si es vol llegir un enter:

    ```c
    int number;
    read(0, &number, sizeof(int));
    ```

- Si es vol llegir una *struct*:

    ```c
    struct example {
        int a;
        char b;
    };
    struct example ex;
    read(0, &ex, sizeof(struct example));
    ```

El problema rau quan interactuem amb l'entrada estàndard (**stdin**), ja que aquesta gestiona les dades en format de caràcter (char). Per tant, si es vol llegir un enter des de l'entrada estàndard, s'ha de llegir com una cadena de caràcters i després convertir-la a enter amb una funció com `atoi`.

Un exemple senzill seria:

```c
char buffer[10];
read(0, buffer, sizeof(buffer));
int number = atoi(buffer);
```

Aquest és un exemple simple, en un cas real s'hauria de gestionar millor la conversió, com comprovar si la cadena conté caràcters no numèrics, si el nombre és massa gran, etc.
