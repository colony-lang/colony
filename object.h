#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <float.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

enum co_own_t;

typedef bool co_bool_t;
typedef int8_t co_i8_t;
typedef uint8_t co_u8_t;
typedef int16_t co_i16_t;
typedef uint16_t co_u16_t;
typedef int32_t co_i32_t;
typedef uint32_t co_u32_t;
typedef int64_t co_i64_t;
typedef uint64_t co_u64_t;
typedef float co_f32_t;
typedef double co_f64_t;
struct co_bytes_t;
struct co_str_t;
struct co_mut_array_t;
struct co_array_t;
struct co_mut_map_t;
struct co_map_t;
struct co_code_t;
struct co_fn_t;
struct co_method_t;
struct co_frame_t;
struct co_mut_type_t;
struct co_type_t;
struct co_mut_instance_t;
struct co_instance_t;
struct co_mut_module_t;
struct co_module_t;

enum co_kind_t;
union co_value_t;
struct co_object_t;

struct co_map_entry_t; // used for mut_map and map

#include "vm.h"

/*
 * ownership, used for str, bytes, mut_array, array, mut_map, map 
 */
typedef enum co_own_t {
    CO_OWN_NONE = 0,        // the recipient does not own the value
    
    CO_OWN_CONTAINER = 1,   // the recipient owns the container, but not the elements.

    CO_OWN_FULL = 128       // for scalar types, the recipient owns the entire value
                            //
                            // for container types, this means the recipient owns
                            // container, but "ref counts" its elements
} co_own_t;

typedef void (*co_pointer_free_func)(struct co_object_t* self);

typedef struct co_bytes_t {
    size_t len;
    char* data;
    enum co_own_t own;
} co_bytes_t;

typedef struct co_str_t {
    size_t len;
    char* data;
    enum co_own_t own;
} co_str_t;

typedef struct co_mut_array_t {
    struct co_object_t* item_type;      // Object, default
    size_t cap;
    size_t len;
    struct co_object_t* items;
    enum co_own_t own;
} co_mut_array_t;

typedef struct co_array_t {
    struct co_object_t* item_type;      // Object, default
    size_t cap;
    size_t len;
    struct co_object_t* items;
    enum co_own_t own;
} co_array_t;

typedef struct co_mut_map_t {
    struct co_object_t* key_type;       // Object, default
    struct co_object_t* value_type;     // Object, default
    size_t cap;
    size_t fill;
    size_t used;
    struct co_map_entry_t* entries;
    enum co_own_t own;
    struct co_map_entry_t* first_entry; // by default NULL
    struct co_map_entry_t* last_entry;  // by default NULL
} co_mut_map_t;

typedef struct co_map_t {
    struct co_object_t* key_type;       // Object, default
    struct co_object_t* value_type;     // Object, default
    size_t cap;
    size_t fill;
    size_t used;
    struct co_map_entry_t* entries;
    enum co_own_t own;
    struct co_map_entry_t* first_entry; // by default NULL
    struct co_map_entry_t* last_entry;  // by default NULL
} co_map_t;

typedef struct co_code_t {
    size_t len;
    struct co_inst_t* insts;
    enum co_own_t own;
} co_code_t;

typedef struct co_fn_t {
    struct co_object_t* name;               // Option<Str>, function name
    struct co_object_t* type_param_names;   // Array<Str>, example: ['T', 'U', 'V', 'W'], used for generics, `fn f1<T, U, V, W>(x: T, y: U, z: V) -> W { ... }`
    struct co_object_t* params;             // Array<Param(name: Str, type: Type, default_value: Option<Object>)>, `name [: type] [= default_value]`
    struct co_object_t* closure;            // Map<str, Object>, closure, function non-local variables/constanst
    struct co_object_t* code;               // Code
} co_fn_t;

typedef struct co_method_t {
    struct co_object_t* fn;                 // Fn
    struct co_object_t* obj;                // Object
} co_method_t;

typedef struct co_frame_t {
    struct co_object_t* prev_frame;         // Option<Frame>
    struct co_object_t* regs;               // Array[Object]
    struct co_object_t* fn;                 // Option<Fn>
    struct co_object_t* code;               // Code
    size_t pc;                              // program counter
} co_frame_t;

