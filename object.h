#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>

#include "vm.h"

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
struct co_mut_map_entry_t;
struct co_mut_map_t;
struct co_array_t;
struct co_map_entry_t;
struct co_map_t;
struct co_code_t;
struct co_func_t;
struct co_type_t;
struct co_instance_t;
struct co_module_t;

enum co_own_t;
enum co_kind_t;
union co_value_t;
struct co_object_t;


typedef struct co_bytes_t {
    size_t len;
    char* data;
} co_bytes_t;

typedef struct co_str_t {
    size_t len;
    char* data;
} co_str_t;

typedef struct co_mut_array_t {
    size_t cap;
    size_t len;
    struct co_object_t** items;
} co_mut_array_t;

typedef struct co_map_entry_t {
    size_t hash;
    struct co_object_t* key;
    struct co_object_t* value;
    struct co_map_entry_t* next_entry; // by default NULL
} co_map_entry_t;

typedef struct co_mut_map_t {
    size_t cap;
    size_t fill;
    size_t used;
    struct co_map_entry_t* entries;
    struct co_map_entry_t* first_entry; // by default NULL
    struct co_map_entry_t* last_entry; // by default NULL
} co_mut_map_t;

typedef struct co_array_t {
    size_t len;
    struct co_object_t** items;
} co_array_t;

typedef struct co_map_t {
    size_t cap;
    size_t used;
    struct co_map_entry_t* entries;
    struct co_map_entry_t* first_entry; // by default NULL
    struct co_map_entry_t* last_entry; // by default NULL
} co_map_t;

typedef struct co_code_t {
    void* insts; // TODO
} co_code_t;

typedef struct co_func_t {
    struct co_str_t* name; // function name, can be NULL if lambda
    struct co_map_t* typeparams; // used for generics, `fn f1<T, U, V, W>(x: T, y: U, z: V) -> W { ... }`
    struct co_map_t* params; // `name [: type] [= default_value]`
    struct co_str_t* args; // variable args name, `[args]`, can be NULL 
    struct co_str_t* kwargs; // variable kwargs name, `{kwargs}`, can be NULL 
    struct co_code_t* code;
} co_func_t;

typedef struct co_type_t {
    struct co_str_t* name; // type name, can be NULL if anonymous
    struct co_map_t* typeparams; // used for generics, `type Some<T, U, V, W> { ... }`
    struct co_array_t* interfaces; // interfaces, `type A: B, C {}`, where [B, C] are interfaces
    struct co_map_t* fields; // struct-like fields
    struct co_map_t* funcs; // methods-like
} co_type_t;

typedef struct co_instance_t {
    struct co_type_t* type; // instance-of
    struct co_map_t* fields; // struct-like fields
} co_instance_t;

typedef struct co_module_t {
    struct co_str_t* path; // path to module such as "/home/user/proj/a.co"
    struct co_str_t* name; // name of module such as "a"
    struct co_map_t* ns; // namespace containing module's types/functions/objects
} co_module_t;

typedef struct co_pointer_t {
    void* data;
    void* extra;
    void (*free_func)(struct co_object_t* self, void* extra);
} co_pointer_t;

typedef enum co_own_t {
    CO_OWN_NONE = 0,    // the recipient does not own the value
    CO_OWN_CONTAINER,   // the recipient owns the container, but not the elements
    CO_OWN_FULL         // the recipient owns the entire value.
                        // container type, this means the recipient owns both container and elements.
} co_own_t;

typedef enum co_kind_t {
    CO_KIND_NIL = 0, // same as None ?!
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
    CO_KIND_MUT_MAP,
    CO_KIND_ARRAY,
    CO_KIND_MAP,
    CO_KIND_CODE,
    CO_KIND_FUNC,
    CO_KIND_TYPE,
    CO_KIND_INSTANCE,
    CO_KIND_MODULE,
    CO_KIND_POINTER
} co_kind_t;

