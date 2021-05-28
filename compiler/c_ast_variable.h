#ifndef C_VARIABLE_H_
#define C_VARIABLE_H_

#pragma once

#include "c_ast_expression.h"

#include <stddef.h>
#include <stdint.h>

enum c_ast_variable_type {
    c_ast_variable_type_stack,
    c_ast_variable_type_global
};

#define c_ast_variable_cast(node) ((struct c_ast_variable *)(node))

#define c_ast_variable_symbol(node)      (((struct c_ast_variable *)(node))->symbol)
#define c_ast_variable_type(node)        (((struct c_ast_variable *)(node))->type)
#define c_ast_variable_addr(node)        (((struct c_ast_variable *)(node))->addr)
#define c_ast_variable_typename(node)    (((struct c_ast_variable *)(node))->typename)
#define c_ast_variable_int_value(node)   (((struct c_ast_variable *)(node))->int_value)
#define c_ast_variable_float_value(node) (((struct c_ast_variable *)(node))->float_value)

struct c_ast_variable {
    c_ast_node_contents;

    char                     symbol[32u];
    enum c_ast_variable_type type;

    uint32_t                 addr;

    struct c_ast_typename   *typename;

    union {
        int                     int_value;
        float                   float_value;
        struct c_ast_structure *structure_value;
    } values;
};

struct c_ast_node *c_ast_variable_create(const char *symbol, size_t symbol_len, struct c_ast_typename *typename, enum c_ast_variable_type type);

#endif