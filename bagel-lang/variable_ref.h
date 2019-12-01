#ifndef BAGELC_VARIABLE_REF_H_
#define BAGELC_VARIABLE_REF_H_

#pragma once

#include "ast_node.h"

#define c_ast_variable_ref_name(node)  (((struct c_ast_variable_ref *)(node))->name)

struct c_ast_variable_ref {
    c_ast_node_contents;

    char name[255];
};

#define c_ast_variable_ref_cast(node) ((struct c_ast_variable_ref *)(node))

struct c_ast_node *c_ast_variable_ref_create(const char *name);

#endif