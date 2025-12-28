
#ifndef __MAIN_H_INCLUDE
#define __MAIN_H_INCLUDE

#ifndef EXECUTION_DELAY
#	define EXECUTION_DELAY 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <libHD6303R.h>
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
uint8_t test_Unknown(uint8_t Mnemonic);
uint8_t test_NOP();
bool test_NOP_exec();
uint8_t test_LSRD();
bool test_LSRD_exec();
uint8_t test_ASLD();
bool test_ASLD_exec();
uint8_t test_TAP();
bool test_TAP_exec();
uint8_t test_TPA();
bool test_TPA_exec();
uint8_t test_INX();
bool test_INX_exec();
uint8_t test_DEX();
bool test_DEX_exec();
uint8_t test_CLV();
bool test_CLV_exec();
uint8_t test_SEV();
bool test_SEV_exec();
uint8_t test_CLC();
bool test_CLC_exec();
uint8_t test_SEC();
bool test_SEC_exec();
uint8_t test_CLI();
bool test_CLI_exec();
uint8_t test_SEI();
bool test_SEI_exec();
uint8_t test_SBA();
bool test_SBA_exec();
uint8_t test_CBA();
bool test_CBA_exec();
uint8_t test_TAB();
bool test_TAB_exec();
uint8_t test_TBA();
bool test_TBA_exec();
uint8_t test_XGDX();
bool test_XGDX_exec();
uint8_t test_DAA();
bool test_DAA_exec();
uint8_t test_ABA();
bool test_ABA_exec();
uint8_t test_BRA();
bool test_BRA_exec(int8_t Rel);
#endif
