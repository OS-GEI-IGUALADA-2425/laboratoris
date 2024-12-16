# Programació de Scripts (BASH)

## Sintaxi bàsica

Un script **Bash** és un conjunt de comandes emmagatzemat en un fitxer de text amb l'extensió *.sh*. Aquest script es pot executar com un programa per mitjà de la línia de comandes. Els paràmetres es passen a l'script mitjançant les variables especials $1, $2, etc., on $1 és el primer paràmetre, $2 és el segon, i així successivament.

```bash
if [ $# -ne 2 ]; then
    echo "Usage: $0 <dir> <ext>"
    exit 1
fi
```

En aquest fragment, **$#** representa el nombre total de paràmetres passats. L'estructura if verifica si el nombre de paràmetres és diferent de 2. En aquest cas, mostra un missatge d'ús i acaba amb un codi d'error. L'estructura **$0** representa el nom del programa.

## Activitat 01: Calculadora

En aquesta activitat, implementarem una calculadora que ens permeti sumar, restar, multiplicar i dividir dos nombres enters. Per això, crearem un script anomenat **calc.sh**. Aquest script rep dos paràmetres i una opció. Els dos paràmetres són els dos nombres enters i l'opció és l'operació que volem realitzar. Aquest script mostrarà el resultat de l'operació per pantalla.

```bash
#!/bin/bash
# Nom: calc.sh

if [ $# -ne 3 ]; then
    echo "Usage: $0 <num1> <num2> <op>"
    exit 1
fi

num1=$1
num2=$2
op=$3

case $op in
    "sum")
        echo "$num1 + $num2 = $((num1+num2))"
        ;;
    "sub")
        echo "$num1 - $num2 = $((num1-num2))"
        ;;
    "mul")
        echo "$num1 * $num2 = $((num1*num2))"
        ;;
    "div")
        echo "$num1 / $num2 = $((num1/num2))"
        ;;
    *)
        echo "Error: $op is not a valid operation"
        exit 1
        ;;
esac
```

Aquest script utilitza la sentència `case`. Aquesta sentència ens permet avaluar una variable i executar una acció en funció del valor d'aquesta variable. En aquest cas, la variable és **$op** i l'acció és mostrar el resultat de l'operació.

Aquest script es pot executar de la següent manera:

```bash
bash calc.sh 2 3 sum
# Resultat: 2 + 3 = 5
```

Ara millorarem aquest script per assegurar-nos que els paràmetres que rep són enters. Per això, utilitzarem la comanda `expr`. Aquesta comanda ens permet avaluar una expressió. La comanda `expr "$1" + 1` intenta avaluar l'expressió aritmètica **$1 + 1**. Si *$1* no és un enter, això generaria un error, que redirigim a **/dev/null**. Aquest procés es repeteix per al segon paràmetre.

```bash
#!/bin/bash

if ! expr $1 + 1 &> /dev/null || ! expr $2 + 1 &> /dev/null; then
    echo "Error: $1 or $2 is not an integer"
    exit 1
fi
```

Podem utilitzar una expressió regular per comprovar si els paràmetres són enters. Per exemple, per comprovar si el paràmetre $1 és un enter:

```bash
if [[ ! "$1" =~ ^[0-9]+$ ]] || [[ ! "$2" =~ ^[0-9]+$ ]]; then
    echo "Error: $1 or $2 is not an integer"
    exit 1
fi
```

Per avaluar expressions regular en bash es requereix **[[ var =~regex ]]**. L'expressió regular **^[0-9]+$** indica que la cadena ha de contenir només dígits (0-9) i res més. Si alguna cosa diferent d'un enter es troba, llavors mostrarà un missatge d'error i sortirà amb un codi d'error.

Notes sobre expressions regulars:

- El caràcter *^*, això fixa l'expressió a l'inici d'una línia.
- La expressió *[0-9]+*, això coincideix amb almenys un caràcter del conjunt 0-9 -> 1 o més caràcters del rang 0-9.
- La expressió *.+*, això coincideix com a mínim amb un caràcter de qualsevol tipus.
- La expressió *[0-9]*, coincideix amb un sol dígit.
- El caràcter *?*, assegura 0 o 1 de l'expressió anterior.
- El caràcter *$*, això fixa l'expressió al final de la línia.

