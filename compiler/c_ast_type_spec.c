#include "c_ast_type_spec.h"

#include "c_view.h"

#include <stdlib.h>
#include <string.h>

static const char *c_type_spec_strings[] = {
    [c_ast_type_spec_void] = "void",
    [c_ast_type_spec_char] = "char",
    [c_ast_type_spec_short] = "short",
    [c_ast_type_spec_int] = "int",
    [c_ast_type_spec_long] = "long",
    [c_ast_type_spec_float] = "float",
    [c_ast_type_spec_double] = "double",
    [c_ast_type_spec_signed] = "signed",
    [c_ast_type_spec_unsigned] = "unsigned"
};

static enum c_ast_type_spec_type c_ast_string_to_type_spec(const struct c_view *view) {
    size_t index;

    for (index = 0u; index < c_ast_type_spec_max; ++index) {
        if (strncmp(view->begin, c_type_spec_strings[index], strlen(c_type_spec_strings[index])) == 0) {
            return index;
        }
    }
    
    return c_ast_type_spec_invalid;
}

static struct c_ast_node *c_ast_evaluate_typespec(struct c_ast_node *node, struct c_ast_context *context) {

    return NULL;
}

//struct c_ast_node *c_ast_typename_create_builtin(enum c_ast_typename_type type) {
//
//
//
//    //struct c_ast_type_spec *node = malloc(sizeof *node);
//    //memset(node, 0, sizeof *node);
//    //node->type = c_ast_node_typename;
//    //node->type = type;
//
//
//
//
//    switch (node->type) {
//        //case c_ast_typename_type_int:
//        //case c_ast_typename_type_float:
//            //node->alignment = 4U;
//            //node->size = 4U;
//        //break;
//    }
//    
//    return c_ast_node_cast(node);
//}

//const char *c_ast_typename_type_to_string(struct c_ast_node *node) {
//    switch (c_ast_typename_type(node)) {
//        case c_ast_typename_type_void:          return "void";
//        case c_ast_typename_type_signed_char:   return "signed char";
//        case c_ast_typename_type_unsigned_char: return "unsigned char";
//        case c_ast_typename_type_char:          return "char";
//        case c_ast_typename_type_short_int:     return "short int";
//        case c_ast_typename_type_int:           return "int";
//        case c_ast_typename_type_long_int:      return "long int";
//        case c_ast_typename_type_float: return "float";
//    }
//
//    return NULL;
//}
//
//enum c_ast_typename_type c_ast_string_to_typename_type(const char *type, size_t len) {

//}

struct c_ast_node *c_ast_type_spec_create(const struct c_ast_create_info *create_info) {
    struct c_ast_type_spec *node = NULL;

    enum c_ast_type_spec_type type_spec = c_ast_string_to_type_spec(&create_info->view);
    if (type_spec == c_ast_type_spec_invalid) {
        return NULL;
    }

    node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_type_spec;
    node->evaluate_fn = c_ast_evaluate_typespec;
    node->type_spec = type_spec;

    return c_ast_node_cast(node);
}