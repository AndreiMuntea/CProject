#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Windows.h>

typedef long STATUS;

#define ERROR_BITS                  0xFFFF0000
#define WARNING_BITS                0x0000FFFF
#define INTERNAL_ERROR_BITS         0xF0000000

#define ZERO_EXIT_STATUS            0x00000000
#define SUCCESS(status)             (!((status) & ERROR_BITS))
#define INTERNAL_ERROR(status)      ((status) & INTERNAL_ERROR_BITS)

#define BAD_ALLOCATION              0x10000000
#define NULL_POINTER                0x20000000
#define FILE_IO_ERROR               0x30000000

#define INVALID_INDEX               0x00010000
#define ITEM_NOT_FOUND              0x00020000


#endif //DEFINITIONS_H
