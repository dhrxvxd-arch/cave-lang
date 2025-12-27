#include "../include/tokens.h"
#include <stdlib.h>
#include <stdio.h>

void init_token_array(struct token_array *array)
{
    array->tokens = malloc(sizeof(struct token_data) * 1);
    array->size = 0;
    array->capacity = 1;
}

void free_token_array(struct token_array *array)
{
    if (array->tokens != NULL)
    {
        free(array->tokens);
        array->tokens = NULL;
        array->size = 0;
        array->capacity = 0;
    }
}

void append_token_array(struct token_array *array, struct token_data token)
{
    if (array->size >= array->capacity)
    {
        size_t new_capacity = (array->capacity == 0) ? 1 : array->capacity * 2;
        struct token_data *new_tokens = realloc(array->tokens, new_capacity * sizeof(struct token_data));
        if (new_tokens == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for token array\n");
            return;
        }
        array->tokens = new_tokens;
        array->capacity = new_capacity;
    }
    array->tokens[array->size] = token;
    array->size++;
}
