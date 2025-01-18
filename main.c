#include <stdio.h>

void lexer(const char *filename);
void parse_program(const char *filename);

int main() {
    const char *filename = "input.txt";

    printf("======= Analyse lexicale ========\n");
    lexer(filename);
    printf("Analyse lexicale terminee.\n");

    // printf("======= Analyse syntaxique ========\n");
    // parse_program(filename);
    // printf("Analyse syntaxique terminee.\n");

    return 0;
}