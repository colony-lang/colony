#ifndef CO_OBJECT_H
#define CO_OBJECT_H

enum co_kind_t;
union co_value_t;
struct co_object_t;

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "../core/ctx.h"

typedef enum co_kind_t {
    CO_KIND_CTX,
    CO_KIND_BOOL,
    CO_KIND_I8,
    CO_KIND_I16,
    CO_KIND_I32,
    CO_KIND_I64,
    CO_KIND_U8,
    CO_KIND_U16,
    CO_KIND_U32,
    CO_KIND_U64,
    CO_KIND_F32,
    CO_KIND_F64,
    CO_KIND_STR,
    CO_KIND_LIST,
    CO_KIND_DICT,
    CO_KIND_NS,
    CO_KIND_CODE,
    CO_KIND_FUNC,
    CO_KIND_STRUCT,
    CO_KIND_UNION,
    CO_KIND_PTR
} co_kind_t;

typedef union co_value_t {
    struct co_ctx_t *ctx;
    _Bool b;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    float f32;
    double f64;
    // struct co_str_t *str;
    // struct co_list_t *list;
    // struct co_dict_t *dict;
    // struct co_ns_t *ns;
    // struct co_code_t *code;
    // struct co_func_t *func;
    // struct co_struct_t *struct_;
    // struct co_union_t *union_;
    // struct co_ptr_t *ptr;
} co_value_t;

typedef struct co_object_t {
    size_t rc;
    struct co_object_t *ctx;
    enum co_kind_t k;
    union co_value_t v;
} co_object_t;

inline void co_ref(struct co_ctx_t *ctx, struct co_object_t *obj);
inline void co_unref(struct co_ctx_t *ctx, struct co_object_t *obj);

struct co_object_t *co_object_new(struct co_ctx_t *ctx, enum co_kind_t k, union co_value_t v);
struct co_object_t *co_object_free(struct co_ctx_t *ctx, struct co_object_t *self);

#endif