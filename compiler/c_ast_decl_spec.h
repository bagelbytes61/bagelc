#ifndef C_AST_DECL_SPEC_H_
#define C_AST_DECL_SPEC_H_

#pragma once

#include "c_ast_node.h"

enum c_ast_decl_spec_type {
    c_ast_decl_function
};

struct c_ast_decl_spec {
    c_ast_node_contents

    struct c_ast_type_spec *type_spec;
};

#define c_ast_decl_spec_cast(node) ((struct c_ast_decl_spec *)(node))

//struct c_ast_decl_create_info {
//
//};

struct c_ast_node *c_ast_decl_spec_create(const struct c_ast_create_info *create_info);

#endif