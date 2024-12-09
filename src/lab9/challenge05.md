# Challenge05: Tres en ratlla

En aquest repte, es demana implementar un joc de tres en ratlla  utilitzant Bash. Per fer-ho, seguireu els seguents passos:

1. Implementar una funció que mostri el tauler del joc amb una mida fixa representada per una matriu 3x3.

    - Per fer-ho, podeu crear un array amb valors del 1 al 9, que representaran les caselles del tauler.

    ```bash
    | 1 | 2 | 3 |
    | 4 | 5 | 6 |
    | 7 | 8 | 9 |
    ```

    - Implementar la funció `imprimir_tauler` que mostri el tauler amb els valors de l'array anomenat **tauler**.
  
2. Implementar una funció que permeti als jugadors introduir les seves jugades al tauler.

    - La funció `introduir_jugada` ha de permetre als jugadors introduir les seves jugades al tauler. El jugador 1 es representarà amb la lletra `X` i el jugador 2 amb la lletra `O`.

    ```bash
    | 1 | 2 | 3 |
    | 4 | 5 | 6 |
    | 7 | 8 | 9 |

    Introdueix la teva jugada (1-9): 
    ```

    - Un cop introduïda la jugada, el tauler s'actualitzarà amb la jugada del jugador. Per tant, es important validar que la casella seleccionada estigui lliure i que la casella seleccionada estigui dins dels límits del tauler.

    ```bash
    | 1 | 2 | 3 |
    | 4 | X | 6 |
    | 7 | 8 | 9 |

    Introdueix la teva jugada (1-9): 65
    Error: La casella seleccionada no és vàlida. Introdueix una casella vàlida (1-9): 5
    Error: La casella seleccionada ja està ocupada. Introdueix una casella vàlida (1-9): 3
    ```

    Un cop validada la jugada, el tauler s'actualitzarà amb la jugada del jugador.

    ```bash
    | 1 | 2 | O |
    | 4 | X | 6 |
    | 7 | 8 | 9 |
    ```

3. Implementeu un sistema de torns per alternar les jugades dels jugadors.

    - La funció `torn` ha de permetre alternar les jugades dels jugadors. El jugador 1 començarà la partida.
    - Durant el torn del jugador 1, el tauler mostrarà el següent missatge: `Torn del jugador 1 (X)`.
    - Es mostrarà l'estat actual del tauler.
    - Es demanarà al jugador 1 que introdueixi la seva jugada.
    - S'actualitzarà el tauler amb la jugada del jugador 1.
    - Es canviarà de torn al jugador 2.
    - Un cop acabats els 9 torns, màxima quantitat de jugades possibles, el joc acabarà.

    ```bash
    Torn del jugador 1 (X)
    | 1 | 2 | 3 |
    | 4 | 5 | 6 |
    | 7 | 8 | 9 |
    Introdueix la teva jugada (1-9): 5

    Torn del jugador 2 (O)
    | 1 | 2 | 3 |
    | 4 | X | 6 |
    | 7 | 8 | 9 |
    Introdueix la teva jugada (1-9): 3

    ...
    ```

4. Implementar una funció que comprovi si hi ha un guanyador.

    - La funció `guanyador` ha de comprovar si hi ha un guanyador. El joc acaba quan un jugador aconsegueix fer tres en ratlla en horitzontal, vertical o diagonal.

    - Reviseu les línies, columnes i diagonals per comprovar si hi ha un guanyador.


5. Integrar la funció guanyador al torn per comprovar si hi ha un guanyador en cada torn.

    - Si hi ha un guanyador, el joc acabarà i es mostrarà el missatge `El jugador X ha guanyat!` o `El jugador O ha guanyat!`.

    ```bash
    Torn del jugador 2 (X)
    | X | 2 | X |
    | 4 | O | 6 |
    | 7 | O | X |
    Introdueix la teva jugada (1-9): 2
    El jugador 2 (X) ha guanyat!
    ```

6. Implementar una funció que comprovi si hi ha un empat.

## Funcionalitats extra

- Utilitzeu colors per ressaltar les jugades dels jugadors.
- Utilitzeu la funció `clear` per netejar la pantalla després de cada jugada. I mostreu l'estat de la partida.
- Implementeu el joc per a taulells de mida variable (N en ratlla), però sempre quadrats (4x4, 5x5, 6x6, etc.).
  