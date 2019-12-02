#ifndef BAGELC_AST_TYPENAME_H_
#define BAGELC_AST_TYPENAME_H_

#pragma once

#include "ast_node.h"

#include <stdint.h>

enum c_ast_typename_type {
    c_ast_typename_type_int,
    c_ast_typename_type_float,

    c_ast_typename_type_typedef
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

#endif