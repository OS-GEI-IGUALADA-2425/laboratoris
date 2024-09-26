# Activitats bàsiques amb C

En aquest recull d'activitats resoltes a classe, es presenten una sèrie d'exercicis bàsics per a practicar els conceptes fonamentals de la programació en C.

- `structs`: Estructures de dades.
- `pointers`: Punters i adreces de memòria.
- `arrays`: Matrius i vectors.

1. Quin serà el resultat d'aquesta execució?

    ```c
    #include<stdio.h>
    int main(){

        int x = 5;
        int *p;
        p=&x;
        x++;
        printf("%d\n", *p);
    }
    ```

    **Solució**: La funció main declara una variable `x` de tipus enter amb valor 5. A continuació, declara un punter `p` a un enter i l'assigna a l'adreça de memòria de `x`. Després incrementa el valor de `x` en 1. Finalment, imprimeix el valor al que apunta `p`, que és 6.

    | Adreça | Contingut |
    |--------|-----------|
    |@x      | ~~5~~ 6   |
    |@p      | @x        |

2. Completa el codi següent:

    ```c
    #include <stdio.h>
    int main(){
        const char *s = "";
        char str[] = "Hola";
        s = str;
        while(*s)
            printf("%c", ???);
        return 0;
    }
    ```

    **Solució**:

    ```c
    #include <stdio.h>
    int main(){
    const char *s = "";
    char str[] = "Hola";
    s = str;
    while(*s)
    ~        printf("%c", *s++);
        return 0;
    }
    ~ // Nota: *s++ : Retorna el valor de *s i incrementa la posició de memòria a la que apunta s.
    ```

3. Analitzeu el següent codi i mostreu el contingut de la memòria durant l'execució del programa.

    ```c
    int main(){

        struct pokemon {
            int id;
            char* name;
        };

        struct pokemon p1 = {1, "Bulbasaur"};

        printf("Id: %d\n", p1.id);
        printf("Name: %s\n", p1.name);

    }
    ```

    **Solució**: Aquest codi declara una estructura `pokemon` amb dos camps: un enter `id` i un punter a caràcter `name`. A continuació, declara una variable `p1` de tipus `pokemon` i li assigna l'ID 1 i el nom "Bulbasaur". Finalment, imprimeix l'ID i el nom del Pokémon.

    | Adreça   | Contingut |
    |----------|-----------|
    |@p1       | @p1.id    |
    |@p1.id    | 1         |
    |@p1.name  | @name     |
    |@name     | B         |
    |@name+1   | u         |
    |@name+2   | l         |
    |@name+3   | b         |
    |@name+4   | a         |
    |@name+5   | s         |
    |@name+6   | a         |
    |@name+7   | u         |
    |@name+8   | r         |
    |@name+9   | \0        |

    **Explicació**:

    - La variable p1 ocupa espai en la memòria per emmagatzemar els seus dos components: l'enter id i el punter name.
    - El camp p1.id ocupa una cel·la de memòria que conté el valor 1.
    - El camp p1.name és un punter que apunta a l'adreça on es troba la cadena "Bulbasaur", que es guarda en un altre espai de memòria.
    - La cadena "Bulbasaur" es desa com una seqüència de caràcters que ocupen una cel·la de memòria per cada caràcter, seguit del caràcter nul \0 per indicar el final de la cadena.

4. Analitza el codi següent i digues quin és el resultat de la seva execució.

    ```c
    int main(){
        char * s = "Hola";
        char * t = "Adéu";
        char * u;

        s = t;
        u = strdup(s);

        // Nota: strdup retorna un punter a una nova cadena de caràcters que és una còpia exacta de la cadena de caràcters passada com a argument.

        printf("s: %s\n", s);
        printf("t: %s\n", t);
        printf("u: %s\n", u);
    }
    ```

    **Solució**: Aquest programa declara tres punters a caràcter `s`, `t` i `u`. Inicialitza `s` amb la cadena "Hola" i `t` amb la cadena "Adéu". A continuació, assigna `t` a `s` i fa una còpia de `s` a `u` amb la funció `strdup`. Finalment, imprimeix el contingut de `s`, `t` i `u`.

    El resultat de l'execució del programa és:

    ```bash
    s: Adéu
    t: Adéu
    u: Adéu
    ```

    | Adreça | Contingut |
    |--------|-----------|
    |@s      | ~~h~~ @t|
    |@s+1    | o         |
    |@s+2    | l         |
    |@s+3    | a         |
    |@t      | a         |
    |@t+1    | d         |
    |@t+2    | é         |
    |@t+3    | u         |
    |@u      | @s_copy   |
    |@s_copy | a         |
    |@u+1    | d         |
    |@u+2    | é         |
    |@u+3    | u         |

