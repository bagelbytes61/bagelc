#ifndef BAGELC_FUNCTION_REF_H_
#define BAGELC_FUNCTION_REF_H_

#pragma once

#include "ast_node.h"

struct c_ast_function_ref {
    c_ast_node_contents;

    char name[255];
};

#endif