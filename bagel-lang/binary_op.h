#ifndef BAGELC_BINARY_OPERATOR_H_
#define BAGELC_BINARY_OPERATOR_H_

#include "ast_node.h"

#pragma once

enum c_ast_binary_op_type {
    c_ast_binary_op_addition,
    c_ast_binary_op_subtraction,

    c_ast_binary_op_assignment
};

#define c_ast_binary_op_lhs_exp(node) (((struct c_ast_binary_op *)(node))->lhs_exp)
#define c_ast_binary_op_rhs_exp(node) (((struct c_ast_binary_op *)(node))->rhs_exp)

struct c_ast_binary_op {
    c_ast_node_contents;

    struct c_ast_node *lhs_exp;
    struct c_ast_node *rhs_exp;
};

#define c_ast_binary_op_cast(node) ((struct c_ast_binary_op *)(node))

struct c_ast_node *c_ast_binary_op_create(enum c_ast_binary_op_type type, struct c_ast_node *lhs, struct c_ast_node *rhs);

#endif