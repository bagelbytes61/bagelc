#include "c_parser_grammar.h"

#include "../compiler/c_ast_decl.h"
#include "../compiler/c_ast_decl_spec.h"
#include "../compiler/c_ast_func.h"
#include "../compiler/c_ast_node.h"
#include "../compiler/c_ast_param_list.h"
#include "../compiler/c_ast_statement_block.h"
#include "../compiler/c_ast_translation_unit.h"
#include "../compiler/c_ast_type_spec.h"

#include "../lexer/c_lexer_token_stream.h"

extern const struct c_bnf_expr c_external_declaration;
extern const struct c_bnf_expr c_function_definition;
extern const struct c_bnf_expr c_declarator;
extern const struct c_bnf_expr c_declaration;
extern const struct c_bnf_expr c_declaration_specifier;
extern const struct c_bnf_expr c_init_declarator;
extern const struct c_bnf_expr c_initializer;
extern const struct c_bnf_expr c_compound_statement;
extern const struct c_bnf_expr c_statement;
static const struct c_bnf_expr c_expression_statement;
extern const struct c_bnf_expr c_type_qualifier;
extern const struct c_bnf_expr c_type_specifier;
extern const struct c_bnf_expr c_assignment_expression;
extern const struct c_bnf_expr c_logical_or_expression;
extern const struct c_bnf_expr c_expression;
extern const struct c_bnf_expr c_logical_and_expression;
extern const struct c_bnf_expr c_inclusive_or_expression;
extern const struct c_bnf_expr c_exclusive_or_expression;
extern const struct c_bnf_expr c_and_expression;
extern const struct c_bnf_expr c_equality_expression;
extern const struct c_bnf_expr c_relational_expression;
extern const struct c_bnf_expr c_shift_expression;
extern const struct c_bnf_expr c_additive_expression;
extern const struct c_bnf_expr c_multiplicative_expression;
extern const struct c_bnf_expr c_cast_expression;
extern const struct c_bnf_expr c_unary_expression;
extern const struct c_bnf_expr c_postfix_expression;
extern const struct c_bnf_expr c_primary_expression;
extern const struct c_bnf_expr c_assignment_expression;
extern const struct c_bnf_expr c_assignment_operator;
extern const struct c_bnf_expr c_unary_operator;
extern const struct c_bnf_expr c_parameter_type_list;
extern const struct c_bnf_expr c_parameter_list;
extern const struct c_bnf_expr c_parameter_declaration;

static struct c_ast_create_info *match(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, int *tokens_consumed, int *result);

static struct c_ast_node *match_identifier(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, struct c_ast_create_info *create_info, int *ret) {
    struct c_lexer_token tok = c_lexer_token_stream_front(stream);

    *ret = tok.type == c_lexer_token_identifier ? 0 : -1;

    return NULL;
}

//static int match_translation_unit(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, struct c_ast_node **node) {
//    int ret = -1;
//
//    struct c_ast_decl *declarations = NULL;
//    //struct c_ast_func *functions = NULL;
//
//    ret = match(stream, expr, &declarations, node);
//    if (ret != -1) {
//        //expr->create_ast_node(0, 5, 1);
//        //*node = c_ast_translation_unit_create("local", declarations, NULL);
//    }
//
//    return ret;
//}

//static int match_init_declarator(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, struct c_ast_node **node) {
//    int ret = -1;
//
//    ret = match(stream, expr, node, NULL);
//    if (ret != -1) {
//        //*node = c_ast_var_create()
//    }
//
//    return ret;
//}

static struct c_ast_node *match_declaration_specifier(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, struct c_ast_create_info *create_info, int *ret) {
    *ret = 0;

    return NULL;
}

static int test = 0;

static struct c_ast_create_info *match_subexprs(struct c_lexer_token_stream *stream, const struct c_bnf_expr **exprs, const char *lookahead_symbol, int match_any, int *tokens_matched, int *result) {
    struct c_ast_create_info *create_info = NULL;

