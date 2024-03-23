#ifndef C_AST_PARAM_LIST_H_
#define C_AST_PARAM_LIST_H_

#pragma once

#include "c_ast_node.h"

struct c_ast_func_param;

//#define c_ast_func_sig_return_type(node) (((struct c_ast_func_sig *)(node))->return_type)
//#define c_ast_func_sig_param_list(node)  (((struct c_ast_func_sig *)(node))->param_list)

struct c_ast_param_list {
    c_ast_node_contents

    struct c_ast_decl *params;
    //struct c_ast_typename *return_type;
    //struct c_ast_variable *param_list;
};

#define c_ast_param_list_cast(node) ((struct c_ast_param_list *)(node))

struct c_ast_node *c_ast_param_list_create(struct c_ast_create_info *create_info);

#endif