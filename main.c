#include "colony.h"

void example_bool(co_object_t ctx) {
    co_object_t b0 = co_bool_c_new(ctx, true);
    co_object_t b1 = co_bool_c_new(ctx, false);
    co_object_t b2 = co_bool_c_not(ctx, b0);
    assert(b2.v.b == false);
    co_print_c(ctx, b2);
    
    co_object_t b3 = co_bool_c_and(ctx, b0, b1);
    assert(b3.v.b == false);
    co_print_c(ctx, b3);
    
    co_object_t b4 = co_bool_c_or(ctx, b0, b1);
    assert(b4.v.b == true);
    co_print_c(ctx, b4);
}

void example_i64(co_object_t ctx) {
    co_object_t v0 = co_i64_c_new(ctx, 1);
    co_object_t v1 = co_i64_c_new(ctx, 20);
    co_object_t v2 = co_i64_c_add(ctx, v0, v1);
    co_print_c(ctx, v2);

    // co_object_t sv2 = co_i64_c_repr(ctx, v2); // str
    // co_print_c(ctx, sv2);
    // CO_OBJECT_C_DECREF(ctx, sv2);
}

void example_f64(co_object_t ctx) {
    co_object_t v0 = co_f64_c_new(ctx, 1.0);
    co_object_t v1 = co_f64_c_new(ctx, 20.0);
    co_object_t v2 = co_f64_c_add(ctx, v0, v1);
    co_print_c(ctx, v2);
}

void example_bytes(co_object_t ctx) {
    co_object_t b0 = co_bytes_c_new(ctx, 5, "Hello", CO_OWN_TRANS_COPY);
    co_object_t b1 = co_bytes_c_new(ctx, 5, "Hello", CO_OWN_TRANS_COPY);
    co_object_t v0 = co_bytes_c_eq(ctx, b0, b1);
    assert(v0.v.b == true);
    CO_OBJECT_C_DECREF(ctx, b0);
    CO_OBJECT_C_DECREF(ctx, b1);

    co_object_t b2 = co_bytes_c_new(ctx, 5, "Hello", CO_OWN_TRANS_COPY);
    co_object_t b3 = co_bytes_c_new(ctx, 1, " ", CO_OWN_TRANS_COPY);
    co_object_t b4 = co_bytes_c_new(ctx, 5, "world", CO_OWN_TRANS_COPY);
    co_object_t b5 = co_bytes_c_new(ctx, 1, "!", CO_OWN_TRANS_COPY);
    
    co_object_t b6 = co_bytes_c_add(ctx, b2, b3);
    co_object_t b7 = co_bytes_c_add(ctx, b6, b4);
    co_object_t b8 = co_bytes_c_add(ctx, b7, b5);

    co_print_c(ctx, b2);
    co_print_c(ctx, b3);
    co_print_c(ctx, b4);
    co_print_c(ctx, b5);
    co_print_c(ctx, b8);
    
    CO_OBJECT_C_DECREF(ctx, b2);
    CO_OBJECT_C_DECREF(ctx, b3);
    CO_OBJECT_C_DECREF(ctx, b4);
    CO_OBJECT_C_DECREF(ctx, b5);
    CO_OBJECT_C_DECREF(ctx, b6);
    CO_OBJECT_C_DECREF(ctx, b7);
    CO_OBJECT_C_DECREF(ctx, b8);
}

int main(int argc, char **argv) {
    // root context
    co_object_t root_ctx = co_ctx_c_new_root();
    
    // context with root contect as parent
    co_object_t ctx = co_ctx_c_spawn(root_ctx);
    co_object_t ctx2 = co_ctx_c_spawn(ctx);
    
    // bool
    example_bool(ctx);

    // i64
    example_i64(ctx);

    // f64
    example_f64(ctx);

    // bytes
    example_bytes(ctx);

    // cleanup
    CO_OBJECT_C_DECREF(root_ctx, ctx2);
    CO_OBJECT_C_DECREF(root_ctx, ctx);
    CO_OBJECT_C_DECREF(root_ctx, root_ctx);
    
    return 0;
}
