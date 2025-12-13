
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

void printBreak(const char*ch, int repeat);

void ResetMPU();
MPU_State getMPUState();

void PrepareForNextTest();

/*********************************************************************************************************************
 * UNIT TESTS
 *********************************************************************************************************************/
bool test_Unknown(uint8_t Mnemonic);
bool test_NOP();
bool test_LSRD();
bool test_LSRD_exec(uint16_t value);
bool test_ASLD();
bool test_ASLD_exec(uint16_t value);
bool test_TAP();
bool test_TAP_exec(uint8_t value);
#endif
