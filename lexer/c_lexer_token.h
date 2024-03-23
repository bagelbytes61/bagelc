#ifndef C_LEXER_TOKEN_H_
#define C_LEXER_TOKEN_H_

#pragma once

#include "c_view.h"

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum c_symbol_class_flag {
    c_symbol_class_space =  (1 << 0u),
    c_symbol_class_punc =   (1 << 1u),
    c_symbol_class_num =    (1 << 2u),
    c_symbol_class_hexnum = (1 << 3u),
    c_symbol_class_alpha =  (1 << 4u)
};

static const int c_symbol_class_lookup[] = {
    0 /*NUL*/, 0 /*SOH*/, 0 /*STX*/, 0 /*ETX*/, 0 /*EOT*/,
    0 /*ENQ*/, 0 /*ACK*/, 0 /*BEL*/, 0 /*BS */, 
    c_symbol_class_space,                         // TAB,
    c_symbol_class_space,                         // LF
    c_symbol_class_space,                         // VT
    c_symbol_class_space,                         // FF
    c_symbol_class_space,                         // CR
    0 /*SO */, 0 /*SI */, 0 /*DLE*/, 0 /*DC1*/, 0 /*DC2*/,
    0 /*DC3*/, 0 /*DC4*/, 0 /*NAK*/, 0 /*SYN*/, 0 /*ETB*/, 
    0 /*CAN*/, 0 /*EM */, 0 /*SUB*/, 0 /*ESC*/, 0 /*FS */, 
    0 /*GS */, 0 /*RS */, 0 /*US */,
    c_symbol_class_space,                         // Space
    c_symbol_class_punc,                          // !
    c_symbol_class_punc,                          // "
    c_symbol_class_punc,                          // #
    c_symbol_class_punc,                          // $
    c_symbol_class_punc,                          // %
    c_symbol_class_punc,                          // &
    c_symbol_class_punc,                          // '
    c_symbol_class_punc,                          // (
    c_symbol_class_punc,                          // )
    c_symbol_class_punc,                          // *
    c_symbol_class_punc,                          // +
    c_symbol_class_punc,                          // 
    c_symbol_class_punc,                          // -
    c_symbol_class_punc,                          // .
    c_symbol_class_punc,                          // /
    c_symbol_class_num,                           // 0
    c_symbol_class_num,                           // 1
    c_symbol_class_num,                           // 2
    c_symbol_class_num,                           // 3
    c_symbol_class_num,                           // 4
    c_symbol_class_num,                           // 5
    c_symbol_class_num,                           // 6
    c_symbol_class_num,                           // 7
    c_symbol_class_num,                           // 8
    c_symbol_class_num,                           // 9
    c_symbol_class_punc,                          // :
    c_symbol_class_punc,                          // ;
    c_symbol_class_punc,                          // <
    c_symbol_class_punc,                          // =
    c_symbol_class_punc,                          // >
    c_symbol_class_punc,                          // ?
    c_symbol_class_punc,                          // @
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // A(0xA)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // B(0xB)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // C(0xC)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // D(0xD)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // E(0xE)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // F(0xF)
    c_symbol_class_alpha,                         // G
    c_symbol_class_alpha,                         // H
    c_symbol_class_alpha,                         // I
    c_symbol_class_alpha,                         // J
    c_symbol_class_alpha,                         // K
    c_symbol_class_alpha,                         // L
    c_symbol_class_alpha,                         // M
    c_symbol_class_alpha,                         // N
    c_symbol_class_alpha,                         // O
    c_symbol_class_alpha,                         // P
    c_symbol_class_alpha,                         // Q
    c_symbol_class_alpha,                         // R
    c_symbol_class_alpha,                         // S
    c_symbol_class_alpha,                         // T
    c_symbol_class_alpha,                         // U
    c_symbol_class_alpha,                         // V
    c_symbol_class_alpha,                         // W
    c_symbol_class_alpha,                         // X
    c_symbol_class_alpha,                         // Y
    c_symbol_class_alpha,                         // Z
    c_symbol_class_punc,                          // [
    c_symbol_class_punc,                          // \ (prevent line continuation)
    c_symbol_class_punc,                          // ]
    c_symbol_class_punc,                          // ^
    c_symbol_class_punc,                          // _
    c_symbol_class_punc,                          // `
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // a(0xa)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // b(0xb)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // c(0xc)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // d(0xe)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // e(0xe)
    c_symbol_class_alpha
    | c_symbol_class_hexnum,                      // f(0xf)
    c_symbol_class_alpha,                         // g
    c_symbol_class_alpha,                         // h
    c_symbol_class_alpha,                         // i
    c_symbol_class_alpha,                         // j
    c_symbol_class_alpha,                         // k
    c_symbol_class_alpha,                         // l
    c_symbol_class_alpha,                         // m
    c_symbol_class_alpha,                         // n
    c_symbol_class_alpha,                         // o
    c_symbol_class_alpha,                         // p
    c_symbol_class_alpha,                         // q
    c_symbol_class_alpha,                         // r
    c_symbol_class_alpha,                         // s
    c_symbol_class_alpha,                         // t
    c_symbol_class_alpha,                         // u
    c_symbol_class_alpha,                         // v
    c_symbol_class_alpha,                         // w
    c_symbol_class_alpha,                         // x
    c_symbol_class_alpha,                         // y
    c_symbol_class_alpha,                         // z
    c_symbol_class_punc,                          // {
    c_symbol_class_punc,                          // |
    c_symbol_class_punc,                          // }
    c_symbol_class_punc,                          // ~
    0                                             // DEL
};

