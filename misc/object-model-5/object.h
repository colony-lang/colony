#ifndef CO_OBJECT_H
#define CO_OBJECT_H

typedef enum co_kind_t {
    // primitive values
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

    // ref counted values
    CO_KIND_GC,

    // CO_KIND_CTX,
    // CO_KIND_NS,
    // CO_KIND_STR,
    // CO_KIND_LIST,
    // CO_KIND_MUT_LIST,
    // CO_KIND_DICT,
    // CO_KIND_MUT_DICT,
    // CO_KIND_CODE,
    // CO_KIND_FUNC,
    // CO_KIND_ASYNC_FUNC,
    
    // misc
    // CO_KIND_TYPE,
    // CO_KIND_STRUCT,
    // CO_KIND_UNION,
    // CO_KIND_OPTION,
    // CO_KIND_SOME,
    // CO_KIND_NONE,
    // CO_KIND_RESULT,
    // CO_KIND_OK,
    // CO_KIND_ERR,
    // CO_KIND_FUTURE,
} co_kind_t;

struct _co_type_t;
struct co_type_t;

/* used to transfer ownership */
typedef enum co_own_t {
    CO_OWN_NONE,
    CO_OWN_FULL
} co_own_t;

struct co_gc_t;
union co_value_t;
struct co_object_t;

#define CO_OBJECT_HEAD \
    union { \
        enum co_kind_t k; \
        struct co_type_t *t; \
    }

#define CO_TYPE_HEAD \
    struct co_object_t *type; \
    struct co_object_t *name; \
    struct co_object_t *bases; \
    struct co_object_t *attrs;

#define CO_GC_HEAD \
    size_t rc;


#define CO_OBJECT(obj) ((struct co_object_t*)(obj))
#define CO_OBJ(obj) CO_OBJECT(obj)

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "ctx.h"
#include "result.h"

typedef struct co_gc_t {
    CO_GC_HEAD;
} co_gc_t;

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

    // gc'ed values
    struct co_gc_t *gc;
} co_value_t;

typedef struct co_object_t {
    CO_OBJECT_HEAD;
    union co_value_t v;
} co_object_t;

/*
 * type
 */
typedef struct _co_type_t {
    CO_GC_HEAD;
    CO_TYPE_HEAD;
} _co_type_t;

typedef struct co_type_t {
    CO_OBJECT_HEAD;
    struct _co_type_t *_type;
} co_type_t;

/*
 * gc
 */
void co_ref(struct co_object_t *ctx, struct co_object_t *self);
void co_unref(struct co_object_t *ctx, struct co_object_t *self);

/*
 * object
 */
struct co_object_t *co_object_new(struct co_object_t *ctx, enum co_kind_t k, union co_value_t v);

/* (self: 'Self') -> Result[str, str] */
struct co_object_t *co_object_free(struct co_object_t *ctx, struct co_object_t *self);

/*
 * type
 */
/* (cls: type, name: str, bases: list[type], attrs: dict[str, object]) -> 'Self' */
struct co_object_t *co_type_new(struct co_object_t *ctx, struct co_object_t *type, struct co_object_t *name, struct co_object_t *bases, struct co_object_t *attrs);

/* (self: 'Self') -> object */
struct co_object_t *co_type_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: type, args: list[object], kwargs: dict[str, object]) -> 'Self' */
struct co_object_t *co_type_call(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *args, struct co_object_t *kwargs);

#endif
