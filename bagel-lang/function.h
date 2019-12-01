#ifndef BAGELC_FUNCTION_H_
#define BAGELC_FUNCTION_H_

#pragma once

#include "ast_node.h"

#define c_ast_function_func_name(node) (((struct c_ast_function *)(node))->func_name)
#define c_ast_function_func_sig(node)  (((struct c_ast_function *)(node))->func_sig)
#define c_ast_function_func_body(node) (((struct c_ast_function *)(node))->func_body)

struct c_ast_function {
    c_ast_node_contents;

    char                         func_name[255];
    struct c_ast_function_sig   *func_sig;
    struct c_ast_statement_list *func_body;
};

#define c_ast_function_cast(node) ((struct c_ast_function *)(node))

struct c_ast_node *c_ast_function_create(const char *name, struct c_ast_function_sig *sig, struct c_ast_statement_list *body);

#endif