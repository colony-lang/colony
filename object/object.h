#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define CO_GC_HEAD ssize_t rc

enum co_type_t;

struct co_gc_t;
struct co_bytes_t;
struct co_str_t;
struct co_struct_t;
struct co_union_t;
struct co_list_t;
struct co_dict_entry_t;
struct co_dict_t;
struct co_tuple_t;
struct co_block_t;
struct co_code_t;
enum co_fn_args_type_t;
struct co_fn_t;
struct co_option_t;
struct co_some_t;
struct co_none_t;
struct co_result_t;
struct co_ok_t;
struct co_err_t;

union co_value_t;

struct co_object_t;

#include "../core/ctx.h"

typedef enum co_type_t {
    // primitive types
    CO_TYPE_BOOL = 1,
    CO_TYPE_U8 = 2,
    CO_TYPE_I8 = 3,
    CO_TYPE_U16 = 4,
    CO_TYPE_I16 = 5,
    CO_TYPE_U32 = 6,
    CO_TYPE_I32 = 7,
    CO_TYPE_U64 = 8,
    CO_TYPE_I64 = 9,
    CO_TYPE_F32 = 10,
    CO_TYPE_F64 = 11,

    // GC'ed types
    CO_TYPE_BYTES = 20,
    CO_TYPE_STR = 21,
    CO_TYPE_TUPLE = 30,
    CO_TYPE_STRUCT = 31,
    CO_TYPE_UNION = 32,
    CO_TYPE_LIST = 40,
    CO_TYPE_DICT = 41,
    CO_TYPE_CODE = 50,
    CO_TYPE_BLOCK = 51,
    CO_TYPE_FN = 52,
    CO_TYPE_OPTION = 60,
    CO_TYPE_SOME = 61,
    CO_TYPE_NONE = 62,
    CO_TYPE_RESULT = 63,
    CO_TYPE_OK = 64,
    CO_TYPE_ERR = 65,
    CO_TYPE_OBJECT = 66,
} co_type_t;

typedef struct co_gc_t {
    CO_GC_HEAD;
} co_gc_t;

typedef struct co_bytes_t {
    CO_GC_HEAD;
    size_t len;
    char *items;
} co_bytes_t;

typedef struct co_str_t {
    CO_GC_HEAD;
    size_t len;
    char *items;
} co_str_t;

typedef struct co_tuple_entry_t {
    size_t index;
    struct co_object_t *name;       // None[str] | str
    struct co_object_t *type;       // None[str] | str | type
    struct co_object_t *value;      // None[Any] | Any
} co_tuple_entry_t;

// NOTE: can be optimized to know if tuple representing generic, args, params
typedef struct co_tuple_t {
    CO_GC_HEAD;
    struct co_option_t *generics;   // None[tuple] | tuple
    size_t len;
    struct co_tuple_entry_t *items;
    struct co_object_t *args;       // None[list] | list
    struct co_object_t *kwargs;     // None[dict] | dict
} co_tuple_t;

typedef struct co_struct_t {
    CO_GC_HEAD;
    struct co_option_t *generics;   // None[tuple] | tuple
    struct co_option_t *fields;     // tuple
} co_struct_t;

typedef struct co_union_t {
    CO_GC_HEAD;
    struct co_option_t *generics;   // None[tuple] | tuple
    struct co_option_t *types;      // tuple
} co_union_t;

typedef struct co_list_t {
    CO_GC_HEAD;
    size_t cap;
    size_t len;
    struct co_option_t *item_type;  // None[type] | type
    struct co_option_t *items;
} co_list_t;

typedef struct co_dict_entry_t {
    ssize_t hash;
    struct co_object_t *key;        // Any
    struct co_object_t *value;      // Any
} co_dict_entry_t;

typedef struct co_dict_t {
    CO_GC_HEAD;
    size_t fill;
    size_t used;
    size_t mask;
    struct co_option_t *key_type;       // None[type] | type
    struct co_option_t *value_type;     // None[type] | type
    struct co_dict_entry_t *entries;
} co_dict_t;

typedef struct co_code_t {
    CO_GC_HEAD;
    size_t len;
    char *items;
} co_code_t;

typedef struct co_block_t {
    CO_GC_HEAD;
    struct co_object_t *ret_type;   // None[type] | type
    struct co_object_t *code;       // code
} co_block_t;

