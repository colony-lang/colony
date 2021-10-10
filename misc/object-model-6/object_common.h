#ifndef CO_OBJECT_COMMON_H
#define CO_OBJECT_COMMON_H

enum co_kind_t;
enum co_own_t;

/* kind of object, mainly used to distinguish between primitive and GC'ed objects */
typedef enum co_kind_t {
    // primitive values
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

    // ref counted values
    CO_KIND_GC,
    
    // special
    CO_KIND_TYPE,
    CO_KIND_CTX,
    CO_KIND_BYTES,
    CO_KIND_STR,
    CO_KIND_LIST_TYPE,
    CO_KIND_LIST,
    CO_KIND_DICT_TYPE,
    CO_KIND_DICT,
    CO_KIND_NS,

    // Result, Ok, Err
    CO_KIND_OK_TYPE,
    CO_KIND_OK,
    CO_KIND_ERR_TYPE,
    CO_KIND_ERR,
    CO_KIND_RESULT_TYPE,

    // Option, Some, None
    CO_KIND_SOME_TYPE,
    CO_KIND_SOME,
    CO_KIND_NONE,
    CO_KIND_OPTION_TYPE,
} co_kind_t;

/* used to transfer ownership */
typedef enum co_own_t {
    CO_OWN_NONE,
    CO_OWN_FULL,
} co_own_t;


#endif

