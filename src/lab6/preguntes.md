# Preguntes de seguiment

1. Assumeix un planificador **Round Robin** amb un determinat *quantum Q*. Es pot afirmar que pel mateix *workload*, el temps d'espera mitjà és més petit que el de FCFS?

    <details>
    <summary>Veure la resposta</summary>

    Aquesta afirmació no es compleix necessàriament, sobretot en valors petits de quantum. Per exemple podem assumir el següent cas:

    1. Considereu 3 processos: P1, P2 i P3
    2. Temps d'arribada: 0, 1 i 2
    3. Temps de CPU: 3 unitats per a cada procés

    A continuació, es mostra el diagrama de Gantt per a FCFS:

    |  |0 |1 |2 |3 |4 |5 |6 |7 |8 |9 |
    |--|--|--|--|--|--|--|--|--|--|--|
    |P1|E |E |E |F |  |  |  |  |  |  |
    |P2|  |P |P |E |E |E |F |  |  |  |
    |P3|  |  |P |P |P |P |E |E |E |F |

    $$\text{Temps d'espera mitjà FCFS} = \frac{0+2+4}{2}= 2$$

    A continuació, es mostra el diagrama de Gantt per a Round Robin amb un quantum de 1:

    |  |0 |1 |2 |3 |4 |5 |6 |7 |8 |9 |
    |--|--|--|--|--|--|--|--|--|--|--|
    |P1|E |P |E |P |P |E |F |  |  |  |
    |P2|  |E |P |E |P |P |E |F |  |  |
    |P3|  |  |P |P |E |P |P |E |E |F |

    $$\text{Temps d'espera mitjà Round Robin} = \frac{3+3+4}{3}= 3.33$$
  
    En aquest cas, el temps d'espera mitjà de Round Robin és més gran que el de FCFS.
    </details>

2. L'algorisme **Round Robin** amb **quantum** infinit és equivalent a l'algorisme **First Come First Serve**. Com es podria implementar un algorisme Round Robin amb un quantum infinit?

    <details>
    <summary>Veure la resposta</summary>

    Aquesta afirmació és correcta. Amb un *quantum infinit*, el planificador Round Robin es comporta de manera idèntica al *FCFS*, ja que cada procés s'executa completament abans de passar al següent, seguint l'ordre d'arribada.

    Una manera d'implementar un algorisme Round Robin amb un quantum infinit seria la següent:

    - El planificador assigna un valor al quantum equivalent al número de ticks de rellotge des de l'inici del sistema fins al moment actual.

    - Això garanteix que el quantum sempre sigui més gran que el temps d'execució de qualsevol procés, eliminant així els canvis de context abans de la finalització de cada procés.
    </details>

3. Una bona forma de decidir el valor *Quantum* és assignar-li un valor llegurament inferior al valor mitjà de CPU del conjunt de processos a executar.

    <details>
    <summary>Veure la resposta</summary>

    Aquesta afirmació és incorrecta. Assignar un valor de *Quantum* lleugerament inferior al valor mitjà de CPU del conjunt de processos a executar pot ser problemàtic per a processos curts, ja que poden experimentar temps d'espera excessius.

    Imagina't un cas on el valor mitjà de CPU és de 10 unitats de temps. Si assignem un *Quantum* de 9 unitats de temps, els processos curts hauran d'esperar fins que els processos llargs acabin d'executar-se, cosa que pot provocar temps d'espera excessius per als processos curts.

    En general, el valor del *Quantum* hauria de ser prou gran per mantenir un bon rendiment per als processos llargs, però prou petit per evitar temps d'espera excessius per als processos curts.
     </details>

4. Els planificadors round-robin normalment mantenen una llista on cada procés executable apareix exactament una vegada. Quines implicacions tindria, a nivell de planificació, si un procés aparegués més d’una vegada a la llista? Pots identificar algun avantatge o raó per implementar aquest sistema

    <details>
    <summary>Veure la resposta</summary>

    Si un procés apareix diverses vegades a la llista, obtindrà múltiples quàntums per cicle, augmentant així el seu temps de CPU. Aquest enfocament es podria utilitzar per prioritzar processos més importants, assignant-los una quota més gran de la CPU. No obstant això, si el procés queda bloquejat, totes les seves entrades s’haurien d’eliminar de la llista de processos en execució.
    </details>

5. Quin és l'impacte del canvi de context sobre el *quantum* i del *quantum* sobre el canvi de context?

    <details>
    <summary>Veure la resposta</summary>

    Si el canvi de context és gran, el valor del *quantum* ha de ser proporcionalment gran. En cas contrari, l'overhead del canvi de context pot ser bastant elevat.

    Per exemple, si el canvi de context és de 10ms, i el *quantum* és de 5ms, llavors el 50% del temps de CPU es perd en canvis de context.

    Si el canvi de context és molt petit o negligible, llavors el valor del *quantum* pot ser escollit amb més llibertat.

    </details>

6. Assumeix:
   - T com el temps d'execució mig d'un procés
   - S com el temps de canvi de context
   - Q com el quantum

    Proporciona una fórmula per calcular l'eficiència del planificador en funció  de T,S i Q.

    <details>
    <summary>Veure la resposta</summary>

    Per calcular l'eficiència del planificador, es considera la relació entre el temps efectiu dedicat a l'execució dels processos i el temps total de CPU, incloent-hi els costos de canvi de context.

    L'eficiència del planificador es pot calcular de la següent manera:

    $$\text{Eficiència} = \frac{T}{T + \frac{ST}{Q}}$$

    El temps de canvi de context es divideix pel *quantum* per obtenir el nombre de canvis de context per unitat de temps. Això es multiplica pel temps d'execució mitjà per obtenir el temps total de canvi de context per unitat de temps.

    Per exemple, si **T = 10,S = 1 i Q = 5**, llavors l'eficiència del planificador seria:

    $$\text{Eficiència} = \frac{10}{10 + \frac{1 \cdot 10}{5}} = \frac{10}{12} = 0.83$$

    </details>

7. Quan els processos tenen durades de CPU molt variades, l'algorisme First Come First Serve (FCFS) ofereix millor temps de finalització mitjà que Shortest Job First (SJF)?

    <details>
    <summary>Veure la resposta</summary>

    El temps de finalització mitjà és el temps que els processos triguen a completar-se des de la seva arribada fins que acaben. En general, l’algorisme First Come First Serve (FCFS) no ofereix un temps de finalització mitjà millor que el Shortest Job First (SJF) quan les durades de CPU dels processos són molt variades.

    Això es deu al fet que el FCFS atén els processos en ordre d'arribada sense tenir en compte la seva durada.

    Per exemple:

    - Procés 1: 10 unitats de CPU
    - Procés 2: 1 unitat de CPU
    - Procés 3: 2 unitats de CPU

    Asummeix que arriben tots al mateix temps (instant 0) en ordre 1, 2, 3.

       - FCFS: (10 + 11 + 13) / 3 = 11.33
       - SJF: (1 + 2 + 12) / 3 = 5

    </details>