// ?
// ARGS naming vs regular args ??
// KWARGS naming vs regular kwargs ??
typedef enum co_fn_args_type_t {
    CO_FN_ARGS_TYPE_NONE,
    CO_FN_ARGS_TYPE_CLS,
    CO_FN_ARGS_TYPE_CLS_VALUE,
    CO_FN_ARGS_TYPE_CLS_C_VALUE,
    CO_FN_ARGS_TYPE_CLS_ARGS,
    CO_FN_ARGS_TYPE_CLS_KWARGS,
    CO_FN_ARGS_TYPE_CLS_ARGS_KWARGS,
    CO_FN_ARGS_TYPE_SELF,
    CO_FN_ARGS_TYPE_SELF_VALUE,
    CO_FN_ARGS_TYPE_SELF_C_VALUE,
    CO_FN_ARGS_TYPE_SELF_ARGS,
    CO_FN_ARGS_TYPE_SELF_KWARGS,
    CO_FN_ARGS_TYPE_SELF_ARGS_KWARGS,
    CO_FN_ARGS_TYPE_ARGS,
    CO_FN_ARGS_TYPE_KWARGS,
    CO_FN_ARGS_TYPE_ARGS_KWARGS,
} co_fn_args_type_t;

// NOTE: function can be defined with generics, and specialized with types for given generics
typedef struct co_fn_t {
    CO_GC_HEAD;
    enum co_fn_args_type_t args_type;
    struct co_object_t *params;     // tuple, can include generics
    struct co_object_t *ret;
    struct co_code_t *code;
} co_fn_t;

typedef struct co_result_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
} co_result_t;

typedef struct co_ok_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
    struct co_option_t *v;
} co_ok_t;

typedef struct co_err_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
    struct co_option_t *e;
} co_err_t;

typedef struct co_option_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
} co_option_t;

typedef struct co_some_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
    struct co_option_t *v;
} co_some_t;

typedef struct co_none_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
} co_none_t;

typedef union co_value_t {
    // primitive values
    _Bool b;
    uint8_t u8;
    int8_t i8;
    uint16_t u16;
    int16_t i16;
    uint32_t u32;
    int32_t i32;
    uint64_t u64;
    int64_t i64;
    float f32;
    double f64;

    // GC'ed values
    struct co_bytes_t *bytes;
    struct co_str_t *str;
    struct co_struct_t *struct_;
    struct co_union_t *union_;
    struct co_list_t *list;
    struct co_dict_t *dict;
    struct co_tuple_t *tuple;
    struct co_code_t *code;
    struct co_block_t *block;
    struct co_fn_t *fn;
    struct co_result_t *result;
    struct co_ok_t *ok;
    struct co_err_t *err;
    struct co_option_t *option;
    struct co_some_t *some;
    struct co_none_t *none;
    struct co_object_t *obj;
} co_value_t;

typedef struct co_object_t {
    enum co_type_t t;
    union co_value_t v;
} co_object_t;

/*
 * GC'ed object
 */
inline ssize_t co_object_incref(struct co_ctx_t *ctx, struct co_object_t self);
inline ssize_t co_object_decref(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * object
 */
struct co_object_t co_object_new_from_raw(struct co_ctx_t *ctx, enum co_type_t t, union co_value_t v);
struct co_object_t co_object_free(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * bool
 */
/* fn((ffi.c._Bool,), bool) */
struct co_object_t co_bool_new_from_raw(struct co_ctx_t *ctx, _Bool b);
/* fn((bool,), Any) */
struct co_object_t co_bool_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), str) */
struct co_object_t co_bool_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), int) */
struct co_object_t co_bool_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool, bool), bool) */
struct co_object_t co_bool_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bool, bool), bool) */
struct co_object_t co_bool_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bool,), bool) */
struct co_object_t co_bool_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool, bool), bool) */
struct co_object_t co_bool_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bool, bool), bool) */
struct co_object_t co_bool_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bool, bool), bool) */
struct co_object_t co_bool_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bool,), bool) */
struct co_object_t co_bool_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), u8) */
struct co_object_t co_bool_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), i8) */
struct co_object_t co_bool_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), u16) */
struct co_object_t co_bool_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), i16) */
struct co_object_t co_bool_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), u32) */
struct co_object_t co_bool_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), i32) */
struct co_object_t co_bool_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), u64) */
struct co_object_t co_bool_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), i64) */
struct co_object_t co_bool_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), f32) */
struct co_object_t co_bool_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bool,), f64) */
struct co_object_t co_bool_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * u8
 */
