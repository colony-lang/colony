#ifndef CO_COLONY_H
#define CO_COLONY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <uchar.h>

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

#define BITMASK_SET(x, mask) ((x) |= (mask))
#define BITMASK_CLEAR(x, mask) ((x) &= (~(mask)))
#define BITMASK_FLIP(x, mask) ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x, mask) (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x, mask) ((x) & (mask))

enum co_kind_t;
union co_value_t;
struct co_obj_t;

struct co_generic_entry_t;
struct co_dict_entry_t;
struct co_struct_entry_t;

#define CO_KIND_UNDEFINED 0
#define CO_KIND_BOOL 1
#define CO_KIND_U8 2
#define CO_KIND_U64 3
#define CO_KIND_I64 4
#define CO_KIND_F64 5
// meta kind, everything below is GC'ed
#define CO_KIND_GC 6
// utf8
#define CO_KIND_STR 7
#define CO_KIND_GENERIC 8
#define CO_KIND_ARRAY 9
#define CO_KIND_DICT 10
#define CO_KIND_STRUCT 11
#define CO_KIND_UNION 12
#define CO_KIND_CODE 13
#define CO_KIND_FN 14
#define CO_KIND_MODULE 15
#define CO_KIND_CTX 16
#define CO_KIND_PTR 17

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

typedef struct co_str_t {
    CO_GC_RC;
    co_i64_t hash;
    size_t len;
    char8_t *items;
} co_str_t;

typedef struct co_generic_t {
    CO_GC_RC;
    struct co_obj_t *type;
    size_t items_len;
    struct co_generic_entry_t *items;
} co_generic_t;

typedef struct co_array_t {
    CO_GC_RC;
    struct co_obj_t *item_type;
    size_t len;
    size_t cap;
    struct co_obj_t *items;
} co_array_t;

/*
A := <T: type=type> -> Array.__type__.__generic_get_item__(Array, [T])
A := <T: type=type> -> Array<T>
a := A<f64>([1.0, 2.0, 3.0])
a := <f64>[1.0, 2.0, 3.0]

D := <K:=type, V:=type> -> Dict.__type__.__generic_get_item__(Dict, [K, V])
D := <K:=type, V:=type> -> Dict<K, V>
d := D<str, i64>({'x': 1, 'y': 2})
d := <str, i64>{'x': 1; 'y': 2}
*/

typedef struct co_dict_t {
    CO_GC_RC;
    struct co_obj_t *key_type;
    struct co_obj_t *value_type;
    size_t fill;        // used + number of entries with a dummy key
    size_t used;        // the number of entires used in the table
    size_t mask;        // length of table - 1. used to fetch values.
    struct co_dict_entry_t *items;
} co_dict_t;

typedef struct co_struct_t {
    CO_GC_RC;
    struct co_obj_t *generic_type;      // Option<generic>
    struct co_obj_t *type;              // type
    size_t items_len;
    struct co_struct_entry_t *items;
} co_struct_t;

typedef struct co_union_t {
    CO_GC_RC;
    struct co_obj_t *generic_type;      // Option<generic>
    struct co_obj_t *items;             // Array<type>
} co_union_t;

/*
A := i64 | f64

A := <X: type=i64 | f64, Y: type=i64 | f64> -> (x: X, y: Y)

G := <X: type=i64 | f64, Y: type=i64 | f64>
R := (x: G.X, y: G.Y)
A := G -> R

a := A<i64, f64>(1, 2.0)

B := <X: type=i64 | f64. Y: type=i64 | f64> -> (array<X> | dict<X, Y>)

F := <X: type=i64 | f64. Y: type=i64 | f64, Z: type=i64 | f64> -> (x: X, y: Y) -> Z {
    z: Z = x + y
    z
}

r: f64 = F<f64, f64, f64>(1.0, 2.0)
*/

typedef struct co_inst_t {
    size_t op;
    void *dummy; // TODO: unions, specialized instructions
} co_inst_t;

typedef struct co_code_t {
    CO_GC_RC;
    size_t insts_len;
    struct co_inst_t *insts;
    // TODO: consts
} co_type_t;

typedef struct co_fn_t {
    CO_GC_RC;
    struct co_obj_t *name;      // Option<str>
    struct co_obj_t *in_type;   // type
    struct co_obj_t *out_type;  // type
    struct co_obj_t *code;      // code
} co_fn_t;

typedef struct co_module_t {
    CO_GC_RC;
    struct co_obj_t *name;      // str
    struct co_obj_t *path;      // str
    struct co_obj_t *code;      // code
    struct co_obj_t *attrs;     // struct-like object holding attributes after code is executed
} co_module_t;

typedef struct co_ctx_t {
    CO_GC_RC;
    struct co_obj_t *parent_ctx;        // Option<ctx>
    struct co_obj_t *fn;                // Option<fn>
    struct co_obj_t *module;            // Option<module>
    struct co_obj_t *code;              // code
    struct co_obj_t *regs;              // array<object>
} co_ctx_t;

typedef struct co_ptr_t {
    void *p;
    struct co_obj_t (*_co_ptr_free_cb)(struct co_obj_t ctx, struct co_obj_t ptr);  // TODO: can be NULL, but work on def
} co_ptr_t;

// value
typedef union co_value_t {
    co_bool_t b;
    co_u8_t u8;
    co_u64_t u64;
    co_i64_t i64;
    co_f64_t f64;
    struct co_str_t *str;
    struct co_generic_t *generic;
    struct co_array_t *array;
    struct co_dict_t *dict;
    struct co_struct_t *struct_;
    struct co_union_t *union_;
    struct co_code_t *code;
    struct co_fn_t *fn;
    struct co_module_t *module;
    struct co_ctx_t *ctx;
    struct co_ptr_t *ptr;
} co_value_t;

// obj
typedef struct co_obj_t {
    uint8_t k;
    union co_value_t v;
} co_obj_t;

typedef struct co_small_str_obj_t {
    uint8_t k;
    char8_t v[15];
} co_small_str_obj_t;

// entry 
typedef struct co_generic_entry_t {
    struct co_obj_t a;  // attr
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_generic_entry_t;

// dict
typedef struct co_dict_entry_t {
    struct co_obj_t k;  // key
    struct co_obj_t v;  // value
} co_dict_entry_t;

// struct
typedef struct co_struct_entry_t {
    struct co_obj_t a;  // attr
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_struct_entry_t;

/*

Some: type = <T: type=type> -> (v: T)
None: type = ()
Option: type = <T: type=type> -> (Some<T> | None)

Ok: type = <V: type=type> -> (v: V)
Err: type = <E: type=type> -> (e: E)
Result: type = <V: type=type, E: type=type> -> (Ok<V>, Err<E>)

IOError: type = (e: Option<str>=None)
ZeroDivisionError: type = (e: Option<str>=None)
OverflowError: type = (e: Option<str>=None)

Error := (
    IOError,
    ZeroDivisionError,
    OverflowError,
)

sum_i64_i64 := (x: i64, y: i64) -> Result<i64, Error> {
    // r: Result<i64, Error> = i64.__add__(x, y)
    r: Result<i64, Error> = ops.add(x, y)

    z: i64 = r.unwrap()
    z
}

*/

#endif

