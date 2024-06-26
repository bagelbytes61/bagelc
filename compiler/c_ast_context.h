#ifndef C_AST_CONTEXT_H_
#define C_AST_CONTEXT_H_

#pragma once

#include <stdint.h>

#define c_ast_context_eax_status(context) ((context)->eax_status & 0x01)
#define c_ast_context__ax_status(context) ((context)->eax_status & 0x02)

#define c_ast_context_ebx_status(context) ((context)->ebx_status & 0x01)
#define c_ast_context__bx_status(context) ((context)->ebx_status & 0x02)

#define c_ast_context_ecx_status(context) ((context)->ecx_status & 0x01)
#define c_ast_context__cx_status(context) ((context)->ecx_status & 0x02)

#define c_ast_context_edx_status(context) ((context)->edx_status & 0x01)
#define c_ast_context__dx_status(context) ((context)->edx_status & 0x02)

uint8_t eax_status, ebx_status;
uint8_t ecx_status, edx_status;

uint8_t esi_status, edi_status, ebp_status;
uint8_t eip_status, esp_status;

struct c_ast_context {
    struct c_ast_translation_unit *current_translation_unit;
    struct c_ast_func             *current_func;
    struct c_ast_statement_block  *current_statement_block;

    uint32_t esp_offset;

};

void c_ast_context_init(struct c_ast_context *context);

#endif