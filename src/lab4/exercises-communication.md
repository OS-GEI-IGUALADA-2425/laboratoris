# Exercicis de Comunicació i Sincronització de Processos

En aquesta secció trobareu els exercicis resolts realitzats i explicats a l'aula. Aquests exercicis tracten sobre la comunicació i sincronització de processos en C. Utilitzarem les crides al sistema `fork()`, `pipe()`, `wait()`, `kill()`, `signal()`, `alarm()`, `execlp()`, `open()`, `close()`, `dup()`, `read()`, `write()`, `mkfifo()` i `unlink()`.

1. Analitza el següent programa i digues quants senyals s'envien i quants es reben. Què fa el programa?

    ```c
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <signal.h>
    #include <sys/wait.h>

    int n_sigchld=0;
    int n_sigalarm=0;
    char msg [200];

    void cont1(){ n_sigchld=n_sigchld+1;}
    void cont2(){ n_sigalarm=n_sigalarm+1;}

    int main(){

        signal(SIGCHLD, cont1);
        signal(SIGALRM, cont2);

        int id = fork();
        if(id == 0){
            alarm(5);
            while(n_sigalarm==0);
            sprintf(msg,"FILL -> SIGSTOP:1 SIGCONT:1 SIGALARM:%d SIGCHLD:%d TOTAL:%d\n", 
                n_sigalarm, n_sigchld, 1+1+n_sigalarm+n_sigchld );
            write(1,msg,strlen(msg));
            exit(1);
        } else {
            kill(id, SIGSTOP);
            alarm(5);
            while(n_sigalarm==0);
            kill(id, SIGCONT);
            wait(NULL);

            sprintf(msg,"PARE -> SIGALARM:%d SIGCHLD:%d TOTAL:%d\n",
                n_sigalarm, n_sigchld, n_sigalarm+n_sigchld );
            write(1,msg,strlen(msg));
            exit(0);
        }
    }
    ```

    **Resposta:**

    Aquest programa crea un fill. Els dos processos tenen dos rutines de tractament de senyals, `cont1` i `cont2`, que incrementen dues variables globals `n_sigchld` i `n_sigalarm` respectivament. El fill s'adorm amb una alarma de 5. El pare enviara un senyal `SIGSTOP` al fill i també s'adorm amb una alarma de 5. Quan el fill adormit rep el senyal `SIGSTOP` actualitza el seu estat a parat. Això provoca que el pare rebi un senyal `SIGCHLD`. Un cop passen 5 segons el pare rep un senyal `SIGALARM` i continua la seva execució. En aquest moment envia un senyal `SIGCONT` al fill. Això fa que el fill retorni de l'estat parat a l'estat d'execució. En aquest punt, es genera un nou senyal `SIGCHLD` que el pare tracta. El pare espera a que el fill acabi on es notifica amb una `SIGCHLD`. Els dos processos mostren per pantalla el nombre de senyals rebuts.

    El pare envia 2 senyals (`SIGSTOP` i `SIGCONT`) i rep 3 senyals (`SIGCHLD`), el fill envia 3 senyal (`SIGCHLD`) mostrant els canvis d'estat:

    - *running* a *stopped*
    - *stopped* a *running*
    - *running* a *terminated*.

    A més a més, pare i fill s'envien i reben un senyal `SIGALARM` cada un.

