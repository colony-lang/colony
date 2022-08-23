#include "builtins.h"

struct co_object_t co_builtins_c_populate_ctx(struct co_ctx_t *ctx) {
    // TODO:
    //
    // co_object_t obj;
    // co_object_t builtins_module;
    //
    // obj = (co_object_t){.k = CO_KIND_UNDEFINED};
    // // builtins_module = co_module_new(ctx, obj);
    // return builtins_module;

    return ctx->undefined;
}
