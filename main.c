#include <stdio.h>
#include "colony.h"

int main(int argc, char **argv) {
    // root context
    co_ctx_t *root_ctx = co_ctx_new();
    co_object_t builtins;

    // root context - builtins
    builtins = co_builtins_c_populate_ctx(root_ctx);
    
    // context with root contect as parent
    // co_ctx_t *ctx = co_ctx_new(root_ctx);

    // cleanup
    // co_ctx_free(ctx);
    co_ctx_free(root_ctx);
    // CO_OBJECT_DEC_RC(root_ctx, res);
    return 0;
}
