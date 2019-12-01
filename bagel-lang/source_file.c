#define _CRT_SECURE_NO_WARNINGS

#include "source_file.h"

#include "ast_context.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_source_file(struct c_ast_node *node, struct c_ast_context *context) {

    {
        struct c_ast_node *variable = c_ast_source_file_variables(node);
        for (; variable != NULL; variable = c_ast_node_next(variable)) {
            c_ast_node_evaluate(variable, context);
        }
    }

    context->current_source_file = node;

    {
        struct c_ast_node *function = c_ast_source_file_functions(node);
        for (; function != NULL; function = c_ast_node_next(function)) {
            c_ast_node_evaluate(function, context);
        }
    }

    return NULL;
}

struct c_ast_node *c_ast_source_file_create(const char *path) {
    struct c_ast_source_file *node = c_ast_source_file_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_source_file;
    node->node_evaluate_fn = c_ast_evaluate_source_file;
    strcpy(node->path, path);

    return c_ast_node_cast(node);
}