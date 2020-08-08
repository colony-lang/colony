#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>


enum co_type_t;
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
struct co_array_t;
struct co_map_entry_t;
struct co_map_t;
struct co_code_t;
struct co_func_t;
union co_value_t;
struct co_object_t;

typedef enum co_type_t {
    CO_TYPE_UNKNOWN = 0,
    CO_TYPE_BOOL,
    CO_TYPE_I8,
    CO_TYPE_U8,
    CO_TYPE_I16,
    CO_TYPE_U16,
    CO_TYPE_I32,
    CO_TYPE_U32,
    CO_TYPE_I64,
    CO_TYPE_U64,
    CO_TYPE_F32,
    CO_TYPE_F64,
    CO_TYPE_BYTES,
    CO_TYPE_STR,
    CO_TYPE_ARRAY,
    CO_TYPE_MAP,
    CO_TYPE_CODE,
    CO_TYPE_FUNC
} co_type_t;

typedef struct co_bytes_t {
    size_t len;
    char* data;
} co_bytes_t;

typedef struct co_str_t {
    size_t len;
    char* data;
} co_str_t;

typedef struct co_array_t {
    size_t cap;
    size_t len;
    struct co_object_t** items;
} co_array_t;

typedef struct co_map_entry_t {
    size_t hash;
    struct co_object_t* key;
    struct co_object_t* value;
} co_map_entry_t;

typedef struct co_map_t {
    size_t fill;
    size_t used;
    size_t mask;
    struct co_map_entry_t* items;
} co_map_t;

typedef struct co_code_t {
    void* dummy;
} co_code_t;

typedef struct co_func_t {
    void* dummy;
} co_func_t;

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
    struct co_array_t array;
    struct co_map_t map;
    struct co_code_t code;
    struct co_func_t func;
} co_value_t;

typedef struct co_object_t {
    enum co_type_t t;
    union co_value_t v;
} co_object_t;

#endif