#include "object.h"

/*
 * bool
 */
co_object_t* co_bool_new(co_vm_t* vm, co_bool_t b) {
    co_value_t value = {.b = b};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_BOOL, value);
    return self;
}

void co_bool_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * i8
 */
co_object_t* co_i8_new(co_vm_t* vm, co_i8_t i8) {
    co_value_t value = {.i8 = i8};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_I8, value);
    return self;
}

void co_i8_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * u8
 */
co_object_t* co_u8_new(co_vm_t* vm, co_u8_t u8) {
    co_value_t value = {.u8 = u8};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_U8, value);
    return self;
}

void co_u8_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * i16
 */
co_object_t* co_i16_new(co_vm_t* vm, co_i16_t i16) {
    co_value_t value = {.i16 = i16};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_I16, value);
    return self;
}

void co_i16_free(co_vm_t* vm, co_object_t* self){
    free(self);
}

/*
 * u16
 */
co_object_t* co_u16_new(co_vm_t* vm, co_u16_t u16) {
    co_value_t value = {.u16 = u16};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_U16, value);
    return self;
}

void co_u16_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * i32
 */
co_object_t* co_i32_new(co_vm_t* vm, co_i32_t i32) {
    co_value_t value = {.i32 = i32};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_I32, value);
    return self;
}

void co_i32_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * u32
 */
co_object_t* co_u32_new(co_vm_t* vm, co_u32_t u32) {
    co_value_t value = {.u32 = u32};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_U32, value);
    return self;
}

void co_u32_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * i64
 */
co_object_t* co_i64_new(co_vm_t* vm, co_i64_t i64) {
    co_value_t value = {.i64 = i64};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_I64, value);
    return self;
}

void co_i64_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * u64
 */
co_object_t* co_u64_new(co_vm_t* vm, co_u64_t u64) {
    co_value_t value = {.u64 = u64};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_U64, value);
    return self;
}

void co_u64_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * f32
 */
co_object_t* co_f32_new(co_vm_t* vm, co_f32_t f32) {
    co_value_t value = {.f32 = f32};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_F32, value);
    return self;
}

void co_f32_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * f64
 */
co_object_t* co_f64_new(co_vm_t* vm, co_f64_t f64) {
    co_value_t value = {.f64 = f64};
    co_object_t* self = co_object_new(vm, CO_OWN_FULL, CO_KIND_F64, value);
    return self;
}

