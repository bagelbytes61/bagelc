#include "typename.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_typename(struct c_ast_node *node, struct c_ast_context *context) {

    return NULL;
}

struct c_ast_node *c_ast_typename_create_builtin(enum c_ast_typename_type type) {
    struct c_ast_typename *node = c_ast_typename_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_typename;
    node->type = type;
    switch (node->type) {
        case c_ast_typename_type_int:
        case c_ast_typename_type_float:
            node->alignment = 4U;
            node->size = 4U;
        break;
    }
    
    return c_ast_node_cast(node);
}