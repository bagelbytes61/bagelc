#ifndef C_AST_TRANSLATION_UNIT_H_
#define C_AST_TRANSLATION_UNIT_H_

#pragma once

#include "c_ast_node.h"

#define c_ast_translation_unit_path(node)      (((struct c_ast_translation_unit *)(node))->path)
#define c_ast_translation_unit_declarations(node) (((struct c_ast_translation_unit *)(node))->declarations)
#define c_ast_translation_unit_functions(node) (((struct c_ast_translation_unit *)(node))->functions)

struct c_ast_translation_unit {
    c_ast_node_contents

    char                   path[255];
    struct c_ast_decl     *declarations;
    //struct c_ast_func     *functions;
};

#define c_ast_translation_unit_cast(node) ((struct c_ast_translation_unit *)(node))

struct c_ast_node *c_ast_translation_unit_create(const struct c_ast_create_info *create_info);

#endif