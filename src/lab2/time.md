# Temps i Dates a Debian

- `date`: Mostra la data i hora actual.
- `uptime`: Mostra el temps transcorregut des de l'últim reinici.
- `time`: Mesura el temps d'execució d'una comanda i en dóna informació detallada.

En el següent exemple, es mostra com es poden utilitzar aquestes comandes i el tipus d'informació que proporcionen:

```sh
jordi@debianlab:~$ date
     dijous, 20 de juliol de 2023, 10:26:05 CEST
jordi@debianlab:~$ uptime
     10:26:36 up 59 min,  1 user,  load average: 0,00, 0,01, 0,00
jordi@debianlab:~$ time ls
     shell  3,49s user 2,55s system 0% cpu 58:34,01 total
     children  54,04s user 17,78s system 2% cpu 58:34,01 total
```

En molts sistemes, el tipus de dades `time_t` s'utilitza per representar valors de temps. Aquest tipus de dades emmagatzema el temps com un nombre enter, que sol ser un nombre de segons des de l'1 de gener de 1970. **time_t** emmagatzema el temps com un nombre enter signat de 32 bits.

Per tant, únicament pot representar enters entre [−(231) i 231 −1], l'última hora que es pot codificar correctament és **231 − 1** segons després de l'època UNIX *(03:14:07 UTC el 19 de gener de 2038)*. Intentar augmentar al segon següent(03:14:08)* **farà que l'enter es desbord**i, establint el seu valor a **-(231)**, que els sistemes interpretaran com a **231 segons abans de l'època** *(20:45:52 UTC el 13 de desembre de 1901)*. Podeu consultar la següent font per a informació detallada sobre el problema [https://en.wikipedia.org/wiki/Year_2038_problem](https://en.wikipedia.org/wiki/Year_2038_problem)

Els desenvolupadors de Debian han tingut en compte aquest problema i han pres les mesures adequades per a evitar-ne les conseqüències negatives. Això proporciona als usuaris de Debian la confiança de poder utilitzar el sistema de forma fiable i precisa en la gestió de temps, sense preocupar-se pel problema del 2038.

En el següent exemple es pot observar com debian es capaç de representar una data superior al 2038. Això és deu a que **time_t** utilitza un nombre amb 64 bits.

```sh
jordi@debianlab:~$ date -d "1 Jan 2040"
Thu Jan  1 00:00:00 UTC 2040
```
