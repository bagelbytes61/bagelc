#ifndef C_AST_LITERAL_H_
#define C_AST_LITERAL_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_literal_typename(node)    (((struct c_ast_literal *)(node))->typename)
#define c_ast_literal_int_value(node)   (((struct c_ast_literal *)(node))->value.int_value)
#define c_ast_literal_float_value(node) (((struct c_ast_literal *)(node))->value.float_value)

struct c_ast_literal {
    c_ast_node_contents;

    struct c_ast_node  *typename;

    union {
        int                     int_value;
        float                   float_value;
        struct c_ast_structure *structure_value;
    } value;
};

#define c_ast_literal_cast(node) ((struct c_ast_literal *)(node))

struct c_ast_node *c_ast_literal_create_int(int value);
struct c_ast_node *c_ast_literal_create_float(float value);

#endif