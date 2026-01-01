
#ifndef __LIB6303_H_INCLUDE
#define __LIB6303_H_INCLUDE
//Don't mangle me
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

// HD6303R_MPU_ stuff..
typedef struct _HD6303R_MPU {
	uint16_t pc;
	uint8_t flagRegister;
	uint8_t accumulatorB;
	uint8_t accumulatorA;
	uint16_t * accumulatorD;
	uint16_t indexRegister;
	uint16_t stackPointer;
	uint8_t MemoryMap[0x10000];
	uint8_t lastCommandMneunomicLen;
} HD6303R_MPU;

// HD6303R_MPU_ Functions
HD6303R_MPU * HD6303R_MPU_Alloc();
void HD6303R_MPU_Free(HD6303R_MPU *);
void HD6303R_MPU_PrintRegisters(HD6303R_MPU *);

// ALU Functions
uint8_t		ALU_HD6303R_Fetch(HD6303R_MPU *);
uint16_t	ALU_HD6303R_Execute(HD6303R_MPU *, uint8_t instruction);
char * ALU_HD6303R_GetCurrentMneunomic(HD6303R_MPU * p);
void ALU_HD6303R_PrintCurrentMneunomic(HD6303R_MPU *);

// Memory Functions
uint8_t MemoryRead(HD6303R_MPU *, uint16_t);
uint8_t MemoryWrite(HD6303R_MPU * p, uint16_t address, uint8_t value);

//Helpful flags
#define HD6303R_FLAG_C	(uint8_t)(0x1 << 0)
#define HD6303R_FLAG_V	(uint8_t)(0x1 << 1)
#define HD6303R_FLAG_Z	(uint8_t)(0x1 << 2)
#define HD6303R_FLAG_N	(uint8_t)(0x1 << 3)
#define HD6303R_FLAG_I	(uint8_t)(0x1 << 4)
#define HD6303R_FLAG_H	(uint8_t)(0x1 << 5)
#define HD6303R_FLAG_VERIFIED (uint8_t)(0x1 << 6)
#define HD6303R_FLAG_IMP (uint8_t)(0x1 << 7)

#ifdef __cplusplus
}
#endif

#endif
