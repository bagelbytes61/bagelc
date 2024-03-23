#include "c_ast_decl.h"

#include "c_ast_decl_spec.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *evaluate(struct c_ast_node *node, struct c_ast_context *context) {
    
}

struct c_ast_node *c_ast_decl_create(const struct c_ast_create_info *create_info) {
    struct c_ast_decl *node = c_ast_decl_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_decl;
    node->evaluate_fn = evaluate;
    node->decl_spec = c_ast_decl_spec_cast(create_info->ast_node);

    return c_ast_node_cast(node);
}