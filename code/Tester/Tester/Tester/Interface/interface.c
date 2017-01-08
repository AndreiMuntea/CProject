#include "interface.h"

#include <stdlib.h>

#include "../Helper/stringhelper.h"
#include "../Helper/constants.h"

#define MAX_COMMAND_LENGTH    256
#define TEST_NAME_LENGTH      4

STATUS CreateInputFile(char** inputFile, const char* file)
{
   STATUS status;
   char* destination;

   status = ZERO_EXIT_STATUS;
   destination = NULL;

   if (NULL == inputFile)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   status = StringCopy(&destination, IN_FILES_PATH);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = StringAppend(&destination, file);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = StringAppend(&destination, ".in");
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   *inputFile = destination;

EXIT:
   if (!SUCCESS(status))
   {
      free(destination);
      destination = NULL;
   }
   return status;
}

STATUS CreateOutputFile(char** outputFile, const char* file)
{
   STATUS status;
   char* destination;

   status = ZERO_EXIT_STATUS;
   destination = NULL;

   if (NULL == outputFile)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   status = StringCopy(&destination, RES_FILES_PATH);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = StringAppend(&destination, file);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = StringAppend(&destination, ".res");
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   *outputFile = destination;

EXIT:
   if (!SUCCESS(status))
   {
      free(destination);
      destination = NULL;
   }
   return status;
}

STATUS CreateTestFileName(char** outputFile, const char* file)
{
   STATUS status;
   int sz;
   int i, j;
   char* tempFile;

   status = ZERO_EXIT_STATUS;
   sz = Length(file);
   i = 0;
   j = 0;

   if (NULL == outputFile)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempFile = (char*)malloc(TEST_NAME_LENGTH * sizeof(char));
   if (NULL == tempFile)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }
   for (j = sz - 1, i = TEST_NAME_LENGTH - 2; i >= 0 && j >= 0; --i, --j)
   {
      tempFile[i] = file[j];
   }
   
   for (; i >= 0; i--)
   {
      tempFile[i] = '0';
   }
   tempFile[TEST_NAME_LENGTH - 1] = 0;

   *outputFile = tempFile;

EXIT:
   return status;
}

const char* ErrorMessage(STATUS errorStatus)
{

   switch (errorStatus)
   {
   case INVALID_INPUT:
      return INVALID_INPUT_ERR;
   case INVALID_COMMAND:
      return INVALID_COMMAND_ERR;
   case NULL_POINTER:
      return NULL_POINTER_ERR;
   case BAD_ALLOCATION:
      return BAD_ALLOCATION_ERR;
   case FILE_IO_ERROR:
      return FILE_IO_ERR;
   case INVALID_INDEX:
      return OUT_OF_BOUNDS_ERR;
   case STRUCTS_LIMIT_REACHED:
      return STRUCTS_LIMIT_ERR;
   case OPEN_FILE_ERROR:
      return OPEN_FILE_ERR;
   case ITEM_NOT_FOUND:
      return ITEM_NOT_FOUND_ERROR;
   case CAPACITY_LIMIT_REACHED:
      return CAPACITY_FULL_ERR;
   case CURRENT_STRUCTURE_UNDEFINED:
      return UNDEFINED_STRUCTURE;
   case PREVIOUS_STRUCTURE_UNDEFINED:
      return UNDEFINED_PREVIOUS;
   case BUFFER_OVERFLOW:
      return INVALID_COMMAND_ERR;
   default:
      return UNDEFINED_ERROR;
   }

}

void TreatFatalError(STATUS errorStatus)
{
   fprintf_s(stderr, "%s : %s \n%s\n", INTERNAL_ERROR_OCCURED, ErrorMessage(errorStatus), TERMINATE_EXECUTION);
}

STATUS TreatError(PMY_INTERFACE myInterface, STATUS errorStatus)
{
   STATUS status;
   int err;

   err = 0;
   status = ZERO_EXIT_STATUS;

   if (INTERNAL_ERROR(errorStatus))
   {
      status = errorStatus;
      goto EXIT;
   }

   err = fprintf_s(myInterface->outputFile, "%s\n", ErrorMessage(errorStatus));
   if (err < 0)
   {
      status = FILE_IO_ERROR;
   }


EXIT:
   return status;
}


