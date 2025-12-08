#include "MC6803_UNIT.h"
#include "ItemList.h"

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

	addItem(&list, "AIM", test_AIM());
	PrepareForNextTest();

	addItem(&list, "OIM", test_OIM());
	PrepareForNextTest();

	addItem(&list, "EIM", test_EIM());
	PrepareForNextTest();

	addItem(&list, "TIM", test_TIM());
	PrepareForNextTest();

	// Load/Store
	addItem(&list, "LDAA", test_LDAA());
	PrepareForNextTest();
	addItem(&list, "LDAB", test_LDAB());
	PrepareForNextTest();
	addItem(&list, "STAA", test_STAA());
	PrepareForNextTest();
	addItem(&list, "STAB", test_STAB());
	PrepareForNextTest();

	// Arithmetic
	addItem(&list, "ADDA", test_ADDA());
	PrepareForNextTest();
	addItem(&list, "ADDB", test_ADDB());
	PrepareForNextTest();
	addItem(&list, "SUBA", test_SUBA());
	PrepareForNextTest();
	addItem(&list, "SUBB", test_SUBB());
	PrepareForNextTest();

	// Logic
	addItem(&list, "ANDA", test_ANDA());
	PrepareForNextTest();
	addItem(&list, "ANDB", test_ANDB());
	PrepareForNextTest();
	addItem(&list, "ORAA", test_ORAA());
	PrepareForNextTest();
	addItem(&list, "ORAB", test_ORAB());
	PrepareForNextTest();
	addItem(&list, "EORA", test_EORA());
	PrepareForNextTest();
	addItem(&list, "EORB", test_EORB());
	PrepareForNextTest();

	// Provide a sumary of results
	printf("Testing Summary: \n");
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
	printf("Testing 0x%02X\n", Mnemonic);
	return verifyUnknownMnemonic(ALU_MC6803E_Execute(p, Mnemonic));
}

bool test_NOP()
{
	printf("Testing NOP\n");
	printBreak("-",70);

	bool passAllTests = true;

	printf("Case startup NOP\n");
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
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	printf("\nCase Values set NOP\n");

	p->accumulatorB = 0x12;
	p->accumulatorA = 0x34;
	// D should be set already because of A and B
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
	passAllTests &= CheckSame((uint8_t)(prev.flagRegister & 0x3F), (uint8_t)(curr.flagRegister & 0x3F), "Flags");

	return passAllTests;
}

bool test_AIM()
{
	printf("Testing AIM\n");
	printBreak("-",70);
	bool passAllTests = true;

	// AIM #$F0, $10 (Direct)
	// Memory at $10 = $AA (10101010)
	// Imm = $F0 (11110000)
	// Result = $A0 (10100000)
	// Flags: N=1, Z=0, V=0

	p->MemoryMap[0xE000] = 0x71; // AIM Direct
	p->MemoryMap[0xE001] = 0xF0; // Imm
	p->MemoryMap[0xE002] = 0x10; // Direct Addr
	p->MemoryMap[0x0010] = 0xAA; // Initial value

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x71);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 3);
	passAllTests &= CheckSame((uint8_t)0xA0, curr.MemoryMap[0x0010], "Memory Result");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_OIM()
{
	printf("Testing OIM\n");
	printBreak("-",70);
	bool passAllTests = true;

	// OIM #$0F, $10 (Direct)
	// Memory at $10 = $A0 (10100000)
	// Imm = $0F (00001111)
	// Result = $AF (10101111)
	// Flags: N=1, Z=0, V=0

	p->MemoryMap[0xE000] = 0x72; // OIM Direct
	p->MemoryMap[0xE001] = 0x0F; // Imm
	p->MemoryMap[0xE002] = 0x10; // Direct Addr
	p->MemoryMap[0x0010] = 0xA0; // Initial value

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x72);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 3);
	passAllTests &= CheckSame((uint8_t)0xAF, curr.MemoryMap[0x0010], "Memory Result");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_EIM()
{
	printf("Testing EIM\n");
	printBreak("-",70);
	bool passAllTests = true;

	// EIM #$FF, $10 (Direct)
	// Memory at $10 = $AA (10101010)
	// Imm = $FF (11111111)
	// Result = $55 (01010101)
	// Flags: N=0, Z=0, V=0

	p->MemoryMap[0xE000] = 0x75; // EIM Direct
	p->MemoryMap[0xE001] = 0xFF; // Imm
	p->MemoryMap[0xE002] = 0x10; // Direct Addr
	p->MemoryMap[0x0010] = 0xAA; // Initial value

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x75);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 3);
	passAllTests &= CheckSame((uint8_t)0x55, curr.MemoryMap[0x0010], "Memory Result");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_TIM()
{
	printf("Testing TIM\n");
	printBreak("-",70);
	bool passAllTests = true;

	// TIM #$0F, $10 (Direct)
	// Memory at $10 = $F0 (11110000)
	// Imm = $0F (00001111)
	// Result = $00 (00000000)
	// Flags: N=0, Z=1, V=0
	// Memory should NOT change

	p->MemoryMap[0xE000] = 0x7B; // TIM Direct
	p->MemoryMap[0xE001] = 0x0F; // Imm
	p->MemoryMap[0xE002] = 0x10; // Direct Addr
	p->MemoryMap[0x0010] = 0xF0; // Initial value

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x7B);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 3);
	passAllTests &= CheckSame((uint8_t)0xF0, curr.MemoryMap[0x0010], "Memory Result (Unchanged)");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

