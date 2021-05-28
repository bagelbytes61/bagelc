#ifndef C_STATEMENT_BLOCK_H_
#define C_STATEMENT_BLOCK_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_statement_block_variables(node)  (((struct c_ast_statement_block *)(node))->variables)
#define c_ast_statement_block_statements(node) (((struct c_ast_statement_block *)(node))->statements)
#define c_ast_statement_block_next(node)       (((struct c_ast_statement_block *)(node))->next)
#define c_ast_statement_block_parent(node)     (((struct c_ast_statement_block *)(node))->parent)

struct c_ast_statement_block {
    c_ast_node_contents;

    struct c_ast_variable *variables;
    struct c_ast_statement *statements;
};

#define c_ast_statement_block_cast(node) ((struct c_ast_statement_block *)(node))

struct c_ast_node *c_ast_statement_block_create(struct c_ast_variable *vars, struct c_ast_statements *statements);

#endif