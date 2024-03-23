#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_decl.h"

#include "c_ast_context.h"
#include "c_ast_type_spec.h"
//#include "c_ast_v.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct c_ast_node *c_ast_evaluate_variable(struct c_ast_node *node, struct c_ast_context *context) {
    //struct c_ast_var *var = c_ast_var_cast(node);

    /*if (var->scope == c_ast_var_sc) {
        context->esp_offset += c_ast_typename_size(c_ast_variable_typename(node));
        c_ast_variable_addr(node) = context->esp_offset;

        printf("SUB ESP, %u\n", c_ast_variable_typename(node)->size);
    }
    else if (c_ast_variable_type(node) == c_ast_variable_type_global) {
        printf("%s: DB %u\n", c_ast_variable_symbol(node), c_ast_variable_typename(node)->size);
    }*/

    return NULL;
}

//struct c_ast_node *c_ast_decl_create(const struct c_ast_node_create_info *create_info) {
//    
//    struct c_ast_decl *node = malloc(sizeof *node);
//    memset(node, 0, sizeof *node);
//    //node->type = c_ast_node_variable;
//    node->evaluate_fn = c_ast_evaluate_variable;
//    //strncpy(node->symbol, symbol, symbol_len);
//    //node->typename = typename;
//    //node->type = type;
//
//    return c_ast_node_cast(node);
//}