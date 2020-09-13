#ifndef C_LEXER_TOKEN_H_
#define C_LEXER_TOKEN_H_

#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>



struct c_lexer_token_view {
    const char *begin, *end;
};

enum c_lexer_token_type {
    c_lexer_token_type_character,
    c_lexer_token_type_number,
    c_lexer_token_type_real,
    c_lexer_token_type_string,
    c_lexer_token_type_symbol
};

#define c_lexer_token_contents          \
    enum c_lexer_token_type token_type; \
    struct c_lexer_token_view view      \

struct c_lexer_token {
    c_lexer_token_contents;
};
//enum c_lexer_token_keyword_type {
//    c_lexer_token_keyword_type_default,
//    c_lexer_token_keyword_type_char,
//    c_lexer_token_keyword_type_break,
//    c_lexer_token_keyword_type_auto,
//    c_lexer_token_keyword_type_case,
//    c_lexer_token_keyword_type_continue,
//    c_lexer_token_keyword_type_const,
//    c_lexer_token_keyword_type_do,
//    c_lexer_token_keyword_type_double,
//    c_lexer_token_keyword_type_else,
//    c_lexer_token_keyword_type_enum,
//    c_lexer_token_keyword_type_extern,
//    c_lexer_token_keyword_type_float,
//    c_lexer_token_keyword_type_for,
//    c_lexer_token_keyword_type_goto,
//    c_lexer_token_keyword_type_if,
//    c_lexer_token_keyword_type_int,
//    c_lexer_token_keyword_type_long,
//    c_lexer_token_keyword_type_register,
//    c_lexer_token_keyword_type_return,
//    c_lexer_token_keyword_type_short,
//    c_lexer_token_keyword_type_signed,
//    c_lexer_token_keyword_type_sizeof,
//    c_lexer_token_keyword_type_static,
//    c_lexer_token_keyword_type_struct,
//    c_lexer_token_keyword_type_switch,
//    c_lexer_token_keyword_type_typedef,
//    c_lexer_token_keyword_type_union,
//    c_lexer_token_keyword_type_unsigned,
//    c_lexer_token_keyword_type_void,
//    c_lexer_token_keyword_type_volatile,
//    c_lexer_token_keyword_type_while
//};

//enum c_lexer_state {
//    c_lexer_state_lexing_keyword,
//    c_lexer_state_lexing_identifier
//};
//
//struct c_lexer_context {
//    const char *cstart, *ccurrent;
//    size_t nread;
//    enum c_lexer_state state;
//};
//
//inline const char *c_lexer_cursor_advance(struct c_lexer_context *context) {
//    return ++context->nread, ++context->ccurrent;
//}
//
//inline const char *c_lexer_cursor_advance_no_track(struct c_lexer_context *context) {
//    return ++context->ccurrent;
//}
//
//inline const char *c_lexer_cursor_peek(struct c_lexer_context *context) {
//    return context->ccurrent + 1;
//}
//
//inline const char *c_lexer_cursor_at(struct c_lexer_context *context) {
//    return context->ccurrent;
//}
//
//inline size_t c_lexer_read_until_space(struct c_lexer_context *context) {
//    for (; !c_lexer_isspace(*c_lexer_cursor_at(context)); c_lexer_cursor_advance(context));
//
//    return context->nread;
//}
//
//inline size_t c_lexer_read_until_alpha(struct c_lexer_context *context) {
//    for (; !c_lexer_isalpha(*c_lexer_cursor_at(context)); c_lexer_cursor_advance(context));
//
//    return context->nread;
//}
//
//inline size_t c_lexer_read_until_numeric(struct c_lexer_context *context) {
//    for (; !c_lexer_isnum(*c_lexer_cursor_at(context)); c_lexer_cursor_advance(context));
//
//    return context->nread;
//}
//
//inline size_t c_lexer_read_until(char c, struct c_lexer_context *context) {
//    for (; *c_lexer_cursor_at(context) != c; c_lexer_cursor_advance(context));
//
//    return context->nread;
//}
//


//void c_lexer_cursor_reset(struct c_lexer_context *context) {
//    context->cstart = context->ccurrent;
//    context->nread = 0U;
//    //context->state = c_lexer_state_lexing_keyword;
//}


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