// Load/Store
bool test_LDAA()
{
	printf("Testing LDAA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// LDAA Immediate #$55
	p->MemoryMap[0xE000] = 0x86; 
	p->MemoryMap[0xE001] = 0x55;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x86);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x55, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_LDAB()
{
	printf("Testing LDAB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// LDAB Immediate #$AA
	p->MemoryMap[0xE000] = 0xC6; 
	p->MemoryMap[0xE001] = 0xAA;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xC6);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0xAA, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_STAA()
{
	printf("Testing STAA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// STAA Direct $10
	p->accumulatorA = 0x55;
	p->MemoryMap[0xE000] = 0x97; 
	p->MemoryMap[0xE001] = 0x10;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x97);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x55, curr.MemoryMap[0x0010], "Memory Result");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_STAB()
{
	printf("Testing STAB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// STAB Direct $10
	p->accumulatorB = 0xAA;
	p->MemoryMap[0xE000] = 0xD7; 
	p->MemoryMap[0xE001] = 0x10;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xD7);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0xAA, curr.MemoryMap[0x0010], "Memory Result");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

// Arithmetic
bool test_ADDA()
{
	printf("Testing ADDA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// ADDA Immediate #$10 (A=$20 -> $30)
	p->accumulatorA = 0x20;
	p->MemoryMap[0xE000] = 0x8B; 
	p->MemoryMap[0xE001] = 0x10;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x8B);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x30, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_H) ? 1 : 0), "Flag H");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_C) ? 1 : 0), "Flag C");

	return passAllTests;
}

bool test_ADDB()
{
	printf("Testing ADDB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// ADDB Immediate #$F0 (B=$20 -> $10, Carry)
	p->accumulatorB = 0x20;
	p->MemoryMap[0xE000] = 0xCB; 
	p->MemoryMap[0xE001] = 0xF0;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xCB);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x10, curr.accumulatorB, "Accumulator B");
	// H flag not affected by ADDB? Actually it is for ADD instructions usually.
	// But let's check standard flags.
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_C) ? 1 : 0), "Flag C");

	return passAllTests;
}

bool test_SUBA()
{
	printf("Testing SUBA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// SUBA Immediate #$10 (A=$20 -> $10)
	p->accumulatorA = 0x20;
	p->MemoryMap[0xE000] = 0x80; 
	p->MemoryMap[0xE001] = 0x10;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x80);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x10, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_C) ? 1 : 0), "Flag C");

	return passAllTests;
}

bool test_SUBB()
{
	printf("Testing SUBB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// SUBB Immediate #$30 (B=$20 -> $F0, Carry/Borrow)
	p->accumulatorB = 0x20;
	p->MemoryMap[0xE000] = 0xC0; 
	p->MemoryMap[0xE001] = 0x30;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xC0);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0xF0, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V"); // V is complicated
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_C) ? 1 : 0), "Flag C");

	return passAllTests;
}

// Logic
bool test_ANDA()
{
	printf("Testing ANDA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// ANDA Immediate #$0F (A=$F0 -> $00)
	p->accumulatorA = 0xF0;
	p->MemoryMap[0xE000] = 0x84; 
	p->MemoryMap[0xE001] = 0x0F;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x84);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x00, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_ANDB()
{
	printf("Testing ANDB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// ANDB Immediate #$F0 (B=$0F -> $00)
	p->accumulatorB = 0x0F;
	p->MemoryMap[0xE000] = 0xC4; 
	p->MemoryMap[0xE001] = 0xF0;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xC4);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x00, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_ORAA()
{
	printf("Testing ORAA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// ORAA Immediate #$0F (A=$F0 -> $FF)
	p->accumulatorA = 0xF0;
	p->MemoryMap[0xE000] = 0x8A; 
	p->MemoryMap[0xE001] = 0x0F;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x8A);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0xFF, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_ORAB()
{
	printf("Testing ORAB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// ORAB Immediate #$F0 (B=$0F -> $FF)
	p->accumulatorB = 0x0F;
	p->MemoryMap[0xE000] = 0xCA; 
	p->MemoryMap[0xE001] = 0xF0;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xCA);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0xFF, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_EORA()
{
	printf("Testing EORA\n");
	printBreak("-",70);
	bool passAllTests = true;

	// EORA Immediate #$FF (A=$AA -> $55)
	p->accumulatorA = 0xAA;
	p->MemoryMap[0xE000] = 0x88; 
	p->MemoryMap[0xE001] = 0xFF;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0x88);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0x55, curr.accumulatorA, "Accumulator A");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}

bool test_EORB()
{
	printf("Testing EORB\n");
	printBreak("-",70);
	bool passAllTests = true;

	// EORB Immediate #$FF (B=$55 -> $AA)
	p->accumulatorB = 0x55;
	p->MemoryMap[0xE000] = 0xC8; 
	p->MemoryMap[0xE001] = 0xFF;

	MPU_State prev = getMPUState();
	ALU_MC6803E_Execute(p, 0xC8);
	MPU_State curr = getMPUState();

	passAllTests &= checkPC(prev.pc, curr.pc, 2);
	passAllTests &= CheckSame((uint8_t)0xAA, curr.accumulatorB, "Accumulator B");
	passAllTests &= CheckSame((uint8_t)1, (uint8_t)((curr.flagRegister & MC6803E_FLAG_N) ? 1 : 0), "Flag N");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_Z) ? 1 : 0), "Flag Z");
	passAllTests &= CheckSame((uint8_t)0, (uint8_t)((curr.flagRegister & MC6803E_FLAG_V) ? 1 : 0), "Flag V");

	return passAllTests;
}