Anem a millorar aquest script perquè ens permeti realitzar operacions amb nombres decimals. Per això, utilitzarem la comanda `bc`. Aquesta comanda ens permet avaluar expressions aritmètiques. Per exemple, per avaluar l'expressió aritmètica **2.5 + 3.5**:

```bash
echo "2.5 + 3.5" | bc
# Resultat: 6.0
```

Modifiquem el script anterior perquè ens permeti realitzar operacions amb nombres decimals. Per això, utilitzarem la comanda `bc`. Aquesta comanda ens permet avaluar expressions aritmètiques. Per exemple, per avaluar l'expressió aritmètica **2.5 + 3.5**:

```bash
#!/bin/bash
# Nom: calc.sh

if [ $# -ne 3 ]; then
    echo "Usage: $0 <num1> <num2> <op>"
    exit 1
fi

num1=$1
num2=$2
op=$3

if [[ ! "$1" =~ ^[0-9]+\.?[0-9]*$ ]] || [[ ! "$2" =~ ^[0-9]+\.?[0-9]*$ ]]; then
    echo "Error: $1 or $2 is not a number"
    exit 1
fi

case $op in
    "sum")
        echo "$num1 + $num2 = $(echo "$num1 + $num2" | bc)"
        ;;
    "sub")
        echo "$num1 - $num2 = $(echo "$num1 - $num2" | bc)"
        ;;
    "mul")
        echo "$num1 * $num2 = $(echo "$num1 * $num2" | bc)"
        ;;
    "div")
        echo "$num1 / $num2 = $(echo "$num1 / $num2" | bc)"
        ;;
    *)
        echo "Error: $op is not a valid operation"
        exit 1
        ;;
esac
```

## Activitat 02: Convertint format de fitxers

Assumiu que heu fet una còpia de la base de dades i teniu un fitxer anomenat **series.db**. Aquest fitxer conté una llista de sèries de televisió, personatges i les seves frases. El format d'aquest fitxer és el següent:

```bash
Friends:Monica:Welcome to the real world. It sucks. You’re gonna love it!
Friends:Janice:Oh… my… God!
Friends:Rachel:How long do cats live? Like assuming you don’t throw ‘em under a bus or something?
Friends:Ross:You know how you come home at the end of the day and throw your jacket on a chair?
Friends:Joey:Yeah.
Friends:Ross:Well, instead of a jacket, it’s a pile of garbage. And instead of a chair, it’s a pile of garbage. And instead of the end of the day, it’s the end of time and garbage is all that has survived.
Friends:Rachel:Guys, guess what?!
Friends:Chandler:Ok, the fifth dentist caved and now they’re ALL recommending Trident?
Friends:Chandler:WHOOOPAH!
Friends:Joey:Sure I peed on her. And if I had to, I’d pee on any one of you!
Friends:Phoebe:He must decide. He must decide. Even though I made him up, he must decide!
Friends:Joey:Here come the meat sweats…
Friends:Ross:Wow, you guys sure have a lot of books about being a lesbian.
Friends:Susan:Well, you know, you have to take a course. Otherwise they don’t let you do it.
Friends:Chandler:All right, kids, I gotta get to work. If I don’t input those numbers… it doesn’t make much of a difference.
Friends:Joey:Well, I’m sorry if I’m not a middle-aged black woman. And I’m also sorry if sometimes I go to the wrong audition.
Friends:Joey:Hey, Ross, I got a science question: If the homo sapiens were, in fact, HOMO sapiens…is that why they’re extinct?”
Friends:Ross:Joey, homo sapiens are PEOPLE.
Friends:Joey:Hey, I’m not judgin’!
Friends:Phoebe:Come on Ross, you’re a paleontologist, dig a little deeper.
BigBangTheory:Sheldon:Scissors cuts paper, paper covers rock, rock crushes lizard, lizard poisons Spock, Spock smashes scissors, scissors decapitates lizard, lizard eats paper, paper disproves Spock, Spock vaporizes rock, and as it always has, rock crushes scissors.
BigBangTheory:Sheldon:Why are you crying? 
BigBangTheory:Penny:Because I'm stupid. 
BigBangTheory:Sheldon:That's no reason to cry. One cries because one is sad. For example, I cry because others are stupid, and that makes me sad.
BigBangTheory:Raj:I don't like bugs, okay. They freak me out.
BigBangTheory:Sheldon:Interesting. You're afraid of insects and women. Ladybugs must render you catatonic.
BigBangTheory:Leonard:You'll never guess what just happened.
BigBangTheory:Sheldon:You went out in the hallway, stumbled into an inter-dimensional portal, which brought you 5,000 years into the future, where you took advantage of the advanced technology to build a time machine, and now you're back, to bring us all with you to the year 7010, where we are transported to work at the think-a-torium by telepathically controlled flying dolphins? 
BigBangTheory:Leonard:No. Penny kissed me.
BigBangTheory:Sheldon:Who would ever guess that?
```

