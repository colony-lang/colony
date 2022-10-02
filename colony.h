#ifndef CO_COLONY_H
#define CO_COLONY_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define DEBUG
#define CO_GC_DEBUG 0

#if CO_GC_DEBUG == 1
    #define CO_OBJECT_C_INCREF(ctx, obj) co_object_c_incref(ctx, obj, __FILE__, __LINE__, __FUNCTION__)
    #define CO_OBJECT_C_DECREF(ctx, obj) co_object_c_decref(ctx, obj, __FILE__, __LINE__, __FUNCTION__)

    #define CO_INCREF(ctx, obj) co_object_c_incref(ctx, obj, __FILE__, __LINE__, __FUNCTION__)
    #define CO_DECREF(ctx, obj) co_object_c_decref(ctx, obj, __FILE__, __LINE__, __FUNCTION__)
#else
    #define CO_OBJECT_C_INCREF(ctx, obj) co_object_c_incref(ctx, obj)
    #define CO_OBJECT_C_DECREF(ctx, obj) co_object_c_decref(ctx, obj)
    
    #define CO_INCREF(ctx, obj) co_object_c_incref(ctx, obj)
    #define CO_DECREF(ctx, obj) co_object_c_decref(ctx, obj)
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))

enum co_own_trans_t;    // ownership transfer
struct co_ctx_t;
struct co_frame_t;
enum co_kind_t;
union co_value_t;
struct co_object_t;
struct co_gc_t;
struct co_ctx_t;
struct co_frame_t;
struct co_module_t;
struct co_bytes_t;
struct co_str_t;
struct co_list_t;
struct co_dict_t;
struct co_block_t;
struct co_code_t;
struct co_fn_t;
struct co_struct_t;
struct co_union_t;
struct co_generic_t;
struct co_generic_struct_t;
struct co_generic_union_t;
struct co_generic_type_t;
struct co_generic_fn_t;
struct co_some_t;
struct co_none_t;
struct co_option_t;
struct co_ok_t;
struct co_err_t;
struct co_result_t;

#define CO_GC_T \
    size_t rc;

typedef enum co_own_trans_t {
    CO_OWN_TRANS_NONE,
    CO_OWN_TRANS_COPY,
    CO_OWN_TRANS_MOVE,
} co_own_trans_t;

typedef enum co_kind_t {
    // special kinds
    CO_KIND_UNDEFINED,
    // primitive kinds
    CO_KIND_BOOL,
    CO_KIND_I64,
    CO_KIND_F64,
    // GC kinds
    CO_KIND_GC,
    CO_KIND_CTX,
    CO_KIND_FRAME,
    CO_KIND_MODULE,
    CO_KIND_BYTES,
    CO_KIND_STR,
    CO_KIND_LIST,
    CO_KIND_DICT,
    CO_KIND_BLOCK,
    CO_KIND_CODE,
    CO_KIND_FN,
    CO_KIND_STRUCT,
    CO_KIND_UNION,
    CO_KIND_GENERIC,
    CO_KIND_GENERIC_STRUCT,
    CO_KIND_GENERIC_UNION,
    CO_KIND_GENERIC_TYPE,
    CO_KIND_GENERIC_FN,
    CO_KIND_NONE,
    CO_KIND_SOME,
    CO_KIND_OPTION,
    CO_KIND_OK,
    CO_KIND_ERR,
    CO_KIND_RESULT,
} co_kind_t;

typedef bool co_bool_t;
typedef int64_t co_i64_t;
typedef uint64_t co_u64_t;
typedef double co_f64_t;

// special structure used for hashing of ints and floats
typedef union _co_num_t {
    co_i64_t i64;
    co_u64_t u64;
    co_f64_t f64;
    void *p;
} _co_num_t;

typedef struct co_gc_t {
    CO_GC_T
} co_gc_t;

typedef union co_value_t {
    co_bool_t b;
    co_i64_t i64;
    co_f64_t f64;
    co_gc_t *p;
} co_value_t;

typedef struct co_object_t {
    enum co_kind_t k;
    union co_value_t v;
} co_object_t;

typedef struct co_ctx_t {
    CO_GC_T
    struct co_object_t parent_ctx;
    struct co_object_t current_frame;
} co_ctx_t;

typedef struct co_frame_t {
    CO_GC_T
    struct co_object_t parent_frame;
    struct co_object_t closure; // unsafe mutable struct
} co_frame_t;

typedef struct co_bytes_t {
    CO_GC_T
    co_u64_t len;
    co_own_trans_t ot;
    char *items;
    co_i64_t hash;
} co_bytes_t;

typedef struct co_str_t {
    CO_GC_T
    co_u64_t len;
    co_own_trans_t ot;
    char *items;
    co_i64_t hash;
} co_str_t;

typedef struct co_list_t {
    CO_GC_T
    co_object_t item_type;
    co_u64_t len;
    co_object_t *items;
    co_i64_t hash;
} co_list_t;

/*
 * object
 */
static struct co_object_t CO_OBJECT_UNDEFINED __attribute__ ((unused)) = {
    .k = CO_KIND_UNDEFINED,
    .v = (co_value_t){
        .p = (co_gc_t*)NULL
    }
};

#if CO_GC_DEBUG == 1
    void co_object_c_incref(co_object_t ctx, co_object_t obj, char *filename, int line, const char *funcname);
    void co_object_c_decref(co_object_t ctx, co_object_t obj, char *filename, int line, const char *funcname);
#else
    void co_object_c_incref(co_object_t ctx, co_object_t obj);
    void co_object_c_decref(co_object_t ctx, co_object_t obj);
#endif

