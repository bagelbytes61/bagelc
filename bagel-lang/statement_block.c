#include "statement_block.h"

#include "ast_context.h"
#include "statement.h"
#include "variable.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_statement_block(struct c_ast_node *node, struct c_ast_context *context) {
    {
        struct c_ast_variable *variable = c_ast_statement_block_variables(node);
        for (; variable != NULL; variable = c_ast_node_next(variable)) {
            c_ast_node_evaluate(variable, context);
        }
    }

    if (!context->current_statement_block) {
        context->current_statement_block = node;
    }
    else {
        node->node_parent = context->current_statement_block;
        context->current_statement_block = node;
    }

    {
        struct c_ast_statement *statement = c_ast_statement_block_statements(node);
        for (; statement != NULL; statement = c_ast_node_next(statement)) {
            c_ast_node_evaluate(statement, context);
        }
    }

    if (context->current_statement_block->node_parent != NULL) {
        context->current_statement_block = context->current_statement_block->node_parent;
    }

    return NULL;
}

struct c_ast_node *c_ast_statement_block_create(void) {
    struct c_ast_statement_block *node = c_ast_statement_block_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_statement_block;
    node->node_evaluate_fn = c_ast_evaluate_statement_block;

    return c_ast_node_cast(node);
}