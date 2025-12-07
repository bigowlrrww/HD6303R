#include "MC6803_UNIT.h"
#include "ItemList.h"

//Global Processor pointer
MC6803E_MPU *p;
ItemList list;

int main(int argc, char * argv[])
{
	p = MC6803E_MPU_Alloc();

	initItemList(&list);
	
	// Start execution at 0x4000.
	//p->pc = 0xE000;
	p->pc = 0xE000;

	EnVerbose();

	ALU_MC6803E_Execute(p, 0x00);
	ResetMPU();

	//UNIT Tests
	addItem(&list,"NOP",test_NOP());



	//Provide a sumary of results
	printf("********************************************************************\n\n\n");
	printf("Testing Summary: \n");
	printf("====================================================================\n");
	for (size_t i = 0; i < list.size; i++)
	{
		printf("%s:", list.items[i].name);
		if (list.items[i].flag) PASS();
		else FAIL();
	}

	// Clean up.
	MC6803E_MPU_Free(p);
	freeItemList(&list);
	
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

	return c;
}

/*********************************************************************************************************************
 * UNIT TESTS
 *********************************************************************************************************************/

 bool test_NOP()
 {
	printf("Testing NOP\n");

	bool passAllTests = true;

	printf("\nCase startup NOP\n");
	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x01);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);
	checkVerified(curr.flagRegister);
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister&0x3F), (uint8_t)(curr.flagRegister&0x3F), "Flags");

	
	printf("\nCase Values set NOP\n");

	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	//D should be set already because of A and B
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;

	prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x01);
	curr = getMPUState();

	checkImplemented(curr.flagRegister);
	checkVerified(curr.flagRegister);
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister&0x3F), (uint8_t)(curr.flagRegister&0x3F), "Flags");

	return passAllTests;
 }