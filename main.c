#define _CRT_SECURE_NO_WARNINGS

#include "compiler/c_ast_context.h"
#include "compiler/c_ast_literal.h"
#include "compiler/c_ast_binary_op.h"
#include "compiler/c_ast_func.h"
#include "compiler/c_ast_func_call.h"
#include "compiler/c_ast_func_ref.h"
#include "compiler/c_ast_param_list.h"
#include "compiler/c_ast_node.h"
#include "compiler/c_ast_return.h"
#include "compiler/c_ast_translation_unit.h"
#include "compiler/c_ast_statement.h"
#include "compiler/c_ast_statement_block.h"
#include "compiler/c_ast_type_spec.h"
//#include "compiler/c_ast_variable.h"
#include "compiler/c_ast_variable_ref.h"

#include "lexer/c_lexer_token.h"
#include "lexer/c_lexer_token_stream.h"

#include "parser/c_parser.h"

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
//    .evaluate_fn = c_ast_evaluate_statement_list,
//    .variables = &(struct c_ast_variable) { .name = "x", .integer_value = 5, .type = c_ast_variable_type_integer, 
//        .next = NULL },
//    .statements = NULL,
//    .next = &(struct c_ast_statement_list) {
//        .evaluate_fn = c_ast_evaluate_statement_list,
//        .variables = &(struct c_ast_variable) { .name = "a",.integer_value = 5,.type = c_ast_variable_type_integer,
//            .next = NULL }
//        },
//        .statements = &(struct c_ast_statement) { .statement = &(struct c_ast_binary_op) { .evaluate_fn = c_ast_evaluate_addition,
//            .lhs_exp = &(struct c_ast_variable_reference) { .evaluate_fn = c_ast_evaluate_variable, .name = "a", .scope = &root.next },
//            .rhs_exp = &(struct c_ast_variable_reference) { .evaluate_fn = c_ast_evaluate_variable, .name = "x", .scope = &root }
//        }
//    }
//};

//int main(int argc, char *argv[]) {
//    struct c_ast_context context;
//    c_ast_context_init(&context);
//
//    struct c_ast_node *var_list = c_ast_variable_create("global_var", 10u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_global);
//    struct c_ast_node *func_list =
//    c_ast_node_list_append(
//        c_ast_func_create("add", 3u,
//            c_ast_func_sig_create(
//                c_ast_typename_create_builtin(c_ast_typename_type_int),
//                c_ast_node_list_append(c_ast_variable_create("x", 1u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_stack),
//                    c_ast_variable_create("y", 1u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_stack))),
//            c_ast_statement_block_create(
//                c_ast_variable_create("result", 6u, c_ast_typename_create_builtin(c_ast_typename_type_int), c_ast_variable_type_stack),
//                c_ast_node_list_append(
//                    c_ast_node_list_append(
//                        c_ast_statement_create(
//                            c_ast_binary_op_create(c_ast_binary_op_assignment,
//                                c_ast_variable_ref_create("result"),
//                                c_ast_binary_op_create(c_ast_binary_op_addition,
//                                    c_ast_variable_ref_create("x"),
//                                    c_ast_variable_ref_create("y")))),
//                        c_ast_statement_create(
//                            c_ast_binary_op_create(c_ast_binary_op_assignment,
//                                c_ast_variable_ref_create("result"),
//                                c_ast_binary_op_create(c_ast_binary_op_addition,
//                                    c_ast_variable_ref_create("result"),
//                                c_ast_variable_ref_create("global_var"))))),
//                        c_ast_statement_create(
//                            c_ast_return_create(c_ast_variable_ref_create("result")))))),
//
//        c_ast_func_create("main", 4u,
//            c_ast_func_sig_create(
//                c_ast_typename_create_builtin(c_ast_typename_type_int),
//                NULL),
//            c_ast_statement_block_create(
//                NULL,
//                c_ast_statement_create(
//                    c_ast_return_create(
//                        c_ast_func_call_create(
//                            c_ast_func_ref_create("add"),
//                            c_ast_node_list_append(
//                                c_ast_literal_create_int(10),
//                                c_ast_literal_create_int(5))))))));
//
//
//    struct c_ast_node *main_source = c_ast_source_file_create("main.c", var_list, func_list);
//
//    c_ast_node_evaluate(main_source, &context);
//
//    return 0;
//}

//#include "lexer/c_lexer_token.h"

//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
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

//
//int c_eof(struct c_cursor *cursor) {
//    return !c_cursor_current(cursor);
//}
//
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

int c_lex_character(struct c_lexer_context *context, struct c_lexer_token *token) {
    
    c_lexer_skip_spaces(context), c_lexer_reset_cursor(context);


    return 0;
}

int c_lex_number(struct c_lexer_context *context, struct c_lexer_token *token) {
    
    c_lexer_skip_spaces(context), c_lexer_reset_cursor(context);

    c_lexer_advance(context);

    token->type = c_lexer_token_number;
    token->view = c_lexer_cursor_view(context);

    return 0;
}

int c_lex_symbol(struct c_lexer_context *context, struct c_lexer_token *token) {

    c_lexer_skip_spaces(context), c_lexer_reset_cursor(context);

    c_lexer_advance(context);

    token->type = c_lexer_token_symbol;
    token->view = c_lexer_cursor_view(context);

    return 0;
}

