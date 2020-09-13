#include "c_ast_statement.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_statement(struct c_ast_node *node, struct c_ast_context *context) {
    c_ast_node_evaluate(c_ast_statement_statement(node), context);

    return NULL;
}

struct c_ast_node *c_ast_statement_create(struct c_ast_node *statement) {
    struct c_ast_statement *node = c_ast_statement_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_statement;
    node->node_evaluate_fn = c_ast_evaluate_statement;
    node->statement = statement;

    return c_ast_node_cast(node);
}