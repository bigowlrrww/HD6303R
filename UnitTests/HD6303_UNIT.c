#include "HD6303_UNIT.h"
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
HD6303R_MPU *p;
ItemList list;

int main(int argc, char *argv[])
{
	p = HD6303R_MPU_Alloc();

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
	addItem(&list, "(0x0B) SEV", test_SEV());
	PrepareForNextTest();
	addItem(&list, "(0x0C) CLC", test_CLC());
	PrepareForNextTest();
	addItem(&list, "(0x0D) SEC", test_SEC());
	PrepareForNextTest();
	addItem(&list, "(0x0E) CLI", test_CLI());
	PrepareForNextTest();
	addItem(&list, "(0x0F) SEI", test_SEI());
	PrepareForNextTest();
	addItem(&list, "(0x10) SBA", test_SBA());
	PrepareForNextTest();
	addItem(&list, "(0x11) CBA", test_CBA());
	PrepareForNextTest();
	addItem(&list, "(0x12)", test_Unknown(0x12));
	PrepareForNextTest();
	addItem(&list, "(0x13)", test_Unknown(0x13));
	PrepareForNextTest();
	addItem(&list, "(0x14)", test_Unknown(0x14));
	PrepareForNextTest();
	addItem(&list, "(0x15)", test_Unknown(0x15));
	PrepareForNextTest();
	addItem(&list, "(0x16) TAB", test_TAB());
	PrepareForNextTest();
	addItem(&list, "(0x17) TBA", test_TBA());
	PrepareForNextTest();
	addItem(&list, "(0x18) XGDX", test_XGDX());
	PrepareForNextTest();
	addItem(&list, "(0x19) DAA", test_DAA());
	PrepareForNextTest();
	addItem(&list, "(0x2B) ABA", test_ABA());
	PrepareForNextTest();
	addItem(&list, "(0x1C)", test_Unknown(0x1C));
	PrepareForNextTest();
	addItem(&list, "(0x1D)", test_Unknown(0x1D));
	PrepareForNextTest();
	addItem(&list, "(0x1E)", test_Unknown(0x1E));
	PrepareForNextTest();
	addItem(&list, "(0x1F)", test_Unknown(0x1F));
	PrepareForNextTest();
	addItem(&list, "(0x20) BRA", test_BRA());
	PrepareForNextTest();
	addItem(&list, "(0x21) BRN", test_BRN());
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
	HD6303R_MPU_Free(p);
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
	HD6303R_MPU_Free(p);
	p = HD6303R_MPU_Alloc();
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
	return (verifyUnknownMnemonic(ALU_HD6303R_Execute(p, Mnemonic)) | 0x2);
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
	ALU_HD6303R_Execute(p, 0x01);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
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
	*p->accumulatorD = 0xCAD7;
	p->flagRegister &= ~(HD6303R_FLAG_N | HD6303R_FLAG_C);
	p->flagRegister |= HD6303R_FLAG_Z;
	passAllTests &= test_LSRD_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Carry Set LSRD\n");
	*p->accumulatorD = 0xCADF;
	p->flagRegister &= ~(HD6303R_FLAG_N | HD6303R_FLAG_C | HD6303R_FLAG_V);
	p->flagRegister |= HD6303R_FLAG_Z;
	passAllTests &= test_LSRD_exec();
	printBreak(".",54);

	PrintH2("Clear LSRD\n");
	*p->accumulatorD = 0x0001;
	p->flagRegister &= ~(HD6303R_FLAG_N | HD6303R_FLAG_C | HD6303R_FLAG_V);
	passAllTests &= test_LSRD_exec();
	printBreak(".",54);

	PrintH2("empty LSRD\n");
	*p->accumulatorD = 0x0000;
	p->flagRegister &= ~(HD6303R_FLAG_Z);
	passAllTests &= test_LSRD_exec();
	printBreak(".",54);

	PrintH2("upper set shift LSRD\n");
	*p->accumulatorD = 0xFFFF;
	passAllTests &= test_LSRD_exec();
	passAllTests &= CheckSame(*(p->accumulatorD),0x7FFF, "Zero always shift into MSBit");

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_LSRD_exec()
{
	bool passAllTests = true;
	p->flagRegister |= HD6303R_FLAG_N;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x04);
	ALU_HD6303R_Execute(p, 0x04);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckRSH(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.

	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N); 		//N: Cleared

	if (curr.accumulatorD == 0x0000) 															//Z: if all bits are cleared; cleared otherwise
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	if (!!(curr.flagRegister & HD6303R_FLAG_N)^!!(curr.flagRegister& HD6303R_FLAG_C)) 			// V: Set if, after the completion of the shift operation, N xor C == 1?
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);

	if (prev.accumulatorD & 0x0001) 															//C: Set if, before the operation, the least significant bit of the ACCX or M was set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);

	return passAllTests;
}