Us demano que implementeu un script que transformi el fitxer **series.db** en un output estructura per serie, personatge i les seves frases. Per exemple:

```bash
+ Serie
 - Character: 
    * Quote
    * ...
 - Character:
    * ...
+ Serie
    - Character: 
        * Quote
        * ...
    - Character:
        * ...
```

> **Nota:** No es pot fer servir la comanda `awk` per aquesta activitat.

## Activitat 03: Fàbrica de processos

Ara implementarem un script que ens permeti comprovar si existeix un altre procés en execució amb el mateix nom però PID diferent executant-se en el sistema. En cas afirmatiu, el script ha de mostrar un missatge d'error i acabar amb un codi d'error. 

La comanda `pidof` ens permet obtenir el PID d'un procés a partir del seu nom. Per exemple, per obtenir el PID del procés `bash`:

```bash
pidof bash
```

```bash
sleep 120 &; pidof sleep
# Resultat: 1234
```

La comanda `basename` ens permet obtenir el nom d'un fitxer a partir de la seva ruta. Per exemple, per obtenir el nom del fitxer `/home/user/file.txt`:

```bash
basename /home/user/file.txt
# Resultat: file.txt
```

Per tant, si obtenim un PID a partir del nom del programa (basename $0) i el nombre de PID és major que 1, llavors ja existeix un procés en execució amb el mateix nom. El següent script implementa aquesta funcionalitat:

```bash
#!/bin/bash
# Nom: check_process.sh

if [ $# -ne 1 ]; then
    echo "Usage: $0 <name>"
    exit 1
fi

name=$1

if [ $(pidof $(basename $0) | wc -w) -gt 1 ]; then
    echo "Error: Existeix un procés anomenat $name en execució. El seu PID és $(pidof $(basename $0))."
    exit 1
fi
```

Ara crearem un altre script que farà un bucle infinit. Per exemple:

```bash
#!/bin/bash
# Nom: bucle_infinit.sh

while : ; do
    echo "Press [CTRL+C] to stop.."
    sleep 1
done
```

Aquest script es pot executar en background. Per exemple:

```bash
bash bucle_infinit.sh &
```

Ara podem utiltizar el script `check_process.sh` per comprovar si existeix un procés en execució amb el mateix nom. Per exemple:

```bash
bash check_process.sh bucle_infinit.sh
# Resultat: Error: Existeix un procés anomenat bucle_infinit.sh en execució. El seu PID és 1234.
```

Podem millorar el script `check_process.sh` perquè ens permeti eliminar el procés en execució. Per això, utilitzarem la comanda `kill`.

```bash
#!/bin/bash
# Nom: check_process.sh

if [ $# -ne 1 ]; then
    echo "Usage: $0 <name>"
    exit 1
fi

name=$1
pid=`pidof $(basename $0)`

if [ $(pid | wc -w) -gt 1 ]; then
        echo "[ERROR]: Aquest script ja s’esta executant amb pid $pid"
        kill $pid
        echo "[INFO]: S’ha eliminat el procés $pid"
    fi
    exit 1
fi
```

Ara farem un nou script que ens permeti crear **N** processos en execució al background. Aquest processos faran un sleep d'un nombre aleatori de segons i després acabaran. El procés pare esperarà que els fills acabin i mostrarà l'estat d'acabament de cada procés fill.

