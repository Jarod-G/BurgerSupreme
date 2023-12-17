# BurgerSupreme
Projet : Procédures de vote pour trouver le Burger Supreme - Projet avancé


## COMMENT UTILISER VERIFY_MY_VOTE :

Usage : ./verify_my_vote [nom] [Prenom] [code_secret] [fichier_de_vote]

- nom : Nom electeur en majuscule, ex : DUPONT
- prenom : Prenom de l'electeur avec la 1ere lettre en majuscule, ex : Pierre
- code_secret : Code secret de l'electeur
- fichier_de_vote : Fichier de vote csv, ex VoteCondorcet.csv

- Plus d'informations dans html/index.html

## COMMENT UTILISER SCRUTIN :

Usage : ./scrutin -i [fichier_ballot.csv] -d [matrice.csv] -o [nom_fichier_log] -m [uni1,uni2,cm,cp,cs,jm,all]

- i et d sont incompatibles, utiliser -i ou -d
- i nom de fichier csv traite le fichier cité, ex -i VoteCondorcet.csv
- d nom de fichier csv traite le fichier cité, ex -d wiki_paires.csv
- o est optionnel, nom du fichier de log sinon créer automatiquement sous le nom de log.txt, ex -o fichier_log
- m méthode précise la méthode de scrutin à utiliser, ex -m all

- Plus d'informations dans html/index.html

## COMMENT UTILISER TESTS :

Usage : ./tests

- Tests est un programme permettant de vérifier le bon fonctionnement des fonctions principales à l'aide de tests unitaires.
- Plus d'informations dans html/index.html

Author README : Gineste Jarod
