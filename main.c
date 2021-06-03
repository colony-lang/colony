#include <stdio.h>
#include "core/ctx.h"
#include "object/object.h"
#include "lib/builtins.h"

int main(int argc, char **argv) {
    // root context
    co_ctx_t *root_ctx = co_ctx_new(NULL);
    co_object_t *res;

    // root context - builtins
    res = co_builtins_init(root_ctx);
    
    // context with root contect as parent
    co_ctx_t *ctx = co_ctx_new(root_ctx);

    // cleanup
    co_ctx_free(ctx);
    co_ctx_free(root_ctx);
    CO_OBJECT_DEC_RC(root_ctx, res);
    return 0;
}
