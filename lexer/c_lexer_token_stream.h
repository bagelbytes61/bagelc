#ifndef C_LEXER_TOKEN_STREAM_H_
#define C_LEXER_TOKEN_STREAM_H_

#pragma once

#include "c_lexer_token.h"

#include <stddef.h>
#include <stdlib.h>

struct c_lexer_token_stream {
    size_t                capacity;
    struct c_lexer_token *stream;
    struct c_lexer_token *head;
    struct c_lexer_token *tail;
    int                   empty;
    int                   view;
};

int c_lexer_token_stream_init(struct c_lexer_token_stream *stream, size_t capacity);
void c_lexer_token_stream_destroy(struct c_lexer_token_stream *stream);

int c_lexer_token_stream_empty(struct c_lexer_token_stream *stream);

void c_lexer_token_stream_push_back(struct c_lexer_token_stream *stream, struct c_lexer_token *token);
void c_lexer_token_stream_pop_front(struct c_lexer_token_stream *stream);

struct c_lexer_token c_lexer_token_stream_front(struct c_lexer_token_stream *stream);
struct c_lexer_token c_lexer_token_stream_peak(struct c_lexer_token_stream *stream, size_t offset);

void c_lexer_token_stream_view(const struct c_lexer_token_stream *stream, struct c_lexer_token_stream *view);

void c_lexer_token_stream_sync(struct c_lexer_token_stream *stream, const struct c_lexer_token_stream *view);

#endif