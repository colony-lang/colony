#include <stdio.h>
#include "ctx.h"
#include "object.h"
#include "builtins.h"

int main(int argc, char **argv) {
    co_ctx_t *root_ctx = co_ctx_new(NULL);
    co_object_t *res;

    res = co_builtins_init(root_ctx);
    
    co_ctx_t *ctx = co_ctx_new(root_ctx);
    co_ctx_free(ctx);

    CO_OBJECT_DEC_RC(root_ctx, res);
    return 0;
}
