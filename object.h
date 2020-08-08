#ifndef CO_OBJECT_H
#define CO_OBJECT_H

#include <stdint.h>
#include <stdbool.h>


typedef union co_value_t {
    bool b;
    int8_t i8;
    uint8_t u8;
} co_value_t;


typedef struct co_object_t {
    void* type;
    union co_value_t* value;
} co_object_t;


#endif