    struct c_lexer_token token;
    int lookahead = 0;
    int token_count = 0;

    const struct c_bnf_expr **expr = exprs;

    if (c_lexer_token_stream_empty(stream)) {
        return NULL;
    }

    for (; *expr != NULL; ++expr) {
        if ((*expr)->lookahead_symbol != NULL) {
            printf("Looking ahead for symbol: %s\n", (*expr)->lookahead_symbol);
            lookahead = 1;
            //c_lexer_token_stream_pop_front(stream);
            break;
        }
    }

    expr = exprs;

    token = c_lexer_token_stream_peak(stream, 1u);

    do {
        //const struct c_bnf_expr **expr = exprs;

        struct c_ast_create_info *info = NULL;
        
        for (; *expr != NULL; ++expr) {
            if (lookahead && !test) {
                if ((*expr)->lookahead_symbol != NULL) {
                    if (strncmp(token.view.begin, (*expr)->lookahead_symbol, c_view_len(token.view) != 0)) {
                        puts("Could not match lookahead -- skipping");
                        continue;
                    }
                    puts("Lookahead symbol matched!\n");
                    test = 1;
                    //lookahead = 0;
                } else {
                    continue;
                }
            }

            printf("Attempting to match '%s'\n", (*expr)->debug_name);
            printf("Remaining token stream: %s\n", stream->head->view.begin);
            //c_lexer_token_stream_pop_front(stream);
            info = match(stream, *expr, &token_count, result);
            test = 0;
            if (*result != 0) {
                if (match_any) {
                    continue;
                }

                if ((*expr)->debug_name != NULL) {
                    printf("Could not match '%s'\n", (*expr)->debug_name);
                }

                break;
            }

            if ((*expr)->debug_name != NULL) {
                printf("Matched '%s'\n", (*expr)->debug_name);
                printf("Remaining token stream: %s\n", stream->head->view.begin);
            }

            if (create_info != NULL) {
                struct c_ast_create_info *it = create_info;
                while (it->next != NULL) { it = it->next; }
                it->next = info;
            } else {
                create_info = info;
            }

            if (match_any) {
                break;
            }
        }

        if (*result != 0 && lookahead != 0) {
            //lookahead = 0;

            //expr = exprs;

            //continue;
        }

        break;
    } while (1);

    return create_info;
}

static struct c_ast_create_info *match_nonterminal_expr(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, int *tokens_consumed, int *result) {
    int ret = -1;
    struct c_ast_create_info *create_info =  NULL;

    create_info = match_subexprs(stream, expr->nonterminal.subexprs, expr->lookahead_symbol, expr->nonterminal.match_any, NULL, &ret);
    if (ret != -1) {
        if (expr->create_ast_node != NULL) {
            if (create_info == NULL) {
                create_info = malloc(sizeof *create_info);
                memset(create_info, 0, sizeof *create_info);
            }
            create_info->ast_node = expr->create_ast_node(create_info);
            create_info->type = c_ast_create_info_ast_node;
        } else {
            printf("No create method specified for %s\n", expr->debug_name);
        }
    }

    *result = ret;

    return create_info;
}

static struct c_ast_create_info *match_terminal_expr(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, int *tokens_matched, int *result) {
    int ret = -1;

    struct c_ast_create_info *create_info = NULL;
    struct c_lexer_token token = c_lexer_token_stream_front(stream);

    if (expr->terminal.length != 0u) {
        ret = -(strncmp(token.view.begin, expr->terminal.value, c_view_len(token.view)) != 0);
    } else {
        expr->terminal.match(stream, expr, NULL, &ret);
    }

    if (ret != -1) {
        if (!(expr->flags & c_bnf_match_only)) {
            create_info = malloc(sizeof *create_info);
            memset(create_info, 0, sizeof *create_info);
            create_info->type = c_ast_create_info_view;
            create_info->view = token.view;
        }

        *tokens_matched += 1;

        c_lexer_token_stream_pop_front(stream);
    }

