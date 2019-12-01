#ifndef BAGELC_STATEMENT_H_
#define BAGELC_STATEMENT_H_

#pragma once

#include "ast_node.h"

#define c_ast_statement_statement(node) (((struct c_ast_statement *)(node))->statement)

struct c_ast_statement {
    c_ast_node_contents;

    struct c_ast_node      *statement;
};

#define c_ast_statement_cast(node) ((struct c_ast_statement *)(node))

struct c_ast_node *c_ast_statement_create(struct c_ast_node *statement);

#endif