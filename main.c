#include "colony.h"

void example_bool(co_object_t ctx) {
    co_object_t b0 = co_bool_c_new(ctx, true);
    co_object_t b1 = co_bool_c_new(ctx, false);
    co_object_t b2 = co_bool_c_not(ctx, b0);
    assert(b2.v.b == false);
    
    co_object_t b3 = co_bool_c_and(ctx, b0, b1);
    assert(b3.v.b == false);
    
    co_object_t b4 = co_bool_c_or(ctx, b0, b1);
    assert(b4.v.b == true);
}

void example_bytes(co_object_t ctx) {
    co_object_t b0 = co_bytes_c_new(ctx, 5, "Hello");
    co_object_t b1 = co_bytes_c_new(ctx, 5, "Hello");
    co_object_t v0 = co_bytes_c_eq(ctx, b0, b1);
    assert(v0.v.b == true);

    CO_OBJECT_C_DECREF(ctx, b0);
    CO_OBJECT_C_DECREF(ctx, b1);
}

int main(int argc, char **argv) {
    // root context
    co_object_t root_ctx = co_ctx_c_new_root();
    
    // context with root contect as parent
    co_object_t ctx = co_ctx_c_spawn(root_ctx);
    co_object_t ctx2 = co_ctx_c_spawn(ctx);
    
    // bool
    example_bool(ctx);

    // bytes
    example_bytes(ctx);

    // cleanup
    CO_OBJECT_C_DECREF(root_ctx, ctx2);
    CO_OBJECT_C_DECREF(root_ctx, ctx);
    CO_OBJECT_C_DECREF(root_ctx, root_ctx);
    
    return 0;
}
