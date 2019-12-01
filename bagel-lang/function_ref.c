#include "function_ref.h"

#include <stddef.h>

static struct c_ast_node *c_ast_resolve_function_ref(struct c_ast_node *node) {

    return NULL;
}

struct c_ast_node *c_ast_evaluate_function_ref(struct c_ast_node *node) {
    return c_ast_resolve_function_ref(node);
}