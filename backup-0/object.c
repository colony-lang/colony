#include "object.h"

/*
 * bool
 */
co_object_t* co_bool_alloc(struct co_vm_t* vm, co_bool_t b) {
    co_value_t value = {.b = b};
    co_object_t* self = co_object_alloc(vm, CO_KIND_BOOL, value);
    return self;
}

void co_bool_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

co_object_t* co_bool_init(struct co_vm_t* vm, co_object_t* self, co_object_t* args, co_object_t* kwargs) {
    co_object_t* res = NULL;

    /*
    co_object_t* value = NULL;

    switch (args->kind) {
        case CO_KIND_MUT_ARRAY:
            break;
        case CO_KIND_ARRAY:
            break;
        default:
            // error, unsupported args type/kind
    }
    */

    return res;
}

/*
 * i8
 */
co_object_t* co_i8_alloc(struct co_vm_t* vm, co_i8_t i8) {
    co_value_t value = {.i8 = i8};
    co_object_t* self = co_object_alloc(vm, CO_KIND_I8, value);
    return self;
}

void co_i8_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * i16
 */
co_object_t* co_i16_alloc(struct co_vm_t* vm, co_i16_t i16) {
    co_value_t value = {.i16 = i16};
    co_object_t* self = co_object_alloc(vm, CO_KIND_I16, value);
    return self;
}

/*
 * i32
 */
co_object_t* co_i32_alloc(struct co_vm_t* vm, co_i32_t i32) {
    co_value_t value = {.i32 = i32};
    co_object_t* self = co_object_alloc(vm, CO_KIND_I32, value);
    return self;
}

void co_i32_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * i64
 */
co_object_t* co_i64_alloc(struct co_vm_t* vm, co_i64_t i64) {
    co_value_t value = {.i64 = i64};
    co_object_t* self = co_object_alloc(vm, CO_KIND_I64, value);
    return self;
}

void co_i64_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * u8
 */
co_object_t* co_u8_alloc(struct co_vm_t* vm, co_u8_t u8) {
    co_value_t value = {.u8 = u8};
    co_object_t* self = co_object_alloc(vm, CO_KIND_U8, value);
    return self;
}

void co_u8_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

void co_i16_free(struct co_vm_t* vm, co_object_t* self){
    free(self);
}

/*
 * u16
 */
co_object_t* co_u16_alloc(struct co_vm_t* vm, co_u16_t u16) {
    co_value_t value = {.u16 = u16};
    co_object_t* self = co_object_alloc(vm, CO_KIND_U16, value);
    return self;
}

void co_u16_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * u32
 */
co_object_t* co_u32_alloc(struct co_vm_t* vm, co_u32_t u32) {
    co_value_t value = {.u32 = u32};
    co_object_t* self = co_object_alloc(vm, CO_KIND_U32, value);
    return self;
}

void co_u32_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * u64
 */
co_object_t* co_u64_alloc(struct co_vm_t* vm, co_u64_t u64) {
    co_value_t value = {.u64 = u64};
    co_object_t* self = co_object_alloc(vm, CO_KIND_U64, value);
    return self;
}

void co_u64_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * f32
 */
co_object_t* co_f32_alloc(struct co_vm_t* vm, co_f32_t f32) {
    co_value_t value = {.f32 = f32};
    co_object_t* self = co_object_alloc(vm, CO_KIND_F32, value);
    return self;
}

void co_f32_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * f64
 */
co_object_t* co_f64_alloc(struct co_vm_t* vm, co_f64_t f64) {
    co_value_t value = {.f64 = f64};
    co_object_t* self = co_object_alloc(vm, CO_KIND_F64, value);
    return self;
}

void co_f64_free(struct co_vm_t* vm, co_object_t* self) {
    free(self);
}

/*
 * bytes
 */
co_object_t* co_bytes_alloc(struct co_vm_t* vm, size_t len, char* data, co_own_t own) {
    co_bytes_t* bytes = malloc(sizeof(co_bytes_t));
    bytes->len = len;
    bytes->data = data;
    bytes->own = own;
    co_value_t value = {.bytes = bytes};
    co_object_t* self = co_object_alloc(vm, CO_KIND_BYTES, value);
    return self;
}

