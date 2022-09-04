#include "str.h"
#include "struct.h"

/* (cls: type, other: str) -> str */
co_object_t co_str_new(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, len: size_t, items: char*) -> str */
co_object_t co_str_new_c(co_ctx_t *ctx, size_t len, char *items) {
    // create str value
    co_str_t *v = malloc(sizeof(co_str_t));
    v->rc = 1;
    v->len = len;
    v->items = items;

    // create self object
    co_object_t self = co_object_new_c_ptr(ctx, CO_KIND_STR, v);
    return self;
}

/* (self: str) -> Undefined */
co_object_t co_str_free(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, self: co_object_t) -> Undefined */
co_object_t co_str_free_c(co_ctx_t *ctx, co_object_t self) {
    // free str value
    co_str_t *v = (co_str_t*)self.v.ptr;
    free(v->items);
    free(v);

    // clear object type
    self.k = CO_KIND_UNDEFINED;
    return self;
}

/* (self: str, other: str) -> bool */
co_object_t co_str_lt(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, other: str) -> bool */
co_object_t co_str_eq(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (ctx, self: str, len: size_t, items: char*) -> bool */
co_object_t co_str_eq_c(co_ctx_t *ctx, co_object_t self, size_t len, char *items) {
    co_str_t *v = (co_str_t*)self.v.ptr;
    co_object_t ret;

    if (v->len != len) {
        // TODO: move def to `bool.h/c` file
        ret = (co_object_t){
            .k = CO_KIND_BOOL,
            .v = {
                .b = false
            }
        };

        return ret;
    }

    if (strncmp(v->items, items, len) != 0) {
        // TODO: move def to `bool.h/c` file
        ret = (co_object_t){
            .k = CO_KIND_BOOL,
            .v = {
                .b = false
            }
        };

        return ret;
    }

    // TODO: move def to `bool.h/c` file
    ret = (co_object_t){
        .k = CO_KIND_BOOL,
        .v = {
            .b = true
        }
    };

    return ret;
}

/* (self: str) -> u64 */
co_object_t co_str_hash(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str) -> u64 */
co_object_t co_str_len(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, other: str) -> str */
co_object_t co_str_add(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, other: str) -> list<str> */
co_object_t co_str_split(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, from: u64, to: u64) -> str */
co_object_t co_str_get_slice(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, from: u64, to: u64, other: str) -> str */
co_object_t co_str_set_slice(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, index: u64) -> str */
co_object_t co_str_get_item(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str, index: u64, value: str) -> str */
co_object_t co_str_set_item(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}

/* (self: str) -> bytes */
co_object_t co_str_encode(co_ctx_t *ctx, co_object_t obj) {
    // TODO:
    return ctx->undefined;
}
