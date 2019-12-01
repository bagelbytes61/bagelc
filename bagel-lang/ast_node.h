#ifndef BAGELC_AST_NODE_H_
#define BAGELC_AST_NODE_H_

#pragma once

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

    c_ast_node_type_function,
    c_ast_node_type_function_ref,

    c_ast_node_type_variable,
    c_ast_node_type_variable_ref,

    c_ast_node_type_function_arg,
    c_ast_node_type_function_param,
    c_ast_node_type_function_sig,

    c_ast_node_type_return,
};

#define c_ast_node_contents                 \
    enum c_ast_node_type node_type;         \
    c_ast_evaluate_fn    node_evaluate_fn;  \
    struct c_ast_node   *node_next;         \
    struct c_ast_node   *node_parent


#define c_ast_node_type(node)              (((struct c_ast_node *)(node))->node_type)
#define c_ast_node_evaluate(node, context) (((struct c_ast_node *)(node))->node_evaluate_fn(node, context))
#define c_ast_node_next(node)              (((struct c_ast_node *)(node))->node_next)
#define c_ast_node_parent(node)            (((struct c_ast_node *)(node))->node_parent)

struct c_ast_node {
    c_ast_node_contents;
};

#define c_ast_node_cast(node) ((struct c_ast_node *)(node))

#define c_ast_node_append(node, t)                          \
    do {                                                    \
        struct c_ast_node *n = node;                        \
        if (n) {                                            \
            for (; n->node_next != NULL; n = n->node_next); \
            n->node_next = t;                               \
        }                                                   \
        else {                                              \
            node = t;                                       \
        }                                                   \
    } while (0)

void c_ast_node_free(struct c_ast_node *node);

#endif