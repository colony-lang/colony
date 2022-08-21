#include "ns.h"
#include "../object/str.h"

struct co_ns_t *co_ns_new(struct co_ctx_t *ctx, struct co_frame_t *frame) {
    co_ns_t *ns = malloc(sizeof(co_ns_t));
    ns->ctx = ctx;
    ns->frame = frame;
    ns->attrs_cap = 8;
    ns->attrs_len = 0;
    ns->attrs = calloc(ns->attrs_cap, sizeof(co_object_t));
    return ns;
}

int co_ns_free(struct co_ctx_t *ctx, struct co_ns_t *ns) {
    free(ns->attrs);
    free(ns);
}

struct co_object_t co_ns_getattr(struct co_ns_t *ns, struct co_object_t attr) {
    co_ctx_t *ctx = ns->ctx;
    co_str_t *attr_str_v = (co_str_t*)attr.v.ptr;
    co_object_t value;
    co_object_t res;

    for (int i = 0; i < ns->attrs_len; i++) {
        value = ns->attrs[i];
        res = co_str_eq_c(ctx, value, attr_str_v->len, attr_str_v->items);
        // TODO:
    }
}

struct co_object_t co_ns_setattr(struct co_ns_t *ns, struct co_object_t attr, struct co_object_t value) {

}