STATUS InterfaceCreate(PMY_INTERFACE* myInterface, const char* file)
{
   STATUS status;
   PMY_INTERFACE tempInterface;
   FILE* outputFile;
   char* outputFileName;
   char* inputFileName;
   int err;

   err = 0;
   inputFileName = NULL;
   outputFileName = NULL;
   outputFile = NULL;
   tempInterface = NULL;
   status = ZERO_EXIT_STATUS;

   if (NULL == myInterface)
   {
      status = NULL_POINTER;
      goto EXIT;
   }

   tempInterface = (PMY_INTERFACE)malloc(sizeof(MY_INTERFACE));
   if (NULL == tempInterface)
   {
      status = BAD_ALLOCATION;
      goto EXIT;
   }

   tempInterface->vectorController = NULL;
   tempInterface->listController = NULL;
   tempInterface->hashController = NULL;
   tempInterface->heapController = NULL;
   tempInterface->treeController = NULL;
   tempInterface->parser = NULL;
   tempInterface->outputFile = NULL;

   status = CreateInputFile(&inputFileName, file);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = CreateOutputFile(&outputFileName, file);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = ParserCreate(&(tempInterface->parser), inputFileName);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }


   err = fopen_s(&outputFile, outputFileName, "w");
   if (err != 0)
   {
      status = OPEN_FILE_ERROR;
      goto EXIT;
   }

   status = VectorControllerCreate(&(tempInterface->vectorController));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = DoubleLinkedListControllerCreate(&(tempInterface->listController));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }
   
   status = HashTableControllerCreate(&(tempInterface->hashController));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = HeapControllerCreate(&(tempInterface->heapController));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = BalancedSearchTreeControllerCreate(&(tempInterface->treeController));
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   tempInterface->outputFile = outputFile;
   *myInterface = tempInterface;

EXIT:
   if (!SUCCESS(status))
   {
      InterfaceDestroy(&tempInterface);
   }

   free(outputFileName);
   outputFileName = NULL;

   free(inputFileName);
   inputFileName = NULL;
   
   return status;
}

void InterfaceDestroy(PMY_INTERFACE* myInterface)
{
   PMY_INTERFACE tempInterface;

   tempInterface = NULL;

   if (NULL == myInterface)
   {
      goto EXIT;
   }

   tempInterface = *myInterface;
   if (NULL == tempInterface)
   {
      goto EXIT;
   }

   ParserDestroy(&(tempInterface->parser));

   VectorControllerDestroy(&(tempInterface->vectorController));
   DoubleLinkedListControllerDestroy(&(tempInterface->listController));
   HashTableControllerDestroy(&(tempInterface->hashController));
   HeapControllerDestroy(&(tempInterface->heapController));
   BalancedSearchTreeControllerDestroy(&(tempInterface->treeController));

   if (NULL != tempInterface->outputFile)
   {
      fclose(tempInterface->outputFile);
      tempInterface->outputFile = NULL;
   }

   free(*myInterface);
   *myInterface = NULL;
EXIT:
   return;
}

