#include <stdio.h>
#include "stackVM.h"
#include "instructions.h"
#include "interpretator.h"

int main()
{
   printf("%s\n", "Call Multiplication procedure:");
   printf("%s", "2 * 10 = ");

   const int Mul = 0;

   int program[] = {
     // comments in right show opcode instruction address they will be used 
     // for conditional jumps and procedure calls

     LOAD, -3,     // 0
     CONST_I32, 2, // 2
     MUL_I32,      // 4
     RET,          // 5

     CONST_I32, 10, // 6
     CALL, Mul, 1,
     PRINT, 
     END

   };

   VM* vm = newVM(program,
                   6,    // start address of main function
                   0);   // locals
   run(vm);

   delVM(vm);

   return 0;
}
