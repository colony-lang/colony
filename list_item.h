#ifndef CO_LIST_ITEM_H
#define CO_LIST_ITEM_H

typedef struct co_list_item_t {
    co_object_t *type;  // type
    co_object_t *value; // any
} co_list_item_t;

#endif
