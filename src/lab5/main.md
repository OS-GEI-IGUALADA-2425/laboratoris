# Exercicis de C (II)

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

    pikachu.name = malloc(8 * sizeof(char));
    strcpy(pikachu.name, "Pikachu");
    
    printf("Pokemon: %s\n", pikachu.name);
    printf("Pokemon ID: %d\n", pikachu.pokemon_id);
    printf("Pokemon Height: %f\n", pikachu.height);
    printf("Pokemon Weight: %f\n", pikachu.weight);

    free(pikachu.name);

    return 0;
}
```

> **Nota**:
>
> Quan reserveu memòria per una cadena de caràcters recordeu de reservar 1 byte més per el caràcter de final de cadena **'\0'**.

```c
pikachu.name = malloc( (strlen("Pikachu")+1) * sizeof(char) );
```

Ara anem analitzar els següents supòsits:

```c
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

Per poder reutilitzar el codi que hem creat fins ara, podem crear una llibreria que ens permeti fer operacions amb pokemons. Per exemple, podem moure la definició de la nostra estructura de dades **Pokemon** a un fitxer anomenat **pokemon.h** i la implementació de les funcions a un fitxer anomenat **pokemon.c**.

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

```

Ara podem utilitzar la nostra llibreria:

```c
/*
 * main.c
 */

#include <stdio.h>
#include "pokemon.h"

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

Si compilem i executem:

```sh
gcc pokemon.c main.c -o pokemon
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

Què implica moure la definició de la nostra estructura de dades al fitxer d'implementació?

Si movem la definició de la nostra estructura de dades al fitxer d'implementació, el compilador no podrà veure la definició de la nostra estructura de dades quan compili el nostre programa principal. Per fer-ho necessitem definir el tipus de dades **Pokemon** al fitxer **pokemon.h** i la definició dels atributs de la nostra estructura de dades al fitxer **pokemon.c**.

```c
/*
 * pokemon.h
 */

#ifndef _POKEMON_H_
#define _POKEMON_H_

typedef struct pokemon Pokemon;

#endif // _POKEMON_H_
```

```c
/*
 * pokemon.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen(), strcpy()
#include "pokemon.h"

struct pokemon {
    int          pokemon_id;
    char *       name;
    double       height;
    double       weight;
};
```

Ara en el nostre fitxer **main.c** podem utilitzar la nostra llibreria de la següent manera:

```c
/*
 * main.c
 */

#include <stdio.h>
#include "pokemon.h"

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

En aquest punt els atributs de la nostra estructura de dades són privats i no poden ser modificats des de l'exterior. Per tant, necessitem definir **getters** i **setters** per poder accedir i modificar els atributs de la nostra estructura de dades.

```c
/*
 * pokemon.h
 */

#ifndef _POKEMON_H_
#define _POKEMON_H_

typedef struct pokemon Pokemon;

int get_pokemon_id(Pokemon *pokemon);
void set_pokemon_id(Pokemon *pokemon, int pokemon_id);

char * get_name(Pokemon *pokemon);
void set_name(Pokemon *pokemon, char *name);

double get_height(Pokemon *pokemon);
void set_height(Pokemon *pokemon, double height);

double get_weight(Pokemon *pokemon);
void set_weight(Pokemon *pokemon, double weight);

#endif // _POKEMON_H_
```

Observeu que els **setter** reben un punter a la nostra estructura de dades **Pokemon**. Això és perquè volem modificar l'estructura de dades original i no una còpia de l'estructura de dades. En el cas dels **getter** no necessitem modificar l'estructura de dades original, per tant, no necessitem passar un punter però per evitar còpies innecessàries de l'estructura de dades, passem un punter.

```c
/*
 * pokemon.c
 */

#include <stdio.h>

#include "pokemon.h"

struct pokemon {
    int          pokemon_id;
    char *       name;
    double       height;
    double       weight;
};

int get_pokemon_id(Pokemon *pokemon) {
    return pokemon->pokemon_id;
}

void set_pokemon_id(Pokemon *pokemon, int pokemon_id) {
    pokemon->pokemon_id = pokemon_id;
}

char * get_name(Pokemon *pokemon) {
    return pokemon->name;
}

void set_name(Pokemon *pokemon, char *name) {
    strcpy(pokemon->name, name);
}

double get_height(Pokemon *pokemon) {
    return pokemon->height;
}

void set_height(Pokemon *pokemon, double height) {
    pokemon->height = height;
}

double get_weight(Pokemon *pokemon) {
    return pokemon->weight;
}

void set_weight(Pokemon *pokemon, double weight) {
    pokemon->weight = weight;
}
```

Ara podem utilitzar els **getter** i **setter** de la següent manera:

```c
/*
 * main.c
 */

#include <stdio.h>
#include "pokemon.h"

int main() {
    Pokemon pikachu;
    set_pokemon_id(&pikachu, 25);
    set_name(&pikachu, "Pikachu");
    set_height(&pikachu, 0.4);
    set_weight(&pikachu, 6.0);

    printf("Pokemon: %s\n", get_name(&pikachu));
    printf("Pokemon ID: %d\n", get_pokemon_id(&pikachu));
    printf("Pokemon Height: %f\n", get_height(&pikachu));
    printf("Pokemon Weight: %f\n", get_weight(&pikachu));

    return 0;
}
```

El problema ara resideix en `Pokemon pikachu;` ja que no podem crear una instància de la nostra estructura de dades **Pokemon** ja que la definició de la nostra estructura de dades és privada. Per tant, necessitem crear una funció que ens permeti reservar memòria per a la nostra estructura de dades i retornar un punter a la nostra estructura de dades.

