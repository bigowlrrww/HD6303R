
#ifndef __LIB6803_H_INCLUDE
#define __LIB6803_H_INCLUDE
//Don't mangle me
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

// MC6803E_MPU_ stuff..
typedef struct _MC6803E_MPU {
	uint16_t pc;
	uint8_t flagRegister;
	uint8_t accumulatorA;
	uint8_t accumulatorB;
	uint16_t * accumulatorD;
	uint16_t indexRegister;
	uint16_t stackPointer;
	uint8_t MemoryMap[0x10000];
	uint8_t lastCommandMneunomicLen;
} MC6803E_MPU;

// MC6803E_MPU_ Functions
MC6803E_MPU * MC6803E_MPU_Alloc();
void MC6803E_MPU_Free(MC6803E_MPU *);
void MC6803E_MPU_PrintRegisters(MC6803E_MPU *);

// ALU Functions
uint8_t		ALU_MC6803E_Fetch(MC6803E_MPU *);
uint16_t	ALU_MC6803E_Execute(MC6803E_MPU *, uint8_t instruction);
char * ALU_MC6803E_GetCurrentMneunomic(MC6803E_MPU * p);
void ALU_MC6803E_PrintCurrentMneunomic(MC6803E_MPU *);

// Memory Functions
uint8_t MemoryRead(MC6803E_MPU *, uint16_t);
uint8_t MemoryWrite(MC6803E_MPU * p, uint16_t address, uint8_t value);

//Helpful flags
#define MC6803E_FLAG_C	(uint8_t)(0x1 << 0)
#define MC6803E_FLAG_V	(uint8_t)(0x1 << 1)
#define MC6803E_FLAG_Z	(uint8_t)(0x1 << 2)
#define MC6803E_FLAG_N	(uint8_t)(0x1 << 3)
#define MC6803E_FLAG_I	(uint8_t)(0x1 << 4)
#define MC6803E_FLAG_H	(uint8_t)(0x1 << 5)
#define MC6803E_FLAG_VERIFIED (uint8_t)(0x1 << 6)
#define MC6803E_FLAG_IMP (uint8_t)(0x1 << 7)

#ifdef __cplusplus
}
#endif

#endif
