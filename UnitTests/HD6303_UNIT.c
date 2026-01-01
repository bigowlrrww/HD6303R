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
	addItem(&list, "(0x1A) SLP", 0x7); //Not implemented, or tested atm. Involves interrupts
	PrepareForNextTest();
	addItem(&list, "(0x1B) ABA", test_ABA());
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
	addItem(&list, "(0x22) BHI", test_BHI());
	PrepareForNextTest();
	addItem(&list, "(0x23) BLS", test_BLS());
	PrepareForNextTest();
	addItem(&list, "(0x24) BCC", test_BCC());
	PrepareForNextTest();
	addItem(&list, "(0x25) BCS", test_BCS());
	PrepareForNextTest();
	addItem(&list, "(0x26) BNE", test_BNE());
	PrepareForNextTest();
	addItem(&list, "(0x27) BEQ", test_BEQ());
	PrepareForNextTest();
	addItem(&list, "(0x28) BVC", test_BVC());
	PrepareForNextTest();
	addItem(&list, "(0x29) BVS", test_BVS());
	PrepareForNextTest();
	addItem(&list, "(0x2A) BPL", test_BPL());
	PrepareForNextTest();
	addItem(&list, "(0x2B) BMI", test_BMI());
	PrepareForNextTest();
	addItem(&list, "(0x2C) BGE", test_BGE());
	PrepareForNextTest();
	addItem(&list, "(0x2D) BLT", test_BLT());
	PrepareForNextTest();
	addItem(&list, "(0x2E) BGT", test_BGT());
	PrepareForNextTest();
	addItem(&list, "(0x2F) BLE", test_BLE());
	PrepareForNextTest();
	addItem(&list, "(0x30) TSX", test_TSX());
	PrepareForNextTest();
	addItem(&list, "(0x31) INS", test_INS());
	PrepareForNextTest();
	addItem(&list, "(0x32) PULA", test_PULA());
	PrepareForNextTest();
	addItem(&list, "(0x33) PULB", test_PULB());
	PrepareForNextTest();
	addItem(&list, "(0x34) DES", test_DES());
	PrepareForNextTest();
	addItem(&list, "(0x35) TXS", test_TXS());
	PrepareForNextTest();
	addItem(&list, "(0x36) PSHA", test_PSHA());
	PrepareForNextTest();
	addItem(&list, "(0x37) PSHB", test_PSHB());
	PrepareForNextTest();
	addItem(&list, "(0x38) PULX", test_PULX());
	PrepareForNextTest();
	addItem(&list, "(0x39) RTS", test_RTS());
	PrepareForNextTest();
	addItem(&list, "(0x3A) ABX", test_ABX());
	PrepareForNextTest();
	addItem(&list, "(0x3B) RTI", test_RTI());
	PrepareForNextTest();
	addItem(&list, "(0x3C) PSHX", test_PSHX());
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
		if ((list.items[i].flag & 0x01) && !(list.items[i].flag & 0x04))
			PASS();
		else if (list.items[i].flag & 0x04)
		{
			printf("\033[50G"); 
			printf("\e[33mNOT TESTED\e[0m\n");
		}
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_INX_exec();
	printBreak(".",54);

	PrintH2("INX rolls over\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_DEX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);


	PrintH2("Values set DEX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_DEX_exec();
	printBreak(".",54);

	PrintH2("DEX rolls over\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_CLV_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("V already set CLV\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_SEV_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("V already set SEV (WARN is good)\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_CLC_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C already set CLC\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_SEC_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C already set SEC (WARN is good)\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_I);
	passAllTests &= test_CLI_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("I already set CLI\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_I);
	passAllTests &= test_SEI_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("I already set SEI (WARN is good)\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = 0xFF;
	passAllTests &= test_SBA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z Set SBA\n");
	p->accumulatorA = 0x22;
	p->accumulatorB = 0x22;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("N Set SBA\n");
	p->accumulatorA = 0x81;
	p->accumulatorB = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_N);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("C Set SBA\n");
	p->accumulatorA = 0x01;
	p->accumulatorB = 0x82;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("V Set SBA\n");
	p->accumulatorA = 0x80;
	p->accumulatorB = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_SBA_exec();
	printBreak(".",54);

	PrintH2("N/V/C Set SBA\n");
	p->accumulatorA = 0x01;
	p->accumulatorB = 0x80;
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
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = 0xFF;
	passAllTests &= test_CBA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z Set CBA\n");
	p->accumulatorA = 0x22;
	p->accumulatorB = 0x22;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_Z);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("N Set CBA\n");
	p->accumulatorA = 0x81;
	p->accumulatorB = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_N);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("C Set CBA\n");
	p->accumulatorA = 0x01;
	p->accumulatorB = 0x82;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_C);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("V Set CBA\n");
	p->accumulatorA = 0x80;
	p->accumulatorB = 0x01;
	p->stackPointer = 0x5678;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_CBA_exec();
	printBreak(".",54);

	PrintH2("N/V/C Set CBA\n");
	p->accumulatorA = 0x01;
	p->accumulatorB = 0x80;
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
	p->accumulatorA = 0xDA;
	p->accumulatorB = 0xE5;
	p->flagRegister = (0xc0 | HD6303R_FLAG_Z | HD6303R_FLAG_V);
	passAllTests &= test_TBA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("0xDA TBA\n");
	p->accumulatorA = 0xE5;
	p->accumulatorB = 0xDA;
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

uint8_t test_BHI()
{
	PrintH1("Testing BHI\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Rel 0 BHI\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BHI_exec(0x00);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);
	
	PrintH2("C Z' No Jump BHI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BHI_exec(0x10);
	printBreak(".",54);

	PrintH2("C' Z No Jump BHI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BHI_exec(0x10);
	printBreak(".",54);

	PrintH2("C' Z' No Jump BHI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z;
	passAllTests &= test_BHI_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 8 BHI\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BHI_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BHI\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BHI_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BHI_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x22);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x22);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_C | HD6303R_FLAG_Z)) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BLS()
{
	PrintH1("Testing BLS\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("C Z' Jump BLS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BLS_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C' Z Jump BLS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BLS_exec(0x10);
	printBreak(".",54);

	PrintH2("C Z Jump BLS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z;
	passAllTests &= test_BLS_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BLS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z;
	passAllTests &= test_BLS_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BLS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z;
	passAllTests &= test_BLS_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BLS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C | HD6303R_FLAG_Z;
	passAllTests &= test_BLS_exec(0xF7);

	PrintH2("C' Z' No Jump BLS\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BLS_exec(0x10);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BLS_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x23);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x23);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_C | HD6303R_FLAG_Z)) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BCC()
{
	PrintH1("Testing BCC\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("C No Jump BCC\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BCC_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C' Jump BCC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BCC_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BCC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BCC_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BCC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BCC_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BCC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BCC_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BCC_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x24);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x24);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_C)) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BCS()
{
	PrintH1("Testing BCS\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("C Jump BCS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BCS_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("C' No Jump BCS\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BCS_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BCS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BCS_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BCS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BCS_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BCS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_C;
	passAllTests &= test_BCS_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BCS_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x25);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x25);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_C)) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BNE()
{
	PrintH1("Testing BNE\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Z No Jump BNE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BNE_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z' Jump BNE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BNE_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BNE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BNE_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BNE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BNE_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BNE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BNE_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BNE_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x26);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x26);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_Z)) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BEQ()
{
	PrintH1("Testing BEQ\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Z Jump BEQ\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BEQ_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z' No Jump BEQ\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BEQ_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BEQ\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BEQ_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BEQ\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BEQ_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BEQ\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BEQ_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BEQ_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x27);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x27);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_Z)) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BVC()
{
	PrintH1("Testing BVC\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("V No Jump BVC\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BVC_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("V' Jump BVC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BVC_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BVC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BVC_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BVC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BVC_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BVC\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BVC_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BVC_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x28);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x28);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_V)) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BVS()
{
	PrintH1("Testing BVS\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("V Jump BVS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BVS_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("V' No Jump BVS\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BVS_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BVS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BVS_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BVS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BVS_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BVS\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BVS_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BVS_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x29);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x29);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_V)) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BPL()
{
	PrintH1("Testing BPL\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("N No Jump BPL\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BPL_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("N' Jump BPL\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BPL_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BPL\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BPL_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BPL\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BPL_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BPL\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BPL_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BPL_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x2A);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x2A);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_N)) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BMI()
{
	PrintH1("Testing BMI\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("N Jump BMI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BMI_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("N' No Jump BMI\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BMI_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BMI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BMI_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BMI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BMI_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BMI\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BMI_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BMI_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x2B);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x2B);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((prev.flagRegister & (HD6303R_FLAG_N)) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BGE()
{
	PrintH1("Testing BGE\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("N V Jump BGE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N | HD6303R_FLAG_V;
	passAllTests &= test_BGE_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("N' V No Jump BGE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BGE_exec(0x10);
	printBreak(".",54);

	PrintH2("N V' No Jump BGE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BGE_exec(0x10);
	printBreak(".",54);

	PrintH2("N' V' Jump BGE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGE_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BGE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGE_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BGE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGE_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BGE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGE_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BGE_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x2C);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x2C);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((!!(prev.flagRegister & (HD6303R_FLAG_N))^!!(prev.flagRegister & (HD6303R_FLAG_V))) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BLT()
{
	PrintH1("Testing BLT\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("N V No Jump BLT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N | HD6303R_FLAG_V;
	passAllTests &= test_BLT_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("N' V Jump BLT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BLT_exec(0x10);
	printBreak(".",54);

	PrintH2("N V' Jump BLT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BLT_exec(0x10);
	printBreak(".",54);

	PrintH2("N' V' No Jump BLT\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BLT_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BLT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BLT_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BLT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BLT_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BLT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BLT_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BLT_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x2D);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x2D);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((!!(prev.flagRegister & (HD6303R_FLAG_N))^!!(prev.flagRegister & (HD6303R_FLAG_V))) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BGT()
{
	PrintH1("Testing BGT\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Z N V No Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N | HD6303R_FLAG_V;
	passAllTests &= test_BGT_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z N' V No Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_V;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z N V' No Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z N' V' No Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);

	PrintH2("Z' N V Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N | HD6303R_FLAG_V;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);

	PrintH2("Z' N' V No Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z' N V' No Jump BGT\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z' N' V' Jump BGT\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGT_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BGT\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGT_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BGT\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGT_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BGT\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BGT_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BGT_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x2E);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x2E);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((!!(prev.flagRegister & (HD6303R_FLAG_Z)) | !!(prev.flagRegister & (HD6303R_FLAG_N))^!!(prev.flagRegister & (HD6303R_FLAG_V))) == 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_BLE()
{
	PrintH1("Testing BLE\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Z N V Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N | HD6303R_FLAG_V;
	passAllTests &= test_BLE_exec(0x10);
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Z N' V Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_V;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z N V' Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z | HD6303R_FLAG_N;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z N' V' Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_Z;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);

	PrintH2("Z' N V No Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N | HD6303R_FLAG_V;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);

	PrintH2("Z' N' V Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_V;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z' N V' Jump BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);
	
	PrintH2("Z' N' V' No Jump BLE\n");
	p->flagRegister = 0xC0;
	passAllTests &= test_BLE_exec(0x10);
	printBreak(".",54);

	PrintH2("Rel 0 BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BLE_exec(0x00);
	printBreak(".",54);

	PrintH2("Rel 8 BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BLE_exec(0x08);
	printBreak(".",54);

	PrintH2("Rel -9 BLE\n");
	p->flagRegister = 0xC0 | HD6303R_FLAG_N;
	passAllTests &= test_BLE_exec(0xF7);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_BLE_exec(int8_t Rel)
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x2F);
	MemoryWrite(p,p->pc+1,(uint8_t)Rel);
	ALU_HD6303R_Execute(p, 0x2F);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	if ((!!(prev.flagRegister & (HD6303R_FLAG_Z)) | !!(prev.flagRegister & (HD6303R_FLAG_N))^!!(prev.flagRegister & (HD6303R_FLAG_V))) != 0)
		passAllTests &= CheckPC(prev.pc, curr.pc, 2 + Rel);
	else
		passAllTests &= CheckPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, prev.indexRegister, "Index");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_TSX()
{
	PrintH1("Testing TSX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("SP=0x0010 TSX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_TSX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("SP=0x3FF2 TSX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x3FF2;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_TSX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TSX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x30);
	ALU_HD6303R_Execute(p, 0x30);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckAddition(prev.stackPointer, 1, curr.indexRegister, "SP+1=Index");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_INS()
{
	PrintH1("Testing INS\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("SP=0x0010 INS\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_INS_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("SP=0xFFFF INS\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0xFFFF;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_INS_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_INS_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x31);
	ALU_HD6303R_Execute(p, 0x31);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckAddition(prev.stackPointer, 1, curr.stackPointer, "SP+1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_PULA()
{
	PrintH1("Testing PULA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 PULA\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_PULA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 PULA\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0xFFFF;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xEF);
	passAllTests &= test_PULA_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_PULA_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x32);
	ALU_HD6303R_Execute(p, 0x32);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(curr.accumulatorA, MemoryRead(p, prev.stackPointer+1), "AccA = (SP+1)");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckAddition(prev.stackPointer, 1, curr.stackPointer, "SP+1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_PULB()
{
	PrintH1("Testing PULB\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 PULB\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_PULB_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 PULB\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0xFFFF;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xEF);
	passAllTests &= test_PULB_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_PULB_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x33);
	ALU_HD6303R_Execute(p, 0x33);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(curr.accumulatorB, MemoryRead(p, prev.stackPointer+1), "AccB = (SP+1)");
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckAddition(prev.stackPointer, 1, curr.stackPointer, "SP+1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_DES()
{
	PrintH1("Testing DES\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("SP=0x0010 DES\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_DES_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("SP=0x0000 DES\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0000;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_DES_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_DES_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x34);
	ALU_HD6303R_Execute(p, 0x34);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSubtraction(prev.stackPointer, 1, curr.stackPointer, "SP-1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_TXS()
{
	PrintH1("Testing TXS\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("IX=0x0010 TXS\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->indexRegister = 0x0010;
	p->stackPointer = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_TXS_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("IX=0x3FF2 TXS\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->indexRegister = 0x3FF2;
	p->stackPointer = 0xABCD;
	p->flagRegister = 0xFF;
	passAllTests &= test_TXS_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_TXS_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x35);
	ALU_HD6303R_Execute(p, 0x35);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.accumulatorD, curr.accumulatorD, "Accumulator D");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSubtraction(prev.indexRegister, 1, curr.stackPointer, "Index-1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_PSHA()
{
	PrintH1("Testing PSHA\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 PSHA\n");
	p->accumulatorA = 0xFF;
	p->accumulatorB = 0x12;
	p->stackPointer = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_PSHA_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 PSHA\n");
	p->accumulatorA = 0xFF;
	p->accumulatorB = 0x12;
	p->stackPointer = 0x0000;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xBE);
	MemoryWrite(p, 0xFFFF, 0xEF);
	passAllTests &= test_PSHA_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_PSHA_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x36);
	ALU_HD6303R_Execute(p, 0x36);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(MemoryRead(p, prev.stackPointer), curr.accumulatorA, "SP = (ACCA)");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSubtraction(prev.stackPointer, 1, curr.stackPointer, "SP-1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_PSHB()
{
	PrintH1("Testing PSHB\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 PSHB\n");
	p->accumulatorA = 0xFF;
	p->accumulatorB = 0x12;
	p->stackPointer = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_PSHB_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 PSHB\n");
	p->accumulatorA = 0xFF;
	p->accumulatorB = 0x12;
	p->stackPointer = 0x0000;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xBE);
	MemoryWrite(p, 0xFFFF, 0xEF);
	passAllTests &= test_PSHB_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_PSHB_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x37);
	ALU_HD6303R_Execute(p, 0x37);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(MemoryRead(p, prev.stackPointer), curr.accumulatorB, "SP = (ACCB)");
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckSubtraction(prev.stackPointer, 1, curr.stackPointer, "SP-1=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_PULX()
{
	PrintH1("Testing PULX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 PULX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_PULX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 PULX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0xFFFF;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xEF);
	passAllTests &= test_PULX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_PULX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x38);
	ALU_HD6303R_Execute(p, 0x38);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame((uint8_t)((curr.indexRegister&0xFF00)>>8), MemoryRead(p, prev.stackPointer+1), "IXH = (SP+1)");
	passAllTests &= CheckSame((uint8_t)(curr.indexRegister&0xFF), MemoryRead(p, prev.stackPointer+2), "IXL = (SP+2)");
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckAddition(prev.stackPointer, 2, curr.stackPointer, "SP+2=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_RTS()
{
	PrintH1("Testing RTS\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 RTS\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_RTS_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 RTS\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0xFFFF;
	p->indexRegister = 0xABCD;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xEF);
	passAllTests &= test_RTS_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_RTS_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x39);
	ALU_HD6303R_Execute(p, 0x39);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckSame((uint8_t)((curr.pc&0xFF00)>>8), MemoryRead(p, prev.stackPointer+1), "PCH = (SP+1)");
	passAllTests &= CheckSame((uint8_t)(curr.pc&0xFF), MemoryRead(p, prev.stackPointer+2), "PCL = (SP+2)");
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.indexRegister, curr.indexRegister, "Index");
	passAllTests &= CheckAddition(prev.stackPointer, 2, curr.stackPointer, "SP+2=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_ABX()
{
	PrintH1("Testing ABX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 ABX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0xABCD;
	p->indexRegister = 0x0010;
	MemoryWrite(p, 0x0010, 0xDE);
	MemoryWrite(p, 0x0011, 0xAD);
	p->indexRegister = 0x0001;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_ABX_exec();
	verified = checkVerified(p->flagRegister);
	printBreak(".",54);

	PrintH2("Case 1 ABX\n");
	p->accumulatorA = 0x34;
	p->accumulatorB = 0xF9;
	p->stackPointer = 0xABCD;
	p->indexRegister = 0xFFFF;
	p->flagRegister = 0xFF;
	MemoryWrite(p, 0x0000, 0xEF);
	passAllTests &= test_ABX_exec();

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_ABX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x3A);
	ALU_HD6303R_Execute(p, 0x3A);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame(prev.stackPointer, curr.stackPointer, "Stack Pointer");
	passAllTests &= CheckAddition(prev.indexRegister, prev.accumulatorB, curr.indexRegister, "IX + ACCB = IX");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_RTI()
{
	PrintH1("Testing RTI\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 RTI\n");
	p->accumulatorA = 0xAB;
	p->accumulatorB = 0xCD;
	p->indexRegister = 0x0010;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_RTI_exec();
	verified = checkVerified(p->flagRegister);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_RTI_exec()
{
	bool passAllTests = true;
//Setup Stack for RTI Test
	MemoryWrite(p, 0x1000, 0xC2); //CC
	MemoryWrite(p, 0x1001, 0x12); //ACCB
	MemoryWrite(p, 0x1002, 0x34); //ACCA
	MemoryWrite(p, 0x1003, 0xDE); //IXH
	MemoryWrite(p, 0x1004, 0xAD); //IXL
	MemoryWrite(p, 0x1005, 0xBE); //PCH
	MemoryWrite(p, 0x1006, 0xEF); //PCL
	p->stackPointer = 0xFFF;

	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x3B);
	ALU_HD6303R_Execute(p, 0x3B);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckSame(curr.accumulatorA, 0x34, "Accumulator A");
	passAllTests &= CheckSame(curr.accumulatorB, 0x12, "Accumulator B");
	passAllTests &= CheckSame(curr.indexRegister, 0xDEAD, "Index");
	passAllTests &= CheckSame(curr.pc, 0xBEEF, "PC");
	passAllTests &= CheckAddition(prev.stackPointer, 7, curr.stackPointer, "SP + 7 = SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(0xC2 & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

uint8_t test_PSHX()
{
	PrintH1("Testing PSHX\n");
	printBreak("-",70);

	bool passAllTests = true;
	bool verified = false;

	PrintH2("Case 0 PSHX\n");
	p->accumulatorA = 0x12;
	p->accumulatorB = 0x34;
	p->stackPointer = 0x009F;
	MemoryWrite(p, 0x00A0, 0xDE);
	MemoryWrite(p, 0x00A1, 0xAD);
	p->indexRegister = 0xBEEF;
	p->flagRegister = (0xFF & ~HD6303R_FLAG_V);
	passAllTests &= test_PSHX_exec();
	verified = checkVerified(p->flagRegister);

	return (passAllTests | ((uint8_t)verified << 1));
}

bool test_PSHX_exec()
{
	bool passAllTests = true;
	MPU_State prev = getMPUState();
	MemoryWrite(p,p->pc,0x3C);
	ALU_HD6303R_Execute(p, 0x3C);
	MPU_State curr = getMPUState();
	printf("Executed Mnemonic [%s]\n",ALU_HD6303R_GetCurrentMneunomic(p));

	passAllTests &= checkImplemented(curr.flagRegister);
	passAllTests &= CheckPC(prev.pc, curr.pc, 1);
	passAllTests &= CheckSame(MemoryRead(p, curr.stackPointer+1), (uint8_t)((curr.indexRegister&0xFF00)>>8), "(SP+1) = IXH");
	passAllTests &= CheckSame(MemoryRead(p, curr.stackPointer+2), (uint8_t)(curr.indexRegister&0xFF), "(SP+2) = IXL");
	passAllTests &= CheckSame(prev.accumulatorA, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame(prev.accumulatorB, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSubtraction(prev.stackPointer, 2, curr.stackPointer, "SP-2=SP");

	//Flag Checks
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}