int c_lex_identifier_keyword(struct c_lexer_context *context, struct c_lexer_token *token) {
    
    c_lexer_skip_spaces(context), c_lexer_reset_cursor(context);

    if (!c_lexer_isalpha(context) && !c_lexer_compare(context, '_')) {
        fprintf(stderr, "invalid character %c in identifier\n", c_lexer_peek(context));

        return -1;
    }

    c_lexer_advance(context);

    while (!c_lexer_eof(context) && !c_lexer_isspace(context)) {
        if (!c_lexer_isalnum(context) && !c_lexer_compare(context, '_')) {
            if (c_lexer_ispunc(context)) {
                break;
            }

            fprintf(stderr, "invalid character %c in identifier\n", c_lexer_peek(context));

            return -1;
        }

        c_lexer_advance(context);
    }

    token->type = c_lexer_token_identifier;
    token->view = c_lexer_cursor_view(context);

    {
        const int keyword_type = c_lexer_check_identifier_keyword(token);
        if (keyword_type != c_lexer_token_invalid_keyword) {
            token->type = c_lexer_token_keyword;
            //token->keyword.type = keyword_type;
        }
    }

    return 0;
}

int c_lex(struct c_lexer_context *context, struct c_lexer_token_stream *stream) {
    int ret = -1;

    while (!c_lexer_eof(context)) {
        struct c_lexer_token token = { 0 };
    
        c_lexer_skip_spaces(context), c_lexer_reset_cursor(context);

        if (c_lexer_ispunc(context)) {
            ret = c_lex_symbol(context, &token);
            if (ret != 0) {
                return ret;
            }
        }
        else if (c_lexer_isnum(context)) {
            ret = c_lex_number(context, &token);
            if (ret != 0) {
                return ret;
            }
        }
        else {
            ret = c_lex_identifier_keyword(context, &token);
            if (ret != 0) {
                return ret;
            }
        }

        c_lexer_token_stream_push_back(stream, &token);
    }

    return 0;
}

//static enum c_parse_status c_parse_func_ret_type(struct c_lexer_context *context, struct c_ast_node **node) {
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

static inline uint32_t dbj2(const char *str, size_t len, int prime) {
    uint32_t hash = 0u;

    while (len--) {

        hash = hash * prime ^ str[len];
    }

    return hash;
}

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen("C:/Users/jlyda/Downloads/ceval.c", "r");
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *source = malloc(len + 1);
    fread(source, 1u, len, f);
    fclose(f);

    source[len] = '\0';

    struct c_lexer_token_stream token_stream;
    c_lexer_token_stream_init(&token_stream, 32u);

    struct c_lexer_context lexer_context = {
        .cursor.view.begin = source,
        .cursor.view.current = source
    };

    c_lex(&lexer_context, &token_stream);
    
    //while (!c_lexer_token_stream_empty(&token_stream)) {
    //    const struct c_lexer_token token = c_lexer_token_stream_front(&token_stream);

    //    const size_t len = token.view.end - token.view.begin;
    //    printf("Token: %.*s\n", len, token.view.begin);

    //    c_lexer_token_stream_pop_front(&token_stream);
    //}

    struct c_ast_node *ast_node = NULL;

    if (c_parse(&token_stream, &ast_node) != 0) {
        //puts("Could not match expression!");
    }
    else {
        puts("Matched expression!");

        struct c_ast_context ast_context = { 0 };

        c_ast_node_evaluate(ast_node, &ast_context);

        
    }
}
//
//        c_lexer_stream_pop_back(&lexer_stream);
//    while (!c_lexer_stream_empty(&lexer_stream)) {
//        struct c_lexer_token token = c_lexer_stream_front(&lexer_stream);
//
//        printf("Token: %.*s\n", token.view.end - token.view.begin, token.view.begin);
//
//    }

    /*while (!c_lexer_eof(&context)) {
        struct c_lexer_token token = { 0 };

        if (c_lexer_isnum(&context)) {
            if (0 == c_lex_number(&context, &token)) {
                context.token_stream.tokens[context.token_stream.ntokens] = token;
                context.token_stream.ntokens += 1u;
            }
        }
        if (c_lexer_ispunc(&context)) {
            if (0 == c_lex_symbol(&context, &token)) {
                context.token_stream.tokens[context.token_stream.ntokens] = token;
                context.token_stream.ntokens += 1u;
            }
        }
          
        if (0 == c_lex_identifier_keyword(&context, &token)) {
            context.token_stream.tokens[context.token_stream.ntokens] = token;
            context.token_stream.ntokens += 1u;
        }
    }

    for (size_t i = 0u; i < context.token_stream.ntokens; ++i) {
        const size_t len = context.token_stream.tokens[i].view.end - context.token_stream.tokens[i].view.begin;
        printf("Token: %.*s\n", len, context.token_stream.tokens[i].view.begin);
    }

    for (size_t i = 0u; i < context.token_stream.ntokens; ++i) {
        if (context.token_stream.tokens[i].type == c_lexer_token_keyword) {
            if (context.token_stream.tokens[i + 1].type == c_lexer_token_identifier) {
                if (context.token_stream.tokens[i + 2].type == c_lexer_token_symbol) {
                    const char c = *context.token_stream.tokens[i + 2].view.begin;
                    if (c == ';') {
                        puts("Variable");
                    }
                    else if (c == '(') {
                        puts("Function");
                    }
                    
                }
            }
        }
    }*/


    //struct c_lexer_token c_parse_keyword_identifier(&context);
    //if (identifier) {
    //    printf("Identifier: %.*s\n", identifier_len, identifier);
    //}

//    return 0;
//}

