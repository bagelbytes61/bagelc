#define _CRT_SECURE_NO_WARNINGS

#include "c_ast_func.h"

#include "c_ast_context.h"
#include "c_ast_decl_spec.h"
#include "c_ast_param_list.h"
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
        //struct c_ast_func_sig *func_sig = c_ast_func_signature(node);
        //c_ast_node_evaluate(func_sig, context);
    }

    context->current_func = c_ast_func_cast(node);

    {
        struct c_ast_statement_block *statement_block = c_ast_func_body(node);
        while (statement_block != NULL) {
            c_ast_node_evaluate(statement_block, context);
        
            statement_block = c_ast_node_next_typed(statement_block, c_ast_statement_block);
        }
    }

    printf("ADD ESP, DWORD %u\n", context->esp_offset - fp_offset - 4u);
    puts("POP EBP");
    puts("RET");

    context->esp_offset = fp_offset;

    return NULL;
}

struct c_ast_node *c_ast_func_create(const struct c_ast_create_info *create_info) {
    struct c_ast_func *node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_func;
    node->evaluate_fn = c_ast_evaluate_func;
    node->return_decl_spec = c_ast_decl_spec_cast(create_info->ast_node);

    create_info = create_info->next;
    strncpy(node->symbol, create_info->view.begin, c_view_len(create_info->view));

    create_info = create_info->next;
    //node->
    //strncpy(node->symbol, symbol, symbol_len);
    //node->signature = c_ast_func_sig_cast(signature);
    //node->body = c_ast_statement_block_cast(body);

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