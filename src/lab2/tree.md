# Estrucutra de fitxers i directoris

En els exemples realitzat fins ara heu observat com el sistema de fitxers està organitzat en forma d'arbre. Aquest arbre té un node arrel, que és el directori arrel **/**. Aquest directori arrel conté tots els fitxers i directoris del sistema. Aquests fitxers i directoris poden contenir altres fitxers i directoris, i així successivament. Aquesta estructura d'arbre és la que permet organitzar i accedir als fitxers i directoris en el sistema operatiu. L'estructura **arbre** d'Unix/Linux requereix que per accedir a un *fitxer* o *directori* necessitem especificar la seva **ruta**.

* Ruta absoluta: Especifiquem tot el camí des del directori **arrel**. 
* Ruta relativa: Especifiquem  tot el camí des del directori **actual**.

Imagineu que estem al directori de l'usuari **/home/jordi** i volem imprimir amb ```cat``` el fitxer *a.txt*. Tenim dues opcions:
* Ruta absoluta: ```cat /home/jordi/a.txt```
* Ruta relativa: ```cat a.txt```

Per navegar per l'arbre de directoris, utilitzarem la comanda `cd`. Aquesta comanda ens permet canviar el directori actual. Si no especifiquem cap ruta, la comanda `cd` ens portarà al directori arrel **/**. Hi ha dos rutes especials que podem utilitzar per a navegar per l'arbre de directoris: **.** i **..**. El directori **.** representa el directori actual, mentre que el directori **..** representa el directori pare. 

Anem a estudiar un cas d'ús simple per exemplificar-ho:

1. Primer ens situarem al directori */home/jordi*. *Recordeu modificar jordi pel vostre nom d'usuari*.
2. Crearem un fitxer amb la comanda ```echo```. Redirigim la sortida de la cadena *Hola Jordi* al fitxer **a.txt** amb la redirecció [>]. La redirecció permet enviar la sortida d'una comanda a un fitxer. Més endavant al curs veurem i entendrem com funciona.
3. Imprimim el contingut del fitxer a la sortida estàndard (**stdout**) amb ruta absoluta i relativa.
4. Ens situem al directori anterior.
5. Observem com la ruta absoluta continua funcionant, però no la relativa.

```sh
jordi@debianlab:~$ cd /home/jordi
jordi@debianlab:~$ echo "Hola Jordi" > a.txt
jordi@debianlab:~$ cat /home/jordi/a.txt
jordi@debianlab:~$ cat a.txt
jordi@debianlab:~$ cd ..
jordi@debianlab:~$ cat /home/jordi/a.txt
jordi@debianlab:~$ cat a.txt
```
