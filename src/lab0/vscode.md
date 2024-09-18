# Configurant el meu entorn de desenvolupament amb VSCode

En aquesta secció, instal·larem i configurarem el Visual Studio Code (VSCode) perquè ens ajudi en el desenvolupament del curs connectant-lo a la màquina virtual **debianlab**.

Per instal·lar el Visual Studio podeu descarregar el programari de [https://code.visualstudio.com/download](https://code.visualstudio.com/download) i seguir els passos d'instal·lació.

Un cop hagueu instal·lat el vostre entorn de desenvolupament (IDE), podeu afegir les següents extensions utilitzant el marketplace de VSCode: **remote-ssh**. Primer, feu clic a **Marketplace (1)**, després cerqueu *remote-ssh* i, finalment, feu clic a **(3)** per instal·lar la extensió. Consulteu la imatge:

![Instal·lant la extensió *remote-ssh*](./figures/vscode/remote-ssh.png)

Un cop hagueu instal·lat la extensió, ja podeu connectar-vos a la màquina virtual **debianlab**. Per fer-ho, feu clic a la icona de la part inferior esquerra **(1)** i seleccioneu l'opció **Remote-SSH: Connect to Host... (2)**. Consulteu la imatge:

![Configurant la conexió](./figures/vscode/remote-ssh2.png)

Ara apareixerà una finestra on podreu escriure la connexió SSH. També veureu l'opció **Add a New SSH Host**. Feu clic en aquesta opció i introduïu la comanda SSH per connectar-vos a la màquina virtual **debianlab**. Consulteu la imatge:

![Afegint un nou host](./figures/vscode/add_new_host.png)

Seleccioneu la primera opció del menú desplegable amb la ruta del vostre usuari i feu clic a **Add**. Consulteu la imatge:

![Seleccionant el fitxer de configuració](./figures/vscode/select_config.png)

i comproveu que l'amfitrió s'ha afegit correctament.

![Host afegit](./figures/vscode/host_added.png)


Ara feu clic a **Open Config** i observeu que s'ha creat una nova entrada amb el vostre usuari i la IP de la màquina virtual:

```sh
Host 172.16.10.202
  HostName 172.16.10.202
  User jordi
```

![Fitxer de configuració](./figures/vscode/config_file.png)

Us recomano que modifiqueu el fitxer de configuració perquè sigui més fàcil de recordar. Per exemple, podeu canviar el nom de l'amfitrió per **debianlab** :

```sh
Host debianlab
  HostName 172.16.10.202
  User jordi
```

Un cop hagueu modificat el fitxer de configuració, guardem-lo i tanquem-lo. Ara ja podeu connectar-vos a la màquina virtual **debianlab**. Per fer-ho:

1. Feu clic a la icona de la part inferior esquerra.
2. Seleccioneu **Remote-SSH: Connect to Host...**.
3. Seleccioneu **debianlab** i introduïu la vostra contrasenya.

![Connectant a debianlab](./figures/vscode/connect.png)

La primera vegada pot trigar uns minuts i demanar la contrasenya un parell de cops. Un cop connectat, ja podeu desenvolupar el curs des de VSCode. Assegureu-vos que a la part inferior hi apareix **SSH:debianlab**. Consulteu la imatge:

![Connectat a debianlab](./figures/vscode/ssh_debianlab.png)
