#include "../include/tokens.h"
#include "../include/lexer.h"
#include <ctype.h>
#include <string.h>

static int is_ident_start(char c)
{
    return isalpha((unsigned char)c) || c == '_';
}

static int is_ident_char(char c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static int match(const char *p, const char *s)
{
    while (*s)
        if (*p++ != *s++)
            return 0;
    return 1;
}

static int keyword_lookup(const char *s, size_t len, enum type_keyword *out)
{
    static const struct { const char *s; enum type_keyword k; } table[] = {
        {"auto", type_auto}, {"break", type_break}, {"case", type_case},
        {"char", type_char}, {"const", type_const}, {"continue", type_continue},
        {"default", type_default}, {"do", type_do}, {"double", type_double},
        {"else", type_else}, {"enum", type_enum}, {"extern", type_extern},
        {"float", type_float}, {"for", type_for}, {"goto", type_goto},
        {"if", type_if}, {"inline", type_inline}, {"int", type_int},
        {"long", type_long}, {"register", type_register},
        {"restrict", type_restrict}, {"return", type_return},
        {"short", type_short}, {"signed", type_signed},
        {"sizeof", type_sizeof}, {"static", type_static},
        {"struct", type_struct}, {"switch", type_switch},
        {"typedef", type_typedef}, {"union", type_union},
        {"unsigned", type_unsigned}, {"void", type_void},
        {"volatile", type_volatile}, {"while", type_while},
        {"_Alignas", type__Alignas}, {"_Alignof", type__Alignof},
        {"_Atomic", type__Atomic}, {"_Bool", type__Bool},
        {"_Complex", type__Complex}, {"_Generic", type__Generic},
        {"_Imaginary", type__Imaginary}, {"_Noreturn", type__Noreturn},
        {"_Static_assert", type__Static_assert},
        {"_Thread_local", type__Thread_local}
    };

    for (size_t i = 0; i < sizeof(table) / sizeof(table[0]); i++)
        if (strlen(table[i].s) == len &&
            memcmp(table[i].s, s, len) == 0)
        {
            *out = table[i].k;
            return 1;
        }
    return 0;
}

static enum literal_type classify_integer(const char *s, size_t len)
{
    if (len >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        return literal_int_hex;
    if (s[0] == '0' && len > 1)
        return literal_int_oct;
    for (size_t i = 0; i < len; i++)
        if (s[i] == 'u' || s[i] == 'U')
            return literal_int_u;
    for (size_t i = 0; i < len; i++)
        if (s[i] == 'l' || s[i] == 'L')
            return literal_int_l;
    return literal_int_dec;
}

static enum literal_type classify_float(const char *s, size_t len)
{
    if (s[len - 1] == 'f' || s[len - 1] == 'F')
        return literal_float_f;
    if (s[len - 1] == 'l' || s[len - 1] == 'L')
        return literal_float_l;
    return literal_float;
}

void tokenize(const char *source, struct token_array *tokens)
{
    init_token_array(tokens);

    const char *p = source;

    while (*p)
    {
        if (isspace((unsigned char)*p))
        {
            p++;
            continue;
        }

        if (*p == '/' && p[1] == '/')
        {
            p += 2;
            while (*p && *p != '\n')
                p++;
            continue;
        }

        if (*p == '/' && p[1] == '*')
        {
            p += 2;
            while (*p && !(*p == '*' && p[1] == '/'))
                p++;
            if (*p)
                p += 2;
            continue;
        }

        if (is_ident_start(*p))
        {
            const char *start = p++;
            while (is_ident_char(*p))
                p++;

            size_t len = (size_t)(p - start);
            enum type_keyword kw;

            if (keyword_lookup(start, len, &kw))
            {
                struct token_data t;
                t.type = TOKEN_KEYWORD;
                t.keyword.keyword = kw;
                t.keyword.str = start;
                append_token_array(tokens, t);
            }
            else
            {
                struct token_data t;
                t.type = TOKEN_IDENTIFIER;
                t.identifier.str = start;
                append_token_array(tokens, t);
            }
            continue;
        }

        if (isdigit((unsigned char)*p))
        {
            const char *start = p++;
            int is_float = 0;

            while (isalnum((unsigned char)*p) || *p == '.' || *p == 'x' || *p == 'X')
            {
                if (*p == '.' || *p == 'e' || *p == 'E')
                    is_float = 1;
                p++;
            }

            size_t len = (size_t)(p - start);

            struct token_data t;
            t.type = TOKEN_LITERAL;
            t.literal.str = start;
            t.literal.type = is_float
                ? classify_float(start, len)
                : classify_integer(start, len);

            append_token_array(tokens, t);
            continue;
        }

        if (*p == '"' || *p == '\'')
        {
            char q = *p++;
            const char *start = p - 1;

            while (*p && *p != q)
            {
                if (*p == '\\' && p[1])
                    p += 2;
                else
                    p++;
            }

            if (*p)
                p++;

            struct token_data t;
            t.type = TOKEN_LITERAL;
            t.literal.type = (q == '"') ? literal_string : literal_char;
            t.literal.str = start;
            append_token_array(tokens, t);
            continue;
        }

        static const struct { const char *s; enum type_separator sep; } multi[] = {
            {"...", sep_ellipsis}, {"->", sep_arrow},
            {"++", sep_plus_plus}, {"--", sep_minus_minus},
            {"+=", sep_plus_equal}, {"-=", sep_minus_equal},
            {"*=", sep_star_equal}, {"/=", sep_slash_equal},
            {"%=", sep_percent_equal}, {"&=", sep_ampersand_equal},
            {"|=", sep_pipe_equal}, {"^=", sep_caret_equal},
            {"==", sep_equal_equal}, {"!=", sep_exclamation_equal},
            {"<=", sep_less_equal}, {">=", sep_greater_equal},
            {"&&", sep_double_ampersand}, {"||", sep_double_pipe},
            {"##", sep_double_hash}
        };

        for (size_t i = 0; i < sizeof(multi) / sizeof(multi[0]); i++)
            if (match(p, multi[i].s))
            {
                struct token_data t;
                t.type = TOKEN_SEPARATOR;
                t.separator.separator = multi[i].sep;
                t.separator.str = p;
                append_token_array(tokens, t);
                p += strlen(multi[i].s);
                goto next;
            }

        static const struct { char c; enum type_separator sep; } single[] = {
            {'(', sep_left_paren}, {')', sep_right_paren},
            {'{', sep_left_brace}, {'}', sep_right_brace},
            {'[', sep_left_bracket}, {']', sep_right_bracket},
            {'.', sep_dot}, {'+', sep_plus}, {'-', sep_minus},
            {'*', sep_star}, {'/', sep_slash}, {'%', sep_percent},
            {'^', sep_caret}, {'&', sep_ampersand}, {'|', sep_pipe},
            {'~', sep_tilde}, {'!', sep_exclamation},
            {'=', sep_equal}, {'<', sep_less}, {'>', sep_greater},
            {'?', sep_question}, {':', sep_colon},
            {';', sep_semicolon}, {',', sep_comma},
            {'#', sep_hash}
        };

        for (size_t i = 0; i < sizeof(single) / sizeof(single[0]); i++)
            if (*p == single[i].c)
            {
                struct token_data t;
                t.type = TOKEN_SEPARATOR;
                t.separator.separator = single[i].sep;
                t.separator.str = p;
                append_token_array(tokens, t);
                p++;
                goto next;
            }

        p++;

    next:;
    }
}
