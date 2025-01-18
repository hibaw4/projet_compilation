#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NUM_TOKEN, ID_TOKEN, PLUS_TOKEN, MOINS_TOKEN, MULT_TOKEN, DIV_TOKEN,
    EGAL_TOKEN, AFF_TOKEN, INF_TOKEN, INFEG_TOKEN, SUP_TOKEN, 
    SUPEG_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, PV_TOKEN, 
    IF_TOKEN, ELSE_TOKEN, PRINT_TOKEN, RETURN_TOKEN, FOR_TOKEN, 
    WHILE_TOKEN, DO_TOKEN, BREAK_TOKEN, CONTINUE_TOKEN, 
    SWITCH_TOKEN, CASE_TOKEN, DEFAULT_TOKEN, VOID_TOKEN, 
    ACCO_TOKEN, ACCF_TOKEN, STRING_TOKEN, FIN_TOKEN, INVALID_TOKEN
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

// Prototype de la fonction get_next_token
Token get_next_token(FILE *source, int *line, int *column);

// Fonction pour analyser une expression
void parse_expression(FILE *source, int *line, int *column) {
    Token token = get_next_token(source, line, column);

    // Vérification initiale
    if (token.type == ID_TOKEN || token.type == NUM_TOKEN || token.type == STRING_TOKEN) {
        printf("Expression: %s\n", token.value);
    } else {
        printf("Erreur de syntaxe: Attendu un identifiant, un nombre ou une chaîne, trouve %s\n", token.value);
        return;
    }

    // Vérifier les opérateurs
    while (1) {
        token = get_next_token(source, line, column);
        if (token.type == PLUS_TOKEN || token.type == MOINS_TOKEN || 
            token.type == MULT_TOKEN || token.type == DIV_TOKEN) {
            printf("Operateur: %s\n", token.value);
            
            token = get_next_token(source, line, column);
            if (token.type != ID_TOKEN && token.type != NUM_TOKEN && token.type != STRING_TOKEN) {
                printf("Erreur de syntaxe: Attendu un identifiant, un nombre ou une chaîne, trouve %s\n", token.value);
                return;
            }
            printf("Expression: %s\n", token.value);
        } else {
            ungetc(token.value[0], source); // Remettre le dernier caractère
            break;
        }
    }

    // Vérification pour le point-virgule de fin d'expression
    token = get_next_token(source, line, column);
    if (token.type != PV_TOKEN) {
        printf("Erreur de syntaxe: Attendu ';', trouve %s\n", token.value);
    }
}

// Fonction pour analyser une instruction
void parse_statement(FILE *source, int *line, int *column) {
    Token token = get_next_token(source, line, column);
    
    if (token.type == ID_TOKEN) {
        // Lecture de l'affectation
        token = get_next_token(source, line, column);
        if (token.type == AFF_TOKEN) {
            parse_expression(source, line, column);
            return; // Terminer après une affectation
        } else {
            printf("Erreur de syntaxe: Attendu ':=', trouve %s\n", token.value);
            return;
        }
    } else if (token.type == PRINT_TOKEN) {
        // Gérer l'instruction print
        token = get_next_token(source, line, column);
        if (token.type != PO_TOKEN) {
            printf("Erreur de syntaxe: Attendu '(', trouve %s\n", token.value);
            return;
        }

        token = get_next_token(source, line, column);
        if (token.type != STRING_TOKEN && token.type != ID_TOKEN) {
            printf("Erreur de syntaxe: Attendu une chaîne de caractères ou un identifiant, trouve %s\n", token.value);
            return;
        }
        printf("Print: %s\n", token.value); // Afficher la chaîne ou l'identifiant

        token = get_next_token(source, line, column);
        if (token.type != PF_TOKEN) {
            printf("Erreur de syntaxe: Attendu ')', trouve %s\n", token.value);
            return;
        }

        token = get_next_token(source, line, column);
        if (token.type != PV_TOKEN) {
            printf("Erreur de syntaxe: Attendu ';', trouve %s\n", token.value);
        }
    } else {
        printf("Erreur de syntaxe: Instruction non reconnue, trouve %s\n", token.value);
    }
}

// Fonction principale de l'analyseur syntaxique
void parse_program(const char *filename) {
    FILE *source = fopen(filename, "r");
    if (!source) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    int line = 1, column = 1;
    while (1) {
        Token token = get_next_token(source, &line, &column);
        if (token.type == FIN_TOKEN) break;
        ungetc(token.value[0], source); // Remettre le dernier caractère
        parse_statement(source, &line, &column);
    }

    fclose(source);
}