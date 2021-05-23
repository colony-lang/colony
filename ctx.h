#ifndef CO_CTX_H
#define CO_CTX_H

#include <stdlib.h>

typedef struct co_ctx_t {
	void * dummy;
} co_ctx_t;

co_ctx_t *co_ctx_new(void);
void co_ctx_free(co_ctx_t *ctx);
void *co_ctx_mem_alloc(co_ctx_t *ctx, size_t size);
void co_ctx_mem_free(co_ctx_t *ctx, void *ptr);

#endif
