#ifndef C_FLOW_CONTROL_H_
#define C_FLOW_CONTROL_H_

#pragma once

#include "ast_node.h"

#define c_ast_if_exp(node)        (((struct c_ast_if *)(node))->condition_exp)
#define c_ast_if_true_path(node)  (((struct c_ast_if *)(node))->true_path)
#define c_ast_if_false_path(node) (((struct c_ast_if *)(node))->false_path)

struct c_ast_if {
    c_ast_node_contents;

    struct c_ast_node *condition_exp;
    struct c_ast_node *true_path;
    struct c_ast_node *false_path;
};


#endif