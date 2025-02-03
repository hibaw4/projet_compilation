# Introduction
- Ce projet est un mini-compilateur Pascal écrit en C.

## :ledger: Index

- [About](#beginner-about)
- [Usage](#zap-usage)
  - [Installation](#electric_plug-installation)
  - [Commands](#package-commands)
- [Development](#wrench-development)
  - [Pre-Requisites](#notebook-pre-requisites)
  - [Developmen Environment](#nut_and_bolt-development-environment)
  - [File Structure](#file_folder-file-structure)
- [Community](#cherry_blossom-community)
- [Credit/Acknowledgment](#star2-creditacknowledgment)
  
##  :beginner: About
Ce projet implémente un compilateur pour le langage Pascal en utilisant le langage C.
Il comprend:
- un analyseur lexical
- un analyseur syntaxique.
  
Il ne contient pas:
- un analyseur sémantique
- un générateur de pcode
- un interpréteur

Token reconnus:
- PROGRAM
- VAR
- BEGIN
- END
- IF
- THEN
- ELSE
- WHILE
- DO
- FOR
- TO
- DOWNTO
- REPEAT
- UNTIL
- FUNCTION
- PROCEDURE
- Identificateurs ([a-zA-Z_][a-zA-Z0-9_]*)
- Nombres entiers ([0-9]+)
- Nombres réels ([0-9]+\.[0-9]+)
- Opérateurs : +, -, *, /, :=
- Délimiteurs : ;, ,, ., :
- Parenthèses : ( )
- Comparateurs : =, <>, <, >, <=, >=

Tokens pas reconnus:
- AND
- OR
- NOT
- ARRAY
- OF
- RECORD
- TYPE
- UNIT
- INTERFACE
- IMPLEMENTATION
- USES
- CONST
- TYPEDEF
- LABEL
- CASE
- GOTO
- WITH
- FORWARD
- MOD (modulo)
- DIV (division entière)
- BOOLEAN
- CHAR
- INTEGER
- REAL
- STRING
- FILE
- POINTER
- TEXT
- LONGINT
- SHORTINT
- BYTE
- WORD

## :zap: Usage
Pour utiliser ce compilateur, exécutez le fichier compilateur.exe avec un fichier source en entrée.

###  :electric_plug: Installation
1. Clonez le dépôt :
```
  git clone <URL_DU_REPO>
  cd compilateurpascal
```
2. Assurez-vous d'avoir un compilateur C installé (comme GCC ou Clang).
3. Compilez le projet :
```
gcc -o compilateur Compilateur/main.c Compilateur/lexer.c Compilateur/parser.c -lm
```

###  :package: Commands
- Pour exécuter le compilateur :
```
./compilateur <nom du compilateur: compilateur.exe> input.txt
```


### :notebook: Pre-Requisites
- Un compilateur C (GCC, MinGW, etc.)
- Un éditeur de texte (VS Code, Vim, etc.)

###  :nut_and_bolt: Development Environment
1. Cloner le projet
2. Compiler avec un compilateur C


###  :file_folder: File Structure

```
compilateurpascal/
├── Compilateur/
│   ├── main.c
│   ├── lexer.c
│   ├── parser.c
│   ├── input.txt
│   ├── compilateur.exe
│   └── .git/
```

## :cherry_blossom: Community
Vous pouvez utiliser ce code et le compléter si vous voulez :)

Ce projet nécessite des améliorations et il n'est pas complet. Il y'a une version plus améliorée qui a été réalisée en groupe.
