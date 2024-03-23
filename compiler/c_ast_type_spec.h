#ifndef C_AST_TYPE_SPEC_H_
#define C_AST_TYPE_SPEC_H_

#pragma once

#include "c_ast_node.h"

#include <stdint.h>

enum c_ast_type_spec_type {
    c_ast_type_spec_void,
    c_ast_type_spec_char,
    c_ast_type_spec_short,
    c_ast_type_spec_int,
    c_ast_type_spec_long,
    c_ast_type_spec_float,
    c_ast_type_spec_double,
    c_ast_type_spec_signed,
    c_ast_type_spec_unsigned,

    //c_ast_type_spec_struct_or_union_spec,
    //c_ast_type_spec_enum_spec,
    //c_ast_type_spec_typedef_name,

    c_ast_type_spec_max,

    c_ast_type_spec_invalid
};

#define c_ast_typename_type(node)      (((struct c_ast_typename *)(node))->type)
#define c_ast_typename_alignment(node) (((struct c_ast_typename *)(node))->alignment)
#define c_ast_typename_size(node)      (((struct c_ast_typename *)(node))->size)

struct c_ast_type_spec {
    c_ast_node_contents

    enum c_ast_type_spec_type type_spec;

    uint32_t                  alignment;
    uint32_t                  size;
};

#define c_ast_type_spec_cast(node) ((struct c_ast_type_spec *)(node))


struct c_ast_node *c_ast_type_spec_create(const struct c_ast_create_info *create_info);

//struct c_ast_node *c_ast_typename_create_builtin(enum c_ast_type_spec type);

//const char *c_ast_type_spec_to_string(struct c_ast_node *node);

#endif