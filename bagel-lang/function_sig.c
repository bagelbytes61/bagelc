#include "function_sig.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_function_sig(struct c_ast_node *node, struct c_ast_context *context) {

    {
        struct c_ast_node *param = c_ast_function_sig_param_list(node);
        for (; param != NULL; param = c_ast_node_next(param)) {
            c_ast_node_evaluate(param, context);
        }
    }

    return NULL;
}

struct c_ast_node *c_ast_function_sig_create(struct c_ast_typename *return_type, struct c_ast_function_param *param_list) {
    struct c_ast_function_sig *node = c_ast_function_sig_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_function_sig;
    node->node_evaluate_fn = c_ast_evaluate_function_sig;
    node->return_type = return_type;
    node->param_list = param_list;

    return c_ast_node_cast(node);
}