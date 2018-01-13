#include <stdlib.h>
#include "stackVM.h"

VM* newVM(int* code,    // pointer to table containing a bytecode to be executed  
    int pc,             // address of instruction to be invoked as first one
    int datasize) {     // total locals size 
    VM* vm = (VM*)malloc(sizeof(VM));
    vm->code = code;
    vm->pc = pc;
    vm->fp = 0;
    vm->sp = -1;
    vm->locals = (int*)malloc(sizeof(int) * datasize);
    vm->stack = (int*)malloc(sizeof(int) * STACK_SIZE);

    return vm;
}

void delVM(VM* vm){
    free(vm->locals);
    free(vm->stack);
    free(vm);
}

