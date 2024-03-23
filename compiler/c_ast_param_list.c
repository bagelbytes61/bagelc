#include "c_ast_param_list.h"
#include "c_ast_decl.h"

#include <stdlib.h>
#include <string.h>

static struct c_ast_node *c_ast_evaluate_param_list(struct c_ast_node *node, struct c_ast_context *context) {

    //{
    //    struct c_ast_node *param = c_ast_func_sig_param_list(node);
    //    for (; param != NULL; param = c_ast_node_next(param)) {
    //        c_ast_node_evaluate(param, context);
    //    }
    //}

    return NULL;
}

struct c_ast_node *c_ast_param_list_create(struct c_ast_create_info *create_info) {
    struct c_ast_param_list *node = c_ast_param_list_cast(malloc(sizeof *node));
    memset(node, 0, sizeof *node);
    node->type = c_ast_node_param_list;
    node->evaluate_fn = c_ast_evaluate_param_list;
    node->params = create_info->ast_node;
    //struct c_ast_decl *x = c_ast_decl_cast(create_info->ast_node);
    //node->return_type = return_type;
    //node->param_list = param_list; 

    return c_ast_node_cast(node);
}