2. Analitza el programa següent i indica la evolució de la taula de descriptors oberts de cada fitxer. Explica què fa el programa.

    ```c
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <fcntl.h>

    int main(){
        int fd;
        int pipefd[2];
        char msg[200];
        char buffer[200];

        fd = open("fitxer.txt", O_RDONLY);
        pipe(pipefd);

        if(fork() == 0){
            close(1);
            close(pipefd[0]);
            write(4, "Hola", 4);
            while(1);
            exit(0);
        }

        else{
            close(pipefd[1]);
            read(pipefd[0], buffer, 4);
            sprintf(msg, "PARE -> %s\n", buffer);
            write(1, msg, strlen(msg));
            wait(NULL);
            exit(0);
        }
    }
    ```

    **Resposta**

    Aquesta implementació funcionarà si `fitxer.txt` no existeix. Ja que el descriptor de fitxer associat a la escriptura de la pipe serà **4**. Ara bé, si el fitxer existeix, el descriptor de fitxer associat a la escriptura de la pipe serà **5** i llavors el programa no funcionarà ja que el descriptor de fitxer **5** no està obert. Podem fer aquestes comprovacions amb la comanda `lsof`:

    ```bash
    lsof -p <pid>
    # on <pid> és el pid del procés
    ```

    El programa obre un fitxer en mode lectura i crea una pipe. Crea un fill que escriu "Hola" en el descriptor de fitxer **4** i es queda en un bucle infinit. El pare llegeix del descriptor de fitxer 0 de la pipe i escriu el que ha llegit en el descriptor de fitxer 1. El pare espera a que el fill acabi.

    Si el fitxer no existeix:

    - **Procés pare** 

       | Descriptor | Fitxer |
       |------------|--------|
       | 0          | stdin  |
       | 1          | stdout |
       | 2          | stderr |
       | 3          | pipefd[0] |
       | 4          | ~pipefd[1]~ |

    - **Procés fill**:

        | Descriptor | Fitxer |
        |------------|--------|
        | 0          | stdin  |
        | 1          | ~stdout~ |
        | 2          | stderr |
        | 3          | ~pipefd[0]~ |
        | 4          | pipefd[1] |

    En canvi, si el fitxer existeix:

    - **Procés pare:**

        | Descriptor | Fitxer |
        |------------|--------|
        | 0          | stdin  |
        | 1          | stdout |
        | 2          | stderr |
        | 3          | fitxer.txt |
        | 4          | pipefd[0] |
        | 5          | ~pipefd[1]~ |

    - **Procés fill**:

        | Descriptor | Fitxer |
        |------------|--------|
        | 0          | stdin  |
        | 1          | ~stdout~ |
        | 2          | stderr |
        | 3          | fitxer.txt |
        | 4          | ~pipefd[0]~ |
        | 5          | pipefd[1] |

3. Implementa amb c la comanda següent utilitzant 2 fills i un pare. Per recobrir heu de fer servir **obligatòriament** les crides:

    - `execlp("grep", "grep", "root", NULL)`
    - `execlp("cat", "cat", NULL)`

    ```bash
    cat < /etc/passwd | grep root
    ```

    **Resposta:**

    ```c
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <fcntl.h>

    int main(){
        int pipefd[2];
        char msg[200];
        char buffer[200];

        pipe(pipefd);

        if(fork() == 0){
            close(0);
            dup(pipefd[0]);
            close(pipefd[0]);
            close(pipefd[1]);
            execlp("grep", "grep", "root", NULL);
            exit(0);
        }

        if(fork() == 0){
            close(0);
            open("/etc/passwd", O_RDONLY);
            close(pipefd[0]);
            close(1);
            dup(pipefd[1]);
            close(pipefd[0]);
            close(pipefd[1]);
            execlp("cat", "cat", NULL);
            exit(0);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
        exit(0);

    }
    ```

4. En el programa anterior el filtre és estàtic, com podriam modificar el codi anterior per tenir un filtre dinàmic. 

    ```bash
    ./ex4 filtre
    ```

    **Resposta:**

    ```c
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <fcntl.h>

    int main(int argc, char *argv[]){
        int pipefd[2];
        char msg[200];
        char buffer[200];

        pipe(pipefd);

        if(fork() == 0){
            close(0);
            dup(pipefd[0]);
            close(pipefd[0]);
            close(pipefd[1]);
            execlp("grep", "grep", argv[1], NULL);
            exit(0);
        }

        if(fork() == 0){
            close(0);
            open("/etc/passwd", O_RDONLY);
            close(pipefd[0]);
            close(1);
            dup(pipefd[1]);
            close(pipefd[0]);
            close(pipefd[1]);
            execlp("cat", "cat", NULL);
            exit(0);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
        exit(0);

    }
    ```

