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

#define CO_GC_T \
    size_t rc;

typedef struct co_ctx_t {

    struct co_ctx_t *parent_ctx;
    struct co_frame_t *root_frame;
    struct co_frame_t *current_frame;
} co_ctx_t;

typedef struct co_frame_t {
    struct co_frame_t *parent;
    void *closure; // struct co_object_t * / unsafe mutable struct
} co_frame_t;

typedef enum co_kind_t {
    // special kinds
    CO_KIND_UNDEFINED,
    // primitive kinds
    CO_KIND_BOOL,
    CO_KIND_INT,
    CO_KIND_FLOAT,
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

co_object_t co_ctx_new(co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_ctx_free(co_object_t obj, co_object_t args, co_object_t kwargs);
co_object_t co_ctx_spawn(co_object_t ctx, co_object_t args, co_object_t kwargs);

#endif
