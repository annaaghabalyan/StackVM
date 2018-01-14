#ifndef SVM_INTERPRETATOR
#define SVM_INTERPRETATOR

#define PUSH(vm, v) vm->stack[++vm->sp] = v // push value on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop value from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

void run(VM* vm);

#endif