uint8_t test_ASLD()
{
	PrintH1("Testing ASLD\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Carry Not Set ASLD\n");
	*p->accumulatorD = 0x7AD7;
	p->flagRegister &= ~(HD6303R_FLAG_N | HD6303R_FLAG_C);
	p->flagRegister |= HD6303R_FLAG_Z | HD6303R_FLAG_V;
	passAllTests &= test_ASLD_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Carry Set ASLD\n");
	*p->accumulatorD = 0xFADF;
	p->flagRegister &= ~(HD6303R_FLAG_N | HD6303R_FLAG_C);
	p->flagRegister |= HD6303R_FLAG_Z | HD6303R_FLAG_V;
	passAllTests &= test_ASLD_exec();
	printBreak(".",54);

	PrintH2("Clear ASLD\n");
	*p->accumulatorD = 0x8000;
	p->flagRegister |= HD6303R_FLAG_V;
	passAllTests &= test_ASLD_exec();
	printBreak(".",54);

	PrintH2("Empty ASLD\n");
	*p->accumulatorD = 0x0000;
	p->flagRegister &= ~(HD6303R_FLAG_Z);
	p->flagRegister |= HD6303R_FLAG_V | HD6303R_FLAG_C | HD6303R_FLAG_N;
	passAllTests &= test_ASLD_exec();
	printBreak(".",54);

	PrintH2("N is set ASLD\n");
	*p->accumulatorD = 0x8000;
	p->flagRegister &= ~(HD6303R_FLAG_Z );
	p->flagRegister |= HD6303R_FLAG_C | HD6303R_FLAG_N| HD6303R_FLAG_V;
	passAllTests &= test_ASLD_exec();
	printBreak(".",54);

	PrintH2("lower set shift ASLD\n");
	*p->accumulatorD = 0xFFFF;
	p->flagRegister |= HD6303R_FLAG_V;
	passAllTests &= test_ASLD_exec();
	passAllTests &= CheckSame(*(p->accumulatorD),0xFFFE, "Zero always shift into LSBit");

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_ASLD_exec()
{
	bool passAllTests = true;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x05);
	ALU_HD6303R_Execute(p, 0x05);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckLSH(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.

	if (curr.accumulatorD & 0x8000)																//N: Set if most significant bit of the result is set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (curr.accumulatorD == 0x0000) 															//Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	if (!!(curr.flagRegister & HD6303R_FLAG_N)^!!(curr.flagRegister& HD6303R_FLAG_C)) 			//V: Set if, after the completion of the shift operation, N xor C == 1?
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);

	if (prev.accumulatorD & 0x8000) 															//C: Set if, before the operation, the most significant bit of the ACCX or M was set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);

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
	p->accumulatorA = 0xEA;
	passAllTests &= test_TAP_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TAP\n");
	p->accumulatorA = 0xD5;
	p->flagRegister = 0xE5;
	passAllTests &= test_TAP_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TAP_exec()
{
	bool passAllTests = true;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x06);
	ALU_HD6303R_Execute(p, 0x06);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckSame(prev.accumulatorA, curr.flagRegister | 0xC0, "AccuA -> CCR"); //Ensure that the top 2 are set, they should be in the processor.

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
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
	p->flagRegister = 0xEA;
	passAllTests &= test_TPA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TPA\n");
	p->accumulatorA = 0xE5;
	p->flagRegister = 0xD5;
	passAllTests &= test_TPA_exec();
	printBreak(".",54);
	
	PrintH2("0x00 TPA\n");
	p->accumulatorA = 0x00;
	p->flagRegister = 0xFE;
	passAllTests &= test_TPA_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TPA_exec()
{
	bool passAllTests = true;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x07);
	ALU_HD6303R_Execute(p, 0x07);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckSame((uint8_t)(prev.flagRegister | 0xC0), curr.accumulatorA, "CC is loaded in Accu A"); //Ensure that the top 2 are set, they should be in the processor.
	passAllTests &= CheckSame((uint8_t)(curr.accumulatorA & 0xC0), (uint8_t)0xC0, "Upper bits set in Accu A");
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
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
	p->flagRegister |= HD6303R_FLAG_Z;
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
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_INX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_INX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x08);
	ALU_HD6303R_Execute(p, 0x08);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckAddition(prev.indexRegister, 1, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.

	if (curr.indexRegister == 0x0000) 															//Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Not affected.

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
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
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
	ALU_HD6303R_Execute(p, 0x09);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSubtraction(prev.indexRegister, 1, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.

	if (curr.indexRegister == 0x0000) 															//Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_CLV()
{
	PrintH1("Testing CLV\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("V not set CLV (WARN is good)\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
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
	ALU_HD6303R_Execute(p, 0x0A);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Cleared.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_SEV()
{
	PrintH1("Testing SEV\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("V not set SEV\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_SEV_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("V already set SEV (WARN is good)\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_SEV_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_SEV_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x0B);
	ALU_HD6303R_Execute(p, 0x0B);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);			//V: Set.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_CLC()
{
	PrintH1("Testing CLC\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("C not set CLC (WARN is good)\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_CLC_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C already set CLC\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_CLC_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_CLC_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x0C);
	ALU_HD6303R_Execute(p, 0x0C);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Cleared.

	return passAllTests;
}

uint8_t test_SEC()
{
	PrintH1("Testing SEC\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("C Not set SEC\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_SEC_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C already set SEC (WARN is good)\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_SEC_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_SEC_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x0D);
	ALU_HD6303R_Execute(p, 0x0D);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);			//C: Set.

	return passAllTests;
}

uint8_t test_CLI()
{
	PrintH1("Testing CLI\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("I not set CLI (WARN is good)\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_I);
	passAllTests &= test_CLI_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("I already set CLI\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_CLI_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_CLI_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x0E);
	ALU_HD6303R_Execute(p, 0x0E);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Cleared.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_SEI()
{
	PrintH1("Testing SEI\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("I Not set SEI\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_I);
	passAllTests &= test_SEI_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("I already set SEI (WARN is good)\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_SEI_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_SEI_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x0F);
	ALU_HD6303R_Execute(p, 0x0F);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		//H: Not affected.
	passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Set.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);		//Z: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);		//V: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);		//C: Not affected.

	return passAllTests;
}

uint8_t test_SBA()
{
	PrintH1("Testing SBA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("No Flags set SBA\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = 0xFF;
	passAllTests &= test_SBA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z Set SBA\n");
	p->accumulatorB = 0x22;
	p->accumulatorA = 0x22;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("N Set SBA\n");
	p->accumulatorB = 0x01;
	p->accumulatorA = 0x81;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_N);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("C Set SBA\n");
	p->accumulatorB = 0x82;
	p->accumulatorA = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("V Set SBA\n");
	p->accumulatorB = 0x01;
	p->accumulatorA = 0x80;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("N/V/C Set SBA\n");
	p->accumulatorB = 0x80;
	p->accumulatorA = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~(HD6303R_FLAG_N|HD6303R_FLAG_V|HD6303R_FLAG_C));
	passAllTests &= test_SBA_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_SBA_exec()
{
	bool passAllTests = true;

	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x10);
	ALU_HD6303R_Execute(p, 0x10);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	passAllTests &= CheckSubtraction(prev.accumulatorA, prev.accumulatorB, curr.accumulatorA, "A-B=R?");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		// H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		// I: Not affected.

	if (curr.accumulatorA & 0x80) 																// N: Set if most significant bit of the result is set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (curr.accumulatorA == 0x00) 																// Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	if (__check_sub_overflow(prev.accumulatorA, prev.accumulatorB)) 					// V: Set if there was two’s complement overflow as a result of the operation.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);

	if (__check_sub_carry(prev.accumulatorA,prev.accumulatorB)) 										// C: Carry is set if the absolute value of accumulator B plus previous Carry is larger than the absolute value of accumulator A; reset otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);

	return passAllTests;
}

uint8_t test_CBA()
{
	PrintH1("Testing CBA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("No Flags set CBA\n");
	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = 0xFF;
	passAllTests &= test_CBA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z Set CBA\n");
	p->accumulatorB = 0x22;
	p->accumulatorA = 0x22;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("N Set CBA\n");
	p->accumulatorB = 0x01;
	p->accumulatorA = 0x81;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_N);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("C Set CBA\n");
	p->accumulatorB = 0x82;
	p->accumulatorA = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("V Set CBA\n");
	p->accumulatorB = 0x01;
	p->accumulatorA = 0x80;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("N/V/C Set CBA\n");
	p->accumulatorB = 0x80;
	p->accumulatorA = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~(HD6303R_FLAG_N|HD6303R_FLAG_V|HD6303R_FLAG_C));
	passAllTests &= test_CBA_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_CBA_exec()
{
	bool passAllTests = true;

	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x11);
	ALU_HD6303R_Execute(p, 0x11);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	uint8_t result = (prev.accumulatorA - prev.accumulatorB);
	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		// H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		// I: Not affected.

	if (result & 0x80) 																// N: Set if most significant bit of the result is set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (result == 0x00) 																// Z: Set if all bits of the result are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	if (__check_sub_overflow(prev.accumulatorA, prev.accumulatorB)) 					// V: Set if there was two’s complement overflow as a result of the operation.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);

	if (__check_sub_carry(prev.accumulatorA,prev.accumulatorB)) 										// C: Carry is set if the absolute value of accumulator B plus previous Carry is larger than the absolute value of accumulator A; reset otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);

	return passAllTests;
}

uint8_t test_TAB()
{
	PrintH1("Testing TAB\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("0xE5 TAB\n");
	p->accumulatorA = 0xE5;
	p->accumulatorB = 0xDA;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TAB_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TAB\n");
	p->accumulatorA = 0xDA;
	p->accumulatorB = 0xE5;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TAB_exec();
	printBreak(".",54);

	PrintH2("N set TAB\n");
	p->accumulatorA = 0x80;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TAB_exec();
	printBreak(".",54);

	PrintH2("Z set TAB\n");
	p->accumulatorA = 0x00;
	p->flagRegister = (0xc0 | HD6303R_FLAG_N | HD6303R_FLAG_V);
	passAllTests &= test_TAB_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TAB_exec()
{
	bool passAllTests = true;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x16);
	ALU_HD6303R_Execute(p, 0x16);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorB, "AccuA -> AccuB"); //Ensure that the top 2 are set, they should be in the processor.

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		// H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		// I: Not affected.

	if (curr.accumulatorB & 0x80) 																			// N: Set if the most significant bit of the contents of the accumulator is set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (curr.accumulatorB == 0x00) 																		// Z: Set if all bits of the accumulator are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V); 		// V: Cleared.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C); 		// C: Not affected.
}
uint8_t test_TBA()
{
	PrintH1("Testing TBA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("0xE5 TBA\n");
	p->accumulatorB = 0xE5;
	p->accumulatorA = 0xDA;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TBA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TBA\n");
	p->accumulatorB = 0xDA;
	p->accumulatorA = 0xE5;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TBA_exec();
	printBreak(".",54);

	PrintH2("N set TBA\n");
	p->accumulatorB = 0x80;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TBA_exec();
	printBreak(".",54);

	PrintH2("Z set TBA\n");
	p->accumulatorB = 0x00;
	p->flagRegister = (0xc0 | HD6303R_FLAG_N | HD6303R_FLAG_V);
	passAllTests &= test_TBA_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TBA_exec()
{
	bool passAllTests = true;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister |= 0xC0;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x17);
	ALU_HD6303R_Execute(p, 0x17);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);

	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorA, "AccuB -> AccuA"); //Ensure that the top 2 are set, they should be in the processor.

	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H); 		// H: Not affected.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		// I: Not affected.

	if (curr.accumulatorA & 0x80) 																			// N: Set if the most significant bit of the contents of the accumulator is set; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (curr.accumulatorA == 0x00) 																		// Z: Set if all bits of the accumulator are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V); 		// V: Cleared.
	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C); 		// C: Not affected.
}

uint8_t test_XGDX()
{
	PrintH1("Testing XGDX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("0xE5E5 XGDX\n");
	*p->accumulatorD = 0xE5E5;
	p->indexRegister = 0xDADA;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_XGDX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDADA XGDX\n");
	*p->accumulatorD = 0xDADA;
	p->indexRegister = 0xE5E5;
	p->flagRegister = (0xc0 | HD6303R_FLAG_N | HD6303R_FLAG_C);
	passAllTests &= test_XGDX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_XGDX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x18);
	ALU_HD6303R_Execute(p, 0x18);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(curr.accumulatorD, prev.indexRegister, "AccuD == prevIX");
	passAllTests &= CheckSame(curr.indexRegister, prev.accumulatorD, "IX == prevAccuD");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_DAA()
{
	PrintH1("Testing DAA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("case1 DAA\n");
	p->accumulatorA = 0x33;
	p->flagRegister = (0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_H | HD6303R_FLAG_Z); //C H
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)1, "FLAG_C was set");
	passAllTests &= CheckSame(p->accumulatorA, 0x99, "Result Correct?");
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("case2 DAA\n");
	p->accumulatorA = 0x2B;
	p->flagRegister = (0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z); //C H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)1, "FLAG_C was set");
	passAllTests &= CheckSame(p->accumulatorA, 0x91, "Result Correct?");
	printBreak(".",54);

	PrintH2("case3 DAA\n");
	p->accumulatorA = 0x27;
	p->flagRegister = (0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z); //C H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)1, "FLAG_C was set");
	passAllTests &= CheckSame(p->accumulatorA, 0x87, "Result Correct?");
	printBreak(".",54);

	PrintH2("case4 DAA\n");
	p->accumulatorA = 0xC3;
	p->flagRegister = (0xC0 | HD6303R_FLAG_H | HD6303R_FLAG_Z | HD6303R_FLAG_N); //C' H
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)1, "FLAG_C was set");
	passAllTests &= CheckSame(p->accumulatorA, 0x29, "Result Correct?");
	printBreak(".",54);

	PrintH2("case5 DAA\n");
	p->accumulatorA = 0x9E;
	p->flagRegister = (0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N); //C' H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)1, "FLAG_C was set");
	passAllTests &= CheckSame(p->accumulatorA, 0x04, "Result Correct?");
	printBreak(".",54);

	PrintH2("case6 DAA\n");
	p->accumulatorA = 0xB7;
	p->flagRegister = (0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N); //C' H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)1, "FLAG_C was set");
	passAllTests &= CheckSame(p->accumulatorA, 0x17, "Result Correct?");
	printBreak(".",54);

	PrintH2("case7 DAA\n");
	p->accumulatorA = 0x93;
	p->flagRegister = (0xC0 | HD6303R_FLAG_H | HD6303R_FLAG_Z); //C' H
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)0, "FLAG_C was unset");
	passAllTests &= CheckSame(p->accumulatorA, 0x99, "Result Correct?");
	printBreak(".",54);

	PrintH2("case8 DAA\n");
	p->accumulatorA = 0x6E;
	p->flagRegister = (0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N); //C' H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)0, "FLAG_C was unset");
	passAllTests &= CheckSame(p->accumulatorA, 0x74, "Result Correct?");
	printBreak(".",54);

	PrintH2("case9 DAA\n");
	p->accumulatorA = 0x24;
	p->flagRegister = (0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N); //C' H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)0, "FLAG_C was unset");
	passAllTests &= CheckSame(p->accumulatorA, 0x24, "Result Correct?");
	printBreak(".",54);

	PrintH2("case10 DAA\n");
	p->accumulatorA = 0x00;
	p->flagRegister = (0xC0 | HD6303R_FLAG_N); //C' H'
	passAllTests &= test_DAA_exec();
	passAllTests &= CheckSame((uint8_t)(p->flagRegister & HD6303R_FLAG_C),(uint8_t)0, "FLAG_C was unset");
	passAllTests &= CheckSame(p->accumulatorA, 0x00, "Result Correct?");

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_DAA_exec()
{
	bool passAllTests = true;
	p->indexRegister = 0xDADA;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x19);
	ALU_HD6303R_Execute(p, 0x19);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "AccB");

