#include "builtins.h"

struct co_object_t co_builtins_c_populate_ctx(struct co_ctx_t *ctx) {
    co_object_t obj;
    co_object_t builtins_module;

    obj = (co_object_t){.t = CO_TYPE_UNDEFINED};
    builtins_module = co_module_new(ctx, obj);
    return builtins_module;
}