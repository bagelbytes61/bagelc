#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_translation_unit.h"

#include "c_ast_context.h"
#include "c_ast_decl_spec.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_translation_unit(struct c_ast_node *node, struct c_ast_context *context) {

    {
        //puts("SECTION .data");
        //struct c_ast_decl *decl = c_ast_translation_unit_declarations(node);
        //for (; decl != NULL; decl = c_ast_node_next(decl)) {
        //    c_ast_node_evaluate(decl, context);
        //}
    }

    context->current_translation_unit = node;

    //{
    //    puts("SECTION .text");
    //    struct c_ast_node *func = c_ast_translation_unit_functions(node);
    //    for (; func != NULL; func = c_ast_node_next(func)) {
    //        c_ast_node_evaluate(func, context);
    //    }
    //}

    return NULL;
}

struct c_ast_node *c_ast_translation_unit_create(const struct c_ast_create_info *create_info) {
    struct c_ast_translation_unit *node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_translation_unit;
    node->evaluate_fn = c_ast_evaluate_translation_unit;
    //strcpy(node->path, path);
    node->declarations = create_info->ast_node;
    //node->functions = functions;

    return c_ast_node_cast(node);
}