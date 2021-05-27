#ifndef CO_CODE_COMMON_H
#define CO_CODE_COMMON_H

#include "object_common.h"

typedef struct co_code_t {
    co_list_t *consts;
    co_bytes_t *insts;
} co_code_t;

#endif
