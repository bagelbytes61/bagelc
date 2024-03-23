#ifndef C_AST_FUNCTION_CALL_H_
#define C_AST_FUNCTION_CALL_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_func_call_ref(node)  (((struct c_ast_func_call *)(node))->func_ref)
#define c_ast_func_call_args(node) (((struct c_ast_func_call *)(node))->func_args)

struct c_ast_func_call {
    c_ast_node_contents

    struct c_ast_func_ref *func_ref;
    struct c_ast_func_arg *func_args;
};

#define c_ast_func_call_cast(node) ((struct c_ast_func_call *)(node))

struct c_ast_node *c_ast_func_call_create(struct c_ast_node *ref, struct c_ast_node *args);

#endif