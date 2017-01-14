#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include "Interface/interface.h"
#include "Helper/stringhelper.h"

int main(int argc, char* argv[])
{
   STATUS status; 
   status = ZERO_EXIT_STATUS;

   if (argc == 3)
   {
      status = RunMultipleTests(argv[1], argv[2]);
   }
   else if (argc == 2)
   {
      if (EqualStrings(argv[1], "runall") == TRUE)
      {
         status = RunAllTests();
      }
      else
      {
         status = RunSingleTest(argv[1]);
      }
   }
   else
   {
      fprintf_s(stderr, "Invalid number of arguments!\n");
   }
   
   _CrtDumpMemoryLeaks();
   return status;
}
