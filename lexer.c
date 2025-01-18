#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Définition des types de tokens que le lexeur peut reconnaître
typedef enum {
    NUM_TOKEN,
    ID_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    EGAL_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    PV_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    PRINT_TOKEN,
    RETURN_TOKEN,
    FOR_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    BREAK_TOKEN,
    CONTINUE_TOKEN,
    SWITCH_TOKEN,
    CASE_TOKEN,
    DEFAULT_TOKEN,
    VOID_TOKEN,
    ACCO_TOKEN,
    ACCF_TOKEN,
    STRING_TOKEN,
    FIN_TOKEN,
    INVALID_TOKEN,
} TokenType;

// Structure représentant un token
typedef struct {
    TokenType type;
    char value[64];
} Token;

// Fonction pour convertir le type de token en chaîne de caractères
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case NUM_TOKEN: return "NUMBER";
        case ID_TOKEN: return "IDENTIFIER";
        case PLUS_TOKEN: return "PLUS";
        case MOINS_TOKEN: return "MOINS";
        case MULT_TOKEN: return "MULTIPLIER";
        case DIV_TOKEN: return "DIVISER";
        case EGAL_TOKEN: return "EGAL";
        case AFF_TOKEN: return "AFF";
        case INF_TOKEN: return "INF";
        case INFEG_TOKEN: return "INFEG";
        case SUP_TOKEN: return "SUP";
        case SUPEG_TOKEN: return "SUPEG";
        case DIFF_TOKEN: return "DIFF";
        case PO_TOKEN: return "PARENTHESE OUVRANTE";
        case PF_TOKEN: return "PARENTHESE FERMANTE";
        case PV_TOKEN: return "POINT VIRGULE";
        case IF_TOKEN: return "IF";
        case ELSE_TOKEN: return "ELSE";
        case PRINT_TOKEN: return "PRINT";
        case RETURN_TOKEN: return "RETURN";
        case FOR_TOKEN: return "FOR";
        case WHILE_TOKEN: return "WHILE";
        case DO_TOKEN: return "DO";
        case BREAK_TOKEN: return "BREAK";
        case CONTINUE_TOKEN: return "CONTINUE";
        case SWITCH_TOKEN: return "SWITCH";
        case CASE_TOKEN: return "CASE";
        case DEFAULT_TOKEN: return "DEFAULT";
        case VOID_TOKEN: return "VOID";
        case ACCO_TOKEN: return "OUVERTURE ACCOLADE";
        case ACCF_TOKEN: return "FERMETURE ACCOLADE";
        case STRING_TOKEN: return "STRING";
        case FIN_TOKEN: return "EOF";
        default: return "INVALID";
    }
}

// Fonction pour signaler une erreur de syntaxe
void report_error(const char *token_value, int line, int column) {
    printf("Syntax Error: Unexpected token '%s' at line %d, column %d\n", token_value, line, column);
}

