#include "c_ast_func_call.h"

#include "c_ast_context.h"
#include "c_ast_func.h"
#include "c_ast_func_arg.h"
#include "c_ast_func_ref.h"
#include "c_ast_param_list.h"
#include "c_ast_literal.h"
#include "c_ast_type_spec.h"
//#include "c_ast_variable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_func_call(struct c_ast_node *node, struct c_ast_context *context) {
    //struct c_ast_func_call *func_call = c_ast_func_call_cast(node);

    //struct c_ast_func_arg *arg = NULL;
    //struct c_ast_func     *func = NULL;

    //arg = c_ast_func_call_args(node);
    //func = c_ast_node_evaluate(func_call->func_ref, context);
    //if (!func) {
    //    return NULL;
    //}

    //{
    //    struct c_ast_node *param = c_ast_func_sig_param_list(c_ast_func_signature(func));
    //    for (; param != NULL || arg != NULL; arg = c_ast_node_next(arg), param = c_ast_node_next(param)) {
    //        if ((arg == NULL) && (param != NULL)) {
    //            fprintf(stderr, "too few arguments in function call\n");
    //            abort();
    //        }

    //        if ((arg != NULL) && (param == NULL)) {
    //            fprintf(stderr, "too many arguments in function call\n");
    //            abort();
    //        }

    //        if (c_ast_node_type(arg) == c_ast_node_literal) {
    //           /* if (c_ast_typename_type(c_ast_literal_typename(arg)) != c_ast_typename_type(c_ast_variable_typename(param))) {
    //                printf("argument of type '%s' is incompatible with parameter of type '%s'\n",
    //                    c_ast_typename_type_to_string(c_ast_literal_typename(arg)),
    //                    c_ast_typename_type_to_string(c_ast_variable_typename(param)));
    //                abort();
    //            }

    //            printf("PUSH DWORD %u\n", c_ast_literal_int_value(arg));
    //            context->esp_offset += c_ast_typename_size(c_ast_literal_typename(arg));*/
    //        }
    //        else if (c_ast_node_type(arg) == c_ast_node_variable) {
    //            //if (c_ast_typename_type(c_ast_variable_typename(arg)) != c_ast_typename_type(c_ast_variable_typename(param))) {
    //            //    printf("argument of type '%s' is incompatible with parameter of type '%s'\n",
    //            //        c_ast_typename_type_to_string(c_ast_variable_typename(arg)),
    //            //        c_ast_typename_type_to_string(c_ast_variable_typename(param)));
    //            //    abort();
    //            //}

    //            //if (c_ast_variable_type(arg) == c_ast_variable_type_stack) {
    //            //    printf("PUSH DWORD [ESP - %u]\n", c_ast_variable_addr(arg));
    //            //    context->esp_offset += c_ast_typename_size(c_ast_variable_typename(arg));
    //            //}
    //            //else if (c_ast_variable_type(arg) == c_ast_variable_type_global) {
    //            //    printf("PUSH DWORD [%s]\n", c_ast_variable_symbol(arg));
    //            //    context->esp_offset += c_ast_typename_size(c_ast_variable_typename(arg));
    //            //}
    //        }
    //        else {
    //            printf("expected an expression\n");
    //            abort();
    //        }
    //    }
    //}

    //printf("CALL %s\n", c_ast_func_ref_symbol(c_ast_func_call_ref(node)));

    return NULL;
}

struct c_ast_node *c_ast_func_call_create(struct c_ast_node *ref, struct c_ast_node *args) {
    struct c_ast_func_call *node = c_ast_func_call_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_func_call;
    node->evaluate_fn = c_ast_evaluate_func_call;
    node->func_ref = ref;
    node->func_args = args;

    return c_ast_node_cast(node);
}