#ifndef C_AST_NODE_TYPE_H_
#define C_AST_NODE_TYPE_H_

#pragma once

enum c_ast_node_type {
    c_ast_node_program,
    c_ast_node_translation_unit,
    c_ast_node_decl,
    c_ast_node_decl_spec,
    c_ast_node_unary_op,
    c_ast_node_binary_op,

    c_ast_node_statement,
    c_ast_node_statement_block,

    c_ast_node_literal,

    c_ast_node_enum_tag,
    c_ast_node_struct_tag,
    c_ast_node_union_tag,

    c_ast_node_type_spec,

    c_ast_node_func_call,

    c_ast_node_func,
    c_ast_node_func_ref,

    c_ast_node_variable,
    c_ast_node_variable_ref,

    c_ast_node_func_arg,
    c_ast_node_func_param,
    c_ast_node_param_list,

    c_ast_node_return,
};

#endif