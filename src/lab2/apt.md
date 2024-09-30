# Instal·lació de paquets (apt)

Debian utilitza un sistema de gestió de paquets *APT* (Advanced Package Tool) per instal·lar, actualitzar i eliminar paquets de programari. 

Com a usuari normal, no podem utilitzar la comanda `apt` per a instal·lar, actualitzar i eliminar paquets de programari. Per tant, haurem de fer un pujada de privilegis a **root**.

```sh
jordi@debianlab:~$  su -c "apt update &&  apt upgrade -y"
```

Es bona pràctica mantenir el sistema de paquets actualitzat. Per a això, utilitzarem la comanda `apt update` per actualitzar les llistes de paquets disponibles i `apt upgrade` per actualitzar els paquets instal·lats al sistema. Es recomana executar aquestes comandes periòdicament.

Per instal·lar un nou paquet podem utilitzar la comanda `apt install [paquet]`. Per exemple, per instal·lar el paquet `tree`:

```sh
jordi@debianlab:~$ su -c "apt install tree -y"
```

El paquet `tree` permet visualitzar un directori en forma d'arbre. Per utilitzar-lo, podem executar la comanda `tree /etc/ssh` per visualitzar l'estructura de directoris del directori `/etc/ssh`:

```sh
jordi@debianlab:~$ tree /etc/ssh
/etc/ssh
├── moduli
├── ssh_config
├── ssh_config.d
├── sshd_config
├── sshd_config.d
├── ssh_host_ecdsa_key
├── ssh_host_ecdsa_key.pub
├── ssh_host_ed25519_key
├── ssh_host_ed25519_key.pub
├── ssh_host_rsa_key
└── ssh_host_rsa_key.pub
```

Per eliminar un paquet, podem utilitzar la comanda `apt remove [paquet]`. Per exemple, per eliminar el paquet `tree`:

```sh   
jordi@debianlab:~$ su -c "apt remove tree -y"
```

Si, a part volem eliminar el paquet i els fitxers de configuració associats, podem utilitzar la comanda `apt purge [paquet]`. Per exemple, per eliminar el paquet `tree` i els fitxers de configuració associats:

```sh
jordi@debianlab:~$ su -c "apt purge tree -y"
```

Finalment, apt també ens permet cerca paquets disponibles. Per exemple, per cercar paquets que continguin la paraula `vi`:

```sh
jordi@debianlab:~$ apt search neovim
S'està ordenant… Fet
Cerca a tot el text… Fet
dh-vim-addon/stable 0.4 all
  debhelper addon to help package Vim/Neovim addons

interception-caps2esc/stable 0.3.2-1+b1 amd64
  interception plugin for dual function Esc/Ctrl key at CapsLock

lua-nvim/stable 0.2.4-1-1 amd64
  Lua client for Neovim

lua-nvim-dev/stable 0.2.4-1-1 amd64
  Lua client for Neovim (development files)

neovim/stable 0.7.2-7 amd64
  heavily refactored vim fork

neovim-qt/stable 0.2.16-1 amd64
  neovim client library and GUI

neovim-runtime/stable 0.7.2-7 all
  heavily refactored vim fork (runtime files)

python3-neovim/stable 0.4.2-2 all
  transitional dummy package

python3-pynvim/stable 0.4.2-2 all
  Python3 library for scripting Neovim processes through its msgpack-rpc API

ruby-neovim/stable 0.8.1-1 all
  Ruby client for Neovim

vim-ale/stable 3.3.0-1 all
  Asynchronous Lint Engine for Vim 8 and NeoVim

vim-redact-pass/stable 1.7.4-6 all
  stop pass(1) passwords ending up in Vim cache files
```

Observem que podem instal·lar el paquet `neovim` per utilitzar-lo com a editor de text en la versio *0.7.2-7*. Neovim és un editor de text que es basa en el projecte Vim. Neovim té com a objectiu millorar Vim, mantenint la compatibilitat amb els scripts i plugins de Vim. Per instal·lar el paquet `neovim`:

```sh
jordi@debianlab:~$ su -c "apt install neovim -y"
```
