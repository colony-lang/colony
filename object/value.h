#ifndef CO_VALUE_H
#define CO_VALUE_H

union co_value_t;

#include <stdlib.h>
#include <stdint.h>
#include "./bool.h"
#include "./bytes.h"
#include "./code.h"
#include "./dict.h"
#include "./err.h"
#include "./f64.h"
#include "./i64.h"
#include "./list.h"
#include "./mut_dict.h"
#include "./mut_list.h"
#include "./none.h"
#include "./ns.h"
#include "./object.h"
#include "./ok.h"
#include "./option.h"
#include "./result.h"
#include "./some.h"
#include "./str.h"
#include "./struct.h"
#include "./type.h"
#include "./union.h"

typedef union co_value_t {
    struct co_type_t *type;
    _Bool b;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    float f32;
    double f64;
    struct co_bytes_t *bytes;
    struct co_str_t *str;
    struct co_list_t *list;
    struct co_mut_list_t *mut_list;
    struct co_dict_t *dict;
    struct co_mut_dict_t *mut_dict;
    struct co_ns_t *ns;
    struct co_code_t *code;
    void *func;
    void *closure; // ?
    void *tuple;
    void *union_;
    struct co_option_t *option;
    struct co_some_t *some;
    struct co_none_t *none;
    struct co_result_t *result;
    struct co_ok_t *ok;
    struct co_err_t *err;
    void *ptr;
} co_value_t;

#endif
