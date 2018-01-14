#ifndef STACK_VIRTUAL_MACHINE
#define STACK_VIRTUAL_MACHINE

#include <stdlib.h>

#define STACK_SIZE 100

typedef struct {  
    int* locals;    // local scoped data
    int* code;      // array od byte codes to be executed
    int* stack;     // virtual stack
    int pc;         // program counter (aka. IP - instruction pointer)
    int sp;         // stack pointer
    int fp;         // frame pointer (for local scope)
} VM;


VM* newVM(int* code, int pc, int datasize);

void delVM(VM* vm);

#endif
