#include "c_ast_binary_op.h"

#include "c_ast_builtin_types.h"
//#include "c_ast_variable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_addition(struct c_ast_node *node, struct c_ast_context *context) {

    struct c_ast_node *lhs_exp = c_ast_node_evaluate(c_ast_binary_op_lhs_exp(node), context);
    struct c_ast_node *rhs_exp = c_ast_node_evaluate(c_ast_binary_op_rhs_exp(node), context);

    if (c_ast_node_type(lhs_exp) == c_ast_node_literal && c_ast_node_type(rhs_exp) == c_ast_node_literal) {


    }
    
    //if (c_ast_node_type(lhs_exp) == c_ast_node_variable) {
    //    if (c_ast_variable_type(lhs_exp) == c_ast_variable_type_stack) {
    //        printf("mov eax, DWORD [ebp + %u]\n", c_ast_variable_addr(lhs_exp));
    //    }
    //    else {
    //        printf("mov eax, DWORD [%s]\n", c_ast_variable_symbol(lhs_exp));
    //    }
    //}

    //if (c_ast_node_type(rhs_exp) == c_ast_node_variable) {
    //    if (c_ast_variable_type(rhs_exp) == c_ast_variable_type_stack) {
    //        printf("mov ebx, DWORD [ebp + %u]\n", c_ast_variable_addr(rhs_exp));
    //    }
    //    else {
    //        printf("mov ebx, DWORD [%s]\n", c_ast_variable_symbol(rhs_exp));
    //    }
    //}

    printf("add eax, ebx\n");

    return NULL;
}

static struct c_ast_node *c_ast_evaluate_subtraction(struct c_ast_node *node, struct c_ast_context * context) {

    struct c_ast_node *lhs_result = c_ast_node_evaluate(c_ast_binary_op_lhs_exp(node), context);
    struct c_ast_node *rhs_result = c_ast_node_evaluate(c_ast_binary_op_rhs_exp(node), context);

    //printf("mov eax, DWORD [ebp + %u]\n", c_ast_variable_addr(lhs_result));
    //printf("mov ebx, DWORD [ebp + %u]\n", c_ast_variable_addr(rhs_result));
    //printf("sub eax, ebx\n");

    return NULL;
}

static struct c_ast_node *c_ast_evaluate_assignment(struct c_ast_node *node, struct c_ast_context *context) {
    struct c_ast_node *lhs_result = c_ast_node_evaluate(c_ast_binary_op_lhs_exp(node), context);
    struct c_ast_node *rhs_result = c_ast_node_evaluate(c_ast_binary_op_rhs_exp(node), context);

    //printf("mov [ebp + %u], eax\n", c_ast_variable_addr(lhs_result));

    return NULL;
}

struct c_ast_node *c_ast_binary_op_create(enum c_ast_binary_op_type type, struct c_ast_node *lhs, struct c_ast_node *rhs) {

    struct c_ast_binary_op *node = c_ast_binary_op_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_binary_op;
    switch (type) {
        case c_ast_binary_op_addition:    node->evaluate_fn = c_ast_evaluate_addition;    break;
        case c_ast_binary_op_subtraction: node->evaluate_fn = c_ast_evaluate_subtraction; break;
        case c_ast_binary_op_assignment:  node->evaluate_fn = c_ast_evaluate_assignment;  break;
    }
    node->lhs_exp = lhs;
    node->rhs_exp = rhs;

    return c_ast_node_cast(node);
}