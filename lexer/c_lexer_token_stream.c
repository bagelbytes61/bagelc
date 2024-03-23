#include "c_lexer_token_stream.h"

#include <assert.h>

int c_lexer_token_stream_init(struct c_lexer_token_stream *stream, size_t capacity) {
    stream->capacity = capacity + 1u;
    stream->stream = calloc(stream->capacity, sizeof(*stream->stream));
    stream->head = stream->stream;
    stream->tail = stream->stream;
    stream->empty = 1;
    stream->view = 0;

    return 0;
}

void c_lexer_token_stream_destroy(struct c_lexer_token_stream *stream) {
    assert(!stream->view);
    
    free(stream->stream);

    stream->capacity = 0u;
    stream->stream = NULL;
    stream->head = stream->tail = NULL;
    stream->empty = 0;
}

int c_lexer_token_stream_empty(struct c_lexer_token_stream *stream) {

    return stream->empty;
}

void c_lexer_token_stream_push_back(struct c_lexer_token_stream *stream, struct c_lexer_token *token) {
    assert(!stream->view);

    *stream->tail++ = *token;

    if (stream->tail - (stream->stream + stream->capacity) >= 0) {
        stream->tail = stream->stream;
    }

    stream->empty = 0;
}

void c_lexer_token_stream_pop_front(struct c_lexer_token_stream *stream) {
    assert(!stream->empty);

    ++stream->head;

    if (stream->head - (stream->stream + stream->capacity) > 0) {
        stream->head = stream->stream;
    }

    stream->empty = stream->head == stream->tail;
}

struct c_lexer_token c_lexer_token_stream_front(struct c_lexer_token_stream *stream) {
    assert(!stream->empty);

    return *stream->head;
}

struct c_lexer_token c_lexer_token_stream_peak(struct c_lexer_token_stream *stream, size_t offset) {
    struct c_lexer_token *token = NULL;

    assert(!stream->empty);
    assert(offset < (stream->head < stream->tail ? (stream->head - stream->tail)
                                                 : (stream->stream + stream->capacity - stream->head) + (stream->tail - stream->stream)));

    if (stream->head + offset >= stream->stream + stream->capacity) {
        return *(stream->stream + (stream->stream + stream->capacity - stream->head));
    }

    return *(stream->head + offset);
}

void c_lexer_token_stream_view(const struct c_lexer_token_stream *stream, struct c_lexer_token_stream *view) {
    *view = *stream;

    view->view = 1;
}

void c_lexer_token_stream_sync(struct c_lexer_token_stream *stream, const struct c_lexer_token_stream *view) {
    stream->head = view->head;
    stream->empty = view->empty;
}