//const char *c;
//while (c = c_lexer_cursor_at(context)) {
//    switch (context->state) {
//    case c_lexer_state_lexing_keyword:
//        if (!c_lexer_isalpha(*c) && *c != '_') {
//            fprintf(stderr, "Invalid keyword format!\n");
//            abort();
//        }
//        else if (c_lexer_isspace(*c)) {
//            context->state = c_lexer_state_lexing_identifier;
//            c_lexer_cursor_reset(context);
//        }
//        continue;
//    case c_lexer_state_lexing_identifier:
//        if (c_lexer_isnum(*c))
//            break;
//    }
//}



//struct c_lexer_keyword_map_node {
//    const char *symbol;
//    struct c_lexer_token_keyword *keyword;
//    struct c_lexer_keyword *left;
//    struct c_lexer_keyword *right;
//};
//
//#define C_LEXER_TOKEN_KEYWORD(type)                            &(struct c_lexer_token_keyword)    { c_lexer_token_type_keyword, type }
//#define C_LEXER_KEYWORD_MAP_NODE(symbol, keyword, left, right) &(struct c_lexer_keyword_map_node) { symbol, keyword, left, right }
//
//const static struct c_lexer_keyword_map_node *c_lexer_keyword_map =
//C_LEXER_KEYWORD_MAP_NODE("int", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_int),
//    C_LEXER_KEYWORD_MAP_NODE("default", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_default),
//        C_LEXER_KEYWORD_MAP_NODE("char", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_char),
//            C_LEXER_KEYWORD_MAP_NODE("break", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_break),
//                C_LEXER_KEYWORD_MAP_NODE("auto", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_auto),
//                    NULL, NULL),
//                C_LEXER_KEYWORD_MAP_NODE("case", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_case),
//                    NULL, NULL))),
//        C_LEXER_KEYWORD_MAP_NODE("continue", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_continue),
//            C_LEXER_KEYWORD_MAP_NODE("const", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_const),
//                NULL, NULL),
//            NULL)),
//    C_LEXER_KEYWORD_MAP_NODE("extern", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_extern),
//        C_LEXER_KEYWORD_MAP_NODE("double", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_double),
//            C_LEXER_KEYWORD_MAP_NODE("do", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_do),
//                NULL, NULL),
//            C_LEXER_KEYWORD_MAP_NODE("else", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_else),
//                C_LEXER_KEYWORD_MAP_NODE("enum", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_enum),
//                    NULL, NULL),
//                NULL)),
//        C_LEXER_KEYWORD_MAP_NODE("goto", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_goto),
//            C_LEXER_KEYWORD_MAP_NODE("for", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_for),
//                C_LEXER_KEYWORD_MAP_NODE("float", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_float),
//                    NULL, NULL),
//                NULL),
//            C_LEXER_KEYWORD_MAP_NODE("if", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_if),
//                NULL, NULL)),
//        C_LEXER_KEYWORD_MAP_NODE("struct", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_struct),
//            C_LEXER_KEYWORD_MAP_NODE("short", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_short),
//                C_LEXER_KEYWORD_MAP_NODE("register", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_register),
//                    C_LEXER_KEYWORD_MAP_NODE("long", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_long),
//                        NULL, NULL),
//                    C_LEXER_KEYWORD_MAP_NODE("return", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_return),
//                        NULL, NULL)),
//                C_LEXER_KEYWORD_MAP_NODE("sizeof", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_sizeof),
//                    C_LEXER_KEYWORD_MAP_NODE("signed", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_signed),
//                        NULL, NULL),
//                    C_LEXER_KEYWORD_MAP_NODE("static", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_static),
//                        NULL, NULL))),
//            C_LEXER_KEYWORD_MAP_NODE("unsigned", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_unsigned),
//                C_LEXER_KEYWORD_MAP_NODE("typedef", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_typedef),
//                    C_LEXER_KEYWORD_MAP_NODE("switch", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_switch),
//                        NULL, NULL),
//                    C_LEXER_KEYWORD_MAP_NODE("union", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_union),
//                        NULL, NULL)),
//                C_LEXER_KEYWORD_MAP_NODE("volatile", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_volatile),
//                    C_LEXER_KEYWORD_MAP_NODE("void", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_void),
//                        NULL, NULL),
//                    C_LEXER_KEYWORD_MAP_NODE("while", C_LEXER_TOKEN_KEYWORD(c_lexer_token_keyword_type_while),
//                        NULL, NULL))))));

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