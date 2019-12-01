#ifndef BAGELC_VARIABLE_H_
#define BAGELC_VARIABLE_H_

#pragma once

#include "ast_node.h"

#include <stdint.h>

enum c_ast_variable_type {
    c_ast_variable_type_stack,
    c_ast_variable_type_global
};

#define c_ast_variable_name(node)        (((struct c_ast_variable *)(node))->name)
#define c_ast_variable_typename(node)    (((struct c_ast_variable *)(node))->typename)
#define c_ast_variable_type(node)        (((struct c_ast_variable *)(node))->type)
#define c_ast_variable_abs_addr(node)    (((struct c_ast_variable *)(node))->abs_addr)
#define c_ast_variable_rel_addr(node)    (((struct c_ast_variable *)(node))->rel_addr)
#define c_ast_variable_int_value(node)   (((struct c_ast_variable *)(node))->int_value)
#define c_ast_variable_float_value(node) (((struct c_ast_variable *)(node))->float_value)


struct c_ast_variable {
    c_ast_node_contents;

    char                     name[255];
    struct c_ast_typename   *typename;
    enum c_ast_variable_type type;

    uint32_t                 abs_addr;
    uint32_t                 rel_addr;

    union {
        int                     int_value;
        float                   float_value;
        struct c_ast_structure *structure_value;
    };
};

#define c_ast_variable_cast(node) ((struct c_ast_variable *)(node))

struct c_ast_node *c_ast_variable_create(const char *name, struct c_ast_typename *typename);

#endif