5. Implementació d'un simulador **escape room** amb un únic candau. El programa pare rebrà per parametres el temps de la partida, el nombre de jugadors i la clau de 4 xifres que els jugadors hauran d'acceptar. Els jugadors es comunicaran amb el pare utilitzant 1 única pipe. El pare i el fill s'implementaran en dos fitxers diferents.

    ![Escape Room](figures/disseny.png)

    - Implementació del fitxer `jugador.c`:

    ```c
    #include <time.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <signal.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <errno.h>

    void end_handler(); 
    void end_handler(){
        exit(0);
    }

    int main()
    {
        signal(SIGUSR1, end_handler);

        int n = 4;
        char pass[n];

        time_t t;
        time(&t);
        srand(t + getpid());

        int i = 0;
        while(1){
        for(i = 0; i < n; i++) {
            pass[i] = 'A' + rand() % 62;
        }
        write(1,pass,n);
        }
        
    }
    ```

    - Implementació del fitxer `pare.c`:

    ```c
    #include <stdlib.h>
    #include <stdio.h>
    #include <signal.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <errno.h>

    int atrapats = 0;
    int jugant = 1;

    char *color_blue   = "\033[01;34m";
    char *color_end    = "\033[00m";
    char *color_red    = "\033[01;31m";
    char *color_green  = "\033[01;32m";

    char *args[] = {"jugador", "jugador", NULL};

    void alarm_handler(); 

    void alarm_handler(){
        char s[100];
        sprintf(s, "%s**********DING DONG %s\n", color_red,color_end);
        write(1,s,strlen(s));
        atrapats=1;
        jugant=0;
    }

    int main(int argc, char *argv[])
    {
        int fd[2];
        char s[100];
        

        if (argc < 4) {
            fprintf(stderr, "Usage: %s tempsPartida numJugadors clau \n", argv[0]);
            exit(1);
        }

        int numJugadors = atoi(argv[2]);
        int tempsPartida = atoi(argv[1]);
        char* clau = malloc(4 * sizeof(char));
        strcpy(clau, argv[3]);

        int* pids = malloc(numJugadors * sizeof(int));

        signal(SIGALRM, alarm_handler);

        if (pipe(fd)<0)
        {
            perror("Error de creació del pipe");
            exit(1);
        }
        
        sprintf(s, "Inici del Room Escape [%d] (%d segons)\n",getpid(),tempsPartida);
        if (write(1, s, strlen(s)) < 0) perror("write");

        sprintf(s, "--- Entren %d jugadors a la sala\n",numJugadors);
        if (write(1, s, strlen(s)) < 0) perror("write");

        sprintf(s, "--- La paraula a endevinar és = %s\n",clau);
        if (write(1, s, strlen(s)) < 0) perror("write");

        for(int i = 0; i<numJugadors; i=i+1){

            switch (pids[i]=fork()){

            case -1:
                perror("Error creació pipe");
                exit(2);
                break;
                        
            case 0:	
                if (close(fd[0]) < 0) perror("close");
                if (dup2(fd[1], 1) < 0) perror("dup2");
                if (close(fd[1]) < 0) perror("close");
                        
                execv(args[0], args);
                exit(-1);
        
            default:
                sprintf(s, "%s EscapeRoom[%d] ha entrat el jugador[%d] %s\n",
                    color_blue, getpid(), pids[i], color_end);
                if (write(1, s, strlen(s)) < 0) perror("write");
            }
        }

        close(fd[1]);
        alarm(tempsPartida);
        

        char buff[4];
                    
        while( (jugant==1) &&
                    (read(fd[0],&buff,sizeof(buff))>0) )
        {
            if (strncmp(buff,clau,4) == 0){
                    sprintf(s,"--- Els jugadors obren el candau amb la clau %s\n",clau);
                    write(1,s,strlen(s));
                    jugant=0;
                    break;
                }
        }
                

        for(int i = 0; i<numJugadors; i++){
            if (atrapats==1){
                sprintf(s, "%s El jugador [%d] ha quedat atrapat i surt de EscapeRoom[%d].%s\n",
                    color_red, pids[i],getpid(), color_end);
                if (write(1, s, strlen(s)) < 0) perror("write");
            }
            else{
                sprintf(s, "%s El jugador [%d] ha escapat i surt de EscapeRoom[%d].%s\n",
                    color_green, pids[i],getpid(), color_end);
                if (write(1, s, strlen(s)) < 0) perror("write");
            }
            kill(pids[i], SIGUSR1);
            wait(0);
        }

        if (atrapats==1){
            sprintf(s, "--- El jugadors han perdut la partida. Fins aviat.\n");
            if (write(1, s, strlen(s)) < 0) perror("write");
        }
        else {
            sprintf(s, "--- El jugadors ha guanyat la partida en %d segons.\n", tempsPartida - alarm(tempsPartida));
            if (write(1, s, strlen(s)) < 0) perror("write");
        }

        close(fd[0]);
        free(clau);
        free(pids);
        exit(0);
    }
    ```

    - Makefile: Per compilar els dos fitxers anteriors, es pot fer servir el següent `Makefile`:

    ```makefile
    all: sala jugador

    sala: sala.o
        gcc sala.o -o sala

    sala.o: sala.c
        gcc -c sala.c -o sala.o

    jugador: jugador.o
        gcc jugador.o -o jugador

    jugador.o: jugador.c
        gcc -c jugador.c -o jugador.o

    clean:
        rm -r jugador jugador.o sala sala.o

    test:
        ./sala 60 5 AAAA

    run:
        ./sala $(ARGS)
    ```

    **Sortida de l'execució**:

    ![Escape Room](figures/victoria.png)

    ![Escape Room](figures/derrota.png)

