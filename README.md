Etudiant : Théo Dubus 22008507

# TP2 C++

## Ajouts dans cette version
  - Support des fonctions unitaires
  - Support des fonctions n-aires
  - Support des fonction à nombre variable d'arguments

## Difficultés rencontrés

L'ajout des fonction à nombre variable d'arguments, notamment pour le passage des arguments à la fonction lambda stockée en mémoire.
La mémoire des fonction à aussi été complexe, au final cette mémoire est gérée par une classe dédiée `funStorage` avec toutes les méthodes nécessaire au management de cette mémoire, dont la vérification du nombre d'arguments.

## Choix d'implémentation

La classe `Function` qui hérite de `Token` à été ajoutée pour gérer les fonctions. Ces fonctions sont calculées dans la méthode eval, ce qui permet de respecter la hiérarchie lexer/parser.
On utilise `funStorage` pour stocker des fonction lambda associées à leur nom et leur nombre d'argument (mis à -1 si la fonction possède un nombre variable d'arguments). \
Les tests unitaires ont aussi été ajoutés dans `test/programTest.cpp`.
Une modification de la classe `Expression`, notamment de `tokensFormString()` simplifie le code et limite les passages d'arguments.

## Compilation du projet

Le projet utilise le système de build CMake.
Un script `buildrun.sh` permet de compiler, lancer les test et la calculatrice en 1 commande.

Le projet compile sous :

- `clang 10.0.0` sur Windows/Ubuntu
  
- `gcc 7.5.0` sur Ubuntu ou WSL (sous-système Windows pour Linux)

## Tests

Les tests sont regroupés dans le répertoire `\test`. J'ai choisi d'utiliser la libairie de test Googletest qui est l'une des plus populaire ( Catch, Boost.Test et Ctest sont aussi de bons candidats).

Les test sont séparés en 2 fichiers `.cpp` :

- `expressionTest.cpp` : Les tests d'analyse de tokens, crées au début du projet pour vérifier le   fonctionnement de `tokensFromString`

- `programTest.cpp` : Les tests du fonctionnement du programme complet
  - programme en une ligne ( addition, priorités opératoires, parenthèses )
  - programme multi lignes ( variables, affichage ou non avec `;` , calcul du volume d'un cylindre...)

## Fuites mémoire

Le projet a été testé avec `valgrind` pour détecter la présence ou non de 'memleaks'.
Un script `testValgrind.sh` permet de tester les fuites sur un programme type composé de toutes les possibilités du langage.

## Continuous integration

Le repo de ce projet est hébergé sur github.com (en privé pour éviter la copie), j'en ai donc profité pour expérimenter la continuous intégration avec <a href="https://github.com/features/actions"> Github Actions</a> qui permet d'effectuer une série de test pour valider mes commit à chaque push.

`.github/workflow/cmake.yml` contient le fichier yaml qui s'occupe de cette continuous integration.\
Il y est effectué en autre:

- la compilation du projet avec CMake.

- Le lancement des tests Googletest.

- La vérification de présence des fuites mémoires avec Valgrind.

Exemples d'execution de CI : \

- Execution du "workflow" avec succès :

![Execution du "workflow" avec succès](.markdown/succes.png)

- Echec de la tache Valgrind Memcheck :

![Echec de la tache Valgrind Memcheck](.markdown/echec.png)