#include "MC6803_UNIT.h"
#include "ItemList.h"

#define PrintH1(fmt, ...) printf("\033[35m" fmt "\033[0m", ##__VA_ARGS__)
#define PrintH2(fmt, ...) printf("\033[36m" fmt "\033[0m", ##__VA_ARGS__)

bool NOT_VERIFIED()
{
    printf("\033[55G"); 
    printf("\e[33m(NOT_VERIFIED)\e[0m");
    return true;
}

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
	addItem(&list, "(0x00)", test_Unknown(0x00));
	PrepareForNextTest();
	addItem(&list, "(0x01) NOP", test_NOP());
	PrepareForNextTest();
	addItem(&list, "(0x02)", test_Unknown(0x02));
	PrepareForNextTest();
	addItem(&list, "(0x03)", test_Unknown(0x03));
	PrepareForNextTest();
	addItem(&list, "(0x04) LSRD", test_LSRD());
	PrepareForNextTest();
	addItem(&list, "(0x05) ASLD", test_ASLD());
	PrepareForNextTest();
	addItem(&list, "(0x06) TAP", test_TAP());
	PrepareForNextTest();
	addItem(&list, "(0x07) TPA", test_TPA());
	PrepareForNextTest();
	addItem(&list, "(0x08) INX", test_INX());
	PrepareForNextTest();
	addItem(&list, "(0x09) DEX", test_DEX());
	PrepareForNextTest();
	addItem(&list, "(0x0A) CLV", test_CLV());
	PrepareForNextTest();
	addItem(&list, "(0x12)", test_Unknown(0x12));
	PrepareForNextTest();
	addItem(&list, "(0x13)", test_Unknown(0x13));
	PrepareForNextTest();
	addItem(&list, "(0x14)", test_Unknown(0x14));
	PrepareForNextTest();
	addItem(&list, "(0x15)", test_Unknown(0x15));
	PrepareForNextTest();
	addItem(&list, "(0x1C)", test_Unknown(0x1C));
	PrepareForNextTest();
	addItem(&list, "(0x1D)", test_Unknown(0x1D));
	PrepareForNextTest();
	addItem(&list, "(0x1E)", test_Unknown(0x1E));
	PrepareForNextTest();
	addItem(&list, "(0x1F)", test_Unknown(0x1F));
	PrepareForNextTest();
	addItem(&list, "(0x41)", test_Unknown(0x41));
	PrepareForNextTest();
	addItem(&list, "(0x42)", test_Unknown(0x42));
	PrepareForNextTest();
	addItem(&list, "(0x45)", test_Unknown(0x45));
	PrepareForNextTest();
	addItem(&list, "(0x4B)", test_Unknown(0x4B));
	PrepareForNextTest();
	addItem(&list, "(0x4E)", test_Unknown(0x4E));
	PrepareForNextTest();
	addItem(&list, "(0x51)", test_Unknown(0x51));
	PrepareForNextTest();
	addItem(&list, "(0x52)", test_Unknown(0x52));
	PrepareForNextTest();
	addItem(&list, "(0x55)", test_Unknown(0x55));
	PrepareForNextTest();
	addItem(&list, "(0x5B)", test_Unknown(0x5B));
	PrepareForNextTest();
	addItem(&list, "(0x5E)", test_Unknown(0x5E));
	PrepareForNextTest();
	addItem(&list, "(0x87)", test_Unknown(0x87));
	PrepareForNextTest();
	addItem(&list, "(0x8F)", test_Unknown(0x8F));
	PrepareForNextTest();
	addItem(&list, "(0xC7)", test_Unknown(0xC7));
	PrepareForNextTest();
	addItem(&list, "(0xCD)", test_Unknown(0xCD));
	PrepareForNextTest();
	addItem(&list, "(0xCF)", test_Unknown(0xCF));


	// Provide a sumary of results
	printBreak("-",70);
	PrintH1("Testing Summary: \n");
	printBreak("=",70);
	bool AllPass = true;
	for (size_t i = 0; i < list.size; i++)
	{
		printf("%s:", list.items[i].name);
		if (!(list.items[i].flag & 0x02)) NOT_VERIFIED();
		if (list.items[i].flag & 0x01)
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

//Special case, returns uint8_t with verified flag thrown.
uint8_t test_Unknown(uint8_t Mnemonic)
{
	PrintH1("Testing 0x%02X\n", Mnemonic);
	printBreak("-",70);
	return (verifyUnknownMnemonic(ALU_MC6803E_Execute(p, Mnemonic)) | 0x2);
}

uint8_t test_NOP()
{
	PrintH1("Testing NOP\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case startup NOP\n");
	passAllTests &= test_NOP_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case Values set NOP\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_NOP_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_NOP_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x01);
	ALU_MC6803E_Execute(p, 0x01);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_LSRD()
{
	PrintH1("Testing LSRD\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Carry Not Set LSRD\n");
	p->flagRegister &= ~(MC6803E_FLAG_N | MC6803E_FLAG_C);
	p->flagRegister |= MC6803E_FLAG_Z;
	passAllTests &= test_LSRD_exec(0xCAD7);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Carry Set LSRD\n");
	p->flagRegister &= ~(MC6803E_FLAG_N | MC6803E_FLAG_C | MC6803E_FLAG_V);
	p->flagRegister |= MC6803E_FLAG_Z;
	passAllTests &= test_LSRD_exec(0xCADF);
	printBreak(".",54);

	PrintH2("Clear LSRD\n");
	p->flagRegister &= ~(MC6803E_FLAG_N | MC6803E_FLAG_C | MC6803E_FLAG_V);
	passAllTests &= test_LSRD_exec(0x0001);
	printBreak(".",54);

	PrintH2("empty LSRD\n");
	p->flagRegister &= ~(MC6803E_FLAG_Z);
	passAllTests &= test_LSRD_exec(0x0000);
	printBreak(".",54);

	PrintH2("upper set shift LSRD\n");
	passAllTests &= test_LSRD_exec(0xFFFF);
	passAllTests &= CheckSame(*(p->accumulatorD),0x7FFF, "Zero always shift into MSBit");

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_LSRD_exec(uint16_t value)
{
	bool passAllTests = true;
	*p->accumulatorD = value;
	p->flagRegister |= MC6803E_FLAG_N;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x04);
	ALU_MC6803E_Execute(p, 0x04);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);

	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckRSH(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_I); 		//I: Not affected.

	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N); 		//N: Cleared

	if (curr.accumulatorD == 0x0000) 															//Z: if all bits are cleared; cleared otherwise
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);

	if (!!(curr.flagRegister & MC6803E_FLAG_N)^!!(curr.flagRegister& MC6803E_FLAG_C)) 			// V: Set if, after the completion of the shift operation, N xor C == 1?
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);

	if (prev.accumulatorD & 0x0001) 															//C: Set if, before the operation, the least significant bit of the ACCX or M was set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);

	return passAllTests;
}

