#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_func.h"

#include "c_ast_context.h"
#include "c_ast_statement_block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct c_ast_node *c_ast_evaluate_func(struct c_ast_node *node, struct c_ast_context *context) {
    const uint32_t fp_offset = context->esp_offset;

    printf("%s:\n", c_ast_func_symbol(node));
    puts("PUSH EBP");
    puts("MOV  EBP, ESP"); 

    context->esp_offset += 4;
    
    {
        struct c_ast_node *func = c_ast_func_signature(node);
        c_ast_node_evaluate(func, context);
    }

    context->current_func = node;

    {
        struct c_ast_node *statement_block = c_ast_func_body(node);
        for (; statement_block != NULL; statement_block = c_ast_node_next(statement_block)) {
            c_ast_node_evaluate(statement_block, context);
        }
    }

    printf("ADD ESP, DWORD %u\n", context->esp_offset - fp_offset - 4u);
    puts("POP EBP");
    puts("RET");

    context->esp_offset = fp_offset;

    return NULL;
}

struct c_ast_node *c_ast_func_create(const char *symbol, size_t symbol_len, struct c_ast_node *signature, struct c_ast_node *body) {

    struct c_ast_func *node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->node_type = c_ast_node_type_func;
    node->node_evaluate_fn = c_ast_evaluate_func;
    strncpy(node->symbol, symbol, symbol_len);
    node->signature = signature;
    node->body = body;

    return c_ast_node_cast(node);
}

void c_ast_func_destroy(struct c_ast_node *node) {
    struct c_ast_func *func = c_ast_func_cast(node);

    free(func);
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