#ifndef C_PARSER_H_
#define C_PARSER_H_

#pragma once

int c_parse(struct c_lexer_token_stream *stream, struct c_ast_node **ast);

#endif
