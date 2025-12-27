#ifndef __MEMORY_H_INCLUDE
#define __MEMORY_H_INCLUDE

#include "HD6303R_Core.h"

#ifdef _WIN32
  #define HD6303R_API __declspec(dllexport)
#else
  #define HD6303R_API
#endif

HD6303R_API uint8_t MemoryRead(HD6303R_MPU *, uint16_t);
HD6303R_API uint8_t MemoryWrite(HD6303R_MPU *, uint16_t, uint8_t);
HD6303R_API uint8_t MemoryWrite16(HD6303R_MPU *, uint16_t, uint16_t);
uint8_t MemoryReadIndexValue(HD6303R_MPU *, uint8_t);
uint8_t MemoryWriteIndexValue(HD6303R_MPU *, uint8_t, uint8_t);
uint8_t MemoryWriteIndexValue16(HD6303R_MPU *, uint8_t, uint16_t);

#endif