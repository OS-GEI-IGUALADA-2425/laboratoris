# Problemes de Planificació de Processos

En aquests problemes assumirem les següents convencions:

- El cost de canvi de context és de 0, si no s'indica el contrari.
- Els processos es poden trobar en el següents estats: <span style="color:blue">Preparat</span>, <span style="color:orange">Espera</span>, <span style="color:green">Execució</span> i <span style="color:red">Finalitzat</span>.
- Els processos poden fer E/S de forma simultània entre ells.

## Problema 0

Assumeix que tens els següents processos:

| Procés | Temps arribada | Ràfegues                                    |
|--------|----------------|---------------------------------------------|
| A      | 0              | $$2_{CPU}$$                                 |
| B      | 1              | $$6_{CPU}$$                                 |
| C      | 4              | $$1_{CPU}$$                                 |
| D      | 7              | $$4_{CPU}$$                                 |
| E      | 8              | $$3_{CPU}$$                                 |

Es demana:

1. Mostrar la planificació dels processos en un diagrama de Gantt per l'algorisme **FCFS**, **SRT** i **RR** amb **Q=1**. Assumeix una sola CPU.

| T | FCFS | SRT | RR |
|---|------|-----|----|
| 0 | A    | A   | A  |
| 1 | A    | A   | B  |
| 2 | B    | B   | A  |
| 3 | B    | B   | B  |
| 4 | B    | C   | C  |
| 5 | B    | B   | B  |
| 6 | B    | B   | B  |
| 7 | B    | B   | D  |
| 8 | C    | B   | E  |
| 9 | D    | E   | B  |
| 10| D    | E   | D  |
| 11| D    | E   | E  |
| 12| D    | D   | B  |
| 13| E    | D   | D  |
| 14| E    | D   | E  |
| 15| E    | D   | D  |

## Problema 1

Realitza la planificació dels següents processos utilitzant els algorismes de planificació. En cas d'empat on 2 processos arribin a la cua de preparats al mateix temps, s'executarà el procés amb prioritat més elevada (**1 és la prioritat més alta**).
  
| Procés | Prioritat | Temps arribada | Ràfegues                                    |
|--------|-----------|----------------|---------------------------------------------|
| A      | 4         | 3              | $$1_{CPU},4_{E/S},1_{CPU},5_{E/S},1_{CPU}$$ |
| B      | 3         | 0              | $$4_{CPU},1_{E/S},3_{CPU},1_{E/S},2_{CPU}$$ |
| C      | 2         | 1              | $$1_{CPU},5_{E/S},1_{CPU},1_{E/S},2_{CPU}$$ |
| D      | 1         | 2              | $$5_{CPU},2_{E/S},4_{CPU}$$                 |

Es demana:

1. Mostrar la planificació dels processos en un diagrama de Gantt.
2. Calcular totes les mètriques de planificació per a cada algorisme.
3. Discuteix els avantatges o desavantages de la planificació, i avalua l'impacte de 1 o 2 CPUs.

### FCFS amb 1 CPU

|   | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 |
|---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| A |    |    |    |**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:green">E</span>**| **<span style="color:red">F</span>**|
| B |**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:red">F</span>**|
| C |    |**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**| **<span style="color:red">F</span>**|
| D |    |    |**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:orange">W</span>**|**<span style="color:orange">W</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:blue">P</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:green">E</span>**|**<span style="color:red">F</span>**|

- **\% ús CPU** = 89,29%
- **Productivitat** = 0,14

| Procés  | Temps Espera | Temps Resposta | Temps de Servei | Temps de Retorn | Temps de Retorn (N)  |
|---------|--------------|----------------|-----------------|-----------------|----------------------|
| A       | 13           | 7              | 12              | 25              | 2,1                  |
| B       | 10           | 0              | 11              | 21              | 1,9                  |
| C       | 13           | 3              | 10              | 23              | 2,3                  |
| D       | 6            | 3              | 11              | 17              | 1,54                 |
| **AVG** | 10,5         | 3,25           | 11              | 21,5            | 1,96                 |

