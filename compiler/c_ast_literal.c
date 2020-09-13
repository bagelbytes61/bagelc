#include "c_ast_literal.h"

#include "c_ast_typename.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_literal(struct c_ast_node *node, struct c_ast_context *context) {
    return node;
}

static struct c_ast_node *c_ast_literal_create(enum c_ast_literal_type type, const void *value) {

    struct c_ast_literal *node = c_ast_literal_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_literal;
    node->node_evaluate_fn = c_ast_evaluate_literal;
    node->typename = c_ast_typename_create_builtin(type);
    switch (type) {
        case c_ast_typename_type_int: node->value.int_value = *(int *)value; break;
        case c_ast_typename_type_float: node->value.float_value = *(float *)value; break;
    }

    return c_ast_node_cast(node);
}

struct c_ast_node *c_ast_literal_create_int(int value) {
    
    return c_ast_literal_create(c_ast_typename_type_int, &value);
}

struct c_ast_node *c_ast_literal_create_float(float value) {
    
    return c_ast_literal_create(c_ast_typename_type_float, &value);
}

struct c_ast_node *c_ast_literal_create_double(double value) {

}