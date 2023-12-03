# BurgerSupreme
Projet : Procédures de vote pour trouver le Burger Supreme - Projet avancé


## COMMENT UTILISER VERIFY_MY_VOTE :

Usage : ./verify_my_vote [nom] [Prenom] [code_secret] [fichier_de_vote]

- nom : Nom electeur en majuscule, ex : DUPONT
- prenom : Prenom de l'electeur avec la 1ere lettre en majuscule, ex : Pierre
- code_secret : Code secret de l'electeur
- fichier_de_vote : Fichier de vote csv, ex VoteCondorcet.csv
Plus d'informations dans doxygen_doc/index.html

## COMMENT UTILISER UNINOMINAL* :

Usage : ./mainUninominal [1/2 tours] [fichier_de_vote]

- 1/2 tours : Permet de choisir uninominal à 1 tour ou 2
- fichier_de_vote : Fichier de vote csv, ex VoteCondorcet.csv
Plus d'informations dans doxygen_doc/index.html

## COMMENT UTILISER CONDORCET* :

Usage : ./condorcet
Plus d'informations dans doxygen_doc/index.html