typedef union co_value_t {
    co_bool_t b;
    co_i8_t i8;
    co_u8_t u8;
    co_i16_t i16;
    co_u16_t u16;
    co_i32_t i32;
    co_u32_t u32;
    co_i64_t i64;
    co_u64_t u64;
    co_f32_t f32;
    co_f64_t f64;
    struct co_bytes_t bytes;
    struct co_str_t str;
    struct co_mut_array_t mut_array;
    struct co_mut_map_t mut_map;
    struct co_array_t array;
    struct co_map_t map;
    struct co_code_t code;
    struct co_func_t func;
    struct co_type_t type;
    struct co_instance_t instance;
    struct co_module_t module;
    struct co_pointer_t pointer;
} co_value_t;

typedef struct co_object_t {
    size_t rc;
    enum co_own_t own;
    enum co_kind_t kind;
    union co_value_t value;
} co_object_t;


/*
 * bool
 */
co_object_t* co_bool_new(co_vm_t* vm, co_bool_t b);
void co_bool_free(co_vm_t* vm, co_object_t* self);

/*
 * i8
 */
co_object_t* co_i8_new(co_vm_t* vm, co_i8_t i8);
void co_i8_free(co_vm_t* vm, co_object_t* self);

/*
 * u8
 */
co_object_t* co_u8_new(co_vm_t* vm, co_u8_t u8);
void co_u8_free(co_vm_t* vm, co_object_t* self);

/*
 * i16
 */
co_object_t* co_i16_new(co_vm_t* vm, co_i16_t i16);
void co_i16_free(co_vm_t* vm, co_object_t* self);

/*
 * u16
 */
co_object_t* co_u16_new(co_vm_t* vm, co_u16_t u16);
void co_u16_free(co_vm_t* vm, co_object_t* self);

/*
 * i32
 */
co_object_t* co_i32_new(co_vm_t* vm, co_i32_t i32);
void co_i32_free(co_vm_t* vm, co_object_t* self);

/*
 * u32
 */
co_object_t* co_u32_new(co_vm_t* vm, co_u32_t u32);
void co_u32_free(co_vm_t* vm, co_object_t* self);

/*
 * i64
 */
co_object_t* co_i64_new(co_vm_t* vm, co_i64_t i64);
void co_i64_free(co_vm_t* vm, co_object_t* self);

/*
 * u64
 */
co_object_t* co_u64_new(co_vm_t* vm, co_u64_t u64);
void co_u64_free(co_vm_t* vm, co_object_t* self);

/*
 * f32
 */
co_object_t* co_f32_new(co_vm_t* vm, co_f32_t f32);
void co_f32_free(co_vm_t* vm, co_object_t* self);

/*
 * f64
 */
co_object_t* co_f64_new(co_vm_t* vm, co_f64_t f64);
void co_f64_free(co_vm_t* vm, co_object_t* self);

/*
 * bytes
 */
co_object_t* co_bytes_new(co_vm_t* vm, co_own_t own, size_t len, char* data);
void co_bytes_free(co_vm_t* vm, co_object_t* self);

/*
 * str
 */
co_object_t* co_str_new(co_vm_t* vm, co_own_t own, size_t len, char* data);
void co_str_free(co_vm_t* vm, co_object_t* self);

/*
 * mut_array
 */
co_object_t* co_mut_array_new(co_vm_t* vm, co_own_t own, size_t cap, size_t len, co_object_t** items);
void co_mut_array_free(co_vm_t* vm, co_object_t* self);

/*
 * mut_map
 */
co_object_t* co_mut_map_new(co_vm_t* vm, co_own_t own, size_t cap, size_t used, size_t fill, co_map_entry_t* entries);
void co_mut_map_free(co_vm_t* vm, co_object_t* self);

/*
 * array
 */

/*
 * map
 */

/*
 * code
 */

/*
 * func
 */

/*
 * type
 */

/*
 * instance
 */

/*
 * module
 */

/*
 * object
 */
#define CO_OBJECT_REF(vm, self) self->rc++
#define CO_OBJECT_UNREF(vm, self) \
    self->rc--; \
    if (self->rc == 0) co_object_free(vm, self)

co_object_t* co_object_new(co_vm_t* vm, co_own_t own, co_kind_t kind, co_value_t value);
void co_object_free(co_vm_t* vm, co_object_t* self);
inline void co_object_ref(co_vm_t* vm, co_object_t* self);
inline void co_object_unref(co_vm_t* vm, co_object_t* self);

#endif