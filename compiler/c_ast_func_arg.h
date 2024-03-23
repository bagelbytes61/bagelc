#ifndef C_AST_FUNCTION_ARG_H_
#define C_AST_FUNCTION_ARG_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_func_arg_exp(node) (((struct c_ast_func_arg *)(node))->exp)

struct c_ast_func_arg {
    c_ast_node_contents

    struct c_ast_node *exp;
};

#define c_ast_func_arg_cast(node) ((struct c_ast_func_arg *)(node))

struct c_ast_node *c_ast_func_arg_create(struct c_ast_node *expression);

#endif