uint8_t test_ASLD()
{
	PrintH1("Testing ASLD\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Carry Not Set ASLD\n");
	p->flagRegister &= ~(MC6803E_FLAG_N | MC6803E_FLAG_C);
	p->flagRegister |= MC6803E_FLAG_Z | MC6803E_FLAG_V;
	passAllTests &= test_ASLD_exec(0x7AD7);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Carry Set ASLD\n");
	p->flagRegister &= ~(MC6803E_FLAG_N | MC6803E_FLAG_C);
	p->flagRegister |= MC6803E_FLAG_Z | MC6803E_FLAG_V;
	passAllTests &= test_ASLD_exec(0xFADF);
	printBreak(".",54);

	PrintH2("Clear ASLD\n");
	p->flagRegister |= MC6803E_FLAG_V;
	passAllTests &= test_ASLD_exec(0x8000);
	printBreak(".",54);

	PrintH2("Empty ASLD\n");
	p->flagRegister &= ~(MC6803E_FLAG_Z);
	p->flagRegister |= MC6803E_FLAG_V | MC6803E_FLAG_C | MC6803E_FLAG_N;
	passAllTests &= test_ASLD_exec(0x0000);
	printBreak(".",54);

	PrintH2("N is set ASLD\n");
	p->flagRegister &= ~(MC6803E_FLAG_Z );
	p->flagRegister |= MC6803E_FLAG_C | MC6803E_FLAG_N| MC6803E_FLAG_V;
	passAllTests &= test_ASLD_exec(0x8000);
	printBreak(".",54);

	PrintH2("lower set shift ASLD\n");
	p->flagRegister |= MC6803E_FLAG_V;
	passAllTests &= test_ASLD_exec(0xFFFF);
	passAllTests &= CheckSame(*(p->accumulatorD),0xFFFE, "Zero always shift into LSBit");

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_ASLD_exec(uint16_t value)
{
	bool passAllTests = true;
	*p->accumulatorD = value;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x05);
	ALU_MC6803E_Execute(p, 0x05);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);

	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckLSH(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_I); 		//I: Not affected.

	if (curr.accumulatorD & 0x1000)																//N: Set if most significant bit of the result is set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N);

	if (curr.accumulatorD == 0x0000) 															//Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);

	if (!!(curr.flagRegister & MC6803E_FLAG_N)^!!(curr.flagRegister& MC6803E_FLAG_C)) 			//V: Set if, after the completion of the shift operation, N xor C == 1?
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);

	if (prev.accumulatorD & 0x1000) 															//C: Set if, before the operation, the most significant bit of the ACCX or M was set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);

	return passAllTests;
}

