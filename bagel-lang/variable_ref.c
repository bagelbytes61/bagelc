#define _CRT_SECURE_NO_WARNINGS

#include "variable_ref.h"

#include "ast_context.h"
#include "func.h"
#include "func_sig.h"
#include "source_file.h"
#include "statement_block.h"
#include "variable.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_resolve_variable_ref(struct c_ast_node *node, struct c_ast_context *context) {
    struct c_ast_node *var_ref, *var;

    {
        var_ref = c_ast_variable_ref_cast(node);
    }

    {
        struct c_ast_node *statement_block = context->current_statement_block;
        for (; statement_block != NULL; statement_block = statement_block->node_parent) {
            var = c_ast_statement_block_variables(statement_block);
            for (; var != NULL; var = c_ast_node_next(var)) {
                if (strcmp(c_ast_variable_ref_symbol(var_ref), c_ast_variable_symbol(var)) == 0) {
                    return var;
                }
            }
        }
    }

    {
        var = c_ast_func_sig_param_list(c_ast_func_func_sig(context->current_func));
        for (; var != NULL; var = c_ast_node_next(var)) {
            if (strcmp(c_ast_variable_ref_symbol(var_ref), c_ast_variable_symbol(var)) == 0) {
                return var;
            }
        }
    }

    {
        var = c_ast_source_file_vars(context->current_source_file);
        for (; var != NULL; var = c_ast_node_next(var)) {
            if (strcmp(c_ast_variable_ref_symbol(var_ref), c_ast_variable_symbol(var)) == 0) {
                return var;
            }
        }
    }

    return NULL;
}

static struct c_ast_node *c_ast_evaluate_variable_ref(struct c_ast_node *node, struct c_ast_context *context) {
    return c_ast_resolve_variable_ref(node, context);
}

struct c_ast_node *c_ast_variable_ref_create(const char *symbol) {
    struct c_ast_variable_ref *node = c_ast_variable_ref_cast(malloc(sizeof *node));
    node->node_type = c_ast_node_type_variable_ref;
    node->node_evaluate_fn = c_ast_evaluate_variable_ref;
    strcpy(node->symbol, symbol);

    return c_ast_node_cast(node);
}