    *result = ret;

    return create_info;
}

static struct c_ast_create_info *match(struct c_lexer_token_stream *stream, const struct c_bnf_expr *expr, int *tokens_matched, int *result) {
    int ret = -1;

    struct c_ast_create_info *create_info = NULL;
    int match_count = 0;
    int token_count = 0;
    struct c_lexer_token_stream stream_view = { 0 };

    printf("Attempting to match: %s\n", expr->debug_name);

    //printf("Depth: %d\n", depth);

    //if (expr->max_depth != 0 && depth > expr->max_depth) {
    //    //*result = -1;

    //    //return NULL;
    //}

    if (c_lexer_token_stream_empty(stream)) {
        if (expr->flags & c_bnf_zero_or_more) {
            *result = 0;
        } else {
            *result = -1;
        }

        return NULL;
    }

    c_lexer_token_stream_view(stream, &stream_view);

    do {
        struct c_ast_create_info *info = NULL;

        token_count = 0;

        if (expr->type == c_bnf_nonterminal_expr) {
            info = match_nonterminal_expr(&stream_view, expr, &token_count, &ret);
        } else if (expr->type == c_bnf_terminal_expr) {
            info = match_terminal_expr(&stream_view, expr, &token_count, &ret);
        }

        if (ret != -1) {
            if (create_info != NULL) {
                struct c_ast_create_info *it = create_info;
                while (it->next != NULL) { it = it->next; }
                create_info->next = info;
            } else {
                create_info = info;
            }

            match_count += 1;
            *tokens_matched += token_count;

            c_lexer_token_stream_sync(stream, &stream_view);
        }
    } while (expr->flags & (c_bnf_zero_or_more | c_bnf_one_or_more) && ret != -1);

    if (ret == -1 && (expr->flags & c_bnf_zero_or_more)) {
        ret = 0;
    }

    if (ret == -1 && (expr->flags & c_bnf_one_or_more) && match_count >= 1) {
        ret = 0;
    }

    if (ret != -1) {
        //if (ast_nodes != NULL) {
        //    //create_info->ast_node = ast_nodes;
        //}
    }

    *result = ret;

    return create_info;
}

const struct c_bnf_expr c_translation_unit = {
    .type = c_bnf_nonterminal_expr,
    .flags = c_bnf_zero_or_more,
    .lookahead_symbol = NULL,
    .create_ast_node = &c_ast_translation_unit_create,
    .nonterminal.subexprs = c_bnf_subexprs(&c_external_declaration),
    .nonterminal.match = match,
    .debug_name = "c_translation_unit"
};

static const struct c_bnf_expr c_external_declaration = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_function_definition),
                                //&c_declaration),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_external_declarations"
};

static const struct c_bnf_expr c_function_definition = {
    .type = c_bnf_nonterminal_expr,
    .create_ast_node = &c_ast_func_create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_easy_nonterminal_expr(
                                    0, 
                                    NULL,
                                    c_bnf_subexprs(&c_declaration_specifier),
                                    match, 
                                    0),
                                &c_declarator,
                                &c_bnf_easy_nonterminal_expr(
                                    c_bnf_zero_or_more,
                                    NULL,
                                    c_bnf_subexprs(&c_declaration),
                                    match,
                                    0),
                                &c_compound_statement),
    .nonterminal.match = match,
    .nonterminal.match_any = 0,
    .debug_name = "c_function_definitions"
};

static const struct c_bnf_expr c_storage_class_specifier = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_simple_terminal_expr("auto"),
                                &c_bnf_simple_terminal_expr("register"),
                                &c_bnf_simple_terminal_expr("static"),
                                &c_bnf_simple_terminal_expr("extern"),
                                &c_bnf_simple_terminal_expr("typedef")),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_storage_class_specifier"
};

static const struct c_bnf_expr c_type_qualifier = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_simple_terminal_expr("const"),
                                &c_bnf_simple_terminal_expr("volatile")),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_type_qualifier"
};