//Flag Checks	
	if (curr.accumulatorA & 0x80) 																// N: Set if the MSB of the result is "1", cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (curr.accumulatorA == 0x00) 																// Z: Set if all bits of the accumulator are cleared; cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	return passAllTests;
}


uint8_t test_ABA()
{
	PrintH1("Testing ABA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("No Flags ABA\n");
	p->accumulatorA = 0x33;
	p->accumulatorB = 0x20;
	p->flagRegister = (0xFF);
	passAllTests &= test_ABA_exec();
	passAllTests &= CheckSame(p->accumulatorA, 0x53, "Result Correct?");
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Flag H ABA\n");
	p->accumulatorA = 0x0F;
	p->accumulatorB = 0x0F;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_H);
	passAllTests &= test_ABA_exec();
	passAllTests &= CheckSame(p->accumulatorA, 0x1E, "Result Correct?");
	printBreak(".",54);

	PrintH2("Flag N ABA\n");
	p->accumulatorA = 0x0F;
	p->accumulatorB = 0x80;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_N);
	passAllTests &= test_ABA_exec();
	passAllTests &= CheckSame(p->accumulatorA, 0x8F, "Result Correct?");
	printBreak(".",54);

	PrintH2("Flag Z ABA\n");
	p->accumulatorA = 0x00;
	p->accumulatorB = 0x00;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_ABA_exec();
	passAllTests &= CheckSame(p->accumulatorA, 0x00, "Result Correct?");
	printBreak(".",54);

	PrintH2("Flag V/C ABA\n");
	p->accumulatorA = 0x81;
	p->accumulatorB = 0x82;
	p->flagRegister = (0xFF & ~(HD6303R_FLAG_V|HD6303R_FLAG_C));
	passAllTests &= test_ABA_exec();
	passAllTests &= CheckSame(p->accumulatorA, 0x03, "Result Correct?");
	printBreak(".",54);

	PrintH2("Flag V/N ABA\n");
	p->accumulatorA = 0x40;
	p->accumulatorB = 0x40;
	p->flagRegister = (0xFF & ~(HD6303R_FLAG_V|HD6303R_FLAG_N));
	passAllTests &= test_ABA_exec();
	passAllTests &= CheckSame(p->accumulatorA, 0x80, "Result Correct?");

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_ABA_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x1B);
	ALU_HD6303R_Execute(p, 0x1B);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckAddition(prev.accumulatorA, prev.accumulatorB, curr.accumulatorA, "AccA+AccB");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");

