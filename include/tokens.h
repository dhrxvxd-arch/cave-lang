#ifndef TOKENS_H
#define TOKENS_H
#include <stddef.h>

enum literal_type
{
    literal_int_dec,
    literal_int_oct,
    literal_int_hex,

    literal_int_u,
    literal_int_l,
    literal_int_ll,
    literal_int_ul,
    literal_int_ull,

    literal_float_f,
    literal_float,
    literal_float_l,

    literal_char,
    literal_char_wide,
    literal_char_utf8,
    literal_char_utf16,
    literal_char_utf32,

    literal_string,
    literal_string_wide,
    literal_string_utf8,
    literal_string_utf16,
    literal_string_utf32
};

enum type_keyword
{
    type_auto,
    type_break,
    type_case,
    type_char,
    type_const,
    type_continue,
    type_default,
    type_do,
    type_double,
    type_else,
    type_enum,
    type_extern,
    type_float,
    type_for,
    type_goto,
    type_if,
    type_inline,
    type_int,
    type_long,
    type_register,
    type_restrict,
    type_return,
    type_short,
    type_signed,
    type_sizeof,
    type_static,
    type_struct,
    type_switch,
    type_typedef,
    type_union,
    type_unsigned,
    type_void,
    type_volatile,
    type_while,

    type__Alignas,
    type__Alignof,
    type__Atomic,
    type__Bool,
    type__Complex,
    type__Generic,
    type__Imaginary,
    type__Noreturn,
    type__Static_assert,
    type__Thread_local
};

enum type_separator
{
    sep_left_paren,
    sep_right_paren,
    sep_left_brace,
    sep_right_brace,
    sep_left_bracket,
    sep_right_bracket,
    sep_dot,
    sep_arrow,
    sep_plus,
    sep_minus,
    sep_star,
    sep_slash,
    sep_percent,
    sep_caret,
    sep_ampersand,
    sep_pipe,
    sep_tilde,
    sep_exclamation,
    sep_equal,
    sep_less,
    sep_greater,
    sep_plus_plus,
    sep_minus_minus,
    sep_plus_equal,
    sep_minus_equal,
    sep_star_equal,
    sep_slash_equal,
    sep_percent_equal,
    sep_caret_equal,
    sep_ampersand_equal,
    sep_pipe_equal,
    sep_equal_equal,
    sep_exclamation_equal,
    sep_less_equal,
    sep_greater_equal,
    sep_double_ampersand,
    sep_double_pipe,
    sep_question,
    sep_colon,
    sep_semicolon,
    sep_comma,
    sep_ellipsis,
    sep_hash,
    sep_double_hash
};

struct token_keyword
{
    enum type_keyword keyword;
    const char *str;
};

struct token_separator
{
    enum type_separator separator;
    const char *str;
};

struct token_literal
{
    enum literal_type type;
    const char *str;
};

struct token_data
{
    union
    {
        struct token_keyword keyword;
        struct token_separator separator;
        struct token_literal literal;
    };
    enum token_type
    {
        TOKEN_KEYWORD,
        TOKEN_SEPARATOR,
        TOKEN_LITERAL
    } type;
};

struct token_array
{
    struct token_data *tokens;
    size_t size;
    size_t capacity;
};

void init_token_array(struct token_array *array);
void free_token_array(struct token_array *array);
void append_token_array(struct token_array *array, struct token_data token);

#endif // TOKENS_H