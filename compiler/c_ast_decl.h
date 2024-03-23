#ifndef C_AST_DECL_H_
#define C_AST_DECL_H_

#pragma once

#include "c_ast_node.h"

struct c_ast_decl {
    c_ast_node_contents

    struct c_ast_decl_spec *decl_spec;
};

#define c_ast_decl_cast(node) ((struct c_ast_decl *)(node))

struct c_ast_node *c_ast_decl_create(const struct c_ast_create_info *create_info);

#endif