//Flag Checks
	uint8_t result = prev.accumulatorA + prev.accumulatorB;
	bool A3 = prev.accumulatorA & 0x08;
	bool B3 = prev.accumulatorB & 0x08;
	bool R3 = result & 0x08;
	bool A7 = prev.accumulatorA & 0x80;
	bool B7 = prev.accumulatorB & 0x80;
	bool R7 = result & 0x80;

	if (A3 & B3 | B3 & !R3 | !R3 & A3) 															// H: Set if a carry from bit3 is generated
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_H);

	passAllTests &= CheckFlagSame(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_I); 		//I: Not affected
	
	if (R7)
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);		//N: Set if the result's MSB is "1"
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_N);

	if (result == 0x0000)			 															//Z: Set if all bits of the result are cleared
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_Z);

	if (A7 & B7 & !R7 | !A7 & !B7 & R7)															// V: Set if the result overflows
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_V);

	if (A7 & B7 | B7 & !R7 | !R7 & A7) 															// C: Set if a carry from the MSB is generated cleared otherwise.
		passAllTests &= CheckFlagSet(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);
	else
		passAllTests &= CheckFlagUnset(prev.flagRegister, curr.flagRegister, HD6303R_FLAG_C);

	return passAllTests;
}

uint8_t test_BRA()
{
	PrintH1("Testing BRA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Rel 0 BRA\n");
	passAllTests &= test_BRA_exec(0x00);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Rel 8 BRA\n");
	passAllTests &= test_BRA_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BRA\n");
	passAllTests &= test_BRA_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BRA_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x20);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x20);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BRN()
{
	PrintH1("Testing BRN\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Rel 0 BRN\n");
	passAllTests &= test_BRN_exec(0x00);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Rel 8 BRN\n");
	passAllTests &= test_BRN_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BRN\n");
	passAllTests &= test_BRN_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BRN_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x21);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x21);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}