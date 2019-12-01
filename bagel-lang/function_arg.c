#include "function_arg.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_function_arg(struct c_ast_node *node, struct c_ast_context *context) {

    c_ast_node_evaluate(node, context);

    return NULL;
}

struct c_ast_node *c_ast_function_arg_create(struct c_ast_node *expression) {
    struct c_ast_function_arg *node = c_ast_function_arg_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_function_arg;
    node->node_evaluate_fn = c_ast_evaluate_function_arg;
    node->exp = expression;

    return c_ast_node_cast(node);
}