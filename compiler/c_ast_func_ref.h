#ifndef C_FUNCTION_REF_H_
#define C_FUNCTION_REF_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_func_ref_symbol(node) (((struct c_ast_func_ref *)(node))->func_symbol)

struct c_ast_func_ref {
    c_ast_node_contents

    char func_symbol[32u];
};

#define c_ast_func_ref_cast(node) ((struct c_ast_func_ref *)(node))

struct c_ast_node *c_ast_func_ref_create(const char *symbol);

#endif