// Fonction pour récupérer le token suivant
Token get_next_token(FILE *source, int *line, int *column) {
    Token token;
    char c;

    while ((c = fgetc(source)) != EOF) {
        // Ignorer les espaces
        if (isspace(c)) {
            if (c == '\n') {
                (*line)++;
                *column = 0;
            } else {
                (*column)++;
            }
            continue;
        }

        // Gestion des commentaires
        if (c == '/') {
            if ((c = fgetc(source)) == '/') {
                while (c != '\n' && c != EOF) {
                    c = fgetc(source);
                }
                (*line)++;
                *column = 0;
                continue;
            } else {
                ungetc(c, source);
            }
        }

        // Gestion des nombres
        if (isdigit(c)) {
            ungetc(c, source);
            fscanf(source, "%63[0-9]", token.value);
            token.type = NUM_TOKEN;
            (*column) += strlen(token.value);
            return token;
        }

        // Gestion des identifiants et mots-clés
        if (isalpha(c) || c == '_') {
            ungetc(c, source);
            fscanf(source, "%63[a-zA-Z_][a-zA-Z0-9_]*", token.value);
            if (strcmp(token.value, "if") == 0) token.type = IF_TOKEN;
            else if (strcmp(token.value, "else") == 0) token.type = ELSE_TOKEN;
            else if (strcmp(token.value, "print") == 0) token.type = PRINT_TOKEN;
            else if (strcmp(token.value, "return") == 0) token.type = RETURN_TOKEN;
            else if (strcmp(token.value, "for") == 0) token.type = FOR_TOKEN;
            else if (strcmp(token.value, "while") == 0) token.type = WHILE_TOKEN;
            else if (strcmp(token.value, "do") == 0) token.type = DO_TOKEN;
            else if (strcmp(token.value, "break") == 0) token.type = BREAK_TOKEN;
            else if (strcmp(token.value, "continue") == 0) token.type = CONTINUE_TOKEN;
            else if (strcmp(token.value, "switch") == 0) token.type = SWITCH_TOKEN;
            else if (strcmp(token.value, "case") == 0) token.type = CASE_TOKEN;
            else if (strcmp(token.value, "default") == 0) token.type = DEFAULT_TOKEN;
            else if (strcmp(token.value, "void") == 0) token.type = VOID_TOKEN;
            else token.type = ID_TOKEN;
            (*column) += strlen(token.value);
            return token;
        }

        // Gestion des chaînes de caractères
        if (c == '"') {
            int i = 0; // Indice pour le tableau de caractères
            while ((c = fgetc(source)) != EOF && c != '"') {
                if (i < 63) { // Limiter la taille de la chaîne
                    token.value[i++] = c; // Ajouter le caractère à la chaîne
                } else {
                    printf("Erreur: Chaîne trop longue\n");
                    token.type = INVALID_TOKEN;
                    return token; // Retourner un token invalide
                }
            }

            if (c == '"') { // Vérifier si on a trouvé le guillemet de fermeture
                token.value[i] = '\0'; // Terminer la chaîne
                token.type = STRING_TOKEN; // Définir le type de token
                (*column) += i + 2; // Mettre à jour la colonne (2 pour les guillemets)
                return token; // Retourner le token de chaîne
            } else {
                printf("Erreur: Fin de fichier inattendue dans la chaîne\n");
                token.type = INVALID_TOKEN;
                return token; // Retourner un token invalide
            }
        }

                // Gestion des opérateurs et des symboles
        switch (c) {
            case '+': token.type = PLUS_TOKEN; break;
            case '-': token.type = MOINS_TOKEN; break;
            case '*': token.type = MULT_TOKEN; break;
            case '/': token.type = DIV_TOKEN; break;
            case ';': token.type = PV_TOKEN; break;
            case '(': token.type = PO_TOKEN; break;
            case ')': token.type = PF_TOKEN; break;
            case '{': token.type = ACCO_TOKEN; break;
            case '}': token.type = ACCF_TOKEN; break;
            case ':':
                // printf("DEBUG: Found ':' at line %d, column %d\n", *line, *column);
                if ((c = fgetc(source)) == '=') {
                    // printf("DEBUG: Found ':=' at line %d, column %d\n", *line, *column);
                    strcpy(token.value, ":=");  // Stocker correctement ":=" dans token.value
                    token.type = AFF_TOKEN;
                    *column += 2;  // Compter les deux caractères
                } else {
                    ungetc(c, source);  // Rejeter le caractère suivant dans le flux
                    token.value[0] = ':';  // Stocker simplement ':'
                    token.value[1] = '\0';
                    report_error("Unexpected token ':'", *line, *column);
                    token.type = INVALID_TOKEN;
                }
                break;
            case '=':
                if (token.type == AFF_TOKEN) break;
                token.type = EGAL_TOKEN;
                strcpy(token.value, "=");
                (*column)++;
                break;
            default:
                token.type = INVALID_TOKEN;
                sprintf(token.value, "%c", c);
                report_error(token.value, *line, *column);
                break;
        }


        // Stockez le caractère dans la valeur du token
        token.value[0] = c;
        token.value[1] = '\0';
        (*column)++;
        return token; // Retourner le token
    }

    // Gérer la fin du fichier
    token.type = FIN_TOKEN;
    strcpy(token.value, "EOF");
    return token;
}

// Fonction principale du lexeur pour lire un fichier source
void lexer(const char *filename) {
    FILE *source = fopen(filename, "r");
    if (!source) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    Token token;
    int line = 1, column = 1;

    do {
        token = get_next_token(source, &line, &column);
        printf("%s: %s\n", token_type_to_string(token.type), token.value);
    } while (token.type != FIN_TOKEN);

    fclose(source);
}