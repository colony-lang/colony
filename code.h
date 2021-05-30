#ifndef CO_CODE_H
#define CO_CODE_H

struct co_code_t;

#include "object.h"
#include "list.h"
#include "bytes.h"

typedef struct co_code_t {
    struct co_list_t *consts;
    struct co_bytes_t *insts;
} co_code_t;

#endif
