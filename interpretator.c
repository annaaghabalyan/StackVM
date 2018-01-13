#include <stdio.h>
#include "instructions.h"
#include "stackVM.h"

#define PUSH(vm, v) vm->stack[++vm->sp] = v // push value on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop value from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

void run(VM* vm) {  
    do {
        int opcode = NCODE(vm);        // fetch
        int v, addr, offset, a, b, argc, rval;

        switch (opcode) {   // decode

        case HALT: return;  // stop the program

        case CONST_I32:
            v = NCODE(vm);   // get next value from code
            PUSH(vm, v);     // move it on top of the stack
            break;

        case ADD_I32:
            b = POP(vm);        // get second value from top of the stack
            a = POP(vm);        // get first value from top of the stack
            PUSH(vm, a + b);    // add those two values and put result on top of the stack
            break;

        case SUB_I32:
            b = POP(vm);
            a = POP(vm);
            PUSH(vm, a - b);
            break;

        case MUL_I32:
            b = POP(vm);
            a = POP(vm);
            PUSH(vm, a * b);
            break;

        case LT_I32:
            b = POP(vm);
            a = POP(vm);
            PUSH(vm, (a < b) ? 1 : 0); // compare
            break;

        case EQ_I32:
            b = POP(vm);
            a = POP(vm);
            PUSH(vm, (a == b) ? 1 : 0);
            break;

        case JMP:
            vm->pc = NCODE(vm);  // unconditionaly jump with program counter to provided address
            break;

        case JMPT:
            addr = NCODE(vm);  // get address pointer from code
            if (POP(vm)) {      // pop value from top of the stack, and if it's true jump
              vm->pc = addr;
            }
            break;

        case JMPF:
            addr = NCODE(vm);
            if (!POP(vm)) {
              vm->pc = addr;
            }
            break;

        case LOAD:
            offset = NCODE(vm);     // get next value from code to identify local variables offset start on the stack
            PUSH(vm, vm->stack[vm->fp+offset]); // put on the top of the stack variable stored relatively to frame pointer
            break;

        case STORE:
            v = POP(vm);            // get value from top of the stack
            offset = NCODE(vm);     // get the relative pointer address from code
            vm->locals[vm->fp+offset] = v;  // store value at address received relatively to frame pointer
            break;

        case GLOAD:
            addr = POP(vm);            
            v = vm->locals[addr];   // load value from memory of the provided addres
            PUSH(vm, v);           
            break;

        case GSTORE:
            v = POP(vm);
            addr = NCODE(vm);
            vm->locals[addr] = v;
            break;

        case CALL:
            // expect all args to be on the stack
            addr = NCODE(vm); // get next instruction as an address of procedure jump
            argc = NCODE(vm); // number of arguments to load
            PUSH(vm, argc);
            PUSH(vm, vm->fp);
            PUSH(vm, vm->pc);
            vm->fp = vm->sp;
            vm->pc = addr;
            break;

        case RET:
            rval = POP(vm);     // pop return value from top of the stack
            vm->sp = vm->fp;
            vm->pc = POP(vm);
            vm->fp = POP(vm);
            argc = POP(vm);
            vm->sp -= argc;
            PUSH(vm, rval);     // leave return value on top of the stack
            break;

        case POP:
            --vm->sp;
            break;

        case PRINT:
            v = POP(vm);
            printf("%d\n", v);
            break;
        default:
            break;
        }

    }while(1);
}

