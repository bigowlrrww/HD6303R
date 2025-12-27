#ifndef __MEMORY_H_INCLUDE
#define __MEMORY_H_INCLUDE

#include "MC6803E_Core.h"

#ifdef _WIN32
  #define MC6803E_API __declspec(dllexport)
#else
  #define MC6803E_API
#endif

MC6803E_API uint8_t MemoryRead(MC6803E_MPU *, uint16_t);
MC6803E_API uint8_t MemoryWrite(MC6803E_MPU *, uint16_t, uint8_t);
MC6803E_API uint8_t MemoryWrite16(MC6803E_MPU *, uint16_t, uint16_t);
uint8_t MemoryReadIndexValue(MC6803E_MPU *, uint8_t);
uint8_t MemoryWriteIndexValue(MC6803E_MPU *, uint8_t, uint8_t);
uint8_t MemoryWriteIndexValue16(MC6803E_MPU *, uint8_t, uint16_t);

#endif