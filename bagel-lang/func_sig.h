#ifndef BAGELC_FUNC_SIG_H_
#define BAGELC_FUNC_SIG_H_

#pragma once

#include "ast_node.h"

struct c_ast_func_param;

#define c_ast_func_sig_return_type(node) (((struct c_ast_func_sig *)(node))->return_type)
#define c_ast_func_sig_param_list(node)  (((struct c_ast_func_sig *)(node))->param_list)

struct c_ast_func_sig {
    c_ast_node_contents;

    struct c_ast_typename *return_type;
    struct c_ast_variable *param_list;
};

#define c_ast_func_sig_cast(node) ((struct c_ast_func_sig *)(node))

struct c_ast_node *c_ast_func_sig_create(struct c_ast_node *return_type, struct c_ast_node *param_list);

#endif