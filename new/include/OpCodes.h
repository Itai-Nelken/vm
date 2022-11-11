#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

typedef enum opcode_type {
    // push <reg>/<const>
    //OP_PUSH_REG,
    OP_PUSH_CONST,
    // pop [<reg>]
    OP_POP,
    //OP_POP_REG,
    OP_HLT
} OpCodeType;

// 8 bits for the opcode, 24 bits for the argument
typedef uint32_t OpCode;

#define ENCODE_OP(op_type) ((OpCode)((op_type) << 24))
#define ENCODE_OP_WITH_ARG(op_type, arg) ((OpCode)((op_type) << 24) + (arg))

#define DECODE_OP(opcode) ((OpCode)((opcode & 0xff000000) >> 24))
#define DECODE_ARG(opcode) ((opcode & 0x00ffffff))

#endif // OPCODES_H
