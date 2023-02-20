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
struct co_ok_entry_t;
struct co_err_entry_t;
struct co_some_entry_t;

#define CO_KIND_UNDEFINED 0     // special value for undefined objects on C-level only
#define CO_KIND_VOID 1          // special value for void objects
#define CO_KIND_BOOL 10         // true, false
#define CO_KIND_U8 20           // [0, 255]
#define CO_KIND_U64 21          // [0, 2**64)
#define CO_KIND_I64 23          // [-2**32, 2**32)
#define CO_KIND_F64 30
#define CO_KIND_GC 40           // meta kind, everything below is GC'ed
#define CO_KIND_BYTES 50        // bytes, Array<u8>
#define CO_KIND_STR 51          // utf8
#define CO_KIND_GENERIC 60
#define CO_KIND_ARRAY 61
#define CO_KIND_DICT 62
#define CO_KIND_STRUCT 63
#define CO_KIND_UNION 64
#define CO_KIND_OK 70           // Ok<V: type=type>
#define CO_KIND_ERR 71          // Err<E: type=type>
#define CO_KIND_RESULT 72       // Result: type = <V: type=type, E: type=type> -> (Ok<V> | Err<E>)
#define CO_KIND_NONE 73         // None - special value
#define CO_KIND_SOME 74         // Some<V: type=type>
#define CO_KIND_OPTION 75       // Option: type = <V: type=type> -> (None | Some<V>)
#define CO_KIND_CODE 80
#define CO_KIND_FN 81
#define CO_KIND_MODULE 82
#define CO_KIND_PTR 90
#define CO_KIND_CTX 100

// 0th bit - immortal, if set to 1
// 1st bit - weak, if set to 1
//
// 0b00... - mortal and strong, 2**62 ref count is max
// 0b01... - weak, and mortal
// 0b10... - immortal, and strong
// 0b11... - impossible!
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

typedef struct co_gc_rc_t {
    co_u64_t immortal : 1;
    co_u64_t weak : 1;
    co_u64_t rc : 62;
} co_gc_rc_t;

typedef struct co_bytes_t {
    CO_GC_RC;
    co_i64_t hash;              // precomputed hash since bytes value is immutable
    size_t len;                 // bytes len
    char8_t *items;             // bytes items stored in char8_t*
} co_bytes_t;

typedef struct co_str_t {
    CO_GC_RC;
    co_i64_t hash;              // precomputed hash since str is immutable
    size_t cap;                 // bytes-level cap of char8_t items
    size_t len;                 // utf8 len
    char8_t *items;             // utf8 items stored in char8_t*
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
Ok: type = <V: type=type> -> (v: V)
*/
typedef struct co_ok_t {
    CO_GC_RC;
    struct co_ok_entry_t *v;
} co_ok_t;

/*
Err: type = <E: type=type> -> (e: E)
*/
typedef struct co_err_t {
    CO_GC_RC;
    struct co_err_entry_t *e;
} co_err_t;

/*
Result: type = <V: type=type, E: type=type> -> (Ok<V> | Err<E>)
*/
typedef struct co_result_t {
    CO_GC_RC;
    struct co_ok_entry_t *v;
    struct co_err_entry_t *e;
} co_result_t;

/*
None: type = (__type__: type=type);
*/
typedef struct co_none_t {
    CO_GC_RC;
} co_none_t;

/*
Some: type = <V: type=type> -> (v: V)
*/
typedef struct co_some_t {
    CO_GC_RC;
    struct co_some_entry_t *v;
} co_some_t;

/*
Option: type = <V: type=type> -> (v: V)
*/
typedef struct co_option_t {
    CO_GC_RC;
    struct co_some_entry_t *v;
} co_option_t;

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
    struct co_ok_t *ok;
    struct co_err_t *err;
    struct co_result_t *result;
    struct co_some_t *some;
    struct co_option_t *option;
    struct co_code_t *code;
    struct co_fn_t *fn;
    struct co_module_t *module;
    struct co_ptr_t *ptr;
    struct co_ctx_t *ctx;
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

// generic entry 
typedef struct co_generic_entry_t {
    struct co_obj_t a;  // attr
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_generic_entry_t;

// dict entry
typedef struct co_dict_entry_t {
    struct co_obj_t k;  // key
    struct co_obj_t v;  // value
} co_dict_entry_t;

// struct entry
typedef struct co_struct_entry_t {
    struct co_obj_t a;  // attr
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_struct_entry_t;

// ok entry
typedef struct co_ok_entry_t {
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_ok_entry_t;

// err entry
typedef struct co_err_entry_t {
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_err_entry_t;

// some entry
typedef struct co_some_entry_t {
    struct co_obj_t t;  // type
    struct co_obj_t v;  // value
} co_some_entry_t;


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

//
// bool
//

//
// object
//
inline co_obj_t co_object_inc_ref(co_obj_t ctx, co_obj_t obj);   // inc RC
inline co_obj_t co_object_dec_ref(co_obj_t ctx, co_obj_t obj);   // dec RC
inline co_obj_t co_object_set_ref(co_obj_t ctx, co_obj_t obj);   // set initial RC
inline co_obj_t co_object_set_immortal_ref(co_obj_t ctx, co_obj_t obj);   // set immortal
inline co_obj_t co_object_set_weak_ref(co_obj_t ctx, co_obj_t obj);   // set weak ref

// object.__free__ := fn(obj) -> void { ... }
co_obj_t co_object_free(co_obj_t ctx, co_obj_t obj);

// object.__call__ := fn(obj, [args], {kwargs}) -> object { ... }
co_obj_t co_object_call(co_obj_t ctx, co_obj_t obj, co_obj_t args, co_obj_t kwargs);

// object.__get_attr__ := fn(obj, attr: str) -> Result
// object.__set_attr__ := fn(obj, attr: str, value: object) -> Result
// object.__set_attr_in__ := fn(obj, attrs: Array<str>, value: object) -> Result
// object.__get_item__ := fn(obj, key: object) -> Result
// object.__set_item__ := fn(obj, key: object, value: object) -> Result
// object.__set_item__ := fn(obj, keys: Array<object>, value: object) -> Result

// object.__neg__ := fn(obj) -> Result
// object.__pos__ := fn(obj) -> Result
// object.__add__ := fn(obj, other) -> Result
// object.__sub__ := fn(obj, other) -> Result
// object.__mul__ := fn(obj, other) -> Result
// object.__div__ := fn(obj, other) -> Result
// object.__pow__ := fn(obj, other) -> Result
// object.__mod__ := fn(obj, other) -> Result

// object.__inv__ := fn(obj) -> Result
// object.__bit_and__ := fn(obj, other) -> Result
// object.__bit_or__ := fn(obj, other) -> Result
// object.__bit_xor__ := fn(obj, other) -> Result
// object.__shl__ := fn(obj, other) -> Result
// object.__shr__ := fn(obj, other) -> Result

// object.__not__ := fn(obj) -> Result
// object.__and__ := fn(obj, other) -> Result
// object.__or__ := fn(obj, other) -> Result

#endif

