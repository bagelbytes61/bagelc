#ifndef BAGELC_FUNCTION_ARG_H_
#define BAGELC_FUNCTION_ARG_H_

#pragma once

#include "ast_node.h"

struct c_ast_func_arg {
    c_ast_node_contents;

    struct c_ast_node *exp;
};

#define c_ast_func_arg_cast(node) ((struct c_ast_func_arg *)(node))

struct c_ast_node *c_ast_func_arg_create(struct c_ast_node *expression);

#endif