void co_bytes_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_bytes_t* bytes = value.bytes;

    if (bytes->own == CO_OWN_FULL) {
        free(bytes->data);
    }
    
    free(bytes);
    free(self);
}

/*
 * str
 */
co_object_t* co_str_alloc(struct co_vm_t* vm, size_t len, char* data, co_own_t own) {
    co_str_t* str = malloc(sizeof(co_str_t));
    str->len = len;
    str->data = data;
    str->own = own;
    co_value_t value = {.str = str};
    co_object_t* self = co_object_alloc(vm, CO_KIND_STR, value);
    return self;
}

void co_str_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_str_t* str = value.str;

    if (str->own == CO_OWN_FULL) {
        free(str->data);
    }

    free(str);
    free(self);
}

/*
 * mut_array
 */
co_object_t* co_mut_array_alloc(struct co_vm_t* vm, co_object_t* item_type, size_t cap, size_t len, co_object_t* items, co_own_t own) {
    co_object_t item;
    co_object_ref(vm, item_type);

    if (cap == 0) {
        cap = 8;
    }

    if (len > 0 && items == NULL) {
        len = 0;
    }

    if (items == NULL) {
        own = CO_OWN_CONTAINER;
        items = calloc(cap, sizeof(co_object_t));
    } else {
        for (size_t i = 0; i < len; i++) {
            item = items[i];
            co_object_ref(vm, &item);
        }
    }

    co_mut_array_t* mut_array = malloc(sizeof(co_mut_array_t));
    mut_array->item_type = item_type;
    mut_array->cap = cap;
    mut_array->len = len;
    mut_array->items = items;
    mut_array->own = own;
    co_value_t value = {.mut_array = mut_array};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MUT_ARRAY, value);
    return self;
}

void co_mut_array_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_array_t* mut_array = value.mut_array;
    co_object_t* item_type = mut_array->item_type;
    co_object_t* items = mut_array->items;
    co_object_t item;

    for (size_t i = 0; i < mut_array->len; i++) {
        item = items[i];
        co_object_unref(vm, &item);
    }

    co_object_unref(vm, item_type);

    switch (mut_array->own) {
        case CO_OWN_NONE:
            break;
        case CO_OWN_CONTAINER:
            free(items);
            break;
        case CO_OWN_FULL:
            free(items);
            break;
    }

    free(self);
}

/*
 * array
 */
co_object_t* co_array_alloc(struct co_vm_t* vm, co_object_t* item_type, size_t cap, size_t len, co_object_t* items, co_own_t own) {
    co_object_t item;
    co_object_ref(vm, item_type);

    if (cap == 0) {
        cap = 8;
    }

    if (len > 0 && items == NULL) {
        len = 0;
    }

    if (items == NULL) {
        own = CO_OWN_CONTAINER;
        items = calloc(cap, sizeof(co_object_t));
    } else {
        for (size_t i = 0; i < len; i++) {
            item = items[i];
            co_object_ref(vm, &item);
        }
    }

    co_array_t* array = malloc(sizeof(co_array_t));
    array->item_type = item_type;
    array->cap = cap;
    array->len = len;
    array->items = items;
    array->own = own;
    co_value_t value = {.array = array};
    co_object_t* self = co_object_alloc(vm, CO_KIND_ARRAY, value);
    return self;
}

void co_array_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_array_t* array = value.array;
    co_object_t* item_type = array->item_type;
    co_object_t* items = array->items;
    co_object_t item;

    for (size_t i = 0; i < array->len; i++) {
        item = items[i];
        co_object_unref(vm, &item);
    }

    co_object_unref(vm, item_type);

    switch (array->own) {
        case CO_OWN_NONE:
            break;
        case CO_OWN_CONTAINER:
            free(items);
            break;
        case CO_OWN_FULL:
            free(items);
            break;
    }

    free(self);
}

/*
 * mut_map
 */
