#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_func_ref.h"

#include "c_ast_context.h"
#include "c_ast_func.h"
#include "c_ast_translation_unit.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_resolve_func_ref(struct c_ast_node *node, struct c_ast_context *context) {
    struct c_ast_func_ref *func_ref = NULL;

    func_ref = c_ast_func_ref_cast(node);
    
    {
        //struct c_ast_func *func_it = context->current_translation_unit->functions;
        //for (; func_it != NULL; func_it = c_ast_node_next(func_it)) {
        //    
        //    if (strcmp(c_ast_func_ref_symbol(func_ref), c_ast_func_symbol(func_it)) == 0) {
        //        
        //        return func_it;
        //    }
        //}
    }

    return NULL;
}

struct c_ast_node *c_ast_evaluate_func_ref(struct c_ast_node *node, struct c_ast_context *context) {
    
    return c_ast_resolve_func_ref(node, context);
}

struct c_ast_node *c_ast_func_ref_create(const char *symbol) {
 
    struct c_ast_func_ref *node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_func_ref;
    node->evaluate_fn = c_ast_evaluate_func_ref;
    strcpy(node->func_symbol, symbol);

    return c_ast_node_cast(node);
}