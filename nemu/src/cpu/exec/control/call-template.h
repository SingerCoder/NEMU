#include "cpu/exec/template-start.h"

#define instr call

make_helper(concat(call_i_, SUFFIX)) {
    //Push(EIP);
    //EIP ← EIP + rel32;    
    int len = concat(decode_i_, SUFFIX)(cpu.eip + 1);
    reg_l(R_ESP) -= DATA_BYTE;
    swaddr_write(reg_l(R_ESP), 4, cpu.eip + len + 1);
    DATA_TYPE_S imm = op_src -> val;
    print_asm("call %x", cpu.eip + 1 + len + imm);
    cpu.eip = cpu.eip + imm;
    return len + 1;
}

make_helper(concat(call_rm_, SUFFIX)) { 
    int len = concat(decode_rm_, SUFFIX)(cpu.eip + 1);
    reg_l(R_ESP) -= DATA_BYTE;
    swaddr_write(reg_l(R_ESP), 4, cpu.eip + len + 1);
    DATA_TYPE_S imm = op_src -> val;
    print_asm("call %x", imm);
    cpu.eip = imm - len - 1;
    return len + 1;
}

#include "cpu/exec/template-end.h"