co_object_t* co_mut_map_alloc(struct co_vm_t* vm, co_object_t* key_type, co_object_t* value_type, size_t cap, size_t used, size_t fill, co_map_entry_t* entries, co_own_t own) {
    co_map_entry_t entry;
    co_object_t k;
    co_object_t v;
    co_object_ref(vm, key_type);
    co_object_ref(vm, value_type);

    if (cap == 0) {
        cap = 8;
    }

    if (entries == NULL) {
        used = 0;
        fill = 0;
        own = CO_OWN_CONTAINER;
        entries = calloc(cap, sizeof(co_map_entry_t));
    } else {
        for (size_t i = 0; i < cap; i++) {
            entry = entries[i];
            k = entry.key;
            v = entry.value;

            if (k.kind != CO_KIND_EMPTY) {
                co_object_ref(vm, &k);
            }

            if (v.kind != CO_KIND_EMPTY) {
                co_object_ref(vm, &v);
            }
        }
    }

    co_mut_map_t* mut_map = malloc(sizeof(co_mut_map_t));
    mut_map->key_type = key_type;
    mut_map->value_type = value_type;
    mut_map->cap = cap;
    mut_map->used = used;
    mut_map->fill = fill;
    mut_map->entries = entries;
    mut_map->own = own;
    co_value_t value = {.mut_map = mut_map};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MUT_MAP, value);
    return self;
}

void co_mut_map_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_map_t* mut_map = value.mut_map;
    co_object_t* key_type = mut_map->key_type;
    co_object_t* value_type = mut_map->value_type;
    co_map_entry_t* entries = mut_map->entries;
    co_map_entry_t entry;
    co_object_t k;
    co_object_t v;

    if (mut_map->own == CO_OWN_NONE || mut_map->own == CO_OWN_CONTAINER) {
        for (size_t i = 0; i < mut_map->cap; i++) {
            entry = entries[i];
            k = entry.key;
            v = entry.value;
            
            if (k.kind != CO_KIND_EMPTY) {
                co_object_unref(vm, &k);
            }

            if (v.kind != CO_KIND_EMPTY) {
                co_object_unref(vm, &v);
            }
        }
    }

    co_object_unref(vm, key_type);
    co_object_unref(vm, value_type);

    switch (mut_map->own) {
        case CO_OWN_NONE:
            break;
        case CO_OWN_CONTAINER:
            free(entries);
            break;
        case CO_OWN_FULL:
            free(entries);
            break;
    }

    free(mut_map);
    free(self);
}

/*
 * map
 */
co_object_t* co_map_alloc(struct co_vm_t* vm, co_object_t* key_type, co_object_t* value_type, size_t cap, size_t used, size_t fill, co_map_entry_t* entries, co_own_t own) {
    co_map_entry_t entry;
    co_object_t k;
    co_object_t v;
    co_object_ref(vm, key_type);
    co_object_ref(vm, value_type);

    if (cap == 0) {
        cap = 8;
    }

    if (entries == NULL) {
        used = 0;
        fill = 0;
        own = CO_OWN_CONTAINER;
        entries = calloc(cap, sizeof(co_map_entry_t));
    } else {
        for (size_t i = 0; i < cap; i++) {
            entry = entries[i];
            k = entry.key;
            v = entry.value;

            if (k.kind != CO_KIND_EMPTY) {
                co_object_ref(vm, &k);
            }

            if (v.kind != CO_KIND_EMPTY) {
                co_object_ref(vm, &v);
            }
        }
    }

    co_map_t* map = malloc(sizeof(co_map_t));
    map->key_type = key_type;
    map->value_type = value_type;
    map->cap = cap;
    map->used = used;
    map->fill = fill;
    map->entries = entries;
    map->own = own;
    co_value_t value = {.map = map};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MAP, value);
    return self;
}

void co_map_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_map_t* map = value.map;
    co_object_t* key_type = map->key_type;
    co_object_t* value_type = map->value_type;
    co_map_entry_t* entries = map->entries;
    co_map_entry_t entry;
    co_object_t k;
    co_object_t v;

    if (map->own == CO_OWN_NONE || map->own == CO_OWN_CONTAINER) {
        for (size_t i = 0; i < map->cap; i++) {
            entry = entries[i];
            k = entry.key;
            v = entry.value;
            
            if (k.kind != CO_KIND_EMPTY) {
                co_object_unref(vm, &k);
            }

            if (v.kind != CO_KIND_EMPTY) {
                co_object_unref(vm, &v);
            }
        }
    }

    co_object_unref(vm, key_type);
    co_object_unref(vm, value_type);

    switch (map->own) {
        case CO_OWN_NONE:
            break;
        case CO_OWN_CONTAINER:
            free(entries);
            break;
        case CO_OWN_FULL:
            free(entries);
            break;
    }

    free(map);
    free(self);
}

