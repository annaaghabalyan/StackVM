#include <stdio.h>
#include "stackVM.h"
#include "instructions.h"
#include "interpretator.h"

int main()
{
   printf("%s\n", "Simple add program:");
   printf("%s", "1 + 2 = ");

   int program[] = {  

     CONST_I32, 1,
     CONST_I32, 2,
     ADD_I32, 
     PRINT,
     END

   };

   VM* vm = newVM(program,
                   0,    // start address of main function
                   2);    // locals to be reserved, fib doesn't require them
   run(vm); 

   return 0;
}
