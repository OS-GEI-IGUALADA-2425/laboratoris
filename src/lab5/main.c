# Exercicis classe: Pokemon (C)

 Pokemon

Un pokemon el podem entendre com una estructura de dades que conté diferents camps. En aquest cas, els camps que ens interessen són:

* **pokemon_id**: identificador únic del pokemon
* **name**: nom del pokemon
* **height**: altura del pokemon
* **weight**: pes del pokemon

Per poder implementar aquesta estructura de dades en C, necessitem definir un tipus de dades que ens permeti agrupar aquests camps. Això ho podem fer mitjançant la paraula reservada **struct**.

```c    
struct pokemon {
    int          pokemon_id;
    char[50]     name;
    double       height;
    double       weight;
};
```

Podem fer un programa molt senzill per crear un pokemon i mostrar-lo per pantalla.

```c
/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcpy

struct pokemon {
    int          pokemon_id;
    char         name[50];
    double       height;
    double       weight;
};

int main() {
    struct pokemon pikachu;
    pikachu.pokemon_id = 25;
    strcpy(pikachu.name, "Pikachu");
    pikachu.height = 0.4;
    pikachu.weight = 6.0;

    printf("Pokemon: %s\n", pikachu.name);
    printf("Pokemon ID: %d\n", pikachu.pokemon_id);
    printf("Pokemon Height: %f\n", pikachu.height);
    printf("Pokemon Weight: %f\n", pikachu.weight);

    return 0;
}
```

Si compilem i executem el programa, funcionarà i obtindrem el resultat esperat:

```sh
gcc -o main main.c
```

```sh
./pokemon 
    Pokemon: Pikachu
    Pokemon ID: 25
    Pokemon Height: 0.400000
    Pokemon Weight: 6.000000
```

En aquesta primera versió hem utilitzat una mida estàtica pel camp **name** utilizant la *stack*. Això vol dir que el nom del pokemon no pot ser més gran de 50 caràcters. També, indica que estem desaprofitant memòria en tots els noms de pokemons inferiors a 50 caràcters. Recordeu que la mèmoria és un recurs molt valuós i que hem d'aprofitar al màxim.

Per tant, per poder solucionar aquest problema, podem utilitzar la *heap* per reservar memòria dinàmicament per al camp **name**. Això ens permetrà utilitzar la memòria de forma més eficient i no tindrem cap limitació en la mida del nom del pokemon. D'aquesta manera podem garantir que cada nom ocupi l'espai que requereixi.


```c    
struct pokemon {
    int          pokemon_id;
    char         *name;
    double       height;
    double       weight;
};
```


Per tant el nostre programa quedaria de la següent manera, on podem veure com reservem memòria per al camp **name** mitjançant la funció **malloc** i alliberem la memòria reservada mitjançant la funció **free**:

```c
/*  
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcpy()

struct pokemon {
    int          pokemon_id;
    char *       name;
    double       height;
    double       weight;
};

int main() {
    struct pokemon pikachu;
    pikachu.pokemon_id = 25;
    pikachu.height = 0.4;
    pikachu.weight = 6.0;

    // Reservem memòria per al camp name
    pikachu.name = malloc(8 * sizeof(char));
    strcpy(pikachu.name, "Pikachu");
    
    printf("Pokemon: %s\n", pikachu.name);
    printf("Pokemon ID: %d\n", pikachu.pokemon_id);
    printf("Pokemon Height: %f\n", pikachu.height);
    printf("Pokemon Weight: %f\n", pikachu.weight);

    // Alliberem la memòria reservada per al camp name
    free(pikachu.name);

    return 0;
}
```

**OBSERVACIÓ**: Tot i això, es aconsellable definir un llindar màxim per evitar problemes. *En aquest exemple, no afegirem aquest llindar, però en un cas real caldria avaluar si es necessari o no i els problemes de afegir o no afegir aquest llindar.*

**NOTA 1**: Quan reserveu memòria per una cadena de caràcters recordeu de reservar 1 byte més per el caràcter de final de cadena **'\0'**.

**NOTA 2**: Si feu anar **strlen** per calcular la mida de la cadena, us retorna la mida en bytes sense comptar el caràcter de final de cadena **'\0'**. 

```c
pikachu.name = malloc( (strlen("Pikachu")+1) * sizeof(char) );
```

Ara anem analitzar els següents supòsits:

```
char name[] = "Pikachu";
pikachu.name = name;
pikachu.name = &name;
pikachu.name = strdup(name);
strcpy(pikachu.name, name);
```

Us deixo les signatures de les funcions que es troben a la llibreria *string.h*:
    
```c
char *strdup(const char *s);
char *strcpy(char *dest, const char *src);
```

* ```pikachu.name = name;```: Aquesta assignació és vàlida ja que *name* és un array de caràcters i, en aquest context, es comporta com un punter al seu primer element (és equivalent a *&name[0]*), que és el que espera pikachu.name. Però si modifiquem la variable name en un altre punt del programa, pikachu.name també canviarà, ja que apunta a la mateixa memòria.

