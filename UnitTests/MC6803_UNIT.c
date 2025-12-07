
/*
	MC6803
	This code creates a MC6803E_MPU_ instance, and then loads a ram image from a file.
	It will then call the code in RAM, until the next instruction is 0x00 (EOC), it will then exit.
*/

#include "MC6803_UNIT.h"

//Global Processor pointer
MC6803E_MPU *p;

int main(int argc, char * argv[])
{
	p = MC6803E_MPU_Alloc();
	
	// Start execution at 0x4000.
	//p->pc = 0xE000;
	p->pc = 0xE000;


	ALU_MC6803E_Execute(p, 0x00);
	ResetMPU();

	//UNIT Tests
	test_NOP();

	
	// Clean up.
	MC6803E_MPU_Free(p);
	
	return 0;
}

/**
 * Test a mnemonic that does an operation on 0 bytes proceeding
 */
void ResetMPU()
{
	MC6803E_MPU_Free(p);
	p = MC6803E_MPU_Alloc();
	p->pc = 0xE000;
}

MPU_State getMPUState()
{
	MPU_State c;

	c.pc = p->pc;
	c.flagRegister = p->flagRegister;
	c.accumulatorA = p->accumulatorA;
	c.accumulatorB = p->accumulatorB;
	c.accumulatorD = *p->accumulatorD;
	c.indexRegister = p->indexRegister;
	c.stackPointer = p->stackPointer;
	memcpy(c.MemoryMap,p->MemoryMap,sizeof(c.MemoryMap));
}

/*********************************************************************************************************************
 * UNIT TESTS
 *********************************************************************************************************************/

 void test_NOP()
 {
	printf("Testing NOP\n");
	MPU_State prev = getMPUState();
	MemoryWrite(p, p->pc, 0x01);
	MPU_State curr = getMPUState();

	CheckSame(prev.pc,curr.pc, "PC");
	CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
 }