uint8_t test_TAP()
{
	PrintH1("Testing TAP\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("0xE5 TAP\n");
	p->flagRegister = 0xD5;
	passAllTests &= test_TAP_exec(0xEA);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TAP\n");
	p->flagRegister = 0xE5;
	passAllTests &= test_TAP_exec(0xD5);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TAP_exec(uint8_t value)
{
	bool passAllTests = true;
	p->accumulatorA = value;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x06);
	ALU_MC6803E_Execute(p, 0x06);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);

	passAllTests &= CheckSame(prev.accumulatorA, curr.flagRegister | 0xC0, "CC is Set"); //Ensure that the top 2 are set, they should be in the processor.

	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
}

uint8_t test_TPA()
{
	PrintH1("Testing TPA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("0xE5 TPA\n");
	p->accumulatorA = 0xD5;
	passAllTests &= test_TPA_exec(0xEA);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TPA\n");
	p->accumulatorA = 0xE5;
	passAllTests &= test_TPA_exec(0xD5);
	printBreak(".",54);
	
	PrintH2("0x00 TPA\n");
	p->accumulatorA = 0x00;
	passAllTests &= test_TPA_exec(0xFE);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TPA_exec(uint8_t value)
{
	bool passAllTests = true;
	p->flagRegister = value;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x07);
	ALU_MC6803E_Execute(p, 0x07);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);

	passAllTests &= CheckSame((uint8_t)(prev.flagRegister | 0xC0), curr.accumulatorA, "CC is loaded in Accu A"); //Ensure that the top 2 are set, they should be in the processor.
	passAllTests &= CheckSame((uint8_t)(curr.accumulatorA & 0xC0), (uint8_t)0xC0, "Upper bits set in Accu A");
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
}

uint8_t test_INX()
{
	PrintH1("Testing INX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;
	PrintH2("startup INX\n");
	p->flagRegister |= MC6803E_FLAG_Z;
	passAllTests &= test_INX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Values set INX\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_INX_exec();
	printBreak(".",54);

	PrintH2("INX rolls over\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xFFFF;
	p->flagRegister = (0xFF & ~MC6803E_FLAG_Z);
	passAllTests &= test_INX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_INX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x08);
	ALU_MC6803E_Execute(p, 0x08);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckAddition(prev.indexRegister, 1, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N);		//N: Not affected.

	if (curr.indexRegister == 0x0000) 															//Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);

	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_DEX()
{
	PrintH1("Testing DEX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("index -> zero DEX\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~MC6803E_FLAG_Z);
	passAllTests &= test_DEX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);


	PrintH2("Values set DEX\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_DEX_exec();
	printBreak(".",54);

	PrintH2("DEX rolls over\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0000;
	p->flagRegister = 0xFF;
	passAllTests &= test_DEX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_DEX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x09);
	ALU_MC6803E_Execute(p, 0x09);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSubtraction(prev.indexRegister, 1, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N);		//N: Not affected.

	if (curr.indexRegister == 0x0000) 															//Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);

	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_CLV()
{
	PrintH1("Testing CLV\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("V not set CLV\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~MC6803E_FLAG_V);
	passAllTests &= test_CLV_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("V already set CLV\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_CLV_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_CLV_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x0A);
	ALU_MC6803E_Execute(p, 0x0A);
	MPU_State curr = getMPUState();

	checkImplemented(curr.flagRegister);
	passAllTests &= checkPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_V);		//V: Cleared.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, MC6803E_FLAG_C);		//C: Not affected.

	return passAllTests;
}