/*
 * code
 */
co_object_t* co_code_alloc(struct co_vm_t* vm, size_t len, struct co_inst_t* insts, co_own_t own) {
    co_code_t* code = malloc(sizeof(co_code_t));
    code->len = len;
    code->insts = insts;
    code->own = own;
    co_value_t value = {.code = code};
    co_object_t* self = co_object_alloc(vm, CO_KIND_CODE, value);
    return self;
}

void co_code_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_code_t* code = value.code;

    if (code->own == CO_OWN_FULL) {
        free(code->insts);
    }
    
    free(code);
    free(self);
}

/*
 * fn
 */
co_object_t* co_fn_alloc(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* params, co_object_t* closure, co_object_t* code) {
    co_object_ref(vm, name);
    co_object_ref(vm, type_param_names);
    co_object_ref(vm, params);
    co_object_ref(vm, closure);
    co_object_ref(vm, code);

    co_fn_t* fn = malloc(sizeof(co_fn_t));
    fn->name = name;
    fn->type_param_names = type_param_names;
    fn->params = params;
    fn->closure = closure;
    fn->code = code;
    co_value_t value = {.fn = fn};
    co_object_t* self = co_object_alloc(vm, CO_KIND_FN, value);
    return self;
}

void co_fn_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_fn_t* fn = value.fn;
    co_object_t* name = fn->name;
    co_object_t* type_param_names = fn->type_param_names;
    co_object_t* params = fn->params;
    co_object_t* closure = fn->closure;
    co_object_t* code = fn->code;

    co_object_unref(vm, name);
    co_object_unref(vm, type_param_names);
    co_object_unref(vm, params);
    co_object_unref(vm, closure);
    co_object_unref(vm, code);

    free(fn);
    free(self);
}

/*
 * method
 */
co_object_t* co_method_alloc(struct co_vm_t* vm, co_object_t* fn, co_object_t* obj) {
    co_object_ref(vm, fn);
    co_object_ref(vm, obj);

    co_method_t* method = malloc(sizeof(co_method_t));
    method->fn = fn;
    method->obj = obj;
    co_value_t value = {.method = method};
    co_object_t* self = co_object_alloc(vm, CO_KIND_METHOD, value);
    return self;
}

void co_method_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_method_t* method = value.method;
    co_object_t* fn = method->fn;
    co_object_t* obj = method->obj;

    co_object_unref(vm, fn);
    co_object_unref(vm, obj);

    free(method);
    free(self);
}

/*
 * frame
 */
co_object_t* co_frame_alloc(struct co_vm_t* vm, co_object_t* prev_frame, co_object_t* regs, co_object_t* fn, co_object_t* code) {
    co_object_ref(vm, prev_frame);
    co_object_ref(vm, regs);
    co_object_ref(vm, fn);
    co_object_ref(vm, code);

    co_frame_t* frame = malloc(sizeof(co_frame_t));
    frame->prev_frame = prev_frame;
    frame->regs = regs;
    frame->fn = fn;
    frame->code = code;
    co_value_t value = {.frame = frame};
    co_object_t* self = co_object_alloc(vm, CO_KIND_FRAME, value);
    return self;
}

void co_frame_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_frame_t* frame = value.frame;
    co_object_t* prev_frame = frame->prev_frame;
    co_object_t* regs = frame->regs;
    co_object_t* fn = frame->fn;
    co_object_t* code = frame->code;

    co_object_unref(vm, prev_frame);
    co_object_unref(vm, regs);
    co_object_unref(vm, fn);
    co_object_unref(vm, code);

    free(frame);
    free(self);
}

/*
 * mut_type
 */
co_object_t* co_mut_type_alloc(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* interfaces, co_object_t* fields, co_object_t* funcs) {
    co_object_ref(vm, name);
    co_object_ref(vm, type_param_names);
    co_object_ref(vm, interfaces);
    co_object_ref(vm, fields);
    co_object_ref(vm, funcs);

    co_mut_type_t* mut_type = malloc(sizeof(co_mut_type_t));
    mut_type->name = name;
    mut_type->type_param_names = type_param_names;
    mut_type->interfaces = interfaces;
    mut_type->fields = fields;
    mut_type->funcs = funcs;
    co_value_t value = {.mut_type = mut_type};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MUT_TYPE, value);
    return self;
}

