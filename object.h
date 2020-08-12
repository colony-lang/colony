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

// typedef struct co_object_t* (*co_cfunc_t)(struct co_vm_t* vm, struct co_object_t* args, struct co_object_t* kwargs);

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
    size_t used;
    struct co_map_entry_t* entries;
    enum co_own_t own;
    struct co_map_entry_t* first_entry; // by default NULL
    struct co_map_entry_t* last_entry;  // by default NULL
} co_map_t;

typedef struct co_code_t {
    size_t len;
    struct co_inst_t* insts;
} co_code_t;

typedef struct co_fn_t {
    struct co_object_t* name;               // Optional<Str>, function name
    struct co_object_t* type_param_names;   // Array<Str>, example: ['T', 'U', 'V', 'W'], used for generics, `fn f1<T, U, V, W>(x: T, y: U, z: V) -> W { ... }`
    struct co_object_t* params;             // Array<Param(name: Str, type: Type, default_value: Optional<Object>)>, `name [: type] [= default_value]`
    struct co_object_t* code;               // Optional<Code>
    struct co_object_t* ic_code;            // Optional<Code>, inline cache code, by default always None
    // co_cfunc_t cfunc;                    // can be NULL if code and/or ic_code is set
} co_fn_t;

typedef struct co_frame_t {
    struct co_object_t* prev_frame;         // Optional<Frame>
    struct co_object_t* regs;               // Array[Object]
    struct co_object_t* func;               // Optional<Fn>
    struct co_object_t* code;               // Code
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
    void* extra;
    void (*free_func)(struct co_object_t* self);
    enum co_own_t own;
} co_pointer_t;

typedef enum co_kind_t {
    CO_KIND_EMPTY = 0, // used in mut_array, array, mut_map, map for not yet set items/entreis
    CO_KIND_NONE = 1,
    CO_KIND_BOOL,
    CO_KIND_I8,
    CO_KIND_U8,
    CO_KIND_I16,
    CO_KIND_U16,
    CO_KIND_I32,
    CO_KIND_U32,
    CO_KIND_I64,
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
 * bool
 */
co_object_t* co_bool_new(struct co_vm_t* vm, co_bool_t b);
void co_bool_free(struct co_vm_t* vm, co_object_t* self);

/*
 * i8
 */
co_object_t* co_i8_new(struct co_vm_t* vm, co_i8_t i8);
void co_i8_free(struct co_vm_t* vm, co_object_t* self);

/*
 * u8
 */
co_object_t* co_u8_new(struct co_vm_t* vm, co_u8_t u8);
void co_u8_free(struct co_vm_t* vm, co_object_t* self);

/*
 * i16
 */
co_object_t* co_i16_new(struct co_vm_t* vm, co_i16_t i16);
void co_i16_free(struct co_vm_t* vm, co_object_t* self);

/*
 * u16
 */
co_object_t* co_u16_new(struct co_vm_t* vm, co_u16_t u16);
void co_u16_free(struct co_vm_t* vm, co_object_t* self);

/*
 * i32
 */
co_object_t* co_i32_new(struct co_vm_t* vm, co_i32_t i32);
void co_i32_free(struct co_vm_t* vm, co_object_t* self);

/*
 * u32
 */
co_object_t* co_u32_new(struct co_vm_t* vm, co_u32_t u32);
void co_u32_free(struct co_vm_t* vm, co_object_t* self);

/*
 * i64
 */
co_object_t* co_i64_new(struct co_vm_t* vm, co_i64_t i64);
void co_i64_free(struct co_vm_t* vm, co_object_t* self);

/*
 * u64
 */
co_object_t* co_u64_new(struct co_vm_t* vm, co_u64_t u64);
void co_u64_free(struct co_vm_t* vm, co_object_t* self);

/*
 * f32
 */
co_object_t* co_f32_new(struct co_vm_t* vm, co_f32_t f32);
void co_f32_free(struct co_vm_t* vm, co_object_t* self);

/*
 * f64
 */
co_object_t* co_f64_new(struct co_vm_t* vm, co_f64_t f64);
void co_f64_free(struct co_vm_t* vm, co_object_t* self);

/*
 * bytes
 */
co_object_t* co_bytes_new(struct co_vm_t* vm, size_t len, char* data, co_own_t own);
void co_bytes_free(struct co_vm_t* vm, co_object_t* self);

/*
 * str
 */
co_object_t* co_str_new(struct co_vm_t* vm, size_t len, char* data, co_own_t own);
void co_str_free(struct co_vm_t* vm, co_object_t* self);

/*
 * mut_array
 */
co_object_t* co_mut_array_new(struct co_vm_t* vm, size_t cap, size_t len, co_object_t* items, co_own_t own);
void co_mut_array_free(struct co_vm_t* vm, co_object_t* self);

/*
 * array
 */
co_object_t* co_array_new(struct co_vm_t* vm, size_t cap, size_t len, co_object_t* items, co_own_t own);
void co_array_free(struct co_vm_t* vm, co_object_t* self);

/*
 * mut_map
 */
co_object_t* co_mut_map_new(struct co_vm_t* vm, size_t cap, size_t used, size_t fill, co_map_entry_t* entries, co_own_t own);
void co_mut_map_free(struct co_vm_t* vm, co_object_t* self);

/*
 * map
 */
co_object_t* co_map_new(struct co_vm_t* vm, size_t cap, size_t used, size_t fill, co_map_entry_t* entries, co_own_t own);
void co_map_free(struct co_vm_t* vm, co_object_t* self);

/*
 * code
 */
co_object_t* co_code_new(struct co_vm_t* vm, size_t len, struct co_inst_t* insts);
void co_code_free(struct co_vm_t* vm, co_object_t* self);

/*
 * fn
 */
co_object_t* co_fn_new(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* params, co_object_t* code);
void co_fn_free(struct co_vm_t* vm, co_object_t* self);

/*
 * frame
 */
co_object_t* co_frame_new(struct co_vm_t* vm, co_object_t* prev_frame, co_object_t* regs, co_object_t* func, co_object_t* code);
void co_frame_free(struct co_vm_t* vm, co_object_t* self);

/*
 * mut_type
 */
co_object_t* co_mut_type_new(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* interfaces, co_object_t* fields, co_object_t* funcs);
void co_mut_type_free(struct co_vm_t* vm, co_object_t* self);

/*
 * type
 */
co_object_t* co_type_new(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* interfaces, co_object_t* fields, co_object_t* funcs);
void co_type_free(struct co_vm_t* vm, co_object_t* self);

/*
 * mut_instance
 */

/*
 * instance
 */

/*
 * mut_module
 */

/*
 * module
 */

/*
 * object
 */
#define CO_OBJECT_REF(vm, self) (self)->rc++
#define CO_OBJECT_UNREF(vm, self) \
    (self)->rc--; \
    if ((self)->rc == 0) co_object_free(vm, self)

co_object_t* co_object_new(struct co_vm_t* vm, co_kind_t kind, co_value_t value);
void co_object_free(struct co_vm_t* vm, co_object_t* self);
void co_object_ref(struct co_vm_t* vm, co_object_t* self);
void co_object_unref(struct co_vm_t* vm, co_object_t* self);

#endif