void co_f64_free(co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * bytes
 */
co_object_t* co_bytes_new(co_vm_t* vm, co_own_t own, size_t len, char* data) {
    co_bytes_t bytes = {.len = len, .data = data};
    co_value_t value = {.bytes = bytes};
    co_object_t* self = co_object_new(vm, own, CO_KIND_BYTES, value);
    return self;
}

void co_bytes_free(co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_bytes_t bytes = value.bytes;

    if (self->own == CO_OWN_FULL) {
        free(bytes.data);
    }

    free(self);
}

/*
 * str
 */
co_object_t* co_str_new(co_vm_t* vm, co_own_t own, size_t len, char* data) {
    co_str_t str = {.len = len, .data = data};
    co_value_t value = {.str = str};
    co_object_t* self = co_object_new(vm, own, CO_KIND_STR, value);
    return self;
}

void co_str_free(co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_str_t str = value.str;

    if (self->own == CO_OWN_FULL) {
        free(str.data);
    }

    free(self);
}

/*
 * mut_array
 */
co_object_t* co_mut_array_new(co_vm_t* vm, co_own_t own, size_t cap, size_t len, co_object_t** items) {
    if (cap == 0) {
        cap = 8;
    }

    if (len > 0 && items == NULL) {
        len = 0;
    }

    if (items == NULL) {
        own = CO_OWN_FULL;
        items = calloc(cap, sizeof(co_object_t*));
    }

    co_mut_array_t mut_array = {.len = len, .cap = cap, .items = items};
    co_value_t value = {.mut_array = mut_array};
    co_object_t* self = co_object_new(vm, own, CO_KIND_MUT_ARRAY, value);
    return self;
}

void co_mut_array_free(co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_array_t mut_array = value.mut_array;
    co_object_t* item = NULL;

    switch (self->own) {
        case CO_OWN_FULL:
            for (size_t i = 0; i < mut_array.len; i++) {
                item = mut_array.items[i];
                CO_OBJECT_UNREF(vm, item);
            }
        case CO_OWN_CONTAINER:
            free(mut_array.items);
        case CO_OWN_NONE:
        default:
            ;
    }

    free(self);
}

/*
 * mut_map
 */
co_object_t* co_mut_map_new(co_vm_t* vm, co_own_t own, size_t cap, size_t used, size_t fill, co_map_entry_t* entries) {
    if (cap == 0) {
        cap = 8;
    }

    if (used > 0 && entries == NULL) {
        used = 0;
    }

    if (fill > 0 && entries == NULL) {
        fill = 0;
    }

    if (entries == NULL) {
        own = CO_OWN_FULL;
        entries = calloc(cap, sizeof(co_map_entry_t));
    }

    co_mut_map_t mut_map = {.cap = cap, .fill = fill, .used = used, .entries = entries};
    co_value_t value = {.mut_map = mut_map};
    co_object_t* self = co_object_new(vm, own, CO_KIND_MUT_MAP, value);
    return self;
}

void co_mut_map_free(co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_map_t mut_map = value.mut_map;
    co_map_entry_t entry;
    co_object_t* k = NULL;
    co_object_t* v = NULL;

    switch (self->own) {
        case CO_OWN_FULL:
            for (size_t i = 0; i < mut_map.cap; i++) {
                entry = mut_map.entries[i];
                k = entry.key;
                v = entry.value;
                
                if (k == NULL) {
                    continue;
                }

                CO_OBJECT_UNREF(vm, k);
                CO_OBJECT_UNREF(vm, v);
            }
        case CO_OWN_CONTAINER:
            free(mut_map.entries);
        case CO_OWN_NONE:
        default:
            ;
    }

    free(self);
}

/*
 * array
 */

/*
 * map
 */

/*
 * code
 */

/*
 * func
 */

/*
 * type
 */

/*
 * instance
 */

/*
 * module
 */

/*
 * object
 */
co_object_t* co_object_new(co_vm_t* vm, co_own_t own, co_kind_t kind, co_value_t value) {
    co_object_t* self = malloc(sizeof(co_object_t));
    self->rc = 1;
    self->own = own;
    self->kind = kind;
    self->value = value;
    return self;
}

void co_object_free(co_vm_t* vm, co_object_t* self) {
    switch (self->kind) {
        case CO_KIND_BOOL:
            co_bool_free(vm, self);
            break;
        case CO_KIND_I8:
            co_i8_free(vm, self);
            break;
        case CO_KIND_U8:
            co_u8_free(vm, self);
            break;
        case CO_KIND_I16:
            co_i16_free(vm, self);
            break;
        case CO_KIND_U16:
            co_u16_free(vm, self);
            break;
        case CO_KIND_I32:
            co_i32_free(vm, self);
            break;
        case CO_KIND_U32:
            co_u32_free(vm, self);
            break;
        case CO_KIND_I64:
            co_i64_free(vm, self);
            break;
        case CO_KIND_U64:
            co_u64_free(vm, self);
            break;
        case CO_KIND_F32:
            co_f32_free(vm, self);
            break;
        case CO_KIND_F64:
            co_f64_free(vm, self);
            break;
        case CO_KIND_BYTES:
            co_bytes_free(vm, self);
            break;
        case CO_KIND_STR:
            co_str_free(vm, self);
            break;
        case CO_KIND_MUT_ARRAY:
            co_mut_array_free(vm, self);
            break;
        case CO_KIND_MUT_MAP:
            co_mut_map_free(vm, self);
            break;
        case CO_KIND_ARRAY:
            break;
        case CO_KIND_MAP:
            break;
        case CO_KIND_CODE:
            break;
        case CO_KIND_FUNC:
            break;
        case CO_KIND_TYPE:
            break;
        case CO_KIND_INSTANCE:
            break;
        case CO_KIND_MODULE:
            break;
        case CO_KIND_POINTER:
            break;
        default:
            free(self);
    }
}

inline void co_object_ref(co_vm_t* vm, co_object_t* self) {
    CO_OBJECT_REF(vm, self);
}

inline void co_object_unref(co_vm_t* vm, co_object_t* self) {
    CO_OBJECT_UNREF(vm, self);
}