co_object_t co_object_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_object_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_object_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_object_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_object_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);

co_object_t co_object_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * bool
 */
co_object_t co_bool_c_new(co_object_t ctx, co_bool_t b);
co_object_t co_bool_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_bool_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_bool_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_bool_c_not(co_object_t ctx, co_object_t obj);
co_object_t co_bool_c_and(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_or(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_le(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_ne(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_ge(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bool_c_gt(co_object_t ctx, co_object_t obj, co_object_t other);

co_object_t co_bool_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * i64
 */
co_object_t co_i64_c_new(co_object_t ctx, co_i64_t i);
co_object_t co_i64_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_i64_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_i64_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_i64_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_le(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_ne(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_ge(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_gt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_add(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_sub(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_mul(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_div(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_mod(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_pow(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_shl(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_shr(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_bitinv(co_object_t ctx, co_object_t obj);
co_object_t co_i64_c_bitand(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_bitor(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_i64_c_bitxor(co_object_t ctx, co_object_t obj, co_object_t other);

co_object_t co_i64_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * f64
 */
co_object_t co_f64_c_new(co_object_t ctx, co_f64_t f64);
co_object_t co_f64_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_f64_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_f64_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_f64_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_le(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_ne(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_ge(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_gt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_add(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_sub(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_mul(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_div(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_f64_c_pow(co_object_t ctx, co_object_t obj, co_object_t other);

co_object_t co_f64_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * ctx
 */
co_object_t co_ctx_c_new_root(void);
co_object_t co_ctx_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_ctx_c_spawn(co_object_t ctx);
co_object_t co_ctx_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_ctx_c_repr(co_object_t ctx, co_object_t obj);

co_object_t co_ctx_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_ctx_spawn(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * frame
 */
co_object_t co_frame_c_new(co_object_t ctx, co_object_t parent_frame);
co_object_t co_frame_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_frame_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_frame_c_hash(co_object_t ctx, co_object_t obj);

co_object_t co_frame_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * module
 */
co_object_t co_module_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_module_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * bytes
 */
co_object_t co_bytes_c_new(co_object_t ctx, co_u64_t len, char *items, co_own_trans_t ot);
co_object_t co_bytes_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_bytes_c_len(co_object_t ctx, co_object_t obj);
co_object_t co_bytes_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_bytes_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_bytes_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bytes_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_bytes_c_add(co_object_t ctx, co_object_t obj, co_object_t other);

co_object_t co_bytes_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * str
 */
co_object_t co_str_c_new(co_object_t ctx, co_u64_t len, char *items, co_own_trans_t ot);
co_object_t co_str_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_str_c_len(co_object_t ctx, co_object_t obj);
co_object_t co_str_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_str_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_str_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_str_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_str_c_add(co_object_t ctx, co_object_t obj, co_object_t other);

co_object_t co_str_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * list
 */
co_object_t co_list_c_new(co_object_t ctx, co_u64_t len, co_object_t *items);
co_object_t co_list_c_free(co_object_t ctx, co_object_t obj);
co_object_t co_list_c_len(co_object_t ctx, co_object_t obj);
co_object_t co_list_c_lt(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_list_c_eq(co_object_t ctx, co_object_t obj, co_object_t other);
co_object_t co_list_c_hash(co_object_t ctx, co_object_t obj);
co_object_t co_list_c_repr(co_object_t ctx, co_object_t obj);
co_object_t co_list_c_get(co_object_t ctx, co_object_t obj, co_object_t index);
co_object_t co_list_c_set(co_object_t ctx, co_object_t obj, co_object_t index, co_object_t value);
co_object_t co_list_c_del(co_object_t ctx, co_object_t obj, co_object_t index);
co_object_t co_list_c_append(co_object_t ctx, co_object_t obj, co_object_t value);
co_object_t co_list_c_prepend(co_object_t ctx, co_object_t obj, co_object_t value);
co_object_t co_list_c_insert(co_object_t ctx, co_object_t obj, co_object_t index, co_object_t value);
co_object_t co_list_c_remove(co_object_t ctx, co_object_t obj, co_object_t value, co_object_t n);
co_object_t co_list_c_replace(co_object_t ctx, co_object_t obj, co_object_t value, co_object_t other, co_object_t n);

co_object_t co_list_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * dict
 */
co_object_t co_dict_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_dict_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * block
 */
co_object_t co_block_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_block_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * code
 */
co_object_t co_code_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_code_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * fn
 */
co_object_t co_fn_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_fn_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * struct
 */
co_object_t co_struct_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_struct_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * union
 */
co_object_t co_union_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_union_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * generic
 */
co_object_t co_generic_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_generic_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * generic struct
 */
co_object_t co_generic_struct_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_generic_struct_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * generic union
 */
co_object_t co_generic_union_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_generic_union_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * generic type
 */
co_object_t co_generic_type_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_generic_type_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * generic fn
 */
co_object_t co_generic_fn_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_generic_fn_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * None
 */
co_object_t co_none_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_none_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * Some
 */
co_object_t co_some_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_some_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * Option
 */
co_object_t co_option_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_option_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * Ok
 */
co_object_t co_ok_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_ok_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * Err
 */
co_object_t co_err_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_err_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * Result
 */
co_object_t co_result_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_result_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * c builtins
 */
co_i64_t co_c_cstr_hash(co_object_t ctx, size_t len, char *items);
co_i64_t co_c_clistitems_hash(co_object_t ctx, size_t len, co_object_t *items);
char *co_c_create_len_str_format(co_object_t ctx, size_t len);
co_object_t co_print_c(co_object_t ctx, co_object_t obj);

#endif