void co_mut_type_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_type_t* mut_type = value.mut_type;
    co_object_t* name = mut_type->name;
    co_object_t* type_param_names = mut_type->type_param_names;
    co_object_t* interfaces = mut_type->interfaces;
    co_object_t* fields = mut_type->fields;
    co_object_t* funcs = mut_type->funcs;

    co_object_unref(vm, name);
    co_object_unref(vm, type_param_names);
    co_object_unref(vm, interfaces);
    co_object_unref(vm, fields);
    co_object_unref(vm, funcs);

    free(mut_type);
    free(self);
}

/*
 * type
 */
co_object_t* co_type_alloc(struct co_vm_t* vm, co_object_t* name, co_object_t* type_param_names, co_object_t* interfaces, co_object_t* fields, co_object_t* funcs) {
    co_object_ref(vm, name);
    co_object_ref(vm, type_param_names);
    co_object_ref(vm, interfaces);
    co_object_ref(vm, fields);
    co_object_ref(vm, funcs);

    co_type_t* type = malloc(sizeof(co_type_t));
    type->name = name;
    type->type_param_names = type_param_names;
    type->interfaces = interfaces;
    type->fields = fields;
    type->funcs = funcs;
    co_value_t value = {.type = type};
    co_object_t* self = co_object_alloc(vm, CO_KIND_TYPE, value);
    return self;
}

void co_type_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_type_t* type = value.type;
    co_object_t* name = type->name;
    co_object_t* type_param_names = type->type_param_names;
    co_object_t* interfaces = type->interfaces;
    co_object_t* fields = type->fields;
    co_object_t* funcs = type->funcs;

    co_object_unref(vm, name);
    co_object_unref(vm, type_param_names);
    co_object_unref(vm, interfaces);
    co_object_unref(vm, fields);
    co_object_unref(vm, funcs);

    free(type);
    free(self);
}

/*
 * mut_instance
 */
co_object_t* co_mut_instance_alloc(struct co_vm_t* vm, co_object_t* type, co_object_t* fields) {
    co_object_ref(vm, type);
    co_object_ref(vm, fields);

    co_mut_instance_t* mut_instance = malloc(sizeof(co_mut_instance_t));
    mut_instance->type = type;
    mut_instance->fields = fields;
    co_value_t value = {.mut_instance = mut_instance};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MUT_INSTANCE, value);
    return self;
}

void co_mut_instance_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_instance_t* mut_instance = value.mut_instance;
    co_object_t* type = mut_instance->type;
    co_object_t* fields = mut_instance->fields;

    co_object_unref(vm, type);
    co_object_unref(vm, fields);

    free(mut_instance);
    free(self);
}

/*
 * instance
 */
co_object_t* co_instance_alloc(struct co_vm_t* vm, co_object_t* type, co_object_t* fields) {
    co_object_ref(vm, type);
    co_object_ref(vm, fields);

    co_instance_t* instance = malloc(sizeof(co_instance_t));
    instance->type = type;
    instance->fields = fields;
    co_value_t value = {.instance = instance};
    co_object_t* self = co_object_alloc(vm, CO_KIND_INSTANCE, value);
    return self;
}

void co_instance_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_instance_t* instance = value.instance;
    co_object_t* type = instance->type;
    co_object_t* fields = instance->fields;

    co_object_unref(vm, type);
    co_object_unref(vm, fields);

    free(instance);
    free(self);
}

/*
 * mut_module
 */
co_object_t* co_mut_module_alloc(struct co_vm_t* vm, co_object_t* path, co_object_t* name, co_object_t* ns) {
    co_object_ref(vm, path);
    co_object_ref(vm, name);
    co_object_ref(vm, ns);

    co_mut_module_t* mut_module = malloc(sizeof(co_mut_module_t));
    mut_module->path = path;
    mut_module->name = name;
    mut_module->ns = ns;
    co_value_t value = {.mut_module = mut_module};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MUT_MODULE, value);
    return self;
}

