#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

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
    // primitive values
    CO_TYPE_BOOL,
    CO_TYPE_I8,
    CO_TYPE_U8,
    CO_TYPE_I16,
    CO_TYPE_U16,
    CO_TYPE_I32,
    CO_TYPE_U32,
    CO_TYPE_I64,
    CO_TYPE_U64,
    CO_TYPE_F32,
    CO_TYPE_F64,

    // GC'ed values
    CO_TYPE_BYTES,
    CO_TYPE_STR,
    CO_TYPE_TUPLE,
    CO_TYPE_STRUCT,
    CO_TYPE_UNION,
    CO_TYPE_LIST,
    CO_TYPE_DICT,
    CO_TYPE_CODE,
    CO_TYPE_BLOCK,
    CO_TYPE_FN,
    CO_TYPE_OPTION,
    CO_TYPE_SOME,
    CO_TYPE_NONE,
    CO_TYPE_RESULT,
    CO_TYPE_OK,
    CO_TYPE_ERR,
    CO_TYPE_STATIC_TYPE,
    CO_TYPE_DYNAMIC_TYPE,
} co_type_t;

#define CO_GC_HEAD ssize_t rc

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
    struct co_object_t *name;
    struct co_object_t *type;
    struct co_object_t *value;
} co_tuple_entry_t;

typedef struct co_tuple_t {
    // NOTE: can be optimized to know if tuple representing generic, args, params
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
    size_t len;
    struct co_tuple_entry_t *items;
    struct co_object_t *args;
    struct co_object_t *kwargs;
} co_tuple_t;

typedef struct co_struct_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
    struct co_option_t *fields; // tuple
} co_struct_t;

typedef struct co_union_t {
    CO_GC_HEAD;
    struct co_option_t *generics; // tuple
    struct co_option_t *types; // tuple
} co_union_t;

typedef struct co_list_t {
    CO_GC_HEAD;
    size_t cap;
    size_t len;
    struct co_option_t *item_type; // type
    struct co_option_t *items;
} co_list_t;

typedef struct co_dict_entry_t {
    ssize_t hash;
    struct co_object_t *key;
    struct co_object_t *value;
} co_dict_entry_t;

typedef struct co_dict_t {
    CO_GC_HEAD;
    size_t fill;
    size_t used;
    size_t mask;
    struct co_option_t *key_type;       // type
    struct co_option_t *value_type;     // type
    struct co_dict_entry_t *entries;
} co_dict_t;

typedef struct co_code_t {
    CO_GC_HEAD;
    size_t len;
    char *items;
} co_code_t;

typedef struct co_block_t {
    struct co_object_t *ret_type;   // type
    struct co_object_t *code;       // code
} co_block_t;

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

typedef struct co_fn_t {
    // NOTE: function can be defined with generics, and specialized with types for given generics
    size_t rc;
    enum co_fn_args_type_t args_type;
    struct co_object_t *params;     // tuple that can hold generics
    struct co_object_t *ret;
    struct co_code_t *code;
} co_fn_t;

typedef struct co_result_t {
    size_t rc;
    struct co_option_t *generics; // tuple
} co_result_t;

typedef struct co_ok_t {
    size_t rc;
    struct co_option_t *generics; // tuple
    struct co_option_t *v;
} co_ok_t;

typedef struct co_err_t {
    size_t rc;
    struct co_option_t *generics; // tuple
    struct co_option_t *e;
} co_err_t;

typedef struct co_option_t {
    size_t rc;
    struct co_option_t *generics; // tuple
} co_option_t;

typedef struct co_some_t {
    size_t rc;
    struct co_option_t *generics; // tuple
    struct co_option_t *v;
} co_some_t;

typedef struct co_none_t {
    size_t rc;
    struct co_option_t *generics; // tuple
} co_none_t;

typedef union co_value_t {
    _Bool b;
    int8_t i8;
    uint8_t u8;
    int16_t i16;
    uint16_t u16;
    int32_t i32;
    uint32_t u32;
    int64_t i64;
    uint64_t u64;
    float f32;
    double f64;
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
    struct co_object_t *static_type;
    struct co_object_t *dynamic_type;
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
struct co_object_t co_object_new_from_c_type_c_value(struct co_ctx_t *ctx, enum co_type_t t, union co_value_t v);
struct co_object_t co_object_free(struct co_ctx_t *ctx, struct co_object_t self);

/*
 * bytes
 */
/* fn((ffi.c.size_t, ffi.c.Pointer(ffi.c.char)), bytes) */
struct co_object_t co_bytes_new_from_c_len_c_char(struct co_ctx_t *ctx, size_t len, char *value);
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
struct co_object_t co_str_new_from_c_len_c_char(struct co_ctx_t *ctx, size_t len, char *value);
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

/*
 * Result
 */

/*
 * Ok
 */

/*
 * Err
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
 * bool
 */
/* fn((ffi.c._Bool,), bool) */
struct co_object_t co_bool_new_from_c_bool(struct co_ctx_t *ctx, _Bool b);
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

/*
 * u8
 */
/* fn((ffi.c.uint8_t,), u8) */
struct co_object_t co_u8_new_from_c_u8(struct co_ctx_t *ctx, uint8_t v);
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

/*
 * i8
 */
/* fn((ffi.c.int8_t,), i8) */
struct co_object_t co_i8_new_from_c_i8(struct co_ctx_t *ctx, int8_t v);
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

/*
 * u16
 */
/* fn((ffi.c.uint16_t,), u16) */
struct co_object_t co_u16_new_from_c_u16(struct co_ctx_t *ctx, uint16_t v);
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

/*
 * i16
 */
/* fn((ffi.c.int16_t,), i16) */
struct co_object_t co_i16_new_from_c_i16(struct co_ctx_t *ctx, int16_t v);
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

/*
 * u32
 */

/*
 * i32
 */

/*
 * u64
 */

/*
 * i64
 */

/*
 * f32
 */

/*
 * f64
 */

#endif

