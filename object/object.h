#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define CO_GC_HEAD size_t rc

enum co_type_t;

struct co_gc_t;

struct co_gc_ptr_t;

struct co_struct_field_t;
struct co_struct_t;
struct co_generic_struct_field_t;
struct co_generic_struct_t;
struct co_param_struct_t;
struct co_union_t;
struct co_param_union_t;
struct co_code_t;
struct co_fn_t;
struct co_param_fn_t;

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

union co_value_t;
struct co_object_t;

#include "../core/ctx.h"

typedef enum co_type_t {
    // special cases, implementation dependent
    CO_TYPE_UNDEFINED = 0,

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
    CO_TYPE_PTR = 12,

    // GC'ed types
    CO_TYPE_GC_PTR = 20,

    CO_TYPE_STRUCT = 30,
    CO_TYPE_GENERIC_STRUCT = 31,
    CO_TYPE_PARAM_STRUCT = 32,
    CO_TYPE_UNION = 33,
    CO_TYPE_PARAM_UNION = 34,
    
    CO_TYPE_MODULE = 40,
    CO_TYPE_CODE = 41,
    CO_TYPE_FN = 42,
    CO_TYPE_FN_DECL = 43,
    CO_TYPE_PARAM_FN = 44,
    CO_TYPE_PARAM_FN_DECL = 45,

    CO_TYPE_BYTES = 50,
    CO_TYPE_STR = 51,
    CO_TYPE_LIST = 52,
    CO_TYPE_DICT = 53,
    
    CO_TYPE_RESULT = 60,
    CO_TYPE_OK = 61,
    CO_TYPE_ERR = 62,
    CO_TYPE_OPTION = 63,
    CO_TYPE_SOME = 64,
    CO_TYPE_NONE = 65
} co_type_t;

typedef struct co_gc_t {
    CO_GC_HEAD;
} co_gc_t;

typedef struct co_gc_ptr_t {
    CO_GC_HEAD;
    // TODO:
} co_gc_ptr_t;

typedef struct co_struct_field_t {
    struct co_object_t *name;               // str
    struct co_object_t *type;               // type
    struct co_object_t *default_value;      // object
} co_struct_field_t;

typedef struct co_struct_t {
    CO_GC_HEAD;
    size_t len;
    struct co_struct_field_t *fields;
} co_struct_t;

typedef struct co_generic_struct_field_t {
    struct co_object_t *name;               // str
    struct co_object_t *type;               // type
    struct co_object_t *default_value;      // type
} co_generic_struct_field_t;

typedef struct co_generic_struct_t {
    CO_GC_HEAD;
    size_t len;
    struct co_generic_struct_field_t *fields;
} co_generic_struct_t;

typedef struct co_param_struct_t {
    CO_GC_HEAD;
    // TODO:
} co_param_struct_t;

typedef struct co_union_t {
    CO_GC_HEAD;
    struct co_object_t *types;  // list
} co_union_t;

typedef struct co_param_union_t {
    CO_GC_HEAD;
    struct co_object_t *items;  // list<type>
} co_param_union_t;

typedef struct co_module_t {
    CO_GC_HEAD;
    struct co_object_t *path;   // str
    struct co_object_t *name;   // str
    struct co_object_t *vars;   // list<struct(a: str, t: type, v: object)>
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
    size_t len;
    struct co_object_t *item_type;
    struct co_object_t *items;
} co_list_t;

typedef struct co_dict_entry_t {
    struct co_object_t *key;
    struct co_object_t *value;
} co_dict_entry_t;

typedef struct co_dict_t {
    CO_GC_HEAD;
    size_t fill;
    size_t used;
    size_t mask;
    struct co_object_t *key_type;
    struct co_object_t *value_type;
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
    void *ptr;

    // GC'ed types
    struct co_struct_t *struct_;
    // struct co_struct_instance_t *struct_instance;
    struct co_generic_struct_t *generic_struct;
    // struct co_generic_struct_instance_t *generic_struct_instance;
    struct co_param_struct_t *param_struct;
    // struct co_param_struct_instance_t *param_struct_instance;
    struct co_union_t *union_;
    struct co_param_union_t *param_union;
    
    struct co_module_t *module;
    struct co_code_t *code;
    struct co_fn_t *fn;
    struct co_fn_decl_t *fn_decl;
    struct co_param_fn_t *param_fn;
    struct co_param_fn_decl_t *param_fn_decl;

    struct co_bytes_t *bytes;
    struct co_str_t *str;
    struct co_list_t *list;
    struct co_dict_t *dict;

    struct co_result_t *result;
    struct co_ok_t *ok;
    struct co_err_t *err;
    struct co_option_t *option;
    struct co_some_t *some;
    struct co_none_t *none;

    struct co_gc_ptr_t *gc_ptr;
} co_value_t;

typedef struct co_object_t {
    enum co_type_t t;
    union co_value_t v;
} co_object_t;

#endif
