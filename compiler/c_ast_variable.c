#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_variable.h"

#include "c_ast_context.h"
#include "c_ast_typename.h"
#include "c_ast_variable.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct c_ast_node *c_ast_evaluate_variable(struct c_ast_node *node, struct c_ast_context *context) {

    if (c_ast_variable_type(node) == c_ast_variable_type_stack) {
        context->esp_offset += c_ast_typename_size(c_ast_variable_typename(node));
        c_ast_variable_addr(node) = context->esp_offset;

        printf("SUB ESP, %u\n", c_ast_variable_typename(node)->size);
    }
    else if (c_ast_variable_type(node) == c_ast_variable_type_global) {
        printf("%s: DB %u\n", c_ast_variable_symbol(node), c_ast_variable_typename(node)->size);
    }

    return NULL;
}

struct c_ast_node *c_ast_variable_create(const char *symbol, size_t symbol_len, struct c_ast_typename *typename, enum c_ast_variable_type type) {
    
    struct c_ast_variable *node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_variable;
    node->node_evaluate_fn = c_ast_evaluate_variable;
    strncpy(node->symbol, symbol, symbol_len);
    node->typename = typename;
    node->type = type;

    return c_ast_node_cast(node);
}