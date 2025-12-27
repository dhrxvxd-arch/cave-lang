#include "../include/tokens.h"
#include "../include/lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void tokenize(const char *source, struct token_array *tokens)
{
    (void)tokens;
    printf("Tokenizing source of length: %zu\n", strlen(source));
}