typedef struct co_mut_type_t {
    struct co_object_t* name;               // Str, type name, can be NULL if anonymous
    struct co_object_t* type_param_names;   // MutMap, used for generics, `type Some<T, U, V, W> { ... }`
    struct co_object_t* interfaces;         // MutArray, interfaces, `type A: B, C {}`, where [B, C] are interfaces
    struct co_object_t* fields;             // MutMap, struct-like fields
    struct co_object_t* funcs;              // MutMap, methods-like
} co_mut_type_t;

typedef struct co_type_t {
    struct co_object_t* name;               // Str, type name, can be NULL if anonymous
    struct co_object_t* type_param_names;   // Map, used for generics, `type Some<T, U, V, W> { ... }`
    struct co_object_t* interfaces;         // Array, interfaces, `type A: B, C {}`, where [B, C] are interfaces
    struct co_object_t* fields;             // Map, struct-like fields
    struct co_object_t* funcs;              // Map, methods-like
} co_type_t;

typedef struct co_mut_instance_t {
    struct co_object_t* type;           // Type, instance-of
    struct co_object_t* fields;         // MutMap, struct-like fields
} co_mut_instance_t;

typedef struct co_instance_t {
    struct co_object_t* type;           // Type, instance-of
    struct co_object_t* fields;         // Map, struct-like fields
} co_instance_t;

typedef struct co_mut_module_t {
    struct co_object_t* path;           // Str, path to module such as "/home/user/proj/a.co"
    struct co_object_t* name;           // Str, name of module such as "a"
    struct co_object_t* ns;             // MutMap, namespace containing module's types/functions/objects
} co_mut_module_t;

typedef struct co_module_t {
    struct co_object_t* path;           // Str, path to module such as "/home/user/proj/a.co"
    struct co_object_t* name;           // Str, name of module such as "a"
    struct co_object_t* ns;             // Map, namespace containing module's types/functions/objects
} co_module_t;

typedef struct co_pointer_t {
    void* data;
    enum co_own_t data_own;
    void* extra;
    enum co_own_t extra_own;
    co_pointer_free_func free_func;
} co_pointer_t;

typedef enum co_kind_t {
    CO_KIND_EMPTY = 0, // used in mut_array, array, mut_map, map for not yet set items/entreis
    CO_KIND_NONE = 1,
    CO_KIND_BOOL,
    CO_KIND_I8,
    CO_KIND_I16,
    CO_KIND_I32,
    CO_KIND_I64,
    CO_KIND_U8,
    CO_KIND_U16,
    CO_KIND_U32,
    CO_KIND_U64,
    CO_KIND_F32,
    CO_KIND_F64,
    CO_KIND_BYTES,
    CO_KIND_STR,
    CO_KIND_MUT_ARRAY,
    CO_KIND_ARRAY,
    CO_KIND_MUT_MAP,
    CO_KIND_MAP,
    CO_KIND_CODE,
    CO_KIND_FN,
    CO_KIND_METHOD,
    CO_KIND_FRAME,
    CO_KIND_MUT_TYPE,
    CO_KIND_TYPE,
    CO_KIND_MUT_INSTANCE,
    CO_KIND_INSTANCE,
    CO_KIND_MUT_MODULE,
    CO_KIND_MODULE,
    CO_KIND_POINTER
} co_kind_t;

typedef union co_value_t {
    co_bool_t b;
    co_i8_t i8;
    co_i16_t i16;
    co_i32_t i32;
    co_i64_t i64;
    co_u8_t u8;
    co_u16_t u16;
    co_u32_t u32;
    co_u64_t u64;
    co_f32_t f32;
    co_f64_t f64;
    struct co_bytes_t* bytes;
    struct co_str_t* str;
    struct co_mut_array_t* mut_array;
    struct co_array_t* array;
    struct co_mut_map_t* mut_map;
    struct co_map_t* map;
    struct co_code_t* code;
    struct co_fn_t* fn;
    struct co_method_t* method;
    struct co_frame_t* frame;
    struct co_mut_type_t* mut_type;
    struct co_type_t* type;
    struct co_mut_instance_t* mut_instance;
    struct co_instance_t* instance;
    struct co_mut_module_t* mut_module;
    struct co_module_t* module;
    struct co_pointer_t* pointer;
} co_value_t;

