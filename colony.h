#ifndef CO_COLONY_H
#define CO_COLONY_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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

#define CO_GC_DEBUG 0

#define CO_GC_T \
    size_t rc;

typedef enum co_kind_t {
    // special kinds
    CO_KIND_UNDEFINED = 0,
    // primitive kinds
    CO_KIND_BOOL = 1,
    CO_KIND_INT = 2,
    CO_KIND_FLOAT = 3,
    // GC kinds
    CO_KIND_GC = 4,
    CO_KIND_CTX = 5,
    CO_KIND_FRAME = 6,
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

typedef _Bool co_bool_t;
typedef int64_t co_int_t;
typedef double co_float_t;

typedef struct co_gc_t {
    CO_GC_T
} co_gc_t;

typedef union co_value_t {
    co_bool_t b;
    co_int_t i;
    co_float_t f;
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

/*
 * object
 */
static struct co_object_t CO_OBJECT_UNDEFINED = (co_object_t){
    .k = CO_KIND_UNDEFINED,
    .v = (co_value_t){
        .p = (co_gc_t*)NULL
    }
};

void co_object_c_incref(co_object_t ctx, co_object_t obj);
void co_object_c_decref(co_object_t ctx, co_object_t obj);

co_object_t co_object_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * bool
 */
co_object_t co_bool_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_bool_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * int
 */
co_object_t co_int_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_int_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * float
 */
co_object_t co_float_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_float_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * ctx
 */
co_object_t co_ctx_c_new_root(void);

co_object_t co_ctx_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_ctx_spawn(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * frame
 */
co_object_t co_frame_c_new(co_object_t ctx, co_object_t parent_frame);

co_object_t co_frame_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * module
 */
co_object_t co_module_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_module_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * bytes
 */
co_object_t co_bytes_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_bytes_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * str
 */
co_object_t co_str_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_str_free(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);

/*
 * list
 */
co_object_t co_list_new(co_object_t ctx, co_object_t obj, co_object_t args, co_object_t kwargs);
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

#endif
