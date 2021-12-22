#ifndef CO_KIND_H
#define CO_KIND_H

typedef enum co_kind_t {
    CO_KIND_TYPE,
    CO_KIND_BOOL,
    CO_KIND_U8,
    CO_KIND_U16,
    CO_KIND_U32,
    CO_KIND_U64,
    CO_KIND_I8,
    CO_KIND_I16,
    CO_KIND_I32,
    CO_KIND_I64,
    CO_KIND_F32,
    CO_KIND_F64,
    CO_KIND_BYTES,
    CO_KIND_STR,
    CO_KIND_LIST,
    CO_KIND_MUT_LIST,
    CO_KIND_DICT,
    CO_KIND_MUT_DICT,
    CO_KIND_NS,
    CO_KIND_CODE,
    CO_KIND_FUNC,
    CO_KIND_CLOSURE, // ?
    CO_KIND_TUPLE,
    CO_KIND_UNION,
    CO_KIND_OPTION,
    CO_KIND_SOME,
    CO_KIND_NONE,
    CO_KIND_RESULT,
    CO_KIND_OK,
    CO_KIND_ERR,
    CO_KIND_PTR
} co_kind_t;

#endif
