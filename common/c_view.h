#ifndef C_VIEW_H_
#define C_VIEW_H_

#pragma once

#define c_view_len(view) ((view).end - (view).begin)

struct c_view {
    const char *begin;
    union {
        const char *current;
        const char *end;
    };
};

#endif