typedef struct co_object_t {
    size_t rc;                  // reference count (garbage collection)
    enum co_kind_t kind;        // kind of object
    union co_value_t value;     // value of object
} co_object_t;

/*
 * map_entry used for mut_map and map types
 */
typedef struct co_map_entry_t {
    size_t hash;
    struct co_object_t key;
    struct co_object_t value;
    struct co_map_entry_t* next_entry; // by default NULL
} co_map_entry_t;

/*
 * Assumption:
 *
  let Integer: Type = i8 ... i64 | u8 ... u64
  let Float: Type = f32 | f64
  let Sequence: Type = MutArray | Array | MutMap | Map

  type None {}
  
  type Some<T> {
    v: T = T.default()
  }

  type Option<T>: None | Some<T>

  type Ok<V> {
    v: T = T.default()
  }

  type Err<E> {
    e: E = E.default()
  }

  type Result<V, E>: Ok<V> | Err<E>

  type Param ...
  
  type Future ...
*/

/*
 * bool
 */
co_object_t* co_bool_alloc(struct co_vm_t* vm, co_bool_t b);
void co_bool_free(struct co_vm_t* vm, co_object_t* self);

// bool, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64 | bytes | str | MutArray | Array | MutMap | Map>], {} -> bool
co_object_t* co_bool_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bool, [], {} -> u64
co_object_t* co_bool_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bool, [bool], {} -> bool
co_object_t* co_bool_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * i8
 */
co_object_t* co_i8_alloc(struct co_vm_t* vm, co_i8_t i8);
void co_i8_free(struct co_vm_t* vm, co_object_t* self);

