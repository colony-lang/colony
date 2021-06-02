#ifndef CO_OBJECT_H
#define CO_OBJECT_H

union co_value_t;
struct co_object_t;

#include <stdlib.h>
#include <stdint.h>
#include "../core/ctx.h"
#include "./kind.h"
#include "./bool.h"
#include "./bytes.h"
#include "./code.h"
#include "./dict.h"
#include "./err.h"
#include "./f64.h"
#include "./i64.h"
#include "./list.h"
#include "./mut_dict.h"
#include "./mut_list.h"
#include "./none.h"
#include "./ns.h"
#include "./object.h"
#include "./ok.h"
#include "./option.h"
#include "./result.h"
#include "./some.h"
#include "./str.h"
#include "./struct.h"
#include "./type.h"
#include "./union.h"

#define CO_OBJECT_INC_RC(ctx, obj) do { \
    ((struct co_object_t *)(obj))->rc++; \
} while(0)

#define CO_OBJECT_DEC_RC(ctx, obj) do { \
    if (obj == NULL) break; \
    ((struct co_object_t *)(obj))->rc--; \
    if (((struct co_object_t *)(obj))->rc == 0) { \
        co_object_free(ctx, (struct co_object_t *)(obj)); \
    } \
} while(0)

typedef union co_value_t {
    struct co_type_t *type;
    _Bool b;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    float f32;
    double f64;
    void *bytes;
    void *str;
    void *list;
    void *mut_list;
    void *dict;
    void *mut_dict;
    struct co_ns_t *ns;
    void *code;
    void *func;
    void *closure; // ?
    void *tuple;
    void *union_;
    void *option;
    void *some;
    void *none;
    void *result;
    void *ok;
    void *err;
    void *ptr;
} co_value_t;

typedef struct co_object_t {
    size_t rc;
    enum co_kind_t kind;
    union co_value_t value;
} co_object_t;

co_object_t *co_object_new(struct co_ctx_t * ctx, co_kind_t kind, co_value_t value);
co_object_t *co_object_free(struct co_ctx_t * ctx, co_object_t *self);

// (self: any) -> str | Err
co_object_t *co_object_repr(struct co_ctx_t * ctx, co_object_t *self);

// (self: any) -> u64 | Err
co_object_t *co_object_hash(struct co_ctx_t * ctx, co_object_t *self);

#endif