static const struct c_bnf_expr c_type_specifier = {
    .type = c_bnf_nonterminal_expr,
    .create_ast_node = &c_ast_type_spec_create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_simple_terminal_expr("void"),
                                &c_bnf_simple_terminal_expr("char"),
                                &c_bnf_simple_terminal_expr("short"),
                                &c_bnf_simple_terminal_expr("int"),
                                &c_bnf_simple_terminal_expr("long"),
                                &c_bnf_simple_terminal_expr("float"),
                                &c_bnf_simple_terminal_expr("double"),
                                &c_bnf_simple_terminal_expr("signed"),
                                &c_bnf_simple_terminal_expr("unsigned")),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_type_specifier"

    //{ .type = c_bnf_expression_expansion, .expression_sequence = c_bnf_expansion_sequence(expect_struct_specifier) },
    //{ .type = c_bnf_expression_expansion, .expression_sequence = c_bnf_expansion_sequence(expect_union_specifier) },
    //{ .type = c_bnf_expression_expansion, .expression_sequence = c_bnf_expansion_sequence(expect_enum_specifier) },
    //{ .type = c_bnf_expression_expansion, .expression_sequence = c_bnf_expansion_sequence(expect_typedef_name) }
};

static const struct c_bnf_expr c_declaration_specifier = {
    .type = c_bnf_nonterminal_expr,
    .create_ast_node = &c_ast_decl_spec_create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_storage_class_specifier,
                                &c_type_qualifier,
                                &c_type_specifier),
    .nonterminal.match = match_declaration_specifier,
    .nonterminal.match_any = 1,
    .debug_name = "c_declaration_specifier"
};

static const struct c_bnf_expr c_identifier = {
    .type = c_bnf_terminal_expr,
    .terminal.match = &match_identifier,
    .debug_name = "c_identifier"
};

static struct c_ast *create(const struct c_ast_create_info *create_info) {
    printf("%.*s\n", c_view_len(create_info->view), create_info->view.begin);

    struct c_ast_node *node = malloc(sizeof *node);
    memset(node, 0, sizeof *node);
    node->type = 55;

    return node;
}

static const struct c_bnf_expr c_direct_declarator = {
    .type = c_bnf_nonterminal_expr,
    //.lookahead_symbol = "(",
    //.create_ast_node = create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_identifier,
                                //&c_bnf_simple_nonterminal_expr(
                                //    c_bnf_subexprs(
                                //        &c_bnf_simple_terminal_expr("("),
                                //        //&c_declarator,
                                //        &c_bnf_simple_terminal_expr(")"))),
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    "(",
                                    c_bnf_subexprs(
                                        &c_direct_declarator,
                                        &c_bnf_simple_terminal_expr_match_only("("),
                                        &c_parameter_type_list,
                                        &c_bnf_simple_terminal_expr_match_only(")")),
                                    match,
                                    0),
        &c_identifier),
    .nonterminal.match_any = 1,
    .max_depth = 10,
    .debug_name = "c_direct_declarator"
};

static const struct c_bnf_expr c_declarator = {
    .type = c_bnf_nonterminal_expr,
    //.create_ast_node = create_declarator,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_direct_declarator),
    .nonterminal.match = match,
    .debug_name = "c_declarator"
};

static const struct c_bnf_expr c_declaration = {
    .type = c_bnf_nonterminal_expr,
    .create_ast_node = &c_ast_decl_create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_easy_nonterminal_expr(
                                    c_bnf_one_or_more,
                                    NULL,
                                    c_bnf_subexprs(&c_declaration_specifier),
                                    match,
                                    0),
                                &c_bnf_easy_nonterminal_expr(
                                    c_bnf_zero_or_more,
                                    NULL,
                                    c_bnf_subexprs(&c_init_declarator),
                                    match,
                                    0)),
    .debug_name = "c_declaration"
};

