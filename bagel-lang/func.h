#ifndef BAGELC_FUNCTION_H_
#define BAGELC_FUNCTION_H_

#pragma once

#include "ast_node.h"

#define c_ast_func_func_symbol(node) (((struct c_ast_func *)(node))->func_symbol)
#define c_ast_func_func_sig(node)    (((struct c_ast_func *)(node))->func_sig)
#define c_ast_func_func_body(node)   (((struct c_ast_func *)(node))->func_body)

struct c_ast_func {
    c_ast_node_contents;

    char               func_symbol[255];
    struct c_ast_node *func_sig;
    struct c_ast_node *func_body;
};

#define c_ast_func_cast(node) ((struct c_ast_func *)(node))

struct c_ast_node *c_ast_func_create(const char *symbol, struct c_ast_node *sig, struct c_ast_node *body);

#endif