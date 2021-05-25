#ifndef CO_DICT_ITEM_H
#define CO_DICT_ITEM_H

typedef struct co_dict_item_t {
    co_object_t *key;   // any
    co_object_t *type;  // type
    co_object_t *value; // any
} co_dict_item_t;

#endif
