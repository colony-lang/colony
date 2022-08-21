#ifndef CO_CTX_H
#define CO_CTX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct co_ctx_t;

#include "frame.h"
#include "../object/object.h"

typedef struct co_ctx_t {
    struct co_ctx_t *parent;
    
    // predefined values
    struct co_object_t undefined;   // special value of undefined
    struct co_object_t builtins;    // builtins module

    // array of ctx's
    size_t ctxs_cap;
    size_t ctxs_len;
    struct co_ctx_t **ctxs;

    // array of frames
    size_t frames_cap;
    size_t frames_len;
    struct co_frame_t **frames;
} co_ctx_t;

struct co_ctx_t *co_ctx_new(void);
struct co_ctx_t *co_ctx_spawn(struct co_ctx_t *ctx);
int co_ctx_free(struct co_ctx_t *ctx);
void co_ctx_panic(struct co_ctx_t *ctx, char *msg);

// { ???

/* (self: ctx, attr: str) -> object */
struct co_object_t co_ctx_getattr(struct co_ctx_t *ctx, struct co_object_t obj);

/* (ctx, attr: char*) -> object */
struct co_object_t co_ctx_getattr_c(struct co_ctx_t *ctx, char *attr);

/* (self: ctx, attr: str, value: object) -> object */
struct co_object_t co_ctx_setattr(struct co_ctx_t *ctx, struct co_object_t obj);

/* (ctx, attr: char*, value: char*) -> object */
struct co_object_t co_ctx_setattr_c(struct co_ctx_t *ctx, char *attr, struct co_object_t value);

// } ???

#endif
