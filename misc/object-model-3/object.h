#ifndef CO_OBJECT_H
#define CO_OBJECT_H

typedef enum co_kind_t {
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
    
    CO_KIND_CTX,
    CO_KIND_NS,
    CO_KIND_STR,
    CO_KIND_LIST,
    CO_KIND_MUT_LIST,
    CO_KIND_DICT,
    CO_KIND_MUT_DICT,
    CO_KIND_CODE,
    CO_KIND_FUNC,
    CO_KIND_ASYNC_FUNC,
    CO_KIND_FUTURE,
    CO_KIND_STRUCT,
    CO_KIND_UNION,
    CO_KIND_OPTION,
    CO_KIND_SOME,
    CO_KIND_NONE,
    CO_KIND_RESULT,
    CO_KIND_OK,
    CO_KIND_ERR
    /*
    CO_KIND_USER_DEFINED
    */
} co_kind_t;

struct _co_rc_t;
union co_value_t;
struct co_object_t;

#define CO_OBJECT_HEAD \
    enum co_kind_t k;

#define CO_RC_HEAD \
    size_t rc;

#define CO_OBJECT(obj) ((struct co_object_t*)(obj))
#define CO_OBJ(obj) CO_OBJECT(obj)
// #define CO_RC(obj) CO_OBJECT(obj)->rc

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "ctx.h"

typedef struct _co_rc_t {
    CO_RC_HEAD;
} _co_rc_t;

typedef union co_value_t {
    // primitive values
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

    // ref counted
    struct _co_rc_t *rc;
    struct _co_ctx_t *ctx;
} co_value_t;

typedef struct co_object_t {
    CO_OBJECT_HEAD;
    union co_value_t v;
} co_object_t;

void co_ref(struct co_object_t *ctx, struct co_object_t *obj);
void co_unref(struct co_object_t *ctx, struct co_object_t *obj);

struct co_object_t *co_object_free(struct co_object_t *ctx, struct co_object_t *self);

#endif