void co_mut_module_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_mut_module_t* mut_module = value.mut_module;
    co_object_t* path = mut_module->path;
    co_object_t* name = mut_module->name;
    co_object_t* ns = mut_module->ns;

    co_object_unref(vm, path);
    co_object_unref(vm, name);
    co_object_unref(vm, ns);

    free(mut_module);
    free(self);
}

/*
 * module
 */
co_object_t* co_module_alloc(struct co_vm_t* vm, co_object_t* path, co_object_t* name, co_object_t* ns) {
    co_object_ref(vm, path);
    co_object_ref(vm, name);
    co_object_ref(vm, ns);

    co_module_t* module = malloc(sizeof(co_module_t));
    module->path = path;
    module->name = name;
    module->ns = ns;
    co_value_t value = {.module = module};
    co_object_t* self = co_object_alloc(vm, CO_KIND_MODULE, value);
    return self;
}

void co_module_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_module_t* module = value.module;
    co_object_t* path = module->path;
    co_object_t* name = module->name;
    co_object_t* ns = module->ns;

    co_object_unref(vm, path);
    co_object_unref(vm, name);
    co_object_unref(vm, ns);

    free(module);
    free(self);
}

/*
 * pointer
 */
co_object_t* co_pointer_alloc(struct co_vm_t* vm, void* data, co_own_t data_own, void* extra, co_own_t extra_own, co_pointer_free_func free_func) {
    co_pointer_t* pointer = malloc(sizeof(co_pointer_t));
    pointer->data = data;
    pointer->data_own = data_own;
    pointer->extra = extra;
    pointer->extra_own = extra_own;
    pointer->free_func = free_func;
    co_value_t value = {.pointer = pointer};
    co_object_t* self = co_object_alloc(vm, CO_KIND_POINTER, value);
    return self;
}

void co_pointer_free(struct co_vm_t* vm, co_object_t* self) {
    co_value_t value = self->value;
    co_pointer_t* pointer = value.pointer;

    if (pointer->free_func != NULL) {
        // it is up to `free_func` to free `data` and `extra` if required
        pointer->free_func(self);
    } else {
        if (pointer->data_own == CO_OWN_FULL) {
            free(pointer->data);
        }

        if (pointer->extra_own == CO_OWN_FULL) {
            free(pointer->extra);
        }
    }
    
    free(pointer);
    free(self);
}

/*
 * object
 */
co_object_t* co_object_alloc(struct co_vm_t* vm, co_kind_t kind, co_value_t value) {
    co_object_t* self = malloc(sizeof(co_object_t));
    self->rc = 1;
    self->kind = kind;
    self->value = value;
    return self;
}

void co_object_free(struct co_vm_t* vm, co_object_t* self) {
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
        case CO_KIND_ARRAY:
            co_array_free(vm, self);
            break;
        case CO_KIND_MUT_MAP:
            co_mut_map_free(vm, self);
            break;
        case CO_KIND_MAP:
            co_map_free(vm, self);
            break;
        case CO_KIND_CODE:
            co_code_free(vm, self);
            break;
        case CO_KIND_FN:
            co_fn_free(vm, self);
            break;
        case CO_KIND_FRAME:
            co_frame_free(vm, self);
            break;
        case CO_KIND_MUT_TYPE:
            co_mut_type_free(vm, self);
            break;
        case CO_KIND_TYPE:
            co_type_free(vm, self);
            break;
        case CO_KIND_MUT_INSTANCE:
            co_mut_instance_free(vm, self);
            break;
        case CO_KIND_INSTANCE:
            co_instance_free(vm, self);
            break;
        case CO_KIND_MUT_MODULE:
            co_mut_module_free(vm, self);
            break;
        case CO_KIND_MODULE:
            co_module_free(vm, self);
            break;
        case CO_KIND_POINTER:
            co_pointer_free(vm, self);
            break;
        default:
            free(self);
    }
}

void co_object_ref(struct co_vm_t* vm, co_object_t* self) {
    CO_OBJECT_REF(vm, self);
}

void co_object_unref(struct co_vm_t* vm, co_object_t* self) {
    CO_OBJECT_UNREF(vm, self);
}
