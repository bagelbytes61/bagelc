#define _CRT_SECURE_NO_WARNINGS

#include "func_ref.h"

#include "ast_context.h"
#include "func.h"
#include "source_file.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_resolve_func_ref(struct c_ast_node *node, struct c_ast_context *context) {
    struct c_ast_node *func_ref, *func;

    {
        func_ref = node;
    }

    {
        func = c_ast_source_file_funcs(context->current_source_file);
        for (; func != NULL; func = c_ast_node_next(func)) {
            if (strcmp(c_ast_func_ref_symbol(func_ref), c_ast_func_func_symbol(func)) == 0) {
                return func;
            }
        }
    }

    return NULL;
}

struct c_ast_node *c_ast_evaluate_func_ref(struct c_ast_node *node, struct c_ast_context *context) {
    return c_ast_resolve_func_ref(node, context);
}

struct c_ast_node *c_ast_func_ref_create(const char *symbol) {
    struct c_ast_func_ref *node = c_ast_func_ref_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_func_ref;
    node->node_evaluate_fn = c_ast_evaluate_func_ref;
    strcpy(node->func_symbol, symbol);

    return c_ast_node_cast(node);
}