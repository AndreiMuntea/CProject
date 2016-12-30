#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include "Interface\interface.h"

int main(int argc, char* argv[])
{
   STATUS status; 
   status = ZERO_EXIT_STATUS;

   if (argc != 2)
   {
      printf("Invalid number of arguments");
      status = 1;
      goto EXIT;
   }

   status = RunSingleTest(argv[1]);

EXIT:
   _CrtDumpMemoryLeaks();
   return status;
}