inline int c_isalpha(char c) {
    return !!(c_symbol_class_lookup[c] & c_symbol_class_alpha);
}

inline int c_isnum(char c) {
    return !!(c_symbol_class_lookup[c] & c_symbol_class_num);
}

inline int c_isalnum(char c) {
    return !!(c_symbol_class_lookup[c] & (c_symbol_class_alpha | c_symbol_class_num));
}

inline int c_ispunc(char c) {
    return !!(c_symbol_class_lookup[c] & c_symbol_class_punc);
}

inline int c_isspace(char c) {
    return !!(c_symbol_class_lookup[c] & c_symbol_class_space);
}

enum c_lexer_token_type {
    c_lexer_token_character,
    c_lexer_token_identifier,
    c_lexer_token_keyword,
    c_lexer_token_number,
    c_lexer_token_real,
    c_lexer_token_string,
    c_lexer_token_symbol
};

#define c_lexer_token_contents    \
    enum c_lexer_token_type type; \
    struct c_view           view; \

//struct c_lexer_keyword {
//    enum c_lexer_keyword_type type;
//};

struct c_lexer_token {
    c_lexer_token_contents
    
    //union {
    //    struct c_lexer_keyword keyword;
    //};
};

static const struct c_lexer_token c_invalid_lexer_token;

enum c_lexer_token_keyword_type {
    c_lexer_token_invalid_keyword, 

    c_lexer_token_keyword_default,
    c_lexer_token_keyword_char,
    c_lexer_token_keyword_break,
    c_lexer_token_keyword_auto,
    c_lexer_token_keyword_case,
    c_lexer_token_keyword_continue,
    c_lexer_token_keyword_const,
    c_lexer_token_keyword_do,
    c_lexer_token_keyword_double,
    c_lexer_token_keyword_else,
    c_lexer_token_keyword_enum,
    c_lexer_token_keyword_extern,
    c_lexer_token_keyword_float,
    c_lexer_token_keyword_for,
    c_lexer_token_keyword_goto,
    c_lexer_token_keyword_if,
    c_lexer_token_keyword_int,
    c_lexer_token_keyword_long,
    c_lexer_token_keyword_register,
    c_lexer_token_keyword_return,
    c_lexer_token_keyword_short,
    c_lexer_token_keyword_signed,
    c_lexer_token_keyword_sizeof,
    c_lexer_token_keyword_static,
    c_lexer_token_keyword_struct,
    c_lexer_token_keyword_switch,
    c_lexer_token_keyword_typedef,
    c_lexer_token_keyword_union,
    c_lexer_token_keyword_unsigned,
    c_lexer_token_keyword_void,
    c_lexer_token_keyword_volatile,
    c_lexer_token_keyword_while
};

//enum c_lexer_state {
//    c_lexer_state_lexing_keyword,
//    c_lexer_state_lexing_identifier
//};
//

struct c_cursor {
    struct c_view view;
    size_t        nread;
};

struct c_lexer_context {
    struct c_cursor    cursor;
    enum c_lexer_state state;

    struct {
        struct c_lexer_token tokens[100u];
        size_t ntokens;
        size_t index;
    } token_stream;
};

inline const char *c_lexer_advance(struct c_lexer_context *context) {
    return ++context->cursor.nread, ++context->cursor.view.current;
}

//inline const char *c_lexer_cursor_advance_no_track(struct c_lexer_context *context) {
//    return ++context->ccurrent;
//}

inline char c_lexer_peek(struct c_lexer_context *context) {
    return *context->cursor.view.current;
}

//inline char c_lexer_cursor_value(struct c_lexer_context *context) {
//    return *context->cursor.current;
//}

inline int c_lexer_isalpha(struct c_lexer_context *context) {
    return c_isalpha(c_lexer_peek(context));
}

inline int c_lexer_isnum(struct c_lexer_context *context) {
    return c_isnum(c_lexer_peek(context));
}

inline int c_lexer_isalnum(struct c_lexer_context *context) {
    return c_isalnum(c_lexer_peek(context));
}

inline int c_lexer_ispunc(struct c_lexer_context *context) {
    return c_ispunc(c_lexer_peek(context));
}