static const struct c_bnf_expr c_init_declarator = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_declarator,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_declarator,
                                        &c_bnf_simple_terminal_expr_match_only("="),
                                        &c_initializer))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_init_declarator"
};

static const struct c_bnf_expr c_initializer = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_assignment_expression),
    .debug_name = "c_initializer"
};

static const struct c_bnf_expr c_compound_statement = {
    .type = c_bnf_nonterminal_expr,
    .create_ast_node = c_ast_statement_block_create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_simple_terminal_expr_match_only("{"),
                                //&c_bnf_easy_nonterminal_expr(
                                //    c_bnf_zero_or_more,
                                //    &c_declaration,
                                //    match,
                                //    0),
                                //&c_bnf_easy_nonterminal_expr(
                                //    c_bnf_zero_or_more,
                                //    &c_statement,
                                //    match,
                                //    0),
                                &c_bnf_simple_terminal_expr_match_only("}")),
    .nonterminal.match = match,
    .nonterminal.match_any = 0,
    .debug_name = "c_compound_statement"
};

static const struct c_bnf_expr c_statement = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_expression_statement),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_statement"
};

//static const struct c_bnf_expr c_expression_statement = {
//    .type = c_bnf_nonterminal_expr,
//    .nonterminal.subexprs = c_bnf_subexprs(
//                                &c_bnf_simple_terminal_expr(
//                                    c_bnf_zero_or_more,
//                                    &c_expression,
//                                    match,
//                                    0),
//                                &c_bnf_simple_terminal_expr("")),
//    .nonterminal.match = match,
//    .nonterminal.match_any = 1
//};

static const struct c_bnf_expr conditional_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_logical_or_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_logical_or_expression,
                                        &c_bnf_simple_terminal_expr("?"),
                                        &c_expression,
                                        &c_bnf_simple_terminal_expr(":"),
                                        &conditional_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_logical_or_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_logical_and_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_logical_or_expression,
                                        &c_bnf_simple_terminal_expr("||"),
                                        &c_logical_and_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_logical_and_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_inclusive_or_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_logical_and_expression,
                                        &c_bnf_simple_terminal_expr("&&"),
                                        &c_inclusive_or_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_inclusive_or_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_exclusive_or_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_inclusive_or_expression,
                                        &c_bnf_simple_terminal_expr("|"),
                                        &c_exclusive_or_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_exclusive_or_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_and_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_exclusive_or_expression,
                                        &c_bnf_simple_terminal_expr("^"),
                                        &c_and_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

const struct c_bnf_expr c_and_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_equality_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_and_expression,
                                        &c_bnf_simple_terminal_expr("&"),
                                        &c_equality_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_equality_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_relational_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_equality_expression,
                                        &c_bnf_simple_terminal_expr("=="),
                                        &c_relational_expression)),
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_equality_expression,
                                        &c_bnf_simple_terminal_expr("!="),
                                        &c_relational_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_relational_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_shift_expression,
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_relational_expression,
                                        &c_bnf_simple_terminal_expr("<"),
                                        &c_shift_expression)),
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_relational_expression,
                                        &c_bnf_simple_terminal_expr(">"),
                                        &c_shift_expression)),
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_relational_expression,
                                        &c_bnf_simple_terminal_expr("<="),
                                        &c_shift_expression)),
                                &c_bnf_simple_nonterminal_expr(
                                    c_bnf_subexprs(
                                        &c_relational_expression,
                                        &c_bnf_simple_terminal_expr(">="),
                                        &c_shift_expression))),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_shift_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_additive_expression,
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_shift_expression,
                                        &c_bnf_simple_terminal_expr("<<"),
                                        &c_additive_expression),
                                    match,
                                    0),
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_shift_expression,
                                        &c_bnf_simple_terminal_expr(">>"),
                                        &c_additive_expression),
                                    match,
                                    0)),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_additive_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_multiplicative_expression,
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_additive_expression,
                                        &c_bnf_simple_terminal_expr("+"),
                                        &c_multiplicative_expression),
                                    match,
                                    0),
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_additive_expression,
                                        &c_bnf_simple_terminal_expr("-"),
                                        &c_multiplicative_expression),
                                    match,
                                    0)),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_multiplicative_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_cast_expression,
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_multiplicative_expression,
                                        &c_bnf_simple_terminal_expr("*"),
                                        &c_cast_expression),
                                    match,
                                    0),
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_multiplicative_expression,
                                        &c_bnf_simple_terminal_expr("/"),
                                        &c_cast_expression),
                                    match,
                                    0),
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_multiplicative_expression,
                                        &c_bnf_simple_terminal_expr("%"),
                                        &c_cast_expression),
                                    match,
                                    0)),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_cast_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(&c_unary_expression),
    .nonterminal.match = match
};

