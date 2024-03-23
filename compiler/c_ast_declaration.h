#ifndef C_AST_DECLARATION_H_
#define C_AST_DECLARATION_H_

#pragma once

#include "c_ast_expression.h"

#include <stddef.h>
#include <stdint.h>

//enum c_ast_var_scope {
//    c_ast_automatic_scope,
//    c_ast_static
//};

#define c_ast_decl_cast(node) ((struct c_ast_decl *)(node))

//struct c_ast_decl {
//    c_ast_node_contents
//
//    //char                   symbol[32u];
//    ////enum c_ast_var_scope   scope;
//
//    //uint32_t               addr;
//
//    //struct c_ast_typename *typename;
//
//    //union {
//    //    int                     int_value;
//    //    float                   float_value;
//    //    struct c_ast_structure *structure_value;
//    //} values;
//};

//struct c_ast_node *c_ast_decl_create(const struct c_ast_node_create_info *create_info);

#endif