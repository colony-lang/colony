#include <stdio.h>

#include "colony.h"

void ex0(void) {
    // co_object_t *ctx = co_ctx_new(NULL, NULL, NULL, NULL);
    
    // co_object_t *s0 = co_str_c_new(ctx, 5, "hello", CO_OWN_NONE, NULL);
    // co_object_t *s1 = co_str_c_new(ctx, 1, " ", CO_OWN_NONE, NULL);
    // co_object_t *s2 = co_str_c_new(ctx, 5, "world", CO_OWN_NONE, NULL);
    
    // co_object_t *s3 = co_str_add(ctx, s0, s1);
    // co_object_t *s4 = co_str_add(ctx, s3, s2);
    
    // co_unref(ctx, s4);
    // co_unref(ctx, s3);
    // co_unref(ctx, s2);
    // co_unref(ctx, s1);
    // co_unref(ctx, s0);
    // co_unref(NULL, ctx);
}

int main(int argc, char **argv) {
    // _co_type_static_init();
    ex0();
    return 0;
}
