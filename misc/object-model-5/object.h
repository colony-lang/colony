#ifndef CO_OBJECT_H
#define CO_OBJECT_H

enum co_kind_t;
struct _co_type_t;
struct co_type_t;
union co_kind_type_t;
enum co_own_t;
struct co_gc_t;
union co_value_t;
struct co_object_t;

/* kind of object, mainly used to distinguish between primitive and GC'ed objects */
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
    
    // special
    CO_KIND_TYPE,
    CO_KIND_CTX,

    // Result, Ok, Err
    CO_KIND_OK_TYPE,
    CO_KIND_OK,
    CO_KIND_ERR_TYPE,
    CO_KIND_ERR,
    CO_KIND_RESULT_TYPE,

    // Option, Some, None
    CO_KIND_SOME_TYPE,
    CO_KIND_SOME,
    CO_KIND_NONE,
    CO_KIND_OPTION_TYPE,
} co_kind_t;

/* used to transfer ownership */
typedef enum co_own_t {
    CO_OWN_NONE,
    CO_OWN_FULL
} co_own_t;

#define CO_GC_HEAD \
    size_t rc;

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

#define CO_OBJECT(obj) ((struct co_object_t*)(obj))

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "ctx.h"
#include "bytes.h"
#include "str.h"
#include "option.h"
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

    // GC'ed values
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

typedef union co_kind_type_t {
    enum co_kind_t k;
    struct co_type_t *t;
} co_kind_type_t;

/*
 * GC - reference counter
 */
void co_ref(struct co_object_t *ctx, struct co_object_t *self);
void co_unref(struct co_object_t *ctx, struct co_object_t *self);

/*
 * object
 */
/* (...) -> object */
struct co_object_t *co_object_alloc(struct co_object_t *ctx, union co_kind_type_t kt, union co_value_t v);

/* (cls: type) -> Self */
struct co_object_t *co_object_new(struct co_object_t *ctx, struct co_object_t *cls); 

/* (self: Self) -> None */
struct co_object_t *co_object_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: Self) -> type */
struct co_object_t *co_object_gettype(struct co_object_t *ctx, struct co_object_t *self);

/* (self: Self, attr: str) -> Result[object, str] */
struct co_object_t *co_object_getattr(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *attr);

/* (self: Self, attr: str, value: object) -> Self */
struct co_object_t *co_object_setattr(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *attr, struct co_object_t *value);

/* (self: Self, attr: str) -> Self */
struct co_object_t *co_object_delattr(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *attr);

/*
 * type
 */
/* (cls: type, name: str, bases: list[type], attrs: NameSpace) -> Self */
struct co_object_t *co_type_new(struct co_object_t *ctx, struct co_object_t *cls, struct co_object_t *name, struct co_object_t *bases, struct co_object_t *attrs);

/* (self: Self) */
struct co_object_t *co_type_free(struct co_object_t *ctx, struct co_object_t *self);

/* (self: type, args: Option[list[object]]=None, kwargs: Option[dict[str, object]]=None) -> Self */
struct co_object_t *co_type_call(struct co_object_t *ctx, struct co_object_t *self, struct co_object_t *args, struct co_object_t *kwargs);

#endif