Amb només una CPU, es pot observar que els temps d'espera són significativament elevats, especialment per als processos que arriben més tard a la cua.

L'**efecte convoy** és pronunciat, especialment quan hi ha processos amb ràfegues llargues de CPU com B,C o D. Això fa que els processos amb ràfegues curtes hagin d'esperar molt, cosa que afecta negativament el temps de resposta.

Tot i que l'ús de la CPU és alt, l'eficiència general es veu afectada pels temps d'espera i de retorn llargs. Aquesta situació podria abordar-se mitjançant la implementació d'alguns algorismes com **SRT o RR**.

### FCFS amb 2 CPU

|   | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
|---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| A |    |    |    |**<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:blue">P</span>**  |**<span style="color:blue">P</span>**  |**<span style="color:blue">P</span>**  |**<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:green">E</span>**  |**<span style="color:red">F</span>**  |
| B |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:blue">P</span>**  |**<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:red">F</span>**  |
| C |    |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:red">F</span>**  |
| D |    |    |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:orange">W</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:red">F</span>** |

- **\% ús CPU** = 62,5%
- **Productivitat** = 0,2

| Procés | Temps Espera | Temps Resposta | Temps de Servei | Temps de Retorn | Temps de Retorn (N) |
|--------|--------------|----------------|-----------------|-----------------|----------------------|
| A      | 5            | 1              | 12              | 17              | 1,42                 |
| B      | 2            | 0              | 11              | 13              | 1,18                 |
| C      | 0            | 0              | 10              | 10              | 1,00                 |
| D      | 0            | 0              | 11              | 11              | 1,00                 |
| **AVG**| 1,75         | 0,25           | 11              | 12,75           | 1,15                 |

Amb dues CPUs, es redueixen dràsticament els temps d'espera, de resposta i de retorn per a tots els processos.

La disponibilitat d'una CPU addicional minimitza l'**efecte convoy**, permetent que els processos curts siguin atesos més ràpidament.

L'ús de dues CPUs millora notablement les mètriques de planificació, especialment en sistemes amb càrrega variada. Tot i que augmenta el cost de recursos, el benefici en termes de temps de resposta i de retorn és considerable. Tot i això, cal tenir en compte el cost de la inversió en hardware addicional.

## Problema 2

Realitza la planificació dels següents processos utilitzant els algorismes de planificació. En cas d'empat on 2 processos arribin a la cua de preparats al mateix temps, s'executarà el procés amb prioritat més elevada (**1 és la prioritat més alta**).
  
| Procés | Prioritat | Temps arribada | Ràfegues                                    |
|--------|-----------|----------------|---------------------------------------------|
| A      | 4         | 3              | $$1_{CPU},4_{E/S},1_{CPU},5_{E/S},1_{CPU}$$ |
| B      | 3         | 0              | $$4_{CPU},1_{E/S},3_{CPU},1_{E/S},2_{CPU}$$ |
| C      | 2         | 4              | $$1_{CPU},5_{E/S},1_{CPU}$$                 |
| D      | 1         | 2              | $$5_{CPU},2_{E/S},4_{CPU}$$                 |

Es demana:

1. Mostrar la planificació dels processos en un diagrama de Gantt.
2. Calcular totes les mètriques de planificació per a cada algorisme.
3. Discuteix els avantatges o desavantages de la planificació, i avalua l'impacte de 1 o 2 CPUs i de diferents valors de **quantum**.

### Round Robin Q=1 amb 1 CPU

|   | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 |
|---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| A |    |    |    | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |    |
| B | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |    |    |
| C |    |    |    |    | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |    |    |    |    |    |    |    |
| D |    |    | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |

- **\% ús CPU** = 100%
- **Productivitat** = 0,17

