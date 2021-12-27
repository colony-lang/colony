#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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
struct co_code_t;
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
    CO_TYPE_BYTES,
    CO_TYPE_STR,
    CO_TYPE_STRUCT,
    CO_TYPE_UNION,
    CO_TYPE_LIST,
    CO_TYPE_DICT,
    CO_TYPE_TUPLE,
    CO_TYPE_CODE,
    CO_TYPE_FN,
    CO_TYPE_OPTION,
    CO_TYPE_SOME,
    CO_TYPE_NONE,
    CO_TYPE_RESULT,
    CO_TYPE_OK,
    CO_TYPE_ERR,
    CO_TYPE_TYPE,
} co_type_t;

typedef struct co_gc_t {
    size_t rc;
} co_gc_t;

typedef struct co_bytes_t {
    size_t rc;
    size_t len;
    char *items;
} co_bytes_t;

typedef struct co_str_t {
    size_t rc;
    size_t len;
    char *items;
} co_str_t;

typedef struct co_struct_t {
    size_t rc;
    struct co_option_t *generics; // tuple
    struct co_option_t *fields; // tuple
} co_struct_t;

typedef struct co_union_t {
    size_t rc;
    struct co_option_t *generics; // tuple
    struct co_option_t *types; // tuple
} co_union_t;

typedef struct co_list_t {
    size_t rc;
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
    size_t rc;
    size_t fill;
    size_t used;
    size_t mask;
    struct co_option_t *key_type;       // type
    struct co_option_t *value_type;     // type
    struct co_dict_entry_t *entries;
} co_dict_t;

typedef struct co_tuple_entry_t {
    size_t index;
    struct co_object_t *name;
    struct co_object_t *type;
    struct co_object_t *value;
} co_tuple_entry_t;

typedef struct co_tuple_t {
    // NOTE: can be optimized to know if tuple representing generic, args, params
    size_t rc;
    struct co_option_t *generics; // tuple
    size_t len;
    struct co_tuple_entry_t *items;
    struct co_object_t *args;
    struct co_object_t *kwargs;
} co_tuple_t;

typedef struct co_code_t {
    size_t rc;
    size_t len;
    char *items;
} co_code_t;

typedef struct co_fn_t {
    // NOTE: function can be defined with generics, and specialized with types for given generics
    size_t rc;
    struct co_object_t *params;     // tuple that can hold generics
    struct co_object_t *ret;
    struct co_code_t *code;
} co_fn_t;

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
    struct co_list_t *list;
    struct co_dict_t *dict;
    struct co_tuple_t *tuple;
    struct co_code_t *code;
    struct co_fn_t *fn;
    struct co_option_t *option;
    struct co_some_t *some;
    struct co_none_t *none;
    struct co_result_t *result;
    struct co_ok_t *ok;
    struct co_err_t *err;
    struct co_object_t *type;
} co_value_t;

typedef struct co_object_t {
    enum co_type_t t;
    union co_value_t v;
} co_object_t;

/*
 * object
 */
size_t co_object_incref(struct co_ctx_t *ctx, struct co_object_t *self);
size_t co_object_decref(struct co_ctx_t *ctx, struct co_object_t *self);

#endif