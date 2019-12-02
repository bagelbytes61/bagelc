#include "func_call.h"

#include "func.h"
#include "func_sig.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_func_call(struct c_ast_node *node, struct c_ast_context *context) {
    struct c_ast_node *arg, *param;

    {
        arg = c_ast_func_call_args(node);
        param = c_ast_node_evaluate(c_ast_func_call_ref(node), context);
    }

    for (; arg != NULL && param != NULL;) {

    }

    printf("CALL %s\n", c_ast_func_call_ref(node));

    return NULL;
}

struct c_ast_node *c_ast_func_call_create(struct c_ast_node *ref, struct c_ast_node *args) {
    struct c_ast_func_call *node = c_ast_func_call_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_func_call;
    node->node_evaluate_fn = c_ast_evaluate_func_call;
    node->func_ref = ref;
    node->func_args = args;

    return c_ast_node_cast(node);
}