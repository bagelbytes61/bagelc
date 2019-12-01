#include "ast_context.h"

#include <string.h>

void c_ast_context_init(struct c_ast_context *context) {
    memset(context, 0, sizeof *context);
}