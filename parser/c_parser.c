#include "c_parser.h"

#include "c_parser_grammar.h"

#include "../compiler/c_ast_translation_unit.h"

int c_parse(struct c_lexer_token_stream *stream, struct c_ast_node **ast_node) {
    int ret = -1;
    
    int depth = 0;
    //struct c_ast_create_info create_info = { 0 };

    c_translation_unit.nonterminal.match(stream, &c_translation_unit, depth, &ret);

    return ret;
}