#ifndef C_AST_NODE_H_
#define C_AST_NODE_H_

#pragma once

struct c_ast_context;

typedef struct c_ast_node *(*c_ast_evaluate_fn)(struct c_ast_node *, struct c_ast_context *);

enum c_ast_node_type {
    c_ast_node_type_program,
    c_ast_node_type_source_file,

    c_ast_node_type_unary_op,
    c_ast_node_type_binary_op,

    c_ast_node_type_statement,
    c_ast_node_type_statement_block,

    c_ast_node_type_literal,

    c_ast_node_type_enum_tag,
    c_ast_node_type_struct_tag,
    c_ast_node_type_union_tag,

    c_ast_node_type_typename,

    c_ast_node_type_func_call,

    c_ast_node_type_func,
    c_ast_node_type_func_ref,

    c_ast_node_type_variable,
    c_ast_node_type_variable_ref,

    c_ast_node_type_func_arg,
    c_ast_node_type_func_param,
    c_ast_node_type_func_sig,

    c_ast_node_type_return,
};

#define c_ast_node_contents                 \
    enum c_ast_node_type node_type;         \
    c_ast_evaluate_fn    node_evaluate_fn;  \
    struct c_ast_node   *node_next;         \
    struct c_ast_node   *node_parent

#define c_ast_node_cast(node) ((struct c_ast_node *)(node))

#define c_ast_node_type(node)              ((node)->node_type)
#define c_ast_node_evaluate(node, context) ((node)->node_evaluate_fn(c_ast_node_cast(node), context))
#define c_ast_node_next(node)              ((node)->node_next)
#define c_ast_node_parent(node)            ((node)->node_parent)

struct c_ast_node {
    c_ast_node_contents;
};

static struct c_ast_node *c_ast_node_list_last(struct c_ast_node *node_list) {

    while (node_list->node_next) {
        node_list = node_list->node_next;
    }

    return node_list;
}

static struct c_ast_node *c_ast_node_list_append(struct c_ast_node *node_list, struct c_ast_node *node) {

    c_ast_node_list_last(node_list)->node_next = node;

    return node_list;
}

void c_ast_node_free(struct c_ast_node *node);

#endif