#ifndef C_AST_UNARY_OP_H_
#define C_AST_UNARY_OP_H_

#include "c_ast_node.h"

#pragma once

#define c_ast_unary_op_exp(node) (((struct c_ast_unary_op *)(node))->exp)

struct c_ast_unary_op {
    c_ast_node_contents;

    struct c_ast_node *exp;
};

#endif