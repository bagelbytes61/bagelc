#include "structure.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_structure(struct c_ast_node *node, struct c_ast_context *context) {

    return NULL;
}

struct c_ast_node *c_ast_structure_create(struct c_ast_variable *fields) {
    struct c_ast_structure *node = c_ast_structure_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_struct_tag;
    node->node_evaluate_fn = c_ast_evaluate_structure;
    node->struct_fields = fields;

    return c_ast_node_cast(node);
}