#include "c_ast_return.h"

#include "c_ast_context.h"
#include "c_ast_type_spec.h"
//#include "c_ast_variable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_return(struct c_ast_node *node, struct c_ast_context *context) {
    struct c_ast_return *ret = c_ast_return_cast(node);

    struct c_ast_node *expression = NULL;

    {
        expression = c_ast_node_evaluate(ret->exp, context);
    }

    if (c_ast_node_type(ret->exp) != c_ast_node_func_call) {
        if (c_ast_node_type(expression) == c_ast_node_variable) {
            //if (c_ast_variable_type(expression) == c_ast_variable_type_stack) {
            //    printf("MOV EAX, [EBP + %u]\n", c_ast_variable_addr(expression));
            //}
            //else {
            //    printf("MOV EAX, %s\n", c_ast_variable_symbol(expression));
            //}
        }
    }

    return node;
}

struct c_ast_node *c_ast_return_create(struct c_ast_node *exp) {
    struct c_ast_return *node = c_ast_return_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_return;
    node->evaluate_fn = c_ast_evaluate_return;
    node->exp = exp;

    return c_ast_node_cast(node);
}