```bash
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1
declare -i completed=0
declare -i failed=0
declare -a pids

for ((i=0; i<$n; i++)); do
    sec=$((RANDOM % 10))
    sleep $sec &
    pids[$i]=$!
    printf "Process %d with pid %d will sleep for %d seconds\n" $i ${pids[$i]} $sec
done

for pid in ${pids[@]}; do
    wait $pid
    status=$?
    echo "Process $pid finished with status $status"
    
    if [ $status -eq 0 ]; then
        completed=$((completed+1))
    else
        failed=$((failed+1))
    fi
done

echo "Completed: $completed"
echo "Failed: $failed"
```

Per causar un error en un procés, el pare pot matar un procés fill. Per això, utilitzarem la comanda `kill`. Per exemple, per matar el procés fill amb PID 1234:

```bash

#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1
declare -i completed=0
declare -i failed=0
declare -a pids

for ((i=0; i<$n; i++)); do
    sec=$((RANDOM % 10))
    sleep $sec &
    pids[$i]=$!
    printf "Process %d with pid %d will sleep for %d seconds\n" $i ${pids[$i]} $sec
done

# Matarem un procés fill
target=$((RANDOM % 9))
kill ${pids[$target]}

for pid in ${pids[@]}; do
    wait $pid
    status=$?
    echo "Process $pid finished with status $status"
    
    if [ $status -eq 0 ]; then
        completed=$((completed+1))
    else
        failed=$((failed+1))
    fi
done

echo "Completed: $completed"
echo "Failed: $failed"
```

Podem millorar aquest script implementant diferents funcions. Per exemple, una funció per crear els processos fills, una funció per esperar que els processos fills acabin i una funció per mostrar l'estat d'acabament de cada procés fill. El següent script implementa aquestes funcions:

```bash
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <n>"
    exit 1
fi

n=$1

declare -i completed=0
declare -i failed=0
declare -a pids

function create_processes() {
    for ((i=0; i<$n; i++)); do
        sec=$((RANDOM % 10))
        sleep $sec &
        pids[$i]=$!
        printf "Process %d with pid %d will sleep for %d seconds\n" $i ${pids[$i]} $sec
    done
}

function wait_processes() {
    for pid in ${pids[@]}; do
        wait $pid
        status=$?
        echo "Process $pid finished with status $status"
        
        if [ $status -eq 0 ]; then
            completed=$((completed+1))
        else
            failed=$((failed+1))
        fi
    done
}

function show_status() {
    echo "Completed: $completed"
    echo "Failed: $failed"
}

create_processes
wait_processes
show_status
```

## Activitat 04: Suma de nombres

Analitzeu el codi següent i digueu quin és el resultat de l'execució d'aquest script. Raoneu la resposta. Indicant per que el resultat és diferent del que s'espera.

```bash
#!/bin/bash
# Nom: ch01.sh

cat > ch01.data << 'EOT'
102
071
210
153
EOT

clear
cat ch01.data
declare -i SUM=0

while read X; do
    SUM+=$X
done < ch01.data

echo "Suma: $SUM != 536"
rm -f ch01.data
```

<details>
<summary>Resposta</summary>

El resultat de l'execució d'aquest script és el següent:

```bash
102
071
210
153
Suma: 522 != 536
```

El resultat és diferent del que s'espera perquè el nombre 071 no és un nombre decimal. Aquest nombre és un nombre octal. Per tant, el resultat de la suma és 522 i no 536. En bash, els nombres que comencen per 0 són nombres octals. Per exemple, el nombre 071 en octal és el nombre 57 en decimal. Per tant, el resultat de la suma és 522 i no 536.

Per assegurar-nos que els nombres que llegim són nombres decimals, podem utilitzar la comanda `bc`. Aquesta comanda ens permet avaluar expressions aritmètiques. Per exemple, per avaluar l'expressió aritmètica **071**:

```bash
echo "071" | bc
# Resultat: 71
```

Per tant, podem millorar el script anterior de la següent manera:

```bash
#!/bin/bash
# Nom: ch01.sh

cat > ch01.data << 'EOT'
102
071
210
153
EOT

clear
cat ch01.data
declare -i SUM=0

while read X; do
    SUM+=$(echo "$X" | bc)
done < ch01.data

echo "Suma: $SUM != 536"
rm -f ch01.data
```

</details>

Aquest exemple s'ha adaptat del Llibre **Bash It Out** de Sylvain Leroux. Podeu trobar més informació amb [FOSS Linux Blog](https://itsfoss.com).