#include "c_ast_decl_spec.h"

#include "c_ast_type_spec.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_decl(struct c_ast_node *node, struct c_ast_context *context) {

	return NULL;
}

struct c_ast_node *c_ast_decl_spec_create(const struct c_ast_create_info *create_info) {
	struct c_ast_decl_spec *node = c_ast_decl_spec_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
	node->type = c_ast_node_decl_spec;
	node->evaluate_fn = c_ast_evaluate_decl;
    node->type_spec = c_ast_type_spec_cast(create_info->ast_node);

	return c_ast_node_cast(node);
}