```c
/*
 * pokemon.h
 */

#ifndef _POKEMON_H_
#define _POKEMON_H_

typedef struct pokemon Pokemon;

Pokemon * create_pokemon();
void destroy_pokemon(Pokemon *pokemon);

...

#endif // _POKEMON_H_
```

```c

/*
 * pokemon.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen(), strcpy()
#include "pokemon.h"

int BUFFER_SIZE = 10;

Pokemon * create_pokemon() {
    Pokemon *pokemon = malloc(sizeof(Pokemon));
    pokemon->name = malloc(BUFFER_SIZE * sizeof(char));
    return pokemon;
}

void destroy_pokemon(Pokemon *pokemon) {
    free(pokemon->name);
    free(pokemon);
}

...

```

Ara podem utilitzar la nostra llibreria de la següent manera:

```c
/*
 * main.c
 */

#include <stdio.h>
#include "pokemon.h"

int main() {
    Pokemon *pikachu = create_pokemon();
    set_pokemon_id(pikachu, 25);
    set_name(pikachu, "Pikachu");
    set_height(pikachu, 0.4);
    set_weight(pikachu, 6.0);

    printf("Pokemon: %s\n", get_name(pikachu));
    printf("Pokemon ID: %d\n", get_pokemon_id(pikachu));
    printf("Pokemon Height: %f\n", get_height(pikachu));
    printf("Pokemon Weight: %f\n", get_weight(pikachu));

    destroy_pokemon(pikachu);

    return 0;
}
```

Una millora necessària seria redimensionar el camp **name** de la nostra estructura de dades **Pokemon** quan la mida de la cadena sigui més gran o més petita que la mida del buffer. Per fer-ho, podem utilitzar la funció **realloc**.

```c
/*
 * pokemon.c
 */

void set_name(Pokemon *pokemon, char *name) {
    if (strlen(name) != strlen(pokemon->name)) {
        pokemon->name = realloc(pokemon->name, strlen(name) * sizeof(char));
    }
    strcpy(pokemon->name, name);
}
```

Per comprovar que la funció **realloc** funciona correctament, podem fer el següent:

```c
/*
 * main.c
 */

#include <stdio.h>
#include <string.h>
#include "pokemon.h"

int main() {
    Pokemon *p = create_pokemon();
    set_name(p, "Pikachu");

    printf("Pokemon: %s\n", get_name(p));
    printf("Pokemon name size: %ld\n", strlen(get_name(p)));

    set_name(p, "Raichu");

    printf("Pokemon: %s\n", get_name(p));
    printf("Pokemon name size: %ld\n", strlen(get_name(p)));

    set_name(p, "Charizard");

    printf("Pokemon: %s\n", get_name(p));
    printf("Pokemon name size: %ld\n", strlen(get_name(p)));

    destroy_pokemon(p);

    return 0;
}
```

Imagineu que ara voleu guardar una llista o vector de pokemons. Com ho faríeu? Una manera seria crear un vector de punters a la nostra estructura de dades **Pokemon**.

```c
/*
 * main.c
 */

#include <stdio.h>
#include <string.h>
#include "pokemon.h"

int main() {
    Pokemon *pokemons[3];

    pokemons[0] = create_pokemon();
    set_name(pokemons[0], "Pikachu");

    pokemons[1] = create_pokemon();
    set_name(pokemons[1], "Raichu");

    pokemons[2] = create_pokemon();
    set_name(pokemons[2], "Charizard");

    for (int i = 0; i < 3; i++) {
        printf("Pokemon: %s\n", get_name(pokemons[i]));
    }

    for (int i = 0; i < 3; i++) {
        destroy_pokemon(pokemons[i]);
    }

    return 0;
}
```

Podem complicar una mica més el disseny. Ara imagineu que voleu crear una llista dinàmica de pokemons. On un usuari us pot demanar quants pokemon vol introduir i després introduir les dades dels pokemons en temps d'execució. Com ho faríeu?

```c
/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

int main() {
    int n;
    printf("Quants pokemons vols introduir? ");
    scanf("%d", &n);

    Pokemon **pokemons = malloc(n * sizeof(Pokemon *));
    int id;
    char* name = malloc(100 * sizeof(char));
    double height, weight;



    for (int i = 0; i < n; i++) {
        pokemons[i] = create_pokemon();

        printf("Introdueix les seves dades en format: id nom altura pes\n");
        scanf("%d %s %lf %lf", &id, name, &height, &weight);

        set_pokemon_id(pokemons[i], id);
        set_name(pokemons[i], name);
        set_height(pokemons[i], height);
        set_weight(pokemons[i], weight);
        
    }

    free(name);

    for (int i = 0; i < n; i++) {
        printf("Pokemon Name: %s\n", get_name(pokemons[i]));
        printf("Pokemon ID: %d\n", get_pokemon_id(pokemons[i]));
        printf("Pokemon Height: %f\n", get_height(pokemons[i]));
        printf("Pokemon Weight: %f\n", get_weight(pokemons[i]));
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        destroy_pokemon(pokemons[i]);
    }

    free(pokemons);

    return 0;
}
```

D'aquesta manera podem crear una llista dinàmica de pokemons i introduir les dades dels pokemons en temps d'execució. Per exemple:

```sh
Quants pokemons vols introduir? 3
Introdueix les seves dades en format: id nom altura pes
25 Pikachu 0.4 6.0
Introdueix les seves dades en format: id nom altura pes
26 Raichu 0.8 30.0
Introdueix les seves dades en format: id nom altura pes
27 Sandshrew 0.6 12.0
```
