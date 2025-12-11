#include "MC6803_UNIT.h"
#include "ItemList.h"

#define PrintH1(fmt, ...) printf("\033[35m" fmt "\033[0m", ##__VA_ARGS__)
#define PrintH2(fmt, ...) printf("\033[36m" fmt "\033[0m", ##__VA_ARGS__)

// Global Processor pointer
MC6803E_MPU *p;
ItemList list;

int main(int argc, char *argv[])
{
	p = MC6803E_MPU_Alloc();

	initItemList(&list);

	// Start execution at 0x4000.
	// p->pc = 0xE000;
	p->pc = 0xE000;

	EnVerbose();

	ResetMPU();

	// UNIT Tests
	//Unknown Opcodes
	addItem(&list, "0x00", test_Unknown(0x00));
	PrepareForNextTest();
	addItem(&list, "0x02", test_Unknown(0x02));
	PrepareForNextTest();
	addItem(&list, "0x03", test_Unknown(0x03));
	PrepareForNextTest();
	addItem(&list, "0x12", test_Unknown(0x12));
	PrepareForNextTest();
	addItem(&list, "0x13", test_Unknown(0x13));
	PrepareForNextTest();
	addItem(&list, "0x14", test_Unknown(0x14));
	PrepareForNextTest();
	addItem(&list, "0x15", test_Unknown(0x15));
	PrepareForNextTest();
	addItem(&list, "0x1C", test_Unknown(0x1C));
	PrepareForNextTest();
	addItem(&list, "0x1D", test_Unknown(0x1D));
	PrepareForNextTest();
	addItem(&list, "0x1E", test_Unknown(0x1E));
	PrepareForNextTest();
	addItem(&list, "0x1F", test_Unknown(0x1F));
	PrepareForNextTest();
	addItem(&list, "0x41", test_Unknown(0x41));
	PrepareForNextTest();
	addItem(&list, "0x42", test_Unknown(0x42));
	PrepareForNextTest();
	addItem(&list, "0x45", test_Unknown(0x45));
	PrepareForNextTest();
	addItem(&list, "0x4B", test_Unknown(0x4B));
	PrepareForNextTest();
	addItem(&list, "0x4E", test_Unknown(0x4E));
	PrepareForNextTest();
	addItem(&list, "0x51", test_Unknown(0x51));
	PrepareForNextTest();
	addItem(&list, "0x52", test_Unknown(0x52));
	PrepareForNextTest();
	addItem(&list, "0x55", test_Unknown(0x55));
	PrepareForNextTest();
	addItem(&list, "0x5B", test_Unknown(0x5B));
	PrepareForNextTest();
	addItem(&list, "0x5E", test_Unknown(0x5E));
	PrepareForNextTest();
	addItem(&list, "0x87", test_Unknown(0x87));
	PrepareForNextTest();
	addItem(&list, "0x8F", test_Unknown(0x8F));
	PrepareForNextTest();
	addItem(&list, "0xC7", test_Unknown(0xC7));
	PrepareForNextTest();
	addItem(&list, "0xCD", test_Unknown(0xCD));
	PrepareForNextTest();
	addItem(&list, "0xCF", test_Unknown(0xCF));
	PrepareForNextTest();

	addItem(&list, "NOP", test_NOP());
	PrepareForNextTest();
	addItem(&list, "LSRD", test_LSRD());

	// Provide a sumary of results
	printBreak("-",70);
	PrintH1("Testing Summary: \n");
	printBreak("=",70);
	bool AllPass = true;
	for (size_t i = 0; i < list.size; i++)
	{
		printf("%s:", list.items[i].name);
		if (list.items[i].flag)
			PASS();
		else
			FAIL();
		AllPass &= list.items[i].flag;
	}
	printBreak("-",70);
	printf("Tested %d of 255 OPCODES\n", list.size);
	if (AllPass) printf("\e[32mAll Passed Yay :)\e[0m\n");
	else printf("\e[31mNot all tests Passed :(\e[0m\n");

	// Clean up.
	MC6803E_MPU_Free(p);
	freeItemList(&list);

	return 0;
}

void printBreak(const char*ch, int repeat)
{
	for(int i = 0; i < repeat; i++)
	{
		printf("%s", ch);
	}
	printf("\n");
}

void PrepareForNextTest()
{
	ResetMPU();
	printBreak("-",70);
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
	memcpy(c.MemoryMap, p->MemoryMap, sizeof(c.MemoryMap));

	return c;
}

/*********************************************************************************************************************
 * UNIT TESTS
 *********************************************************************************************************************/

bool test_Unknown(uint8_t Mnemonic)
{
	PrintH1("Testing 0x%02X\n", Mnemonic);
	printBreak("-",70);
	return verifyUnknownMnemonic(ALU_MC6803E_Execute(p, Mnemonic));
}

bool test_NOP()
{
	PrintH1("Testing NOP\n");
	printBreak("-",70);

	bool passAllTests = true;

	PrintH2("Case startup NOP\n");
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x01);
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
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	PrintH2("\nCase Values set NOP\n");

	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	// D should be set already because of A and B
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;

	prev = getMPUState();
	MemoryWrite(p,p->pc,0x01);
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
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

bool test_LSRD()
{
	PrintH1("Testing LSRD\n");
	printBreak("-",70);

	bool passAllTests = true;

	PrintH2("Carry Not Set LSRD\n");
	passAllTests &= test_LSRD_exec(0xCAD7);

	PrintH2("Carry Set LSRD\n");
	passAllTests &= test_LSRD_exec(0xCADF);

	PrintH2("Clear LSRD\n");
	passAllTests &= test_LSRD_exec(0x0001);

	PrintH2("empty LSRD\n");
	passAllTests &= test_LSRD_exec(0x0000);

	PrintH2("upper set shift LSRD\n");
	passAllTests &= test_LSRD_exec(0xFFFF);
	passAllTests &= CheckSame(*(p->accumulatorD),0x7FFF, "Zero always shift into MSBit");

	return passAllTests;
}

bool test_LSRD_exec(uint16_t value)
{
	bool passAllTests = true;
	*p->accumulatorD = value;
	p->flagRegister |= MC6803E_FLAG_N;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x04);
	ALU_MC6803E_Execute(p, 0x04);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);
	checkVerified(curr.flagRegister);

	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckRSH(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_H); //Same
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_I); //Same

	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N); //Always
	if (!!(curr.flagRegister & MC6803E_FLAG_N)^!!(curr.flagRegister& MC6803E_FLAG_C)) // N xor C == 1?
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);
	
	if (curr.accumulatorD == 0x0000) //Z if all bits are cleared; cleared otherwise
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);

	if (prev.accumulatorD & 0x0001) //before operation lsb of ACCD was set; cleared otherwise
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);

	return passAllTests;
}