#ifndef BAGELC_STATEMENT_BLOCK_H_
#define BAGELC_STATEMENT_BLOCK_H_

#pragma once

#include "ast_node.h"

#define c_ast_statement_block_variables(node)  (((struct c_ast_statement_block *)(node))->variables)
#define c_ast_statement_block_statements(node) (((struct c_ast_statement_block *)(node))->statements)
#define c_ast_statement_block_next(node)       (((struct c_ast_statement_block *)(node))->next)
#define c_ast_statement_block_parent(node)     (((struct c_ast_statement_block *)(node))->parent)

struct c_ast_statement_block {
    c_ast_node_contents;

    struct c_ast_node *variables;
    struct c_ast_node *statements;
};

#define c_ast_statement_block_cast(node) ((struct c_ast_statement_block *)(node))

struct c_ast_node *c_ast_statement_block_create(struct c_ast_node *vars, struct c_ast_node *statements);

#endif