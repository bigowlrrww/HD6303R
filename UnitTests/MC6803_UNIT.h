
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
bool test_AIM();
bool test_OIM();
bool test_EIM();
bool test_TIM();

// Load/Store
bool test_LDAA();
bool test_LDAB();
bool test_STAA();
bool test_STAB();

// Arithmetic
bool test_ADDA();
bool test_ADDB();
bool test_SUBA();
bool test_SUBB();

// Logic
bool test_ANDA();
bool test_ANDB();
bool test_ORAA();
bool test_ORAB();
bool test_EORA();
bool test_EORB();


#endif
