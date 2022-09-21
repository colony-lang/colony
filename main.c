#include <stdio.h>
#include "colony.h"

int main(int argc, char **argv) {
    // root context
    // co_ctx_t *root_ctx = co_ctx_new();
    co_object_t root_ctx = co_ctx_c_new_root();
    
    // context with root contect as parent
    co_object_t ctx = co_ctx_c_spawn(root_ctx);

    // co_object_t builtins;
    
    // root context - builtins
    // builtins = co_builtins_c_populate_ctx(root_ctx);

    // cleanup
    CO_OBJECT_C_DECREF(root_ctx, ctx);
    CO_OBJECT_C_DECREF(root_ctx, root_ctx);

    return 0;
}
