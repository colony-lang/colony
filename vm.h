#ifndef CO_VM_H
#define CO_VM_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

enum co_opcode_name_t;
union co_opcode_t;
union co_operands_t;
struct co_inst_t;
struct co_vm_t;

#include "object.h"

typedef enum co_opcode_name_t {
    CO_OPCODE_NOP,              // Skip
    
    CO_OPCODE_MOV,              // UU; R[a] = R[b]
    CO_OPCODE_LOAD,             // UU; R[a] = C[b]; used for Bytes, Str, Code, Pointer
    CO_OPCODE_LOAD_NONE,        // U; R[a] = None
    CO_OPCODE_LOAD_BOOL,        // Ub; R[a] = b
    CO_OPCODE_LOAD_I8,          // UI8; R[a] = I8
    CO_OPCODE_LOAD_I16,         // UI16; R[a] = I16
    CO_OPCODE_LOAD_I32,         // UI32; R[a] = I32
    CO_OPCODE_LOAD_I64,         // UI64; R[a] = I64
    CO_OPCODE_LOAD_U8,          // UU8; R[a] = U8
    CO_OPCODE_LOAD_U16,         // UU16; R[a] = U16
    CO_OPCODE_LOAD_U32,         // UU32; R[a] = U32
    CO_OPCODE_LOAD_U64,         // UU64; R[a] = U64
    CO_OPCODE_LOAD_F32,         // UF32; R[a] = F32
    CO_OPCODE_LOAD_F64,         // UF64; R[a] = F64
    
    CO_OPCODE_NEW_MUT_ARRAY,    // UUU; R[a] = MutArray<R[b]>(cap=R[b + 1], items=R.slice(b + 2, c)); where b + 2 <= c and c < a
    CO_OPCODE_NEW_ARRAY,        // UUU; R[a] = Array<R[b]>(cap=R[b + 1], items=R.slice(b + 2, c)); where b + 2 <= c and c < a
    CO_OPCODE_NEW_MUT_MAP,      // UUU; R[a] = MutMap<R[b]>(cap=R[b + 1], items=R.slice(b + 2, c)); where b + 2 <= c and c < a
    CO_OPCODE_NEW_MAP,          // UUU; R[a] = Map<R[b]>(cap=R[b + 1], items=R.slice(b + 2, c)); where b + 2 <= c and c < a
    CO_OPCODE_NEW_FN,           // UU; R[a] = Fn name=R[b] <R[b + 1]>(params=R[b + 2], code=R[b + 3]) 
    CO_OPCODE_NEW_MUT_TYPE,     // UU; R[a] = MutType name=R[b] <R[b + 1]>(interfaces=R[b + 2], fields=R[b + 3], funcs=R[b + 4])
    CO_OPCODE_NEW_TYPE,         // UU; R[a] = Type name=R[b] <R[b + 1]>(interfaces=R[b + 2], fields=R[b + 3], funcs=R[b + 4])
    CO_OPCODE_NEW_MUT_INSTANCE, // UU; R[a] = MutInstance(type=R[b], fields=R[b + 1])
    CO_OPCODE_NEW_INSTANCE,     // UU; R[a] = Instance(type=R[b], fields=R[b + 1])
    CO_OPCODE_NEW_MUT_MODULE,   // UU; R[a] = MutModule(path=R[b], name=R[b + 1], ns=R[b + 2])
    CO_OPCODE_NEW_MODULE,       // UU; R[a] = Module(path=R[b], name=R[b + 1], ns=R[b + 2])
    
    CO_OPCODE_POS,              // UU; R[a] = +R[b]
    CO_OPCODE_NEG,              // UU; R[a] = -R[b]
    CO_OPCODE_INV,              // UU; R[a] = ~R[b]
    CO_OPCODE_ADD,              // UUU; R[a] = R[b] + R[c]
    CO_OPCODE_SUB,              // UUU; R[a] = R[b] - R[c]
    CO_OPCODE_MUL,              // UUU; R[a] = R[b] * R[c]
    CO_OPCODE_DIV,              // UUU; R[a] = R[b] / R[c]
    CO_OPCODE_MOD,              // UUU; R[a] = R[b] % R[c]
    CO_OPCODE_POW,              // UUU; R[a] = R[b] ** R[c]
    
    CO_OPCODE_NOT,              // UU; R[a] = !R[b]
    CO_OPCODE_AND,              // UUU; R[a] = R[b] & R[c]
    CO_OPCODE_OR,               // UUU; R[a] = R[b] | R[c]
    CO_OPCODE_XOR,              // UUU; R[a] = R[b] ^ R[c]

    CO_OPCODE_LT,               // UUU; R[a] = R[b] < R[c]
    CO_OPCODE_EQ,               // UUU; R[a] = R[b] == R[c]
    CO_OPCODE_JLT,              // UUI; if R[a] < R[b] then PC += c
    CO_OPCODE_JEQ,              // UUI; if R[a] == R[b] then PC += c
    CO_OPCODE_JMP,              // I; PC += a
    
    CO_OPCODE_CALL,             // UUU; R[a] = R[b](args=R[c], kwargs=R[c + 1])
    CO_OPCODE_RET,              // U; return R[a]
    
    CO_OPCODE_END               // End of code
} co_opcode_name_t;

