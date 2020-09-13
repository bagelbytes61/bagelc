#ifndef C_AST_EXPRESSION_H_
#define C_AST_EXPRESSION_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_expression_contents   \
    c_ast_node_contents

struct c_ast_expression {
    c_ast_expression_contents;
};

#endif