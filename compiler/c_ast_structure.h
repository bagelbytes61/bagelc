#ifndef C_AST_STRUCTURE_H_
#define C_AST_STRUCTURE_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_structure_fields(node) (((struct c_ast_structure *)(node)->struct_fields)

struct c_ast_structure {
    c_ast_node_contents;

    struct c_ast_node *struct_fields;
};

#define c_ast_structure_cast(node) ((struct c_ast_structure *)(node))

struct c_ast_node *c_ast_structure_create(struct c_ast_node *fields);

#endif