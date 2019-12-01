#ifndef BAGELC_FUNCTION_SIG_H_
#define BAGELC_FUNCTION_SIG_H_

#pragma once

#include "ast_node.h"

#define c_ast_function_sig_return_type(node) (((struct c_ast_function_sig *)(node))->return_type)
#define c_ast_function_sig_param_list(node)  (((struct c_ast_function_sig *)(node))->param_list)

struct c_ast_function_sig {
    c_ast_node_contents;

    struct c_ast_typename *return_type;
    struct c_ast_variable *param_list;
};

#define c_ast_function_sig_cast(node) ((struct c_ast_function_sig *)(node))

struct c_ast_node *c_ast_function_sig_create(struct c_ast_typename *return_type, struct c_ast_function_param *param_list);

#endif