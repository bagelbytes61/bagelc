#include "ast_node.h"

#include <stdlib.h>

void c_ast_node_free(struct c_ast_node *node) {
    free(node);
}