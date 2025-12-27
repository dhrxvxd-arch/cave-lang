# C Grammar (C17)

This document defines a **complete, implementation-oriented grammar for ISO C (C17)**. It is intended for compiler, lexer, and parser development rather than pedagogy. The grammar is expressed in **EBNF-like notation**, with explicit precedence and disambiguation notes where required.

#

## 1. Lexical Grammar

### 1.1 Tokens

A translation unit is decomposed into the following token classes:

* Keywords
* Identifiers
* Constants (literals)
* String literals
* Operators
* Punctuators
* Comments (discarded)
* Whitespace (discarded except for line tracking)

#

### 1.2 Keywords

```
auto break case char const continue default do double else enum extern float for goto if inline int long register restrict return short signed sizeof static struct switch typedef union unsigned void volatile while

_Alignas _Alignof _Atomic _Bool _Complex _Generic _Imaginary _Noreturn _Static_assert _Thread_local
```

#

### 1.3 Identifiers

```
identifier ::= identifier-nondigit
             | identifier identifier-nondigit
             | identifier digit

identifier-nondigit ::= nondigit | universal-character-name
nondigit ::= _ | a–z | A–Z
digit ::= 0–9
```

#

### 1.4 Constants (Literals)

#### Integer constants

```
integer-constant ::= decimal-constant integer-suffix?
                   | octal-constant integer-suffix?
                   | hexadecimal-constant integer-suffix?

integer-suffix ::= unsigned-suffix long-suffix?
                 | unsigned-suffix long-long-suffix
                 | long-suffix unsigned-suffix?
                 | long-long-suffix unsigned-suffix?
```

#### Floating constants

```
floating-constant ::= decimal-floating-constant
                    | hexadecimal-floating-constant
```

#### Character constants

```
character-constant ::= 'c'
                     | L'c'
                     | u'c'
                     | U'c'
```

#### String literals

```
string-literal ::= "s"
                 | L"s"
                 | u8"s"
                 | u"s"
                 | U"s"
```

Adjacent string literals are concatenated.

#

## 2. Syntactic Grammar

### 2.1 Translation Unit

```
translation-unit ::= external-declaration+
```

#

### 2.2 External Declarations

```
external-declaration ::= function-definition
                       | declaration
```

#

### 2.3 Declarations

```
declaration ::= declaration-specifiers init-declarator-list? ;
```

```
declaration-specifiers ::= storage-class-specifier declaration-specifiers?
                          | type-specifier declaration-specifiers?
                          | type-qualifier declaration-specifiers?
                          | function-specifier declaration-specifiers?
                          | alignment-specifier declaration-specifiers?
```

#

### 2.4 Function Definitions

```
function-definition ::= declaration-specifiers declarator declaration-list? compound-statement
```

#

### 2.5 Declarators

```
declarator ::= pointer? direct-declarator
```

```
direct-declarator ::= identifier
                    | ( declarator )
                    | direct-declarator [ constant-expression? ]
                    | direct-declarator ( parameter-type-list )
                    | direct-declarator ( identifier-list? )
```

#

### 2.6 Statements

```
statement ::= labeled-statement
            | compound-statement
            | expression-statement
            | selection-statement
            | iteration-statement
            | jump-statement
```

#

### 2.7 Expressions

```
expression ::= assignment-expression
             | expression , assignment-expression
```

```
assignment-expression ::= conditional-expression
                        | unary-expression assignment-operator assignment-expression
```

```
conditional-expression ::= logical-or-expression
                         | logical-or-expression ? expression : conditional-expression
```

#

### 2.8 Operator Precedence (High →  Low)

1. Postfix (`() [] . -> ++ --`)
2. Unary (`+ - ! ~ ++ -- sizeof _Alignof`)
3. Multiplicative (`* / %`)
4. Additive (`+ -`)
5. Shift (`<< >>`)
6. Relational (`< <= > >=`)
7. Equality (`== !=`)
8. Bitwise AND (`&`)
9. Bitwise XOR (`^`)
10. Bitwise OR (`|`)
11. Logical AND (`&&`)
12. Logical OR (`||`)
13. Conditional (`?:`)
14. Assignment (`= += -= *= /= %= <<= >>= &= ^= |=`)
15. Comma (`,`)

#

## 3. Notes for Implementers

* The grammar is **context-sensitive** (typedef names, `_Generic`)
* Requires a **symbol table during parsing**
* `typedef-name` is not a pure identifier
* `_Generic` introduces nested parsing contexts

#

## 4. Compliance

This grammar aligns with:

* ISO/IEC 9899:2018 (C17)
* Excludes GCC/Clang extensions
* Excludes preprocessor grammar (handled separately)

#
