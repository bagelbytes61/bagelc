#ifndef C_AST_SOURCE_FILE_H_
#define C_AST_SOURCE_FILE_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_source_file_path(node)      (((struct c_ast_source_file *)(node))->path)
#define c_ast_source_file_variables(node) (((struct c_ast_source_file *)(node))->variables)
#define c_ast_source_file_functions(node) (((struct c_ast_source_file *)(node))->functions)

struct c_ast_source_file {
    c_ast_node_contents;

    char                   path[255];
    struct c_ast_variable *variables;
    struct c_ast_func     *functions;
};

#define c_ast_source_file_cast(node) ((struct c_ast_source_file *)(node))

struct c_ast_node *c_ast_source_file_create(const char *path, struct c_ast_node *variables, struct c_ast_node *functions);

#endif