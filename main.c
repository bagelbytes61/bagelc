#define _CRT_SECURE_NO_WARNINGS

#include "compiler/c_ast_context.h"
#include "compiler/c_ast_literal.h"
#include "compiler/c_ast_binary_op.h"
#include "compiler/c_ast_func.h"
#include "compiler/c_ast_func_call.h"
#include "compiler/c_ast_func_ref.h"
#include "compiler/c_ast_func_sig.h"
#include "compiler/c_ast_return.h"
#include "compiler/c_ast_source_file.h"
#include "compiler/c_ast_statement.h"
#include "compiler/c_ast_statement_block.h"
#include "compiler/c_ast_typename.h"
#include "compiler/c_ast_variable.h"
#include "compiler/c_ast_variable_ref.h"

//struct c_ast_node *c_ast_evaluate_integer(struct c_ast_node *node) {
//    return node;
//}
//
//static const struct c_ast_binary_op root = {
//    .evaluate_fn = c_ast_evaluate_addition,
//    .type = c_ast_type_addition,
//    .lhs_exp = &(struct c_ast_binary_op) { .evaluate_fn = c_ast_evaluate_subtraction, .type = c_ast_type_subtraction,
//        .lhs_exp = &(struct c_ast_integer) { .evaluate_fn = c_ast_evaluate_integer, .type = c_ast_type_integer, .value = 3 },
//        .rhs_exp = &(struct c_ast_integer) { .evaluate_fn = c_ast_evaluate_integer,.type = c_ast_type_integer, .value = 7 }
//    },
//    .rhs_exp = &(struct c_ast_binary_op) { .evaluate_fn = c_ast_evaluate_addition, .type = c_ast_type_addition,
//        .lhs_exp = &(struct c_ast_integer) { .evaluate_fn = c_ast_evaluate_integer, .type = c_ast_type_integer,.value = 21 },
//        .rhs_exp = &(struct c_ast_integer) { .evaluate_fn = c_ast_evaluate_integer, .type = c_ast_type_integer,.value = 50 }
//    }
//};
//
///*
//{
//    var x, y;
//    x + y;
//    {
//
//    }
//}
//*/
//
//static const struct c_ast_statement_list root = {
//    .node_evaluate_fn = c_ast_evaluate_statement_list,
//    .variables = &(struct c_ast_variable) { .name = "x", .integer_value = 5, .type = c_ast_variable_type_integer, 
//        .next = NULL },
//    .statements = NULL,
//    .next = &(struct c_ast_statement_list) {
//        .node_evaluate_fn = c_ast_evaluate_statement_list,
//        .variables = &(struct c_ast_variable) { .name = "a",.integer_value = 5,.type = c_ast_variable_type_integer,
//            .next = NULL }
//        },
//        .statements = &(struct c_ast_statement) { .statement = &(struct c_ast_binary_op) { .node_evaluate_fn = c_ast_evaluate_addition,
//            .lhs_exp = &(struct c_ast_variable_reference) { .node_evaluate_fn = c_ast_evaluate_variable, .name = "a", .scope = &root.next },
//            .rhs_exp = &(struct c_ast_variable_reference) { .node_evaluate_fn = c_ast_evaluate_variable, .name = "x", .scope = &root }
//        }
//    }
//};

int main(int argc, char *argv[]) {
    struct c_ast_context context;
    c_ast_context_init(&context);

    struct c_ast_node *var_list = c_ast_variable_create("global_var", 10u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_global);
    struct c_ast_node *func_list =
    c_ast_node_list_append(
        c_ast_func_create("add", 3u,
            c_ast_func_sig_create(
                c_ast_typename_create_builtin(c_ast_typename_type_int),
                c_ast_node_list_append(c_ast_variable_create("x", 1u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_stack),
                    c_ast_variable_create("y", 1u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_stack))),
            c_ast_statement_block_create(
                c_ast_variable_create("result", 6u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_stack),
                c_ast_node_list_append(
                    c_ast_node_list_append(
                        c_ast_statement_create(
                            c_ast_binary_op_create(c_ast_binary_op_assignment,
                                c_ast_variable_ref_create("result"),
                                c_ast_binary_op_create(c_ast_binary_op_addition,
                                    c_ast_variable_ref_create("x"),
                                    c_ast_variable_ref_create("y")))),
                        c_ast_statement_create(
                            c_ast_binary_op_create(c_ast_binary_op_assignment,
                                c_ast_variable_ref_create("result"),
                                c_ast_binary_op_create(c_ast_binary_op_addition,
                                    c_ast_variable_ref_create("result"),
                                c_ast_variable_ref_create("global_var"))))),
                        c_ast_statement_create(
                            c_ast_return_create(c_ast_variable_ref_create("result")))))),

        c_ast_func_create("main", 4u,
            c_ast_func_sig_create(
                c_ast_typename_create_builtin(c_ast_typename_type_int),
                NULL),
            c_ast_statement_block_create(
                NULL,
                c_ast_statement_create(
                    c_ast_return_create(
                        c_ast_func_call_create(
                            c_ast_func_ref_create("add"),
                            c_ast_node_list_append(
                                c_ast_literal_create_int(10),
                                c_ast_literal_create_int(5))))))));


    struct c_ast_node *main_source = c_ast_source_file_create("main.c", var_list, func_list);

    c_ast_node_evaluate(main_source, &context);

    return 0;
}