inline int c_lexer_isspace(struct c_lexer_context *context) {
    return c_isspace(*context->cursor.view.current);
}

inline size_t c_lexer_read_until_space(struct c_lexer_context *context) {
    for (; !c_lexer_isspace(context); c_lexer_advance(context));

    return context->cursor.nread;
}

inline size_t c_lexer_read_until_alpha(struct c_lexer_context *context) {
    for (; !c_lexer_isalpha(context); c_lexer_advance(context));

    return context->cursor.nread;
}

inline size_t c_lexer_read_until_num(struct c_lexer_context *context) {
    for (; !c_lexer_isnum(context); c_lexer_advance(context));

    return context->cursor.nread;
}
//
//inline size_t c_lexer_read_until(char c, struct c_lexer_context *context) {
//    for (; *c_lexer_cursor_at(context) != c; c_lexer_cursor_advance(context));
//
//    return context->nread;
//}
//

inline size_t c_lexer_skip_spaces(struct c_lexer_context *context) {
    size_t n = 0u;

    for (; c_lexer_isspace(context); ++n) {
        c_lexer_advance(context);
    }

    return n;
}

inline void c_lexer_reset_cursor(struct c_lexer_context *context) {
    context->cursor.view.begin = context->cursor.view.current;
    context->cursor.nread = 0u;
    //context->state = c_lexer_state_lexing_keyword;
}

inline int c_lexer_compare(struct c_lexer_context *context, char c) {
    return c_lexer_peek(context) == c;
}

inline int c_lexer_eof(struct c_lexer_context *context) {
    return c_lexer_peek(context) == '\0';
}

inline struct c_view c_lexer_cursor_view(struct c_lexer_context *context) {
    return context->cursor.view;
}

inline size_t c_lexer_nread(struct c_lexer_context *context) {
    return context->cursor.nread;
}

/*
    int main(void) {

        return 0;
    }

*/

//inline int c_lexer_context_init(struct c_lexer_context *context, const char *source) {
//    if (!source) {
//        return -1;
//    }
//
//    context->cstart = source;
//    context->ccurrent = context->cstart;
//    context->nread = 0U;
//    context->state = c_lexer_state_lexing_keyword;
//
//    return 0;
//}

inline void c_lexer_lex(struct c_lexer_context *context) {
    struct c_lexer_token *token = NULL;

    {

    }
}

#endif

static const char *c_keywords[32u] = {
        "long",     "break",     "do",     "int",     "else",     "case",     "double",     "default",
        "short",     "continue",     "struct",     "const",     "extern",     "float",     "signed",     "typedef",
        "volatile",     "char",     "enum",     "for",     "static",     "while",     "  sizeof",     "return",
        "register",     "unsigned",     "void",     "if",     "switch",     "goto",     "union",     "auto",
};

static const size_t c_keywords_len = sizeof(c_keywords_len) / sizeof(c_keywords[0]);

inline int c_lexer_check_identifier_keyword(struct c_lexer_token *token) {
    //const struct c_lexer_keyword_map_node *node = c_lexer_keyword_map;

    if (token->type != c_lexer_token_identifier) {
        return -1;
    }

    for (size_t index = 0u; index < c_keywords_len; ++index) {
        const size_t len = token->view.end - token->view.begin;
        
        if (strncmp(token->view.begin, c_keywords[index], len) == 0) {
            return c_lexer_token_keyword_for;
        }
    }
    
    return c_lexer_token_invalid_keyword;
}

//
//inline const struct c_lexer_token *c_lexer_consume_keyword(struct c_lexer_context *context) {
//
//    c_lexer_cursor_reset(context);
//
//    {
//        const char *c = c_lexer_cursor_at(context);
//        if (!isalpha(*c)) {
//            return NULL;
//        }
//
//        do {
//            switch (*c) {
//            case 'i':
//                if (c_lexer_check_for_int_keyword(c)) {
//                    if ()
//
//                        return &c_lexer_token_keyword_int;
//                }
//            default:
//                return NULL;
//            }
//        } while (c = c_lexer_cursor_advance(context));
//    }
//}
//
//inline struct c_lexer_token *c_lexer_expect_identifier(struct c_lexer_context *context) {
//
//    c_lexer_cursor_reset(context);
//
//    {
//        const char *c = c_lexer_cursor_at(context);
//        if (!isalpha(*c) && *c != '_') {
//            return NULL;
//        }
//
//        while (*(c = c_lexer_cursor_advance(context)) != '\0') {
//            if (isspace(*c)) {
//                break;
//            }
//
//            if (!isalnum(*c) && *c != '_') {
//                return NULL;
//            }
//        }
//    }
//
//    struct c_lexer_token_identifier *token = malloc(sizeof *token);
//    token->token_type = c_lexer_token_type_identifier;
//    strncpy(token->identifier, context->cstart, context->nread + 1U);
//
//    return token;
//}