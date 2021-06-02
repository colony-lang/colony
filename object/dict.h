#ifndef CO_DICT_H
#define CO_DICT_H

struct co_dict_item_t;
struct co_dict_t;

#include <stdlib.h>
#include "ctx.h"
#include "object.h"
// #include "lw_type.h"

typedef struct co_dict_item_t {
    struct co_object_t *key;   // any
    struct co_object_t *value; // any
} co_dict_item_t;

typedef struct co_dict_t {
    size_t len;
    struct co_dict_item_t *items;
} co_dict_t;

// (cls: DictType, len: 'size_t'=0, items: Option['co_dict_item_t *']=None) -> dict[any, any]
co_object_t *co_dict_type_new(co_ctx_t *ctx, co_object_t *cls, size_t len, co_dict_item_t *items);

// (cls: DictType, types: (key: any, value: any)) -> dict[types.key, types.value]
co_object_t *co_dict_type_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key_type, co_object_t *value_type);

// (self: dict) -> Result
co_object_t *co_dict_free(co_ctx_t *ctx, co_object_t *self);

// (self: dict, key: any, value: any) -> dict
co_object_t *co_dict_set(co_ctx_t *ctx, co_object_t *self, co_object_t *key, co_object_t *value);

// (self: dict, key: any) -> any | Err
co_object_t *co_dict_get(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> dict | Err
co_object_t *co_dict_del(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, key: any) -> bool
co_object_t *co_dict_has(co_ctx_t *ctx, co_object_t *self, co_object_t *key);

// (self: dict, other: dict) -> dict
co_object_t *co_dict_add(co_ctx_t *ctx, co_object_t *self, co_object_t *other);

// (self: dict) -> list[(any, any)]
co_object_t *co_dict_items(co_ctx_t *ctx, co_object_t *self);

/*static co_object_t co_DictType = (co_object_t){
    .rc = SIZE_MAX,
    .kind = CO_KIND_LW_TYPE,
    .value = {
        .lw_type = &(co_lw_type_t){
            .items = (co_lw_type_item_t*){
                { NULL, NULL, NULL },
                { NULL, NULL, NULL }
            }
        }
    }
};*/

#endif
