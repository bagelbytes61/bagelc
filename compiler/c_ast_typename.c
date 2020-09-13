#include "c_ast_typename.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_typename(struct c_ast_node *node, struct c_ast_context *context) {

    return NULL;
}

struct c_ast_node *c_ast_typename_create_builtin(enum c_ast_typename_type type) {
    struct c_ast_typename *node = c_ast_typename_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_typename;
    node->type = type;
    switch (node->type) {
        case c_ast_typename_type_int:
        case c_ast_typename_type_float:
            node->alignment = 4U;
            node->size = 4U;
        break;
    }
    
    return c_ast_node_cast(node);
}

const char *c_ast_typename_type_to_string(struct c_ast_node *node) {
    switch (c_ast_typename_type(node)) {
        case c_ast_typename_type_void:          return "void";
        case c_ast_typename_type_signed_char:   return "signed char";
        case c_ast_typename_type_unsigned_char: return "unsigned char";
        case c_ast_typename_type_char:          return "char";
        case c_ast_typename_type_short_int:     return "short int";
        case c_ast_typename_type_int:           return "int";
        case c_ast_typename_type_long_int:      return "long int";
        case c_ast_typename_type_float: return "float";
    }

    return NULL;
}

enum c_ast_typename_type c_ast_string_to_typename_type(const char *type, size_t len) {
    if (strncmp(type, "int", len) == 0) {
        return c_ast_typename_type_int;
    }
    else if (strncmp(type, "float", len) == 0) {
        return c_ast_typename_type_float;
    }

    return c_ast_typename_type_unknown;
}