#ifndef C_AST_NODE_H_
#define C_AST_NODE_H_

#pragma once

#include "c_view.h"

#include "c_ast_node_type.h"

struct c_ast_context;

typedef struct c_ast_node *(*c_ast_evaluate_fn)(struct c_ast_node *, struct c_ast_context *);

enum c_ast_create_info_type {
    c_ast_create_info_view,
    c_ast_create_info_ast_node
};

struct c_ast_create_info {
    enum c_ast_create_info_type type;
    struct c_ast_create_info   *next;
    union {
        struct c_view      view;
        struct c_ast_node *ast_node;
    };
};

#define c_ast_node_contents            \
    enum c_ast_node_type type;         \
    c_ast_evaluate_fn    evaluate_fn;  \
    struct c_ast_node   *next;         \
    struct c_ast_node   *parent;


#define c_ast_node_type(node)              ((node)->type)
#define c_ast_node_evaluate(node, context) ((node)->evaluate_fn(c_ast_node_cast(node), context))
#define c_ast_node_next(node)              ((node)->next)
#define c_ast_node_next_typed(node, type)  ((struct type *)((node)->next))
#define c_ast_node_parent(node)            ((node)->parent)

struct c_ast_node {
    c_ast_node_contents
};

#define c_ast_node_cast(node) ((struct c_ast_node *)(node))

static struct c_ast_node *c_ast_node_list_last(struct c_ast_node *node_list) {

    while (node_list->next) {
        node_list = node_list->next;
    }

    return node_list;
}

static struct c_ast_node *c_ast_node_list_append(struct c_ast_node *node_list, struct c_ast_node *node) {

    c_ast_node_list_last(node_list)->next = node;

    return node_list;
}

void c_ast_node_free(struct c_ast_node *node);

#endif