| Procés | Temps Espera | Temps Resposta | Temps de Servei | Temps de Retorn | Temps de Retorn (N) |
|--------|--------------|----------------|-----------------|-----------------|----------------------|
| A      | 6            | 2              | 12              | 18              | 1,50                 |
| B      | 9            | 0              | 11              | 20              | 1,82                 |
| C      | 4            | 2              | 7               | 11              | 1,57                 |
| D      | 10           | 0              | 11              | 21              | 1,91                 |
| **AVG**| 7,25         | 1              | 10,25           | 17,5            | 1,71                 |

### Round Robin Q=3 amb 1 CPU

|   | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 |
|---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
| A |    |    |    | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |
| B | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |    |
| C |    |    |    |    | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |    |    |    |
| D |    |    | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:orange">W</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:blue">P</span>**  | **<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |

- **\% ús CPU** = 100%
- **Productivitat** = 0,17

| Procés | Temps Espera | Temps Resposta | Temps de Servei | Temps de Retorn | Temps de Retorn (N) |
|--------|--------------|----------------|-----------------|-----------------|----------------------|
| A      | 8            | 4              | 12              | 20              | 1,67                 |
| B      | 10           | 0              | 11              | 21              | 1,91                 |
| C      | 8            | 4              | 7               | 15              | 2,14                 |
| D      | 9            | 1              | 11              | 20              | 1,82                 |
| **AVG**| 8,75         | 1,25              | 10,25           | 19              | 1,85                 |

### Round Robin Q=1 amb 2 CPU

|   | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16|
|---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|---|
| A |    |    |    | **<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:green">E</span>**  | **<span style="color:red">F</span>** |
| B |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**   | **<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**   |**<span style="color:green">E</span>**  | **<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |   |
| C |    |    |    |    | **<span style="color:blue">P</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |    |   | 
| D |    |    |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:orange">W</span>**   |**<span style="color:orange">W</span>**   |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  |**<span style="color:green">E</span>**  | **<span style="color:red">F</span>**  |    |    |   |

- **\% ús CPU** = 67,65%
- **Productivitat** = 0,24

| Procés | Temps Espera | Temps Resposta | Temps de Servei | Temps de Retorn | Temps de Retorn (N) |
|--------|--------------|----------------|-----------------|-----------------|----------------------|
| A      | 1            | 1              | 12              | 13              | 1,08                 |
| B      | 2            | 0              | 14              | 13              | 1,08                 |
| C      | 1            | 1              | 7               | 8               | 1,14                 |
| D      | 0            | 0              | 11              | 11              | 1,00                 |
| **AVG**| 1            | 0,5            | 10,25           | 11,25           | 1,10                 |

Si analitzem l'efecte del **quantum** en l'algorisme **Round Robin** amb 1 CPU, podem observar que un **quantum** més gran té un impacte negatiu o equivalent en les mètriques de planificació. Amb un **quantum** més gran, els processos poden ser interromputs menys freqüentment. Per fer una comparativa justa caldria considerar el cost de canvi de context per saber si compensa. Normalment, compensa i **quantum** més gran tendeixen a augmentar la productivitat del sistema.

En aquest exemple:

- Quantum = 1 ha realitzat 20 canvis de context si considerem un cost de 0,25 per canvi de context, el cost total és de 5.
  - **Productivitat** = (23 - 5)/23 = 0,78
- Quantum = 3 ha realitzat 12 canvis de context si considerem un cost de 0,25 per canvi de context, el cost total és de 3.
  - **Productivitat** = (23 - 3)/23 = 0,87

Però, si assumim que el cost de canvi de context és Q(1) és millor.

Els efectes de l'ús de 2 CPUs en l'algorisme **Round Robin** són evidents en la reducció dels temps d'espera i de retorn. Amb 2 CPUs, els processos poden ser atesos simultàniament, reduint els temps d'espera i de retorn. Això millora l'eficiència del sistema i redueix el temps de resposta mitjà. Cal tenir en compte que l'ús de 2 CPUs implica un cost addicional en termes de recursos.
