Projet PSI 2016-17

Nom : Agnel		Prénom : Adrien

Descriptif du projet :
miniShell

Pour le compiler : make
Pour le lancer : ./bin/minishell

Fonctions disponibles:

De se déplacer dans les répertoires :
$ cd dir
$ exit
$ echo $$ pour connaitre le PID du shell

D’exécuter des commandes simple, en “avant plan” et en “arrière plan” :
$ commande : exemple echo test
$ commande & : exemple ls &
$ commande1 ; commande2 ; commande3 & commande4 ; ...  exemple ls ; ls

Rediriger les entrées sorties des commandes
$ commande > file.output ; $ commande 2> file.error
$ commande < file.input
$ commande >> file.appout ; $ commande 2>> file.apperr $ commande >&2
$ commande 2>&1
$ commande1 | commande2 | commande3 | ..

Gérer les variables d’environnement
$ export VAR="ma variable"
$ echo $VAR
$ unset VAR

Gérer les opérateurs !, && et || comme les gère le bash
$ commande1 && commande2
$ commande1 || commande2
$ commande1 < input && commande2
$ commande1 | commande2 | ... && commandeN

De gérer les caractères “joker”
$ commande *.txt
$ commande file??.c
$ commande [0-9][a-z]_file.*.?
