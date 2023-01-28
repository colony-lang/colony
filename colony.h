#ifndef CO_COLONY_H
#define CO_COLONY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct co_obj_t;
struct co_dict_entry_t;

typedef enum co_kind_t {
    CO_KIND_UNDEFINED,
    CO_KIND_BOOL,
    CO_KIND_U8,
    CO_KIND_U64,
    CO_KIND_I64,
    CO_KIND_F64,
    CO_KIND_GC,         // meta kind, everything below is GC'ed
    CO_KIND_BYTES,
    CO_KIND_STR,
    CO_KIND_ARRAY,
    CO_KIND_DICT,
    CO_KIND_CODE,
    CO_KIND_FN,
    CO_KIND_FRAME,
    CO_KIND_STRUCT,
    CO_KIND_UNION,
    CO_KIND_MODULE,
    CO_KIND_PTR,
    CO_KIND_CTX
} co_kind_t;

#define CO_GC_RC \
    co_u64_t rc

typedef bool co_bool_t;
typedef uint8_t co_u8_t;
typedef uint64_t co_u64_t;
typedef int64_t co_i64_t;
typedef double co_f64_t;

typedef struct co_gc_t {
    CO_GC_RC;
} co_gc_t;

typedef struct co_bytes_t {
    CO_GC_RC;
    co_i64_t hash;
    size_t len;
    char *items;
} co_bytes_t;

typedef struct co_str_t {
    CO_GC_RC;
    co_i64_t hash;
    size_t len;
    char *items;
} co_str_t;

typedef struct co_array_t {
    CO_GC_RC;
    size_t len;
    struct co_obj_t *items;
} co_array_t;

typedef struct co_dict_t {
    CO_GC_RC;
    size_t fill;        // used + number of entries with a dummy key
    size_t used;        // the number of entires used in the table
    size_t mask;        // length of table - 1. used to fetch values.
    struct co_dict_entry_t *items;
} co_dict_t;

typedef struct co_inst_t {
    size_t op;
    void *dummy; // TODO: unions, specialized instructions
} co_inst_t;

typedef struct co_code_t {
    CO_GC_RC;
    size_t insts_len;
    struct co_inst_t *insts;
} co_type_t;

typedef struct co_ctx_t {
    CO_GC_RC;
    struct co_ctx_t *parent_ctx;
} co_ctx_t;

typedef union co_value_t {
    co_bool_t b;
    co_u8_t u8;
    co_u64_t u64;
    co_i64_t i64;
    co_f64_t f64;
    struct co_bytes_t bytes;
    struct co_str_t str;
} co_value_t;

// obj
typedef struct co_obj_t {
    enum co_kind_t k;
    union co_value_t v;
} co_obj_t;

// dict
typedef struct co_dict_entry_t {
    struct co_obj_t k;  // key
    struct co_obj_t v;  // value
} co_dict_entry_t;

#endif

