#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_source_file.h"

#include "c_ast_context.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_source_file(struct c_ast_node *node, struct c_ast_context *context) {

    {
        puts("SECTION .data");
        struct c_ast_node *variable = c_ast_source_file_variables(node);
        for (; variable != NULL; variable = c_ast_node_next(variable)) {
            c_ast_node_evaluate(variable, context);
        }
    }

    context->current_source_file = node;

    {
        puts("SECTION .text");
        struct c_ast_node *func = c_ast_source_file_functions(node);
        for (; func != NULL; func = c_ast_node_next(func)) {
            c_ast_node_evaluate(func, context);
        }
    }

    return NULL;
}

struct c_ast_node *c_ast_source_file_create(const char *path, struct c_ast_node *variables, struct c_ast_node *functions) {
    struct c_ast_source_file *node = c_ast_source_file_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_source_file;
    node->node_evaluate_fn = c_ast_evaluate_source_file;
    strcpy(node->path, path);
    node->variables = variables;
    node->functions = functions;

    return c_ast_node_cast(node);
}