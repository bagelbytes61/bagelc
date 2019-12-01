#define _CRT_SECURE_NO_WARNINGS

#include "function.h"

#include "ast_context.h"
#include "statement_block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct c_ast_node *c_ast_evaluate_function(struct c_ast_node *node, struct c_ast_context *context) {
    printf("%s:\n", c_ast_function_func_name(node));
    puts("PUSH EBP");
    puts("MOV  EBP, ESP");

    {
        struct c_ast_node *function = c_ast_function_func_sig(node);
        c_ast_node_evaluate(function, context);
    }

    context->current_function = node;

    {
        struct c_ast_node *statement_list = c_ast_function_func_body(node);
        for (; statement_list != NULL; statement_list = c_ast_node_next(statement_list)) {
            c_ast_node_evaluate(statement_list, context);
        }
    }

    printf("ADD ESP, DWORD %u\n", context->esp_offset);
    puts("POP EBP");
    printf("RET");

    return NULL;
}

struct c_ast_node *c_ast_function_create(const char *func_name, struct c_ast_function_sig *func_sig, struct c_ast_statement_list *func_body) {
    struct c_ast_function *node = c_ast_function_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_function;
    node->node_evaluate_fn = c_ast_evaluate_function;
    strcpy(node->func_name, func_name);
    node->func_sig = func_sig;
    node->func_body = func_body;

    return c_ast_node_cast(node);
}

//if (c_ast_context__ax_status(context)) {
//    if (c_ast_context_eax_status(context)) {
//        puts("PUSH EAX");
//    }
//    else {
//        puts("PUSH AX");
//    }
//}
//
//if (c_ast_context__ax_status(context)) {
//    if (c_ast_context_eax_status(context)) {
//        puts("PUSH EAX");
//    }
//    else {
//        puts("PUSH AX");
//    }
//}