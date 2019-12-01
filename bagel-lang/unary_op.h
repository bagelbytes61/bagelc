#ifndef BAGELC_UNARY_OPERATOR_H_
#define BAGELC_UNARY_OPERATOR_H_

#include "ast_node.h"

#pragma once

#define c_ast_unary_op_exp(node) (((struct c_ast_unary_op *)(node))->exp)

struct c_ast_unary_op {
    c_ast_node_contents;

    struct c_ast_node *exp;
};

#endif