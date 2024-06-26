#ifndef C_AST_VARIABLE_REF_H_
#define C_AST_VARIABLE_REF_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_variable_ref_symbol(node)  (((struct c_ast_variable_ref *)(node))->symbol)

struct c_ast_variable_ref {
    c_ast_node_contents

    char symbol[32u];
};

#define c_ast_variable_ref_cast(node) ((struct c_ast_variable_ref *)(node))

struct c_ast_node *c_ast_variable_ref_create(const char *symbol);

#endif