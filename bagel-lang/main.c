#define _CRT_SECURE_NO_WARNINGS

#include "ast_context.h"
#include "binary_op.h"
#include "function.h"
#include "function_sig.h"
#include "return.h"
#include "source_file.h"
#include "statement.h"
#include "statement_block.h"
#include "typename.h"
#include "variable.h"
#include "variable_ref.h"

struct c_ast_node *c_ast_evaluate_integer(struct c_ast_node *node) {
    return node;
}

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

/*
{
    var x, y;
    x + y;
    {

    }
}
*/

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

    struct c_ast_node *main_source = c_ast_source_file_create("main.c");

    struct c_ast_node *func_add_body = c_ast_statement_block_create();
    c_ast_node_append(c_ast_statement_block_variables(func_add_body), c_ast_variable_create("result", c_ast_typename_create_builtin(c_ast_typename_type_int)));

    c_ast_node_append(c_ast_statement_block_statements(func_add_body), c_ast_statement_create(
        c_ast_binary_op_create(c_ast_binary_op_assignment, c_ast_variable_ref_create("result"),
            c_ast_binary_op_create(c_ast_binary_op_addition, c_ast_variable_ref_create("x"),
                c_ast_variable_ref_create("y", func_add_body)))));
    c_ast_node_append(c_ast_statement_block_statements(func_add_body), c_ast_statement_create(
        c_ast_return_create(c_ast_variable_ref_create("result"))));

    struct c_ast_node *func_add = c_ast_function_create("add", c_ast_function_sig_create(
        c_ast_typename_create_builtin(c_ast_typename_type_int), NULL),
        func_add_body);

    c_ast_node_append(c_ast_function_sig_param_list(c_ast_function_func_sig(func_add)),
        c_ast_variable_create("x", c_ast_typename_create_builtin(c_ast_typename_type_int)));
    c_ast_node_append(c_ast_function_sig_param_list(c_ast_function_func_sig(func_add)),
        c_ast_variable_create("y", c_ast_typename_create_builtin(c_ast_typename_type_int)));

    c_ast_node_append(c_ast_source_file_functions(main_source), func_add);


    //c_ast_statement_append(c_ast_statement_list_statements(func_body), c_ast_statement_create(
    //    c_ast_return_create(c_ast_variable_ref_create("result", func_body))));

    //struct c_ast_function_param *params = c_ast_function_param_create(c_ast_typename_c)

    //struct c_ast_node *func = c_ast_function_create("add", func_body);

    c_ast_node_evaluate(main_source, &context);

    return 0;
}






/*
BEGIN_STATEMENT_LIST
    BEGIN_VARIABLES
      X
      NEXT
        Y
    END_VARIABLES
    BEGIN_STATEMENTS
      X + Y
      NEXT
        BEGIN_STATEMENT_LIST

        END_STATEMENT_LIST
    END_STATEMENTS

END_STATEMENT_LIST
*/




/*

#define c_ast_for_init_statement(node)  (((struct c_ast_for *)(node))->init_statement)
#define c_ast_for_iteration_exp(node)   (((struct c_ast_for *)(node))->iteration_exp)
#define c_ast_for_statement_list(node)  (((struct c_ast_for *)(node))->statement_list)

struct c_ast_for {
    c_ast_node_contents;

    struct c_ast_node *init_statement;
    struct c_ast_node *iteration_exp;
    struct c_ast_node *statement_list;
};

struct c_ast_node *c_ast_evaluate_for(struct c_ast_node *node) {
    struct c_ast_node *init_statement_result = NULL;
    if (c_ast_for_init_statement(node) != NULL) {
        init_statement_result = c_ast_node_evaluate(c_ast_for_init_statement(node));
    }

    struct c_ast_node *iteration_exp_result = NULL;
    if (c_ast_for_iteration_exp(node) != NULL) {
        iteration_exp_result = c_ast_node_evaluate(c_ast_for_iteration_exp(node));
    }

    struct c_ast_node *statement_list_result = NULL;
    if (c_ast_for_statement_list(node) != NULL) {
        statement_list_result = c_ast_node_evaluate(c_ast_for_statement_list(node));
    }

    return NULL;
}
*/