```c
char name[] = "Pikachu";
pikachu.name = name;
printf("Pokemon: %s\n", pikachu.name); // Pikachu
strcpy(name,"Raichu");
printf("Pokemon: %s\n", pikachu.name); // Raichu
```

* ```pikachu.name = &name;```: **&name** és l'adreça de l'array *name*, i **pikachu.name** és un punter a char, així que aquesta assignació no és vàlida, ja que l'adreça de name no és compatible amb un punter a char.

* ```pikachu.name = strdup(name);```: Aquesta assignació és vàlida ja que **strdup** retorna un punter a char, i això és el que espera **pikachu.name**. A més, com que **strdup** reserva memòria nova per a la cadena, no hi ha cap problema si modifiquem la variable name en un altre punt del programa. Es pot fer servir sense reserva prèvia de memòria per a pikachu.name, ja que **strdup** reserva memòria nova per a la cadena i retorna un punter a aquesta memòria.

* ```strcpy(pikachu.name, name);```: Això és vàlid si **pikachu.name** ja té memòria reservada prèviament (per exemple, a través de *malloc* o *calloc*) en la qual es pot realitzar la còpia.

**RECORDATORI**: *Malloc* i *Calloc* ens permeten reservar memòria dinàmicament. La diferència entre malloc i calloc és que malloc no inicialitza la memòria reservada, mentre que calloc inicialitza la memòria reservada a 0. 

## Ús de typedef

Ara podem utilitzar **typedef** per definir un nou tipus de dades que ens permeti crear pokemons de forma més senzilla.

```c
/*
 * main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strdup(),

typedef struct pokemon {
    int          pokemon_id;
    char *       name;
    double       height;
    double       weight;
} Pokemon;

int main() {
    Pokemon pikachu;
    pikachu.pokemon_id = 25;

    pikachu.name = strdup("Pikachu");
    pikachu.height = 0.4;
    pikachu.weight = 6.0;

    printf("Pokemon: %s\n", pikachu.name);
    printf("Pokemon ID: %d\n", pikachu.pokemon_id);
    printf("Pokemon Height: %f\n", pikachu.height);
    printf("Pokemon Weight: %f\n", pikachu.weight);

    return 0;
}
```

**OBSERVACIÓ:** Si utilitzem la funció *strdup*, no cal reservar ni alliberar memòria per al camp *name*.

## Creació i ús de llibreries

Ara podem crear una llibreria que ens permeti fer operacions amb pokemons. Per exemple, podem crear un pokemon amb la funció **create_pokemon** i mostrar-lo per pantalla amb la funció **print_pokemon**. Per fer-ho, crearem un fitxer anomenat **pokemon.h** on definirem les funcions i un fitxer anomenat **pokemon.c** on implementarem les funcions.

En el fitxer **pokemon.h** descriurem la interfície de la nostra llibreria. Això vol dir que definirem les funcions que volem que estiguin disponibles per a l'usuari de la llibreria. També farem accessible la nostra estructura de dades **Pokemon**.

```c
/*
 * pokemon.h
 */

#ifndef _POKEMON_H_
#define _POKEMON_H_

typedef struct pokemon {
    int          pokemon_id;
    char *       name;
    double       height;
    double       weight;
} Pokemon;

Pokemon create_pokemon(int pokemon_id, char *name, double height, double weight);
void print_pokemon(Pokemon pokemon);

#endif // _POKEMON_H_
```

En el fitxer **pokemon.c** implementarem les funcions que hem definit a la interfície de la nostra llibreria.

```c
/*
 * pokemon.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen(), strcpy()
#include "pokemon.h"

Pokemon create_pokemon(int pokemon_id, char *name, double height, double weight) {
    Pokemon pokemon;
    pokemon.pokemon_id = pokemon_id;
    pokemon.name = malloc( (strlen(name) +1) * sizeof(char));
    strcpy(pokemon.name, name);
    pokemon.height = height;
    pokemon.weight = weight;

    return pokemon;
}

void print_pokemon(Pokemon pokemon) {
    printf("Pokemon: %s\n", pokemon.name);
    printf("Pokemon ID: %d\n", pokemon.pokemon_id);
    printf("Pokemon Height: %f\n", pokemon.height);
    printf("Pokemon Weight: %f\n", pokemon.weight);
}
```

Ara podem utilitzar la nostra llibreria:

```c
/*
 * main.c
 */

#include <stdio.h>
#include "pokemon.h"

int main() {
    Pokemon pikachu = create_pokemon(25, "Pikachu", 0.4, 6.0);
    print_pokemon(pikachu);
    return 0;
}
```

Si compilem i executem:

```sh
 gcc -o pokemon pokemon.c main.c
```

```sh
 ./pokemon 
```

Obtindrem el següent resultat, on semblaria que tot funciona correctament:

```sh
Pokemon: Pikachu
Pokemon ID: 25
Pokemon Height: 0.400000
Pokemon Weight: 6.000000
```