#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define CO_GC_HEAD size_t rc

#define CO_STRUCT_FIELDS_END (co_struct_field_t){ \
    .name = {.k = CO_KIND_UNDEFINED, .v = (co_value_t){.ptr = NULL}}, \
    .type = {.k = CO_KIND_UNDEFINED, .v = (co_value_t){.ptr = NULL}}, \
    .default_value = {.k = CO_KIND_UNDEFINED, .v = (co_value_t){.ptr = NULL}} \
}

// #define CO_STRUCT_FIELDS_DEF(name, kind, default_value) (co_struct_field_t){
//     .name = {.k = CO_KIND_UNDEFINED, .v = (co_value_t){.ptr = NULL}},
// }

#define CO_INCREF(ctx, obj) co_object_incref_c(ctx, obj)
#define CO_DECREF(ctx, obj) co_object_decref_c(ctx, obj)
#define CO_RSTREF(ctx, obj) co_object_rstref_c(ctx, obj)
#define CO_CLRREF(ctx, obj) co_object_clrref_c(ctx, obj)

typedef enum co_kind_t {
    // special cases, implementation dependent
    CO_KIND_UNDEFINED = 0,

    // primitive types
    CO_KIND_BOOL = 1,
    CO_KIND_U8 = 2,
    CO_KIND_I8 = 3,
    CO_KIND_U16 = 4,
    CO_KIND_I16 = 5,
    CO_KIND_U32 = 6,
    CO_KIND_I32 = 7,
    CO_KIND_U64 = 8,
    CO_KIND_I64 = 9,
    CO_KIND_F32 = 10,
    CO_KIND_F64 = 11,
    CO_KIND_PTR = 12,

    // GC'ed types
    CO_KIND_GC_PTR = 20,

    CO_KIND_TYPE = 30,
    CO_KIND_STRUCT = 31,
    CO_KIND_STRUCT_INSTANCE = 32,
    CO_KIND_GENERIC_STRUCT = 33,
    CO_KIND_GENERIC_STRUCT_INSTANCE = 34,
    CO_KIND_PARAM_STRUCT = 35,
    CO_KIND_PARAM_STRUCT_INSTANCE = 36,
    CO_KIND_UNION = 37,
    CO_KIND_PARAM_UNION = 38,
    
    CO_KIND_MODULE = 40,
    CO_KIND_CODE = 41,
    CO_KIND_FN = 42,
    CO_KIND_FN_DECL = 43,
    CO_KIND_PARAM_FN = 44,
    CO_KIND_PARAM_FN_DECL = 45,

    CO_KIND_BYTES = 50,
    CO_KIND_STR = 51,
    CO_KIND_LIST = 52,
    CO_KIND_DICT = 53,
    
    CO_KIND_RESULT = 60,
    CO_KIND_OK = 61,
    CO_KIND_ERR = 62,
    CO_KIND_OPTION = 63,
    CO_KIND_SOME = 64,
    CO_KIND_NONE = 65
} co_kind_t;

typedef union co_value_t {
    // primitive types
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
    
    /*
    gc_ptr

    type
    struct_
    struct_instance
    generic_struct
    generic_struct_instance
    param_struct
    param_struct_instance
    union_
    param_union
    
    module
    code
    fn
    fn_decl
    param_fn
    param_fn_decl
    
    bytes
    str
    list
    dict

    result
    ok
    err
    
    option
    some
    none
    */
    void *ptr;
} co_value_t;

typedef struct co_object_t {
    enum co_kind_t k;
    union co_value_t v;
} co_object_t;

typedef struct co_gc_t {
    CO_GC_HEAD;
} co_gc_t;

struct co_gc_ptr_t;

struct co_type_t;
struct co_struct_field_t;
struct co_struct_t;
struct co_struct_instance_t;
struct co_generic_struct_field_t;
struct co_generic_struct_t;
struct co_generic_struct_instance_t;
struct co_param_struct_t;
struct co_param_struct_instance_t;
struct co_union_t;
struct co_param_union_t;

struct co_module_t;
struct co_code_t;
struct co_fn_t;
struct co_param_fn_t;
struct co_param_fn_decl_t;

struct co_bytes_t;
struct co_str_t;
struct co_list_t;
struct co_dict_entry_t;
struct co_dict_t;

struct co_result_t;
struct co_ok_t;
struct co_err_t;
struct co_option_t;
struct co_some_t;
struct co_none_t;

#include "../core/ctx.h"