/* fn((ffi.c.uint8_t,), u8) */
struct co_object_t co_u8_new_from_raw(struct co_ctx_t *ctx, uint8_t v);
/* fn((u8,), Any) */
struct co_object_t co_u8_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), str) */
struct co_object_t co_u8_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), int) */
struct co_object_t co_u8_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8, u8), bool) */
struct co_object_t co_u8_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), bool) */
struct co_object_t co_u8_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8,), bool) */
struct co_object_t co_u8_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8,), u8) */
struct co_object_t co_u8_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8, u8), u8) */
struct co_object_t co_u8_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u8,), bool) */
struct co_object_t co_u8_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), u8) */
struct co_object_t co_u8_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), i8) */
struct co_object_t co_u8_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), u16) */
struct co_object_t co_u8_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), i16) */
struct co_object_t co_u8_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), u32) */
struct co_object_t co_u8_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), i32) */
struct co_object_t co_u8_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), u64) */
struct co_object_t co_u8_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), i64) */
struct co_object_t co_u8_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), f32) */
struct co_object_t co_u8_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u8,), f64) */
struct co_object_t co_u8_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * i8
 */
/* fn((ffi.c.int8_t,), i8) */
struct co_object_t co_i8_new_from_raw(struct co_ctx_t *ctx, int8_t v);
/* fn((i8,), Any) */
struct co_object_t co_i8_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), str) */
struct co_object_t co_i8_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), int) */
struct co_object_t co_i8_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8, i8), bool) */
struct co_object_t co_i8_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), bool) */
struct co_object_t co_i8_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8,), bool) */
struct co_object_t co_i8_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8,), i8) */
struct co_object_t co_i8_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), i8) */
struct co_object_t co_i8_neg(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), i8) */
struct co_object_t co_i8_pos(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8, i8), i8) */
struct co_object_t co_i8_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i8,), bool) */
struct co_object_t co_i8_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), u8) */
struct co_object_t co_i8_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), i8) */
struct co_object_t co_i8_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), u16) */
struct co_object_t co_i8_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), i16) */
struct co_object_t co_i8_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), u32) */
struct co_object_t co_i8_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), i32) */
struct co_object_t co_i8_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), u64) */
struct co_object_t co_i8_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), i64) */
struct co_object_t co_i8_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), f32) */
struct co_object_t co_i8_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i8,), f64) */
struct co_object_t co_i8_as_f64(struct co_ctx_t *ctx, struct co_object_t self);
/*
 * u16
 */
/* fn((ffi.c.uint16_t,), u16) */
struct co_object_t co_u16_new_from_raw(struct co_ctx_t *ctx, uint16_t v);
/* fn((u16,), Any) */
struct co_object_t co_u16_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), str) */
struct co_object_t co_u16_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), int) */
struct co_object_t co_u16_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16, u16), bool) */
struct co_object_t co_u16_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), bool) */
struct co_object_t co_u16_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16,), bool) */
struct co_object_t co_u16_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16,), u16) */
struct co_object_t co_u16_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16, u16), u16) */
struct co_object_t co_u16_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u16,), bool) */
struct co_object_t co_u16_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), u8) */
struct co_object_t co_u16_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), i8) */
struct co_object_t co_u16_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), u16) */
struct co_object_t co_u16_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), i16) */
struct co_object_t co_u16_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), u32) */
struct co_object_t co_u16_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), i32) */
struct co_object_t co_u16_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), u64) */
struct co_object_t co_u16_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), i64) */
struct co_object_t co_u16_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), f32) */
struct co_object_t co_u16_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u16,), f64) */
struct co_object_t co_u16_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * i16
 */
