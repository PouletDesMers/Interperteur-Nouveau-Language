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

## Notion du projet
https://nospy.notion.site/Projet-Cr-ation-d-un-Interpr-teur-de-Langage-de-Programmation-e890d1624945429eafc4ce91cbcce315#0ef937fe9e844396a9da1af3185b965e

## Trello pour suivi des tâches
https://trello.com/invite/b/67028cf74a2e4ed05536b39c/ATTI4653cbb1bdbdabec5c70347f1eda0899F2D0E4CC/creation-dun-interpreteur

## Ressources supplémentaires
https://www.youtube.com/watch?v=YbsZRaaXeZA&t
