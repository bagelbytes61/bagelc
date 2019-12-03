#ifndef C_BUILTIN_TYPES_H_
#define C_BUILTIN_TYPES_H_

#pragma once

#include "ast_node.h"

#define c_ast_int_value(node) (((struct c_ast_int *)(node))->value)

struct c_ast_int {
    c_ast_node_contents;

    int value;
};

#define c_ast_float_value(node) (((struct c_ast_float *))(node)->value)

struct c_ast_float {
    c_ast_node_contents;

    float value;
};

#endif