/* fn((ffi.c.int16_t,), i16) */
struct co_object_t co_i16_new_from_raw(struct co_ctx_t *ctx, int16_t v);
/* fn((i16,), Any) */
struct co_object_t co_i16_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), str) */
struct co_object_t co_i16_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), int) */
struct co_object_t co_i16_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16, i16), bool) */
struct co_object_t co_i16_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), bool) */
struct co_object_t co_i16_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16,), bool) */
struct co_object_t co_i16_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16,), i16) */
struct co_object_t co_i16_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), i16) */
struct co_object_t co_i16_neg(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), i16) */
struct co_object_t co_i16_pos(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16, i16), i16) */
struct co_object_t co_i16_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i16,), bool) */
struct co_object_t co_i16_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), u8) */
struct co_object_t co_i16_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), i8) */
struct co_object_t co_i16_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), u16) */
struct co_object_t co_i16_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), i16) */
struct co_object_t co_i16_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), u32) */
struct co_object_t co_i16_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), i32) */
struct co_object_t co_i16_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), u64) */
struct co_object_t co_i16_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), i64) */
struct co_object_t co_i16_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), f32) */
struct co_object_t co_i16_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i16,), f64) */
struct co_object_t co_i16_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * u32
 */
/* fn((ffi.c.uint32_t,), u32) */
struct co_object_t co_u32_new_from_raw(struct co_ctx_t *ctx, uint32_t v);
/* fn((u32,), Any) */
struct co_object_t co_u32_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), str) */
struct co_object_t co_u32_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), int) */
struct co_object_t co_u32_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32, u32), bool) */
struct co_object_t co_u32_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), bool) */
struct co_object_t co_u32_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32,), bool) */
struct co_object_t co_u32_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32,), u32) */
struct co_object_t co_u32_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32, u32), u32) */
struct co_object_t co_u32_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u32,), bool) */
struct co_object_t co_u32_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), u8) */
struct co_object_t co_u32_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), i8) */
struct co_object_t co_u32_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), u16) */
struct co_object_t co_u32_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), i16) */
struct co_object_t co_u32_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), u32) */
struct co_object_t co_u32_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), i32) */
struct co_object_t co_u32_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), u64) */
struct co_object_t co_u32_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), i64) */
struct co_object_t co_u32_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), f32) */
struct co_object_t co_u32_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u32,), f64) */
struct co_object_t co_u32_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * i32
 */
/* fn((ffi.c.int32_t,), i32) */
struct co_object_t co_i32_new_from_raw(struct co_ctx_t *ctx, int32_t v);
/* fn((i32,), Any) */
struct co_object_t co_i32_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), str) */
struct co_object_t co_i32_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), int) */
struct co_object_t co_i32_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32, i32), bool) */
struct co_object_t co_i32_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), bool) */
struct co_object_t co_i32_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32,), bool) */
struct co_object_t co_i32_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32,), i32) */
struct co_object_t co_i32_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), i32) */
struct co_object_t co_i32_neg(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), i32) */
struct co_object_t co_i32_pos(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32, i32), i32) */
struct co_object_t co_i32_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i32,), bool) */
struct co_object_t co_i32_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), u8) */
struct co_object_t co_i32_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), i8) */
struct co_object_t co_i32_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), u16) */
struct co_object_t co_i32_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), i16) */
struct co_object_t co_i32_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), u32) */
struct co_object_t co_i32_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), i32) */
struct co_object_t co_i32_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), u64) */
struct co_object_t co_i32_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), i64) */
struct co_object_t co_i32_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), f32) */
struct co_object_t co_i32_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i32,), f64) */
struct co_object_t co_i32_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * u64
 */
/* fn((ffi.c.uint64_t,), u64) */
struct co_object_t co_u64_new_from_raw(struct co_ctx_t *ctx, uint64_t v);
/* fn((u64,), Any) */
struct co_object_t co_u64_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), str) */
struct co_object_t co_u64_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), int) */
struct co_object_t co_u64_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64, u64), bool) */
struct co_object_t co_u64_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), bool) */
struct co_object_t co_u64_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64,), bool) */
struct co_object_t co_u64_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64,), u64) */
struct co_object_t co_u64_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64, u64), u64) */
struct co_object_t co_u64_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((u64,), bool) */
struct co_object_t co_u64_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), u8) */
struct co_object_t co_u64_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), i8) */
struct co_object_t co_u64_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), u16) */
struct co_object_t co_u64_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), i16) */
struct co_object_t co_u64_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), u32) */
struct co_object_t co_u64_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), i32) */
struct co_object_t co_u64_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), u64) */
struct co_object_t co_u64_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), i64) */
struct co_object_t co_u64_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), f32) */
struct co_object_t co_u64_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((u64,), f64) */
struct co_object_t co_u64_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * i64
 */
