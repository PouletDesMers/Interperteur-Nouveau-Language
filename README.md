# Interpréteur-Nouveau-Language

## Description du Projet

Ce projet est un **interpréteur** simple conçu pour un langage de programmation basique. L'interpréteur permet d'évaluer des expressions arithmétiques, d'assigner des variables, et d'afficher les résultats via une fonction `print()`. Ce projet vise à fournir une meilleure compréhension des composants d'un interpréteur tels que le lexer, le parser, l'AST (Arbre Syntaxique Abstrait), et la gestion des variables.

Le programme fonctionne en deux modes :
1. **Mode fichier** : Exécution d'un fichier source contenant du code.
2. **Mode interactif** : L'utilisateur peut entrer des commandes directement dans une interface en ligne de commande.

### Fonctionnalités Principales
- **Évaluation d'expressions arithmétiques** : Supporte les opérateurs `+`, `-`, `*`, et `/`.
- **Assignation de variables** : Permet de stocker des valeurs dans des variables.
- **Fonction print()** : Affiche les résultats dans la console.

## Structure du Projet

L'organisation du projet se divise en plusieurs dossiers et fichiers pour une meilleure lisibilité et modularité.

### Dossiers

- **/src/** : Contient tous les fichiers sources du projet.
- **/include/** : Contient les fichiers d'en-tête qui définissent les interfaces des différents composants.

### Fichiers

#### /src/
- **main.c** : Point d'entrée du programme. Il gère l'interaction avec l'utilisateur, en mode fichier ou interactif.
- **lexer.c** : Analyseur lexical (lexer). Il transforme l'entrée utilisateur (chaîne de caractères) en une série de *tokens*.
- **parser.c** : Analyseur syntaxique (parser). Il convertit les *tokens* en un Arbre Syntaxique Abstrait (AST).
- **ast.c** : Implémente la structure et les fonctions associées à l'AST, qui représente la structure hiérarchique du programme.
- **interpreter.c** : Contient la logique de l'interpréteur. Il parcourt l'AST pour évaluer les expressions et exécuter les instructions (comme `print()`).
- **symbolTable.c** : Gère l'environnement des variables (table de hachage ou autre structure) et leurs valeurs.

#### /include/
- **lexer.h** : Définit les types de tokens et les fonctions associées au lexer.
- **parser.h** : Définit les structures et fonctions pour le parsing des expressions.
- **ast.h** : Déclare les structures de l'AST et les fonctions associées.
- **interpreter.h** : Contient les prototypes de fonctions pour l'évaluation et l'exécution des expressions.
- **symbolTable.h** : Définit les structures et fonctions pour la gestion des variables.

## Compilation et Exécution
### Compilation
Pour compiler le projet, vous pouvez utiliser gcc en ligne de commande ou utiliser le Makefile fournis pour automatiser le processus. 

#### Utilisation du Makefile
Le projet inclut un fichier Makefile pour simplifier le processus de compilation. Le Makefile contient les instructions nécessaires pour compiler le programme et gérer les dépendances entre les fichiers.

Pour compiler le programme à l'aide du Makefile, ouvrez un terminal dans le répertoire racine du projet et exécutez la commande suivante :
Voici un exemple de commande pour compiler le programme sans le Makefile :

``` bash
make
```
Cette commande :

Compile tous les fichiers sources situés dans le dossier src/.
Place l'exécutable résultant (généralement nommé interpreteur) dans le répertoire courant.
Si vous souhaitez spécifier un nom d'exécutable différent ou modifier des options de compilation, vous pouvez ajuster le Makefile en conséquence.

#### Nettoyage
Pour supprimer les fichiers objets et l'exécutable générés lors de la compilation, vous pouvez exécuter :

```bash
make clean
```
Cette commande supprime les fichiers intermédiaires et l'exécutable, vous permettant de repartir sur une compilation propre.

Vérifiez d'avoir installé make sur votre poste avant d'utiliser ces commandes, sinon cela vous procurera des erreurs !!

Si vous préférez compiler manuellement sans utiliser le Makefile, vous pouvez utiliser la commande suivante :

``` bash
gcc -o interpreteur src/main.c src/lexer.c src/parser.c src/ast.c src/interpreter.c src/symbolTable.c -I include
```
Cette commande :

- Compile tous les fichiers sources situés dans le dossier src/.
- Utilise le drapeau -I include pour indiquer le dossier des fichiers d'en-tête.
- Produit un exécutable nommé interpreteur.

### Exécution
Le programme peut être exécuté en deux modes :

#### Mode Interactif
Pour lancer le programme en mode interactif, exécutez simplement l'exécutable sans arguments :

```bash
./interpreteur
```

En mode interactif, vous pouvez saisir des instructions directement dans la console. Tapez exit pour quitter le programme.

#### Exemple :

``` shell
Mode interactif. Tapez 'exit' pour quitter.
> x = 5 + 3
> print(x)
8
> y = x * 2
> print(y)
16
> exit

Affichage de l'AST global après exécution:
```

#### Mode Fichier
Pour exécuter un script de code à partir d'un fichier, lancez le programme en fournissant le nom du fichier en argument :

``` bash
./interpreteur mon_script.txt
```

#### Exemple :

Supposons que vous ayez un fichier mon_script.txt contenant :
```
a = 10
b = a + 5
print(b)
```

En exécutant :

```bash
./interpreteur mon_script.txt
```

Le programme affichera :

``` bash
15
Affichage de l'AST global après exécution:
```

### Aide
Si vous fournissez plus d'un argument, le programme affichera l'usage correct :

``` bash
Usage: ./interpreteur [nom_du_fichier]
```

## Notion du projet
https://nospy.notion.site/Projet-Cr-ation-d-un-Interpr-teur-de-Langage-de-Programmation-e890d1624945429eafc4ce91cbcce315#0ef937fe9e844396a9da1af3185b965e

## Trello pour suivi des tâches
https://trello.com/invite/b/67028cf74a2e4ed05536b39c/ATTI4653cbb1bdbdabec5c70347f1eda0899F2D0E4CC/creation-dun-interpreteur