5. Analitza el codi següent i digues quin és el resultat de la seva execució.

    ```c
    int main(){

        int n = 3;
        char* noms[n];
        char* nom = (char*)malloc(20*sizeof(char));

        for(int i = 0; i < n; i++){
            printf("Introdueix el teu nom: ");
            scanf("%s", nom);
            noms[i] = nom;
        }

        printf("Noms introduïts:\n");
        for(int i = 0; i < n; i++){
            printf("%s\n", noms[i]);
        }

        return 0;
    }
    ```

    **Solució**:

    El resultat de l'execució del programa és: imprimirà l'últim nom introduït `n` vegades. Fixeu-vos que tots els elements de l'array `noms` apunten a la mateixa adreça de memòria, que és la que conté l'últim nom introduït. Ja que estem copiant la mateixa adreça de memòria a tots els elements de l'array, quan modifiquem el contingut de `nom` també ho estem fent per tots els elements de `noms`.

    | Adreça | Contingut   |
    |--------|-------------|
    |@n      | 3           |
    |@noms   | @noms[0]    |
    |@noms[0]  | @nom      |
    |@noms[0]+1|           |
    |@noms[0]+2|           |
    |@noms[1]  |@nom       |
    |@noms[1]+1|           |
    |@noms[1]+2|           |
    |@noms[2]  | @nom      |
    |@noms[2]+1|           |
    |@noms[2]+2|           |
    |@nom    | @nom[0]     |
    |@nom[0] |     J       |
    |@nom[1] |     o       |
    |@nom[2] |     r       |
    |@nom[3] |     \0      |
    | ...    |             |
    |@nom[19]  |           |
   


    Per solucionar aquest error, cal copiar la cadena de caràcters a una nova adreça de memòria per a cada nom introduït. Això es pot fer amb la funció `strdup` o bé reservant memòria amb `malloc` i copiant la cadena amb `strcpy`.

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(){

            int n = 3;
            char* noms[n];
            char* nom = (char*)malloc(20*sizeof(char));

            for(int i = 0; i < n; i++){
                printf("Introdueix el teu nom: ");
                scanf("%s", nom);
                //noms[i] = nom;
                //noms[i] = strdup(nom);
                noms[i] = (char*)malloc(strlen(nom)*sizeof(char));
                strcpy(noms[i], nom);
            }

            printf("Noms introduïts:\n");
            for(int i = 0; i < n; i++){
                printf("%s\n", noms[i]);
            }

            return 0;

        }
    ```

6. Analitza el codi següent i digues quin és el resultat de la seva execució.

    ```c
    #include <stdio.h>
    int main()
    {
        int k = 5;
        int *p = &k;  
        int **m = &p;
        **m = 6;  
        printf("%d\n", k);
    }
    ```

    **Solució**:

    | Adreça | Contingut |
    |--------|-----------|
    |@k      | ~~5~~ 6   |
    |@p      | @k        |
    |@m      | @p        |

    El resultat de l'execució del programa és:

    ```bash
    6
    ```

7. Completa el codi següent:

    ```c
    #include <stdio.h>
    int main() {
        int arr[4] = {1, 2, 3, 4};  

        // ????

        printf("Elements of the array using the pointer:\n");
        for (int i = 0; i < 4; i++) {
            printf("ptr[%d] = %d\n", i, (*ptr)[i]);
        }

        return 0;
    }
    ```

    **Solució**:

    ```c
    #include <stdio.h>
    int main() {
        int arr[4] = {1, 2, 3, 4};  
    ~    int (*ptr)[4] = &arr;

        printf("Elements of the array using the pointer:\n");
        for (int i = 0; i < 4; i++) {
            printf("ptr[%d] = %d\n", i, (*ptr)[i]);
        }

        return 0;
    }
    ```

8. Quin serà el resultat d'aquesta execució?

    ```c
    #include <stdio.h>
    int main()
    {

        int a[5] = {5,1,15,20,25};
        int i,j,m;
        i = ++a[1];
        j = a[1]++;
        m = a[i++];

        printf("%d, %d, %d", i, j,m);
        return 0;
    }
    ```

    **Solució**: El resultat serà `3, 2, 15`. En primer lloc, incrementa `a[1]` de 1 a 2 i assigna 2 a `i`. A continuació, assigna l'actual valor de `a[1]` (que ara és 2) a `j` i incrementa `a[1]` de 2 a 3. Finalment, assigna el valor de `a[2]` (que és 15) a `m` i incrementa `i` de 2 a 3.

    | Adreça | Contingut |
    |--------|-----------|
    |@i      | ~~2~~3    |
    |@j      | 2         |
    |@m      | 15        |

    Fixeu-vos que l'ordre de les operacions és important. Si modifiquem `m = a[++i]` en lloc de `m = a[i++]`, el resultat serà `3, 2, 20`.

9. Quin serà el resultat?

    ```c
    #include <stdio.h>

    void foo(int *p)
    {
        int j = 22;
        p = &j;
        printf("%d ", *p);
    }

    int main()
    {
        int i = 17, *p = &i;
        foo(&i);
        printf("%d ", *p);
    }
    ```

    **Solució**: El resultat serà `22 17`.

    | Adreça | Contingut |
    |--------|-----------|
    |@i           | 17        |
    |@p_main      | @i        |
    |@j           | 22        |
    |@p_foo       | @j        |

    Els valors de `i` i `p` no es veuen afectats per la crida a la funció `foo`, ja que la variable `p` de la funció `foo` és una còpia de la variable `p` de la funció `main`. Això significa que les adreçes del punter p són diferents a cada funció. Si a la funció modifiquem el valor amb `*p=22`, aquest canvi si es veurà reflectit a la funció main.

10. Quina serà la sortida?

    ```c
    #include <stdio.h>
    struct p
    {
        int x;
        int y;
    };

    // sizeof(int) == 2 bytes? 
    // sizeof(int) == 4 bytes? 

    int main()
    {
        struct p p1[] = {
            {1, 92}, 
            {3, 94}, 
            {5, 96}
        };

        int x = (sizeof(p1) / 3);

        printf("%ld\n",sizeof(int));
        
        if (x == 8)
            printf("true\n");
        else
            printf("false\n");
    }
    ```

    **Solució**: La sortida serà `true` si `sizeof(int) == 4 bytes` i `false` si `sizeof(int) == 2 bytes`. Això és degut a que la mida de la variable `p1` és de 24 bytes (3 elements de 8 bytes cada un) i la divisió de 24 entre 3 és 8. En canvi, si `sizeof(int) == 2 bytes`, la mida de la variable `p1` seria de 12 bytes (3 elements de 4 bytes cada un) i la divisió de 12 entre 3 és 4.

11. Crear una matriu dinàmica de m x n elements i mostrar-la per pantalla.

    ```c
    #include <stdio.h>
    #include <stdlib.h>

    int main()
    {
        int ** matrix;
        
        printf("Introdueix el nombre de files i columnes de la matriu: ");
        int files, columnes;
        scanf("%d %d", &files, &columnes);

        matrix = (int **)malloc(files * sizeof(int *));
        for (int i = 0; i < files; i++)
        {
            matrix[i] = (int *)malloc(columnes * sizeof(int));
        }

        for (int i = 0; i < files; i++)
        {
            for (int j = 0; j < columnes; j++)
            {
                printf("Introdueix el valor de la posició (%d, %d): ", i, j);
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Matriu introduïda:\n");
        for (int i = 0; i < files; i++)
        {
            for (int j = 0; j < columnes; j++)
            {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        for (int i = 0; i < files; i++)
        {
            free(matrix[i]);
        }

        free(matrix);

        return 0;
    }
    ```

12. Completa el codi següent:

    ```c
    int main(){
    int (*ptr)();
    return 0;
    }
    ```

    **Solució**: En aquesta funció main, es declara un punter a una funció que retorna un enter. Per assignar una funció a aquest punter, cal declarar una funció amb la mateixa signatura (que retorna un enter i no té arguments) i assignar-la al punter. Per exemple:

    ```c
    int sum(){
        return 5;
    }
    int main(){
    int (*ptr)();
    ptr = sum;
    printf("%d", ptr());
    return 0;
    }
    ```