//#include "lexer/c_lexer_token.h"

//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//enum c_symbol_class_flag {
//    c_symbol_class_flag_space =  (1 << 0U),
//    c_symbol_class_flag_punc =   (1 << 1U),
//    c_symbol_class_flag_num =    (1 << 2U),
//    c_symbol_class_flag_hexnum = (1 << 3U),
//    c_symbol_class_flag_alpha =  (1 << 4U)
//};
//
//static const int c_symbol_class_lookup[] = {
//    0 /*NUL*/, 0 /*SOH*/, 0 /*STX*/, 0 /*ETX*/, 0 /*EOT*/,
//    0 /*ENQ*/, 0 /*ACK*/, 0 /*BEL*/, 0 /*BS */, 
//    c_symbol_class_flag_space,                        // TAB,
//    c_symbol_class_flag_space,                        // LF
//    c_symbol_class_flag_space,                        // VT
//    c_symbol_class_flag_space,                        // FF
//    c_symbol_class_flag_space,                        // CR
//    0 /*SO */, 0 /*SI */, 0 /*DLE*/, 0 /*DC1*/, 0 /*DC2*/,
//    0 /*DC3*/, 0 /*DC4*/, 0 /*NAK*/, 0 /*SYN*/, 0 /*CAN*/, 
//    0 /*ETB*/, 0 /*EM */, 0 /*SUB*/, 0 /*ESC*/, 0 /*FS */, 
//    0 /*GS */, 0 /*RS */, 0 /*US */,
//    c_symbol_class_flag_space,                        // Space
//    c_symbol_class_flag_punc,                         // !
//    c_symbol_class_flag_punc,                         // "
//    c_symbol_class_flag_punc,                         // #
//    c_symbol_class_flag_punc,                         // $
//    c_symbol_class_flag_punc,                         // %
//    c_symbol_class_flag_punc,                         // &
//    c_symbol_class_flag_punc,                         // '
//    c_symbol_class_flag_punc,                         // (
//    c_symbol_class_flag_punc,                         // )
//    c_symbol_class_flag_punc,                         // *
//    c_symbol_class_flag_punc,                         // +
//    c_symbol_class_flag_punc,                         // `
//    c_symbol_class_flag_punc,                         // .
//    c_symbol_class_flag_punc,                         // /
//    c_symbol_class_flag_num,                          // 0
//    c_symbol_class_flag_num,                          // 1
//    c_symbol_class_flag_num,                          // 2
//    c_symbol_class_flag_num,                          // 3
//    c_symbol_class_flag_num,                          // 4
//    c_symbol_class_flag_num,                          // 5
//    c_symbol_class_flag_num,                          // 6
//    c_symbol_class_flag_num,                          // 7
//    c_symbol_class_flag_num,                          // 8
//    c_symbol_class_flag_num,                          // 9
//    c_symbol_class_flag_punc,                         // :
//    c_symbol_class_flag_punc,                         // ;
//    c_symbol_class_flag_punc,                         // <
//    c_symbol_class_flag_punc,                         // =
//    c_symbol_class_flag_punc,                         // >
//    c_symbol_class_flag_punc,                         // ?
//    c_symbol_class_flag_punc,                         // @
//    c_symbol_class_flag_alpha
//    | c_symbol_class_flag_hexnum,                     // A(0xA)
//    c_symbol_class_flag_alpha
//    | c_symbol_class_flag_hexnum,                     // B(0xB)
//    c_symbol_class_flag_alpha
//    | c_symbol_class_flag_hexnum,                     // C(0xC)
//    c_symbol_class_flag_alpha
//    | c_symbol_class_flag_hexnum,                     // D(0xD)
//    c_symbol_class_flag_alpha
//    | c_symbol_class_flag_hexnum,                     // E(0xE)
//    c_symbol_class_flag_alpha
//    | c_symbol_class_flag_hexnum,                     // F(0xF)
//    c_symbol_class_flag_alpha,                        // G
//    c_symbol_class_flag_alpha,                        // H
//    c_symbol_class_flag_alpha,                        // I
//    c_symbol_class_flag_alpha,                        // J
//    c_symbol_class_flag_alpha,                        // K
//    c_symbol_class_flag_alpha,                        // L
//    c_symbol_class_flag_alpha,                        // M
//    c_symbol_class_flag_alpha,                        // N
//    c_symbol_class_flag_alpha,                        // O
//    c_symbol_class_flag_alpha,                        // P
//    c_symbol_class_flag_alpha,                        // Q
//    c_symbol_class_flag_alpha,                        // R
//    c_symbol_class_flag_alpha,                        // S
//    c_symbol_class_flag_alpha,                        // T
//    c_symbol_class_flag_alpha,                        // U
//    c_symbol_class_flag_alpha,                        // V
//    c_symbol_class_flag_alpha,                        // W
//    c_symbol_class_flag_alpha,                        // X
//    c_symbol_class_flag_alpha,                        // Y
//    c_symbol_class_flag_alpha,                        // Z
//    c_symbol_class_flag_punc,                         // [
//    c_symbol_class_flag_punc,                         // \ (prevent line continuation)
//    c_symbol_class_flag_punc,                         // ]
//    c_symbol_class_flag_punc,                         // ^
//    c_symbol_class_flag_punc,                         // _
//    c_symbol_class_flag_alpha |
//        c_symbol_class_flag_hexnum,                   // a(0xa)
//    c_symbol_class_flag_alpha |
//        c_symbol_class_flag_hexnum,                   // b(0xb)
//    c_symbol_class_flag_alpha |
//        c_symbol_class_flag_hexnum,                   // c(0xc)
//    c_symbol_class_flag_alpha |
//        c_symbol_class_flag_hexnum,                   // d(0xe)
//    c_symbol_class_flag_alpha |
//        c_symbol_class_flag_hexnum,                   // e(0xe)
//    c_symbol_class_flag_alpha |
//        c_symbol_class_flag_hexnum,                   // f(0xf)
//    c_symbol_class_flag_alpha,                        // g
//    c_symbol_class_flag_alpha,                        // h
//    c_symbol_class_flag_alpha,                        // i
//    c_symbol_class_flag_alpha,                        // j
//    c_symbol_class_flag_alpha,                        // k
//    c_symbol_class_flag_alpha,                        // l
//    c_symbol_class_flag_alpha,                        // m
//    c_symbol_class_flag_alpha,                        // n
//    c_symbol_class_flag_alpha,                        // o
//    c_symbol_class_flag_alpha,                        // p
//    c_symbol_class_flag_alpha,                        // q
//    c_symbol_class_flag_alpha,                        // r
//    c_symbol_class_flag_alpha,                        // s
//    c_symbol_class_flag_alpha,                        // t
//    c_symbol_class_flag_alpha,                        // u
//    c_symbol_class_flag_alpha,                        // v
//    c_symbol_class_flag_alpha,                        // w
//    c_symbol_class_flag_alpha,                        // x
//    c_symbol_class_flag_alpha,                        // y
//    c_symbol_class_flag_alpha,                        // z
//    c_symbol_class_flag_punc,                         // {
//    c_symbol_class_flag_punc,                         // |
//    c_symbol_class_flag_punc,                         // }
//    c_symbol_class_flag_punc,                         // ~
//};
//
//inline int c_isalpha(char c) {
//    return !!(c_symbol_class_lookup[c] & c_symbol_class_flag_alpha);
//}
//
//inline int c_isnum(char c) {
//    return !!(c_symbol_class_lookup[c] & c_symbol_class_flag_num);
//}
//
//inline int c_isalnum(char c) {
//    return !!(c_symbol_class_lookup[c] & (c_symbol_class_flag_alpha | c_symbol_class_flag_num));
//}
//
//inline int c_isspace(char c) {
//    return !!(c_symbol_class_lookup[c] & c_symbol_class_flag_space);
//}
//
//inline int c_ispunc(char c) {
//    return !!(c_symbol_class_lookup[c] & c_symbol_class_flag_punc);
//}
//
//struct c_cursor {
//    const char *begin, *current;
//};
//
//void c_cursor_advance(struct c_cursor *cursor) {
//    ++(cursor->current);
//}
//
//const char *c_cursor_begin(struct c_cursor *cursor) {
//    return cursor->begin;
//}
//
//const char *c_cursor_current(struct c_cursor *cursor) {
//    return cursor->current;
//}
//
//char c_cursor_current_value(struct c_cursor *cursor) {
//    return *(cursor->current);
//}
//
//size_t c_cursor_offset(struct c_cursor *cursor) {
//    return (cursor->current - cursor->begin);
//}
//
//void c_cursor_reset(struct c_cursor *cursor) {
//    cursor->begin = cursor->current;
//}
//
//int c_eof(struct c_cursor *cursor) {
//    return !c_cursor_current(cursor);
//}
//
//static size_t c_skip_spaces(struct c_cursor *cursor) {
//    size_t n = 0U;
//    for (; c_isspace(c_cursor_current_value(cursor)); ++n) {
//        c_cursor_advance(cursor);
//    }
//
//    return n;
//}
//
//static int c_compare(struct c_cursor *cursor, char c) {
//    return c_cursor_current_value(cursor) == c;
//}
//
//enum c_parse_status {
//    c_parse_status_okay,
//    c_parse_status_allocation_failure,
//    c_parse_status_parse_failure
//};
//
//const char *c_parse_keyword_identifier(struct c_cursor *cursor, size_t *identifier_len) {
//    c_skip_spaces(cursor), c_cursor_reset(cursor);
//
//    if (!c_isalpha(c_cursor_current_value(cursor)) && !c_compare(cursor, '_')) {
//        fprintf(stderr, "invalid character %c in identifier\n", c_cursor_current_value(cursor));
//
//        return NULL;
//    }
//
//    c_cursor_advance(cursor);
//
//    while (!c_eof(cursor) && !c_isspace(c_cursor_current_value(cursor))) {
//        if (!c_isalnum(c_cursor_current_value(cursor)) && !c_compare(cursor, '_')) {
//            if (c_compare(cursor, '(') || c_compare(cursor, ')') || c_compare(cursor, ',') || c_compare(cursor, ';')) {
//                break;
//            }
//
//            fprintf(stderr, "invalid character %c in identifier\n", c_cursor_current_value(cursor));
//
//            return NULL;
//        }
//
//        c_cursor_advance(cursor);
//    }
//
//    *identifier_len = c_cursor_offset(cursor);
//
//    return c_cursor_begin(cursor);
//}
//
//static enum c_parse_status c_parse_func_ret_type(struct c_cursor *cursor, struct c_ast_node **node) {
//    size_t ret_sym_len = 0U;
//    const char *ret_sym = c_parse_keyword_identifier(cursor, &ret_sym_len);
//    if (!ret_sym) {
//        return NULL;
//    }
//
//    struct c_ast_typename *ret_type = c_ast_typename_create_builtin(c_ast_string_to_typename_type(ret_sym, ret_sym_len));
//    if (!ret_type) {
//        return c_parse_status_allocation_failure;
//    }
//
//    *node = ret_type;
//
//    return c_parse_status_okay;
//}
//
//static enum c_parse_status c_parse_func_param(struct c_cursor *cursor, struct c_ast_node **node) {
//    c_skip_spaces(cursor);
//
//    size_t param_type_sym_len = 0U;
//    const char *param_type_sym = c_parse_keyword_identifier(cursor, &param_type_sym_len);
//    if (!param_type_sym) {
//        return c_parse_status_parse_failure;
//    }
//
//    c_skip_spaces(cursor);
//
//    size_t param_sym_len = 0U;
//    const char *param_sym = c_parse_keyword_identifier(cursor, &param_sym_len);
//    if (!param_sym) {
//        return c_parse_status_parse_failure;
//    }
//
//    struct c_ast_node *param_type = c_ast_typename_create_builtin(c_ast_string_to_typename_type(param_type_sym, param_type_sym_len));
//    if (!param_type) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return c_parse_status_allocation_failure;
//    }
//
//    struct c_ast_node *param = c_ast_variable_create(param_sym, param_sym_len, param_type, c_ast_variable_type_stack);
//    if (!param) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return c_parse_status_allocation_failure;
//    }
//
//    *node = param;
//
//    return c_parse_status_okay;
//}
//
//static struct c_ast_node *c_parse_func_param_list(struct c_cursor *cursor) {
//    c_skip_spaces(cursor);
//
//    if (!c_compare(cursor, '(')) {
//        return NULL;
//    }
//
//    c_cursor_advance(cursor);
//
//    struct c_ast_node *param_list = NULL;
//
//    while (!c_eof(cursor)) {
//        if (!param_list) {
//            param_list = c_parse_func_param(cursor);
//            if (!param_list) {
//                return NULL;
//            }
//        }
//        else {
//            struct func_param *param = c_parse_func_param(cursor);
//            if (!param) {
//                return NULL;
//            }
//
//            c_ast_node_append(param_list, param);
//        }
//
//        c_skip_spaces(cursor);
//
//        if (c_compare(cursor, ',')) {
//            c_cursor_advance(cursor);
//        }
//        else if (c_compare(cursor, ')')) {
//            break;
//        }
//        else {
//            return NULL;
//        }
//    }
//
//    c_cursor_advance(cursor);
//
//    return param_list;
//}
//
//static enum c_parse_status c_parse_func_var(struct c_cursor *cursor, struct c_ast_node **node) {
//    c_skip_spaces(cursor);
//
//    size_t typename_sym_len = 0U;
//    const char *typename_sym = c_parse_keyword_identifier(cursor, &typename_sym_len);
//    if (!typename_sym) {
//        return c_parse_status_parse_failure;
//    }
//
//    c_skip_spaces(cursor), c_cursor_reset(cursor);
//
//    size_t identifier_sym_len = 0U;
//    const char *identifier_sym = c_parse_keyword_identifier(cursor, &identifier_sym_len);
//    if (!identifier_sym) {
//        return c_parse_status_parse_failure;
//    }
//
//    c_skip_spaces(cursor);
//
//    if (!c_compare(cursor, ';') && !c_compare(cursor, '=')) {
//        fprintf(stderr, "expected an expression after variable definition\n");
//
//        return c_parse_parse_failure;
//    }
//
//    struct c_ast_typename *typename = c_ast_typename_create_builtin(c_ast_string_to_typename_type(typename_sym, typename_sym_len));
//    if (!typename) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return c_parse_status_allocation_failure;
//    }
//
//    struct c_ast_node *var = c_ast_variable_create(identifier_sym, identifier_sym_len, typename, c_ast_variable_type_stack);
//    if (!var) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return c_parse_status_allocation_failure;
//    }
//
//    *node = var;
//
//    return c_parse_status_okay;
//}
//
//struct c_ast_node *c_parse_func_var_list(struct c_cursor *cursor) {
//    c_skip_spaces(cursor);
//
//    if (!c_compare(cursor, '{')) {
//        fprintf(stderr, "expected '{' after function parameter list\n");
//
//        return NULL;
//    }
//
//    c_cursor_advance(cursor);
//
//    struct c_ast_node *var_list = NULL;
//
//    while (!c_eof(cursor)) {
//        if (!var_list) {
//            var_list = c_parse_func_var(cursor);
//            if (!var_list) {
//                fprintf(stderr, "internal compiler allocation failure\n");
//
//                return NULL;
//            }
//        }
//        else {
//            struct c_ast_node *var = c_parse_func_var(cursor);
//            if (!var) {
//                fprintf(stderr, "internal compiler allocation failure\n");
//
//                return NULL;
//            }
//
//            c_ast_node_append(var_list, var);
//        }
//    }
//
//    return var_list;
//}
//
//struct c_ast_node *c_parse_func(struct c_cursor *cursor) {
//    struct c_ast_typename *ret_type = c_parse_func_ret_type(cursor);
//    if (!ret_type) {
//        return NULL;
//    }
//
//    c_skip_spaces(cursor);
//
//    size_t func_sym_len = 0U;
//    const char func_sym = c_parse_keyword_identifier(cursor, &func_sym_len);
//    if (!func_sym) {
//        return NULL;
//    }
//
//    struct c_ast_node *param_list = c_parse_func_param_list(cursor);
//    if (!param_list) {
//        return NULL;
//    }
//
//    struct c_ast_func_sig *sig = c_ast_func_sig_create(ret_type, param_list);
//    if (!sig) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return NULL;
//    }
//
//    struct c_ast_node *var_list = c_parse_func_var_list(cursor);
//    if (!var_list) {
//        return NULL;
//    }
//
//    struct c_ast_statement_block *statement_block = c_ast_statement_block_create(var_list, NULL);
//    if (!statement_block) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return NULL;
//    }
//
//    struct c_ast_func *func = c_ast_func_create(func_sym, func_sym_len, sig, statement_block);
//    if (!func) {
//        fprintf(stderr, "internal compiler allocation failure\n");
//
//        return NULL;
//    }
//
//    return func;
//}

void test(struct c_cursor *cursor) {
    
}

//const char *test_source =   \
//    "int main(void) {"      \
//    ""                      \
//    "   return 0;"          \
//    "}";

//const char *test_source = "int func(int a, int b, int c) { int x; x = 5;}";
//
//
//int main(int argc, char *argv[]) {
//    struct c_cursor cursor = {
//        .begin = test_source,
//        .current = test_source
//    };
//
//    c_parse_func(&cursor);
//
//    return 0;
//}
