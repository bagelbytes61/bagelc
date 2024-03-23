#ifndef C_PARSER_GRAMMAR_H_
#define C_PARSER_GRAMMAR_H_

#pragma once

#include <stddef.h>

#define c_bnf_subexprs(expr, ...) (const struct c_bnf_expr *[]) { expr, __VA_ARGS__, NULL }

#define c_bnf_easy_terminal_expr(v, f) (struct c_bnf_expr){ .type = c_bnf_terminal_expr, .flags = f, .terminal.value = v, .terminal.length = sizeof(v) - 1u, .debug_name = v }

#define c_bnf_easy_nonterminal_expr(f, l, s, m, a) (struct c_bnf_expr){ .type = c_bnf_nonterminal_expr, .flags = f, .lookahead_symbol = l, .nonterminal.subexprs = s, .nonterminal.match = m, .nonterminal.match_any = a }

#define c_bnf_simple_terminal_expr(v)            c_bnf_easy_terminal_expr(v, 0)
#define c_bnf_simple_terminal_expr_match_only(v) c_bnf_easy_terminal_expr(v, c_bnf_match_only)
#define c_bnf_simple_nonterminal_expr(s)         c_bnf_easy_nonterminal_expr(0, NULL, s, match, 0)

typedef struct c_ast_create_info *(*c_bnf_match_expr_fn)(struct c_lexer_token_stream *, const struct c_bnf_expr *, int *, int *);
typedef struct c_ast_node *(*c_bnf_create_ast_node_fn)(const struct c_ast_create_info *);

enum c_bnf_expr_type {
    c_bnf_terminal_expr,
    c_bnf_nonterminal_expr
};

enum c_bnf_flags {
    c_bnf_zero_or_more = 1 << 0u,
    c_bnf_one_or_more = 1 << 1u,
    c_bnf_match_best = 1 << 2u,
    c_bnf_match_only = 1 << 3u
};

struct c_bnf_terminal_expr {
    union {
        struct {
            const char *value;
            size_t      length; /* Here we are relying on the size of both data and function pointers   */
        };                      /* being the same size as to avoid overlap between 'match' and 'length' */

        c_bnf_match_expr_fn match;
    };
};

struct c_bnf_nonterminal_expr {
    size_t                    subexpr_count;
    const struct c_bnf_expr **subexprs;
    c_bnf_match_expr_fn        match;
    int                        match_any;
};

struct c_bnf_expr {
    enum c_expression_type   type;
    int                      flags;
    const char              *lookahead_symbol;
    c_bnf_create_ast_node_fn create_ast_node;
    union {
        struct c_bnf_terminal_expr    terminal;
        struct c_bnf_nonterminal_expr nonterminal;
    };
    
    int max_depth;
    const char *debug_name;
};

extern const struct c_bnf_expr c_translation_unit;

#endif