typedef struct co_gc_ptr_t {
    CO_GC_HEAD;
    void *ptr;
    int(*free_cb)(struct co_ctx_t *ctx, struct co_object_t self);
} co_gc_ptr_t;

typedef struct co_type_t {
    CO_GC_HEAD;
    struct co_object_t type;                // type
} co_type_t;

typedef struct co_struct_field_t {
    struct co_object_t name;               // str
    struct co_object_t type;               // type
    struct co_object_t default_value;      // object
} co_struct_field_t;

typedef struct co_struct_t {
    CO_GC_HEAD;
    size_t cap;
    size_t len;
    struct co_struct_field_t *fields;
} co_struct_t;

typedef struct co_struct_instance_t {
    CO_GC_HEAD;
    // TODO:
} co_struct_instance_t;

typedef struct co_generic_struct_field_t {
    struct co_object_t name;               // str
    struct co_object_t type;               // type
    struct co_object_t default_value;      // type
} co_generic_struct_field_t;

typedef struct co_generic_struct_t {
    CO_GC_HEAD;
    size_t cap;
    size_t len;
    struct co_generic_struct_field_t *fields;
} co_generic_struct_t;

typedef struct co_generic_struct_instance_t {
    CO_GC_HEAD;
    // TODO:
} co_generic_struct_instance_t;

typedef struct co_param_struct_t {
    CO_GC_HEAD;
    // TODO:
} co_param_struct_t;

typedef struct co_param_struct_instance_t {
    CO_GC_HEAD;
    // TODO:
} co_param_struct_instance_t;

typedef struct co_union_t {
    CO_GC_HEAD;
    struct co_object_t types;  // list
} co_union_t;

typedef struct co_param_union_t {
    CO_GC_HEAD;
    struct co_object_t items;  // list<type>
} co_param_union_t;

typedef struct co_module_t {
    CO_GC_HEAD;
    struct co_object_t path;   // str
    struct co_object_t name;   // str
    struct co_object_t vars;   // list<struct(a: str, t: type, v: object)>
} co_module_t;

typedef struct co_code_t {
    CO_GC_HEAD;
    // TODO:
} co_code_t;

typedef struct co_fn_t {
    CO_GC_HEAD;
    // TODO:
} co_fn_t;

typedef struct co_fn_decl_t {
    CO_GC_HEAD;
    // TODO:
} co_fn_decl_t;

typedef struct co_param_fn_t {
    CO_GC_HEAD;
    // TODO:
} co_param_fn_t;

typedef struct co_param_fn_decl_t {
    CO_GC_HEAD;
    // TODO:
} co_param_fn_decl_t;

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

typedef struct co_list_t {
    CO_GC_HEAD;
    size_t cap;
    size_t len;
    struct co_object_t item_type;
    struct co_object_t items;
} co_list_t;

typedef struct co_dict_entry_t {
    struct co_object_t key;
    struct co_object_t value;
} co_dict_entry_t;

typedef struct co_dict_t {
    CO_GC_HEAD;
    size_t fill;
    size_t used;
    size_t mask;
    struct co_object_t key_type;
    struct co_object_t value_type;
    struct co_dict_entry_t *entries;
} co_dict_t;

typedef struct co_result_t {
    CO_GC_HEAD;
    // TODO:
} co_result_t;

typedef struct co_ok_t {
    CO_GC_HEAD;
    // TODO:
} co_ok_t;

typedef struct co_err_t {
    CO_GC_HEAD;
    // TODO:
} co_err_t;

typedef struct co_option_t {
    CO_GC_HEAD;
    // TODO:
} co_option_t;

typedef struct co_some_t {
    CO_GC_HEAD;
    // TODO:
} co_some_t;

typedef struct co_none_t {
    CO_GC_HEAD;
    // TODO:
} co_none_t;

struct co_object_t co_object_new_c(struct co_ctx_t *ctx, enum co_kind_t k, union co_value_t v);
struct co_object_t co_object_new_c_ptr(struct co_ctx_t *ctx, enum co_kind_t k, void *ptr);
int co_object_free_c(struct co_ctx_t *ctx, struct co_object_t self);
void co_object_incref_c(struct co_ctx_t *ctx, struct co_object_t self);
void co_object_decref_c(struct co_ctx_t *ctx, struct co_object_t self);
void co_object_rstref_c(struct co_ctx_t *ctx, struct co_object_t self);
void co_object_clrref_c(struct co_ctx_t *ctx, struct co_object_t self);

#endif