6. Introdueix un *ou de pascua* en el programa anterior. Es crearà un *fifo* enlloc de la *pipe*. D'aquesta manera, un altre procés podrà enviar la clau correcta al pare.

    ```c
    #include <stdlib.h>
    #include <stdio.h>
    #include <signal.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <errno.h>
    #include <fcntl.h>

    int atrapats = 0;
    int jugant = 1;

    char *color_blue   = "\033[01;34m";
    char *color_end    = "\033[00m";
    char *color_red    = "\033[01;31m";
    char *color_green  = "\033[01;32m";

    char *args[] = {"jugador", "jugador", NULL};

    void alarm_handler(); 

    void alarm_handler(){
        char s[100];
        sprintf(s, "%s**********DING DONG %s\n", color_red,color_end);
        write(1,s,strlen(s));
        atrapats=1;
        jugant=0;
    }

    int main(int argc, char *argv[])
    {
        char s[100];
        
        if (argc < 4) {
            fprintf(stderr, "Usage: %s tempsPartida numJugadors clau \n", argv[0]);
            exit(1);
        }

        int numJugadors = atoi(argv[2]);
        int tempsPartida = atoi(argv[1]);
        char* clau = malloc(4 * sizeof(char));
        strcpy(clau, argv[3]);
        int* pids = malloc(numJugadors * sizeof(int));

        signal(SIGALRM, alarm_handler);

        if (mkfifo("myfifo", 0666) < 0) {
            perror("Error al crear el pipe");
            exit(1);
        }

        int fd = open("myfifo", O_RDWR);

        sprintf(s, "Inici del Room Escape [%d] (%d segons) \n",getpid(),tempsPartida);
        if (write(1, s, strlen(s)) < 0) perror("write");

        sprintf(s, "--- Entren %d jugadors a la sala \n",numJugadors);
        if (write(1, s, strlen(s)) < 0) perror("write");

        sprintf(s, "--- La paraula a endevinar és = %s\n",clau);
        if (write(1, s, strlen(s)) < 0) perror("write");

        for(int i = 0; i<numJugadors; i=i+1){

            switch (pids[i]=fork()){

            case -1:
                perror("Error creació pipe");
                exit(2);
                break;
                        
            case 0:
                if (dup2(fd, 1) < 0) perror("dup2");
                execv(args[0], args);
                exit(-1);
        
            
            default:
                sprintf(s, "%s EscapeRoom[%d] ha entrat el jugador[%d] %s\n", 
                    color_blue, getpid(), pids[i], color_end);
                if (write(1, s, strlen(s)) < 0) perror("write");
            }
        }

        alarm(tempsPartida);
        char buf[4];
                
        while( (jugant==1) &&
                (read(fd,&buf,sizeof(buf))>0) )
        {
            if (strncmp(buf,clau,4) == 0){
                sprintf(s,"--- Els jugadors obren el candau amb la clau %s \n",clau);
                write(1,s,strlen(s));
                jugant=0;
                break;
                }
        }
                

        for(int i = 0; i<numJugadors; i++){
            if (atrapats==1){
                sprintf(s, "%s El jugador [%d] ha quedat atrapat i surt de EscapeRoom[%d]. %s\n", 
                    color_red, pids[i],getpid(), color_end);
                if (write(1, s, strlen(s)) < 0) perror("write");
            }
            else{
                sprintf(s, "%s El jugador [%d] ha escapat i surt de EscapeRoom[%d]. %s\n", 
                    color_green, pids[i],getpid(), color_end);
                if (write(1, s, strlen(s)) < 0) perror("write");
            }
            kill(pids[i], SIGUSR1);
            wait(0);
        }

        if (atrapats==1){
            sprintf(s, "--- El jugadors han perdut la partida. Fins aviat. \n");
            if (write(1, s, strlen(s)) < 0) perror("write");
        }
        else {
            sprintf(s, "--- El jugadors ha guanyat la partida en %d segons. \n", 
                tempsPartida - alarm(tempsPartida));
            if (write(1, s, strlen(s)) < 0) perror("write");
        }

        close(fd);
        unlink("myfifo");
        
        free(clau);
        free(pids);

        exit(0);
    }
    ```

Per executar l'ou de pascua, s'ha de fer el següent:

```bash
echo "AAAA" > myfifo
```

![Fifos](figures/fifos.png)

> 👁️ **Observació**:
>
> Aquesta solució amb fifos permet a qualsevol procés del sistema enviar la clau correcta al pare. Mentre que amb pipes només poden ser els fills els que envien la clau correcta.
