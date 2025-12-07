
#ifndef __MAIN_H_INCLUDE
#define __MAIN_H_INCLUDE

#ifndef EXECUTION_DELAY
#	define EXECUTION_DELAY 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <libMC6803E.h>
#include "Tests.h"

void ResetMPU();

typedef struct _MPU_State {
	uint16_t pc;
	uint8_t flagRegister;
	uint8_t accumulatorA;
	uint8_t accumulatorB;
	uint16_t accumulatorD;
	uint16_t indexRegister;
	uint16_t stackPointer;
	uint8_t MemoryMap[0x10000];
} MPU_State;
MPU_State getMPUState();

/*********************************************************************************************************************
 * UNIT TESTS
 *********************************************************************************************************************/

 void test_NOP();


#endif