/* fn((ffi.c.int64_t,), i64) */
struct co_object_t co_i64_new_from_raw(struct co_ctx_t *ctx, int64_t v);
/* fn((i64,), Any) */
struct co_object_t co_i64_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), str) */
struct co_object_t co_i64_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), int) */
struct co_object_t co_i64_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64, i64), bool) */
struct co_object_t co_i64_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), bool) */
struct co_object_t co_i64_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64,), bool) */
struct co_object_t co_i64_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_and(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_or(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_xor(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64,), i64) */
struct co_object_t co_i64_inv(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), i64) */
struct co_object_t co_i64_neg(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), i64) */
struct co_object_t co_i64_pos(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64, i64), i64) */
struct co_object_t co_i64_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((i64,), bool) */
struct co_object_t co_i64_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), u8) */
struct co_object_t co_i64_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), i8) */
struct co_object_t co_i64_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), u16) */
struct co_object_t co_i64_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), i16) */
struct co_object_t co_i64_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), u32) */
struct co_object_t co_i64_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), i32) */
struct co_object_t co_i64_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), u64) */
struct co_object_t co_i64_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), i64) */
struct co_object_t co_i64_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), f32) */
struct co_object_t co_i64_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((i64,), f64) */
struct co_object_t co_i64_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * f32
 */
/* fn((ffi.c.float,), f32) */
struct co_object_t co_f32_new_from_raw(struct co_ctx_t *ctx, float v);
/* fn((f32,), Any) */
struct co_object_t co_f32_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), str) */
struct co_object_t co_f32_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), int) */
struct co_object_t co_f32_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32, f32), bool) */
struct co_object_t co_f32_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32, f32), bool) */
struct co_object_t co_f32_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32,), bool) */
struct co_object_t co_f32_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), f32) */
struct co_object_t co_f32_neg(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), f32) */
struct co_object_t co_f32_pos(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32, f32), f32) */
struct co_object_t co_f32_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32, f32), f32) */
struct co_object_t co_f32_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32, f32), f32) */
struct co_object_t co_f32_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32, f32), f32) */
struct co_object_t co_f32_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32, f32), f32) */
struct co_object_t co_f32_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f32,), bool) */
struct co_object_t co_f32_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), u8) */
struct co_object_t co_f32_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), i8) */
struct co_object_t co_f32_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), u16) */
struct co_object_t co_f32_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), i16) */
struct co_object_t co_f32_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), u32) */
struct co_object_t co_f32_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), i32) */
struct co_object_t co_f32_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), u64) */
struct co_object_t co_f32_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), i64) */
struct co_object_t co_f32_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), f32) */
struct co_object_t co_f32_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f32,), f64) */
struct co_object_t co_f32_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * f64
 */
