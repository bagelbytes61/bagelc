#ifndef C_AST_RETURN_H_
#define C_AST_RETURN_H_

#pragma once

#include "ast_node.h"

#define c_ast_return_exp(node) (((struct c_ast_return *)(node))->exp)

struct c_ast_return {
    c_ast_node_contents;

    struct c_ast_node *exp;
};

#define c_ast_return_cast(node) ((struct c_ast_return *)(node))

struct c_ast_node *c_ast_return_create(struct c_ast_node *exp);

#endif