STATUS AnalyzeCommand(PMY_INTERFACE myInterface, const char* command)
{
   STATUS status, flushStatus;

   status = ZERO_EXIT_STATUS;
   flushStatus = ZERO_EXIT_STATUS;

   if (EqualStrings(command, VECTOR_READ) == TRUE)
   {
      status = VectorRead(myInterface->vectorController, myInterface->parser);
   }
   else if (EqualStrings(command, VECTOR_PRINT) == TRUE)
   {
      status = VectorPrint(myInterface->vectorController, myInterface->outputFile);
      goto EXIT;
   }
   else if (EqualStrings(command, VECTOR_GO_TO) == TRUE)
   {
      status = VectorGoTo(myInterface->vectorController, myInterface->parser);
   }
   else if (EqualStrings(command, VECTOR_LENGHT) == TRUE)
   {
      status = VectorLength(myInterface->vectorController, myInterface->outputFile);
      goto EXIT;
   }
   else if (EqualStrings(command, VECTOR_SEARCH) == TRUE)
   {
      status = VectorSearch(myInterface->vectorController, myInterface->parser, myInterface->outputFile);
   }
   else if (EqualStrings(command, VECTOR_REMOVE_POSITION) == TRUE)
   {
      status = VectorRemovePosition(myInterface->vectorController, myInterface->parser);
   }
   else if (EqualStrings(command, VECTOR_REMOVE_VALUE) == TRUE)
   {
      status = VectorRemoveValue(myInterface->vectorController, myInterface->parser);
   }
   else if (EqualStrings(command, VECTOR_ADD) == TRUE)
   {
      status = VectorAdd(myInterface->vectorController, myInterface->parser);
   }
   else if (EqualStrings(command, LIST_READ) == TRUE)
   {
      status = ListRead(myInterface->listController, myInterface->parser);
   }
   else if (EqualStrings(command, LIST_GO_TO) == TRUE)
   {
      status = ListGoTo(myInterface->listController, myInterface->parser);
   }
   else if (EqualStrings(command, LIST_PRINT) == TRUE)
   {
      status = ListPrint(myInterface->listController, myInterface->outputFile);
      goto EXIT;
   }
   else if (EqualStrings(command, LIST_MERGE) == TRUE)
   {
      status = ListMerge(myInterface->listController);
      goto EXIT;
   }
   else if (EqualStrings(command, LIST_SORT) == TRUE)
   {
      status = ListSort(myInterface->listController);
      goto EXIT;
   }
   else if (EqualStrings(command, LIST_ADD) == TRUE)
   {
      status = ListAdd(myInterface->listController, myInterface->parser);
   }
   else if (EqualStrings(command, HASH_TABLE_READ) == TRUE)
   {
      status = HashTableRead(myInterface->hashController, myInterface->parser);
   }
   else if (EqualStrings(command, HASH_TABLE_SEARCH) == TRUE)
   {
      status = HashTableSearch(myInterface->hashController, myInterface->parser, myInterface->outputFile);
   }
   else if (EqualStrings(command, HASH_TABLE_GO_TO) == TRUE)
   {
      status = HashTableGoTo(myInterface->hashController, myInterface->parser);
   }
   else if (EqualStrings(command, HEAP_READ) == TRUE)
   {
      status = HeapRead(myInterface->heapController, myInterface->parser);
   }
   else if (EqualStrings(command, HEAP_INSERT) == TRUE)
   {
      status = HeapInsert(myInterface->heapController, myInterface->parser);
   }
   else if (EqualStrings(command, HEAP_GO_TO) == TRUE)
   {
      status = HeapGoTo(myInterface->heapController, myInterface->parser);
   }
   else if (EqualStrings(command, HEAP_REMOVE) == TRUE)
   {
      status = HeapRemove(myInterface->heapController, myInterface->outputFile);
      goto EXIT;
   }
   else if (EqualStrings(command, TREE_INSERT) == TRUE)
   {
      status = BalancedTreeInsert(myInterface->treeController, myInterface->parser);
   }
   else if (EqualStrings(command, TREE_READ) == TRUE)
   {
      status = BalancedTreeRead(myInterface->treeController, myInterface->parser);
   }
   else if (EqualStrings(command, TREE_REMOVE) == TRUE)
   {
      status = BalancedTreeRemove(myInterface->treeController, myInterface->parser);
   }
   else if (EqualStrings(command, TREE_GO_TO) == TRUE)
   {
      status = BalancedTreeGoTo(myInterface->treeController, myInterface->parser);
   }
   else if (EqualStrings(command, TREE_SEARCH) == TRUE)
   {
      status = BalancedTreeSearch(myInterface->treeController, myInterface->parser, myInterface->outputFile);
   }
   else
   {
      status = INVALID_COMMAND;
   }

   flushStatus = ParserFlushLine(myInterface->parser);
   if (SUCCESS(status))
   {
      status = flushStatus;
   }

EXIT:
   if (!SUCCESS(status))
   {
      status = TreatError(myInterface, status);
   }
   return status;
}

STATUS RunSingleTest(const char* fileName)
{
   STATUS status;
   PMY_INTERFACE myInterface;
   char* command;
   char* file;

   status = ZERO_EXIT_STATUS;
   myInterface = NULL;
   command = NULL;
   file = NULL;

   status = CreateTestFileName(&file, fileName);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   status = InterfaceCreate(&myInterface, file);
   if (!SUCCESS(status))
   {
      goto EXIT;
   }

   while (SUCCESS(status))
   {
      status = ParserNextString(myInterface->parser, &command, MAX_COMMAND_LENGTH);
      if (INTERNAL_ERROR(status))
      {
         goto EXIT;
      }

      if (!SUCCESS(status))
      {
         status = ParserFlushLine(myInterface->parser);
         if (INTERNAL_ERROR(status))
         {
            goto EXIT;
         }
         status = ParserFlushLine(myInterface->parser);
         if (INTERNAL_ERROR(status))
         {
            goto EXIT;
         }
         status = INVALID_COMMAND;
         status = TreatError(myInterface, status);
      }
      else
      {
         status = ParserFlushLine(myInterface->parser);
         if (INTERNAL_ERROR(status))
         {
            goto EXIT;
         }
         status = AnalyzeCommand(myInterface, command);
      }
      free(command);
      command = NULL;
      
      if (EndOfFile(myInterface->parser) == TRUE)
      {
         break;
      }
   }


EXIT:
   
   if (!SUCCESS(status))
   {
      TreatFatalError(status);
   }

   free(file);
   InterfaceDestroy(&myInterface);
   return status;
}