typedef union co_opcode_t {
    enum co_opcode_name_t name;
    void* addr;
} co_opcode_t;

typedef struct co_operands_u_t {
    unsigned int a;
} co_operands_u_t;

typedef struct co_operands_uu_t {
    unsigned int a;
    unsigned int b;
} co_operands_uu_t;

typedef struct co_operands_uuu_t {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} co_operands_uuu_t;

typedef struct co_operands_ub_t {
    unsigned int a;
    bool b;
} co_operands_ub_t;

typedef struct co_operands_ui8_t {
    unsigned int a;
    int8_t b;
} co_operands_ui8_t;

typedef struct co_operands_ui16_t {
    unsigned int a;
    int16_t b;
} co_operands_ui16_t;

typedef struct co_operands_ui32_t {
    unsigned int a;
    int32_t b;
} co_operands_ui32_t;

typedef struct co_operands_ui64_t {
    unsigned int a;
    int64_t b;
} co_operands_ui64_t;

typedef struct co_operands_uu8_t {
    unsigned int a;
    uint8_t b;
} co_operands_uu8_t;

typedef struct co_operands_uu16_t {
    unsigned int a;
    uint16_t b;
} co_operands_uu16_t;

typedef struct co_operands_uu32_t {
    unsigned int a;
    uint32_t b;
} co_operands_uu32_t;

typedef struct co_operands_uu64_t {
    unsigned int a;
    uint64_t b;
} co_operands_uu64_t;

typedef struct co_operands_uui_t {
    unsigned int a;
    unsigned int b;
    int c;
} co_operands_uui_t;

typedef struct co_operands_i_t {
    int a;
} co_operands_i_t;

typedef union co_operands_t {
    struct co_operands_u_t u;
    struct co_operands_uu_t uu;
    struct co_operands_uuu_t uuu;
    struct co_operands_ub_t ub;
    struct co_operands_ui8_t ui8;
    struct co_operands_ui16_t ui16;
    struct co_operands_ui32_t ui32;
    struct co_operands_ui64_t ui64;
    struct co_operands_uu8_t uu8;
    struct co_operands_uu16_t uu16;
    struct co_operands_uu32_t uu32;
    struct co_operands_uu64_t uu64;
    struct co_operands_uui_t uui;
    struct co_operands_i_t i;
} co_operands_t;

typedef struct co_inst_t {
    union co_opcode_t opcode;
    union co_operands_t operands;
} co_inst_t;

typedef struct co_vm_t {
    struct co_object_t* queued_frames;  // MutArray<Frame>
} co_vm_t;

co_vm_t* co_vm_new(void);
void co_vm_free(co_vm_t* vm);

#endif