/* fn((ffi.c.float,), f64) */
struct co_object_t co_f64_new_from_raw(struct co_ctx_t *ctx, float v);
/* fn((f64,), Any) */
struct co_object_t co_f64_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), str) */
struct co_object_t co_f64_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), int) */
struct co_object_t co_f64_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64, f64), bool) */
struct co_object_t co_f64_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64, f64), bool) */
struct co_object_t co_f64_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64,), bool) */
struct co_object_t co_f64_not(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), f64) */
struct co_object_t co_f64_neg(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), f64) */
struct co_object_t co_f64_pos(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64, f64), f64) */
struct co_object_t co_f64_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64, f64), f64) */
struct co_object_t co_f64_sub(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64, f64), f64) */
struct co_object_t co_f64_mul(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64, f64), f64) */
struct co_object_t co_f64_div(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64, f64), f64) */
struct co_object_t co_f64_pow(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((f64,), bool) */
struct co_object_t co_f64_as_bool(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), u8) */
struct co_object_t co_f64_as_u8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), i8) */
struct co_object_t co_f64_as_i8(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), u16) */
struct co_object_t co_f64_as_u16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), i16) */
struct co_object_t co_f64_as_i16(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), u32) */
struct co_object_t co_f64_as_u32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), i32) */
struct co_object_t co_f64_as_i32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), u64) */
struct co_object_t co_f64_as_u64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), i64) */
struct co_object_t co_f64_as_i64(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), f32) */
struct co_object_t co_f64_as_f32(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((f64,), f64) */
struct co_object_t co_f64_as_f64(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * bytes
 */
/* fn((ffi.c.size_t, ffi.c.Pointer(ffi.c.char)), bytes) */
struct co_object_t co_bytes_new_from_raw(struct co_ctx_t *ctx, size_t len, char *value);
/* fn((bytes,), Any) */
struct co_object_t co_bytes_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bytes,), str) */
struct co_object_t co_bytes_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bytes,), int) */
struct co_object_t co_bytes_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((bytes, bytes), bool) */
struct co_object_t co_bytes_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bytes, bytes), bool) */
struct co_object_t co_bytes_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bytes, int), bytes) */
struct co_object_t co_bytes_get(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t index);
/* fn((bytes, int, int), bytes) */
struct co_object_t co_bytes_getslice(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t begin, struct co_object_t end);
/* fn((bytes, bytes), bytes) */
struct co_object_t co_bytes_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bytes, bytes), bool) */
struct co_object_t co_bytes_find(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bytes, bytes), int) */
struct co_object_t co_bytes_index(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((bytes, list[Any]), bytes) */
struct co_object_t co_bytes_format(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t values);
/* fn((bytes,), str) */
struct co_object_t co_bytes_decode(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * str
 */
/* fn((ffi.c.size_t, ffi.c.Pointer(ffi.c.char)), str) */
struct co_object_t co_str_new_from_raw(struct co_ctx_t *ctx, size_t len, char *value);
/* fn((str,), Any) */
struct co_object_t co_str_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((str,), str) */
struct co_object_t co_str_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((str,), int) */
struct co_object_t co_str_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((str, str), bool) */
struct co_object_t co_str_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((str, str), bool) */
struct co_object_t co_str_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((str, int), str) */
struct co_object_t co_str_get(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t index);
/* fn((str, int, int), str) */
struct co_object_t co_str_getslice(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t begin, struct co_object_t end);
/* fn((str, str), str) */
struct co_object_t co_str_add(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((str, str), bool) */
struct co_object_t co_str_find(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((str, str), int) */
struct co_object_t co_str_index(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((str, list[Any]), str) */
struct co_object_t co_str_format(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t values);
/* fn((str,), bytes) */
struct co_object_t co_str_encode(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * tuple
 */
/* fn((...), tuple) */
struct co_object_t co_tuple_new_from_raw(struct co_ctx_t *ctx, struct co_option_t *generics, size_t len, struct co_tuple_entry_t *items, struct co_object_t *args, struct co_object_t *kwargs);
/* fn((type,), tuple) */
struct co_object_t co_tuple_new_from_entries(struct co_ctx_t *ctx, struct co_option_t *cls);
/* fn((tuple,), Any) */
struct co_object_t co_tuple_free(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((tuple,), str) */
struct co_object_t co_tuple_repr(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((tuple,), int) */
struct co_object_t co_tuple_hash(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((tuple, str), bool) */
struct co_object_t co_tuple_eq(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((tuple, str), bool) */
struct co_object_t co_tuple_lt(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t other);
/* fn((tuple, Any), Any) */
struct co_object_t co_tuple_get(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t key_or_index);
/* fn((tuple, Any, Any), tuple) */
struct co_object_t co_tuple_set(struct co_ctx_t *ctx, struct co_object_t self, struct co_object_t key_or_index);
/* fn((tuple,), list[tuple[Any, Any, Any]]) */
struct co_object_t co_tuple_get_entries(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((tuple,), list[Any]]) */
struct co_object_t co_tuple_get_keys(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((tuple,), list[Any]]) */
struct co_object_t co_tuple_get_types(struct co_ctx_t *ctx, struct co_object_t self);
/* fn((tuple,), list[Any]]) */
struct co_object_t co_tuple_get_values(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * struct
 */

/*
 * union
 */

/*
 * list
 */

/*
 * dict
 */

/*
 * code
 */

/*
 * block
 */

/*
 * fn
 */

/*
 * Option
 */

/*
 * Some
 */

/*
 * None
 */

/*
 * Result
 */

/*
 * Ok
 */

/*
 * Err
 */

#endif
