#ifndef LEXER_H
#define LEXER_H
#include "tokens.h"

void tokenize(const char *source, struct token_array *tokens);

#endif // LEXER_H