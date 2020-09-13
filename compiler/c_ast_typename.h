#ifndef C_AST_TYPENAME_H_
#define C_AST_TYPENAME_H_

#pragma once

#include "c_ast_node.h"

#include <stdint.h>

enum c_ast_typename_type {
    c_ast_typename_type_void,

    c_ast_typename_type_signed_char,
    c_ast_typename_type_unsigned_char,
    c_ast_typename_type_char,

    c_ast_typename_type_short_int,
    c_ast_typename_type_int,
    c_ast_typename_type_long_int,
    c_ast_typename_type_long_long_int,

    c_ast_typename_type_float,
    c_ast_typename_type_double,

    c_ast_typename_type_enum,
    c_ast_typename_type_struct,
    c_ast_typenane_type_union,
    
    c_ast_typename_type_typedef,

    c_ast_typename_type_unknown
};

#define c_ast_typename_type(node)      (((struct c_ast_typename *)(node))->type)
#define c_ast_typename_alignment(node) (((struct c_ast_typename *)(node))->alignment)
#define c_ast_typename_size(node)      (((struct c_ast_typename *)(node))->size)

struct c_ast_typename {
    c_ast_node_contents;

    enum c_ast_typename_type type;

    uint32_t                 alignment;
    uint32_t                 size;
};

#define c_ast_typename_cast(node) ((struct c_ast_typename *)(node))

struct c_ast_node *c_ast_typename_create_builtin(enum c_ast_typename_type type);

const char *c_ast_typename_type_to_string(struct c_ast_node *node);

enum c_ast_typename_type c_ast_string_to_typename_type(const char *type, size_t len);

#endif