static const struct c_bnf_expr c_unary_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(&c_postfix_expression),
    .nonterminal.match = match
};

static const struct c_bnf_expr c_postfix_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(&c_primary_expression),
    .nonterminal.match = match
};

static const struct c_bnf_expr c_primary_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_identifier
        /* &constant, */
        /* &string, */
    /* '(' expression ')', */),
    .nonterminal.match = match,
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_assignment_expression,
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_expression,
                                        &c_bnf_simple_terminal_expr(","),
                                        &c_assignment_expression),
                                    match,
                                    0)),
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_assignment_expression = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_unary_expression,
                                &c_assignment_operator,
                                &c_assignment_expression)
};

static const struct c_bnf_expr c_assignment_operator = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_simple_terminal_expr("="),
                                &c_bnf_simple_terminal_expr("*="),
                                &c_bnf_simple_terminal_expr("/="),
                                &c_bnf_simple_terminal_expr("%="),
                                &c_bnf_simple_terminal_expr("+="),
                                &c_bnf_simple_terminal_expr("-="),
                                &c_bnf_simple_terminal_expr("<<="),
                                &c_bnf_simple_terminal_expr(">>="),
                                &c_bnf_simple_terminal_expr("&="),
                                &c_bnf_simple_terminal_expr("^="),
                                &c_bnf_simple_terminal_expr("|=")),
    .nonterminal.match_any = 1
};

static const struct c_bnf_expr c_unary_operator = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_simple_terminal_expr("&"),
                                &c_bnf_simple_terminal_expr("*"),
                                &c_bnf_simple_terminal_expr("+"),
                                &c_bnf_simple_terminal_expr("-"),
                                &c_bnf_simple_terminal_expr("~"),
                                &c_bnf_simple_terminal_expr("!")),
    .nonterminal.match_any = 1
};
static const struct c_bnf_expr c_parameter_type_list = {
    .type = c_bnf_nonterminal_expr,
    .create_ast_node = c_ast_param_list_create,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_parameter_list,
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_parameter_list,
                                        &c_bnf_simple_terminal_expr(","),
                                        &c_bnf_simple_terminal_expr("...")),
                                    match,
                                    0)),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_parameter_type_list"
};

static const struct c_bnf_expr c_parameter_list = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_parameter_declaration,
                                &c_bnf_easy_nonterminal_expr(
                                    0,
                                    NULL,
                                    c_bnf_subexprs(
                                        &c_parameter_list,
                                        &c_bnf_simple_terminal_expr(","),
                                        &c_parameter_declaration),
                                    match,
                                    0)),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_parameter_list"
};

static const struct c_bnf_expr c_parameter_declaration = {
    .type = c_bnf_nonterminal_expr,
    .nonterminal.subexprs = c_bnf_subexprs(
                                &c_bnf_easy_nonterminal_expr(
                                    c_bnf_one_or_more,
                                    NULL,
                                    c_bnf_subexprs(&c_declaration),
                                    match,
                                    0)),
                                //&c_declarator),
    .nonterminal.match = match,
    .nonterminal.match_any = 1,
    .debug_name = "c_parameter_declaration"
};