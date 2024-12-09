# Challenge04: Acrònims

**Objectiu**: Escriu un script en Bash que, donat un separador i una frase, generi l'acrònim corresponent a la frase, separant les paraules per l'acrònim amb el separador indicat.

El programa ha de complir els següents requisits:

- El programa ha de poder gestionar diferents tipus de separadors (espais, guions, punts, comes, tabuladors, etc.).

El programa ha de ser capaç de:

1. Ignorar caràcters especials (com punts, comes, guions, etc.) que apareguin al principi o al final de les paraules.
2. Convertir totes les lletres a majúscules.
3. El programa ha de generar l'acrònim només amb la primera lletra de cada paraula significativa. No es consideraran paraules significatives aquelles que siguin de llargada 1 caràcter o les preposicions.

Per obtenir les preposicions catalanes, podeu utilitzar la comanda següent:

```bash
curl -s https://ca.wiktionary.org/wiki/Viccionari:Llista_de_preposicions_en_catal%C3%A0 | grep -o -E "title=\"[a-zA-ZàèéíòóúçÀÈÉÍÒÓÚÇ]+\"" | sed -e 's/title=//g' -e 's/\"//g' > preposicions.txt
```

Per transformar una paraula a majúscules, podeu utilitzar la comanda següent:

```bash
echo "paraula" | tr '[:lower:]' '[:upper:]'
```

Exemples de sortides correctes:

1. Test1:
   - Entrada: `Universitat de lleida`
   - Sortida: `UL`

    ```bash
    bash ch4.sh "Universitat de lleida"
    ```

2. Test 2:
   - Entrada: `Sistemes operatius`
   - Separador: `;`
   - Sortida: `S`

    ```bash
    bash ch4.sh "Sistemes operatius" ";"
    ```

3. Test 3:
   - Entrada: `El combinat de les paraules uniformes en 4 idiomes`
   - Separador: ` `
   - Sortida: `CPUI`

    ```bash
    bash ch4.sh "El combinat de les paraules uniformes en 4 idiomes" " "
    ```

4. Test 4:
    - Entrada: `;Casa;Pis;Universitat;Institut`
    - Separador: `;`
    - Sortida: `CPUI`

> Adicionalment, podeu generar un fitxer de test per validar la vostra solució.
