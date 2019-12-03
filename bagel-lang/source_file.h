#ifndef C_SOURCE_FILE_H_
#define C_SOURCE_FILE_H_

#pragma once

#include "ast_node.h"

#define c_ast_source_file_path(node)  (((struct c_ast_source_file *)(node))->path)
#define c_ast_source_file_vars(node)  (((struct c_ast_source_file *)(node))->vars)
#define c_ast_source_file_funcs(node) (((struct c_ast_source_file *)(node))->funcs)

struct c_ast_source_file {
    c_ast_node_contents;

    char                   path[255];
    struct c_ast_variable *vars;
    struct c_ast_func     *funcs;
};

#define c_ast_source_file_cast(node) ((struct c_ast_source_file *)(node))

struct c_ast_node *c_ast_source_file_create(const char *path, struct c_ast_node *vars, struct c_ast_node *funcs);

#endif