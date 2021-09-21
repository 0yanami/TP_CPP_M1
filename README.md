![CMake](https://github.com/Mich3l14/TP_CPP_M1/workflows/CMake/badge.svg)
# TP3 C++

## Ajouts dans cette version
  - Support des fonctions curryfiées
  - Ajout des tests sur les fonctions curryfiées
  - Modification de la classe `Token` (suppression de `v()` qui n'était utile que pour les `Literal`)
  - Ajout des tests de curryfication dans `testValgrind.txt`
  - 
## Choix d'implémentation

Ajout des fonction curryfiées avec une 2ème mémoire qui contient le nom de la nouvelle fonction curryfiée, le nom de la fonction originale, et les arguments déjà spécifiés.
Dans le lexer, la création de nouvelles fonctions curryfiées se fait avec `handleCurryfied()`. On peut ensuite appeller les fonctions comme des fonctions classique après avoir vérifié si la fonction est de type curryfiée et après avoir ajouté les paramètres prédéfinis le cas échéant. A noter que la fonction à nombre variables d'arguments `polynome()` supporte aussi la curryfication.

Le projet compile sous :

- `clang 10.0.0` sur Windows/Ubuntu
  
- `gcc 7.5.0` sur Ubuntu ou WSL (sous-système Windows pour Linux)

Les test sont séparés en 2 fichiers `.cpp` :

- `expressionTest.cpp` : Les tests d'analyse de tokens, crées au début du projet pour vérifier le   fonctionnement de `tokensFromString`

- `programTest.cpp` : Les tests du fonctionnement du programme complet
  - programme en une ligne ( addition, priorités opératoires, parenthèses )
  - programme multi lignes ( variables, affichage ou non avec `;` , calcul du volume d'un cylindre...)

## Fuites mémoire

Le projet a été testé avec `valgrind` pour détecter la présence ou non de 'memleaks' et aucune fuite n'a été trouvée.
Un script `testValgrind.sh` permet de tester les fuites sur un programme type composé de toutes les possibilités du langage. 
