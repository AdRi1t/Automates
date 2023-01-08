# Projet Automates
Le but de ce projet est de créer un programme en C qui prend en entrée un automate fini non déterministe et effectue les opérations suivantes dans l'ordre donné:
- Éxécution sur un mot.
- Déterminisation puis exécution sur le même mot
- Minimisation puis exécution sur le même mot

## Équipe:
* Othmane Abdimi
* Adrien Taberner

## Utilisation
* Le fichier de l'automate doit se trouver dans le dossier ./Automates pas besoin du chemin relatif
* Compilation avec makefile
```
$ make
```
* Exemple
```
./DetMin automate1.txt "bbaba"
```
* Commande
```
 ./DetMin [nom du fichier] [mot à tester]
```
