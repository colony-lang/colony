#include <stdio.h>
#include "colony.h"

int main(int argc, char **argv) {
    // root context
    // co_ctx_t *root_ctx = co_ctx_new();
    co_object_t root_ctx = co_ctx_c_new_root();
    // co_object_t builtins;
    
    // root context - builtins
    // builtins = co_builtins_c_populate_ctx(root_ctx);
    
    // context with root contect as parent
    // co_ctx_t *ctx = co_ctx_spawn(root_ctx);

    // cleanup
    // co_object_c_decref(root_ctx, ctx);
    co_object_c_decref(root_ctx, root_ctx);

    return 0;
}