// i8, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> i8
co_object_t* co_i8_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [], {} -> u64
co_object_t* co_i8_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [], {} -> i8
co_object_t* co_i8_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [], {} -> i8
co_object_t* co_i8_neg(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [], {} -> i8
co_object_t* co_i8_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> i8
co_object_t* co_i8_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> i8
co_object_t* co_i8_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> i8
co_object_t* co_i8_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> i8
co_object_t* co_i8_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> i8
co_object_t* co_i8_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> i8
co_object_t* co_i8_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> bool
co_object_t* co_i8_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> bool
co_object_t* co_i8_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> bool
co_object_t* co_i8_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> bool
co_object_t* co_i8_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i8, [i8], {} -> bool
co_object_t* co_i8_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * i16
 */
co_object_t* co_i16_alloc(struct co_vm_t* vm, co_i16_t i16);
void co_i16_free(struct co_vm_t* vm, co_object_t* self);

// i16, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> i16
co_object_t* co_i16_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [], {} -> u64
co_object_t* co_i16_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [], {} -> i16
co_object_t* co_i16_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [], {} -> i16
co_object_t* co_i16_neg(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [], {} -> i16
co_object_t* co_i16_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> i16
co_object_t* co_i16_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> i16
co_object_t* co_i16_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> i16
co_object_t* co_i16_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> i16
co_object_t* co_i16_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> i16
co_object_t* co_i16_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> i16
co_object_t* co_i16_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> bool
co_object_t* co_i16_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> bool
co_object_t* co_i16_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> bool
co_object_t* co_i16_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> bool
co_object_t* co_i16_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i16, [i16], {} -> bool
co_object_t* co_i16_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * i32
 */
co_object_t* co_i32_alloc(struct co_vm_t* vm, co_i32_t i32);
void co_i32_free(struct co_vm_t* vm, co_object_t* self);

// i32, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> i32
co_object_t* co_i32_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [], {} -> u64
co_object_t* co_i32_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [], {} -> i32
co_object_t* co_i32_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [], {} -> i32
co_object_t* co_i32_neg(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [], {} -> i32
co_object_t* co_i32_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> i32
co_object_t* co_i32_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> i32
co_object_t* co_i32_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> i32
co_object_t* co_i32_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> i32
co_object_t* co_i32_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> i32
co_object_t* co_i32_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> i32
co_object_t* co_i32_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> bool
co_object_t* co_i32_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> bool
co_object_t* co_i32_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> bool
co_object_t* co_i32_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> bool
co_object_t* co_i32_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i32, [i32], {} -> bool
co_object_t* co_i32_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * i64
 */
co_object_t* co_i64_alloc(struct co_vm_t* vm, co_i64_t i64);
void co_i64_free(struct co_vm_t* vm, co_object_t* self);

// i64, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> i64
co_object_t* co_i64_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [], {} -> u64
co_object_t* co_i64_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [], {} -> i64
co_object_t* co_i64_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [], {} -> i64
co_object_t* co_i64_neg(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [], {} -> i64
co_object_t* co_i64_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> i64
co_object_t* co_i64_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> i64
co_object_t* co_i64_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> i64
co_object_t* co_i64_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> i64
co_object_t* co_i64_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> i64
co_object_t* co_i64_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> i64
co_object_t* co_i64_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> bool
co_object_t* co_i64_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> bool
co_object_t* co_i64_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> bool
co_object_t* co_i64_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> bool
co_object_t* co_i64_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// i64, [i64], {} -> bool
co_object_t* co_i64_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * u8
 */
co_object_t* co_u8_alloc(struct co_vm_t* vm, co_u8_t u8);
void co_u8_free(struct co_vm_t* vm, co_object_t* self);

// u8, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> u8
co_object_t* co_u8_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [], {} -> u64
co_object_t* co_u8_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [], {} -> u8
co_object_t* co_u8_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [], {} -> u8
co_object_t* co_u8_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> u8
co_object_t* co_u8_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> u8
co_object_t* co_u8_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> u8
co_object_t* co_u8_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> u8
co_object_t* co_u8_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> u8
co_object_t* co_u8_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> u8
co_object_t* co_u8_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> bool
co_object_t* co_u8_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> bool
co_object_t* co_u8_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> bool
co_object_t* co_u8_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> bool
co_object_t* co_u8_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u8, [u8], {} -> bool
co_object_t* co_u8_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * u16
 */
co_object_t* co_u16_alloc(struct co_vm_t* vm, co_u16_t u16);
void co_u16_free(struct co_vm_t* vm, co_object_t* self);

// u16, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> u16
co_object_t* co_u16_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [], {} -> u64
co_object_t* co_u16_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [], {} -> u16
co_object_t* co_u16_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [], {} -> u16
co_object_t* co_u16_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> u16
co_object_t* co_u16_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> u16
co_object_t* co_u16_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> u16
co_object_t* co_u16_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> u16
co_object_t* co_u16_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> u16
co_object_t* co_u16_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> u16
co_object_t* co_u16_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> bool
co_object_t* co_u16_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> bool
co_object_t* co_u16_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> bool
co_object_t* co_u16_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> bool
co_object_t* co_u16_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u16, [u16], {} -> bool
co_object_t* co_u16_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * u32
 */
co_object_t* co_u32_alloc(struct co_vm_t* vm, co_u32_t u32);
void co_u32_free(struct co_vm_t* vm, co_object_t* self);

// u32, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> u32
co_object_t* co_u32_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [], {} -> u64
co_object_t* co_u32_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [], {} -> u32
co_object_t* co_u32_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [], {} -> u32
co_object_t* co_u32_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> u32
co_object_t* co_u32_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> u32
co_object_t* co_u32_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> u32
co_object_t* co_u32_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> u32
co_object_t* co_u32_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> u32
co_object_t* co_u32_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> u32
co_object_t* co_u32_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> bool
co_object_t* co_u32_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> bool
co_object_t* co_u32_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> bool
co_object_t* co_u32_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> bool
co_object_t* co_u32_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u32, [u32], {} -> bool
co_object_t* co_u32_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * u64
 */
co_object_t* co_u64_alloc(struct co_vm_t* vm, co_u64_t u64);
void co_u64_free(struct co_vm_t* vm, co_object_t* self);

// u64, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> u64
co_object_t* co_u64_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [], {} -> u64
co_object_t* co_u64_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [], {} -> u64
co_object_t* co_u64_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [], {} -> u64
co_object_t* co_u64_inv(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> u64
co_object_t* co_u64_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> u64
co_object_t* co_u64_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> u64
co_object_t* co_u64_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> u64
co_object_t* co_u64_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> u64
co_object_t* co_u64_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> u64
co_object_t* co_u64_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> bool
co_object_t* co_u64_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> bool
co_object_t* co_u64_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> bool
co_object_t* co_u64_xor(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> bool
co_object_t* co_u64_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// u64, [u64], {} -> bool
co_object_t* co_u64_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * f32
 */
co_object_t* co_f32_alloc(struct co_vm_t* vm, co_f32_t f32);
void co_f32_free(struct co_vm_t* vm, co_object_t* self);

// f32, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> f32
co_object_t* co_f32_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [], {} -> u64
co_object_t* co_f32_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [], {} -> f32
co_object_t* co_f32_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [], {} -> f32
co_object_t* co_f32_neg(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> f32
co_object_t* co_f32_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> f32
co_object_t* co_f32_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> f32
co_object_t* co_f32_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> f32
co_object_t* co_f32_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> f32
co_object_t* co_f32_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> f32
co_object_t* co_f32_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> bool
co_object_t* co_f32_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f32, [f32], {} -> bool
co_object_t* co_f32_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * f64
 */
co_object_t* co_f64_alloc(struct co_vm_t* vm, co_f64_t f64);
void co_f64_free(struct co_vm_t* vm, co_object_t* self);

// f64, [Option<bool | i8 ... i64 | u8 ... u64 | f32 | f64>], {} -> f64
co_object_t* co_f64_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [], {} -> u64
co_object_t* co_f64_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [], {} -> f64
co_object_t* co_f64_pos(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [], {} -> f64
co_object_t* co_f64_neg(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> f64
co_object_t* co_f64_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> f64
co_object_t* co_f64_sub(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> f64
co_object_t* co_f64_mul(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> f64
co_object_t* co_f64_div(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> f64
co_object_t* co_f64_mod(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> f64
co_object_t* co_f64_pow(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> bool
co_object_t* co_f64_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// f64, [f64], {} -> bool
co_object_t* co_f64_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * bytes
 */
co_object_t* co_bytes_alloc(struct co_vm_t* vm, size_t len, char* data, co_own_t own);
void co_bytes_free(struct co_vm_t* vm, co_object_t* self);

// bytes, [Option<bytes>], {} -> bytes
co_object_t* co_bytes_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [], {} -> u64
co_object_t* co_bytes_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [bytes], {} -> bytes
co_object_t* co_bytes_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [bytes], {} -> bool
co_object_t* co_bytes_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [bytes], {} -> bool
co_object_t* co_bytes_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Integer | MutArray<Integer>, Array<Integer>], {} -> bytes
co_object_t* co_bytes_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Integer | MutArray<Integer>, Array<Integer>, bytes] -> bytes
co_object_t* co_bytes_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Integer | MutArray<Integer>, Array<Integer>], {} -> bytes
co_object_t* co_bytes_delete(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [], {} -> Integer
co_object_t* co_bytes_len(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [bytes], {} -> Integer
co_object_t* co_bytes_index(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [bytes], {} -> bytes
co_object_t* co_bytes_replace(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Option<bytes>], {} -> bytes
co_object_t* co_bytes_trim(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Array<bytes>], {} -> bytes
co_object_t* co_bytes_join(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Option<bytes>], {} -> Array<bytes>
co_object_t* co_bytes_split(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Fn[[bytes], Object]], {} -> Array
co_object_t* co_bytes_map(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Fn[[bytes], Object]], {} -> Array
co_object_t* co_bytes_filter(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [Option<MutArray | Array>], {} -> bytes
co_object_t* co_bytes_format(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// bytes, [], {} -> str
co_object_t* co_bytes_decode(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * str
 */
co_object_t* co_str_alloc(struct co_vm_t* vm, size_t len, char* data, co_own_t own);
void co_str_free(struct co_vm_t* vm, co_object_t* self);

// str, [Option<str>], {} -> str
co_object_t* co_str_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [], {} -> u64
co_object_t* co_str_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [str], {} -> str
co_object_t* co_str_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [str], {} -> bool
co_object_t* co_str_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [str], {} -> bool
co_object_t* co_str_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Integer | MutArray<Integer>, Array<Integer>], {} -> str
co_object_t* co_str_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Integer | MutArray<Integer>, Array<Integer>, str], {} -> str
co_object_t* co_str_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Integer | MutArray<Integer>, Array<Integer>], {} -> str
co_object_t* co_str_delete(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [], {} -> Integer
co_object_t* co_str_len(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [str], {} -> Integer
co_object_t* co_str_index(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [str], {} -> str
co_object_t* co_str_replace(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Option<str>], {} -> str
co_object_t* co_str_trim(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Array<str>], {} -> str
co_object_t* co_str_join(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Option<str>], {} -> Array<str>
co_object_t* co_str_split(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Fn[[str], Object]], {} -> Array
co_object_t* co_str_map(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Fn[[str], Object]], {} -> Array
co_object_t* co_str_filter(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [Option<MutArray | Array>], {} -> str
co_object_t* co_str_format(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// str, [], {} -> bytes
co_object_t* co_str_encode(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * mut_array
 */
co_object_t* co_mut_array_alloc(struct co_vm_t* vm, co_object_t* item_type, size_t cap, size_t len, co_object_t* items, co_own_t own);
void co_mut_array_free(struct co_vm_t* vm, co_object_t* self);

// MutArray, [MutArray | Array | MutMap | Map], {} -> MutArray
co_object_t* co_mut_array_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [MutArray], {} -> MutArray
co_object_t* co_mut_array_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [MutArray], {} -> bool
co_object_t* co_mut_array_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [MutArray], {} -> bool
co_object_t* co_mut_array_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Integer | MutArray<Integer>, Array<Integer>], {} -> Object | MutArray
co_object_t* co_mut_array_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Integer | MutArray<Integer>, Array<Integer>, MutArray], {} -> MutArray
co_object_t* co_mut_array_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Integer | MutArray<Integer>, Array<Integer>], {} -> MutArray
co_object_t* co_mut_array_delete(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [], {} -> Integer
co_object_t* co_mut_array_len(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [], {}, -> Array
co_object_t* co_mut_array_imut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Object], {} -> MutArray
co_object_t* co_mut_array_push(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Option<Integer>], {} -> Object
co_object_t* co_mut_array_pop(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Object], {} -> MutArray
co_object_t* co_mut_array_remove(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Object], {} -> Integer
co_object_t* co_mut_array_index(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Fn[[Object], Object]], {} -> MutArray
co_object_t* co_mut_array_map(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutArray, [Fn[[Object], Object]], {} -> MutArray
co_object_t* co_mut_array_filter(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * array
 */
co_object_t* co_array_alloc(struct co_vm_t* vm, co_object_t* item_type, size_t cap, size_t len, co_object_t* items, co_own_t own);
void co_array_free(struct co_vm_t* vm, co_object_t* self);

// Array, [MutArray | Array | MutMap | Map], {} -> Array
co_object_t* co_array_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [], {} -> u64
co_object_t* co_array_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Array], {} -> Array
co_object_t* co_array_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Array], {} -> bool
co_object_t* co_array_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Array], {} -> bool
co_object_t* co_array_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Integer | MutArray<Integer>, Array<Integer>], {} -> Object | Array
co_object_t* co_array_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Integer | MutArray<Integer>, Array<Integer>, Array], {} -> Array
co_object_t* co_array_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Integer | MutArray<Integer>, Array<Integer>], {} -> Array
co_object_t* co_array_delete(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [], {} -> Integer
co_object_t* co_array_len(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [], {}, -> MutArray
co_object_t* co_array_mut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Object], {} -> Array
co_object_t* co_array_push(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Option<Integer>], {} -> Array
co_object_t* co_array_pop(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Object], {} -> Array
co_object_t* co_array_remove(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Object], {} -> Integer
co_object_t* co_array_index(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Fn[[Object], Object]], {} -> Array
co_object_t* co_array_map(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Array, [Fn[[Object], Object]], {} -> Array
co_object_t* co_array_filter(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * mut_map
 */
co_object_t* co_mut_map_alloc(struct co_vm_t* vm, co_object_t* key_type, co_object_t* value_type, size_t cap, size_t used, size_t fill, co_map_entry_t* entries, co_own_t own);
void co_mut_map_free(struct co_vm_t* vm, co_object_t* self);

// MutMap, [MutArray | Array | MutMap | Map], {} -> MutMap
co_object_t* co_mut_map_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [MutMap], {} -> MutMap
co_object_t* co_mut_map_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [MutMap], {} -> bool
co_object_t* co_mut_map_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [MutMap], {} -> bool
co_object_t* co_mut_map_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [Object], {} -> Object
co_object_t* co_mut_map_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [Object, Object], {} -> MutMap
co_object_t* co_mut_map_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [Object], {} -> MutMap
co_object_t* co_mut_map_delete(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [], {} -> Integer
co_object_t* co_mut_map_len(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [], {} -> Map
co_object_t* co_mut_map_imut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [Fn[[Object], Object]], {} -> MutMap
co_object_t* co_mut_map_map(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutMap, [Fn[[Object], Object]], {} -> MutMap
co_object_t* co_mut_map_filter(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * map
 */
co_object_t* co_map_alloc(struct co_vm_t* vm, co_object_t* key_type, co_object_t* value_type, size_t cap, size_t used, size_t fill, co_map_entry_t* entries, co_own_t own);
void co_map_free(struct co_vm_t* vm, co_object_t* self);

// Map, [MutArray | Array | MutMap | Map], {} -> Map
co_object_t* co_map_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [], {} -> u64
co_object_t* co_map_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Map], {} -> Map
co_object_t* co_map_add(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Map], {} -> bool
co_object_t* co_map_lt(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Map], {} -> bool
co_object_t* co_map_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Object], {} -> Object
co_object_t* co_map_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Object, Object], {} -> Map
co_object_t* co_map_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Object], {} -> Map
co_object_t* co_map_delete(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [], {} -> Integer
co_object_t* co_map_len(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [], {} -> MutMap
co_object_t* co_map_mut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Fn[[Object], Object]], {} -> Map
co_object_t* co_map_map(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Map, [Fn[[Object], Object]], {} -> Map
co_object_t* co_map_filter(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * code
 */
co_object_t* co_code_alloc(struct co_vm_t* vm, size_t len, struct co_inst_t* insts, co_own_t own);
void co_code_free(struct co_vm_t* vm, co_object_t* self);

// Code, [Option<Code>], {} -> Code
co_object_t* co_code_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Code, [], {} -> u64
co_object_t* co_code_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Code, [Code], {} -> Code
co_object_t* co_code_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * fn
 */
co_object_t* co_fn_alloc(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* params, co_object_t* closure, co_object_t* code);
void co_fn_free(struct co_vm_t* vm, co_object_t* self);

// Fn, [Option<Fn>], {} -> Fn
co_object_t* co_fn_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Fn, [], {} -> u64
co_object_t* co_fn_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Fn, [Fn], {} -> bool
co_object_t* co_fn_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Fn, Array<Object>, Map<Object, Object> -> Object
co_object_t* co_fn_call(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * method
 */
co_object_t* co_method_alloc(struct co_vm_t* vm, co_object_t* fn, co_object_t* obj);
void co_method_free(struct co_vm_t* vm, co_object_t* self);

// Method, [Fn, Object], {} -> Method
co_object_t* co_method_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Method, [], {} -> u64
co_object_t* co_method_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Method, [Method], {} -> bool
co_object_t* co_method_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Method, Array<Object>, Map<Object, Object> -> Object
co_object_t* co_method_call(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * frame
 */
co_object_t* co_frame_alloc(struct co_vm_t* vm, co_object_t* prev_frame, co_object_t* regs, co_object_t* fn, co_object_t* code);
void co_frame_free(struct co_vm_t* vm, co_object_t* self);

// Frame, [Frame, MutArray, Fn, Code], {} -> Frame
co_object_t* co_frame_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Frame, [], {} -> u64
co_object_t* co_frame_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Frame, [Frame], {} -> bool
co_object_t* co_frame_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * mut_type
 */
co_object_t* co_mut_type_alloc(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* interfaces, co_object_t* fields, co_object_t* funcs);
void co_mut_type_free(struct co_vm_t* vm, co_object_t* self);

// MutType, [Str, MutMap | Map, MutArray | Array, MutMap | Map, MutMap | Map], {} -> MutType
co_object_t* co_mut_type_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, [MutType], {} -> bool
co_object_t* co_mut_type_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, [MutType], {} -> MutType
co_object_t* co_mut_type_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType. [MutType], {} -> MutType
co_object_t* co_mut_type_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, [Object], {} -> Object
co_object_t* co_mut_type_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, [Object, Object] -> MutType
co_object_t* co_mut_type_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, [Array<MutType | Type>], {} -> MutType
co_object_t* co_mut_type_specialize(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, Array<Object>, Map<Object, Object> -> MutInstance
co_object_t* co_mut_type_call(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutType, [], {} -> Type
co_object_t* co_mut_type_imut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * type
 */
co_object_t* co_type_alloc(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* interfaces, co_object_t* fields, co_object_t* funcs);
void co_type_free(struct co_vm_t* vm, co_object_t* self);

// Type, [Str, Map, Array, Map, Map], {} -> Type
co_object_t* co_type_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [], {} -> u64
co_object_t* co_type_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [Type], {} -> bool
co_object_t* co_type_eq(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [Type], {} -> Type
co_object_t* co_type_and(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [Type], {} -> Type
co_object_t* co_type_or(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [Object], {} -> Object
co_object_t* co_type_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [Object, Object], {} -> Type
co_object_t* co_type_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [Array<Type>], {} -> Type
co_object_t* co_type_specialize(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, Array<Object>, Map<Object, Object> -> Instance
co_object_t* co_type_call(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Type, [], {} -> MutType
co_object_t* co_type_mut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * mut_instance
 */
co_object_t* co_mut_instance_alloc(struct co_vm_t* vm, co_object_t* type, co_object_t* fields);
void co_mut_instance_free(struct co_vm_t* vm, co_object_t* self);

// MutInstance, [MutType | Type, MutMap | Map], {} -> MapInstance
co_object_t* co_mut_instance_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutInstance, [Object], {} -> Object
co_object_t* co_mut_instance_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutInstance, [Object, Object] -> MutInstance
co_object_t* co_mut_instance_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutInstance, [], {} -> Instance
co_object_t* co_mut_instance_imut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * instance
 */
co_object_t* co_instance_alloc(struct co_vm_t* vm, co_object_t* type, co_object_t* fields);
void co_instance_free(struct co_vm_t* vm, co_object_t* self);

// Instance, [Type, Map], {} -> Instance
co_object_t* co_instance_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Instance, [], {} -> u64
co_object_t* co_instance_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Instance, [Object], {} -> Object
co_object_t* co_instance_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Instance, [Object, Object] -> Instance
co_object_t* co_instance_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Instance, [], {}, -> MutInstance
co_object_t* co_instance_mut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * mut_module
 */
co_object_t* co_mut_module_alloc(struct co_vm_t* vm, co_object_t* path, co_object_t* name, co_object_t* ns);
void co_mut_module_free(struct co_vm_t* vm, co_object_t* self);

// MutModule, [str, str, MutMap | Map], {} -> MutModule
co_object_t* co_mut_module_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutModule, [Object], {} -> Object
co_object_t* co_mut_module_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutModule, [Object, Object], {} -> MutModule
co_object_t* co_mut_module_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// MutModule, [], {} -> Module
co_object_t* co_mut_module_imut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * module
 */
co_object_t* co_module_alloc(struct co_vm_t* vm, co_object_t* path, co_object_t* name, co_object_t* ns);
void co_module_free(struct co_vm_t* vm, co_object_t* self);

// Module, [str, str, Map], {} -> Module
co_object_t* co_module_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Module, [], {} -> u64
co_object_t* co_module_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Module, [Object], {} -> Object
co_object_t* co_module_get(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Module, [Object, Object], {} -> Module
co_object_t* co_module_set(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Module, [], {} -> MutModule
co_object_t* co_module_mut(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * pointer
 */
co_object_t* co_pointer_alloc(struct co_vm_t* vm, void* data, co_own_t data_own, void* extra, co_own_t extra_own, co_pointer_free_func free_func);
void co_pointer_free(struct co_vm_t* vm, co_object_t* self);

// Pointer, [], {} -> Pointer
co_object_t* co_pointer_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

// Pointer, [], {} -> u64
co_object_t* co_pointer_hash(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs);

/*
 * object
 */
#define CO_OBJECT_REF(vm, self) (self)->rc++
#define CO_OBJECT_UNREF(vm, self) \
    (self)->rc--; \
    if ((self)->rc == 0) co_object_free(vm, self)

co_object_t* co_object_alloc(struct co_vm_t* vm, co_kind_t kind, co_value_t value);
void co_object_free(struct co_vm_t* vm, co_object_t* self);
void co_object_ref(struct co_vm_t* vm, co_object_t* self);
void co_object_unref(struct co_vm_t* vm, co_object_t* self);

#endif
