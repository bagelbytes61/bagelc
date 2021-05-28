#ifndef C_AST_FUNCTION_H_
#define C_AST_FUNCTION_H_

#pragma once

#include "c_ast_node.h"

#include <stddef.h>

#define c_ast_func_symbol(node)    (((struct c_ast_func *)(node))->symbol)
#define c_ast_func_signature(node) (((struct c_ast_func *)(node))->signature)
#define c_ast_func_body(node)      (((struct c_ast_func *)(node))->body)

struct c_ast_func {
    c_ast_node_contents;

    char                          symbol[32u];
    struct c_ast_func_sig        *signature;
    struct c_ast_statement_block *body;
};

#define c_ast_func_cast(node) ((struct c_ast_func *)(node))

struct c_ast_node *c_ast_func_create(const char *symbol, size_t symbol_len, struct c_ast_node *signature, struct c_ast_node *body);

#endif