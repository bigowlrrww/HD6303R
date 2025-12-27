
#include "MC6803E_Core.h"
#include "MC6803E_Memory.h"
#include "MC6803E_ALU.h"

MC6803E_API MC6803E_MPU * MC6803E_MPU_Alloc(void)
{
	MC6803E_MPU * p = malloc(sizeof(MC6803E_MPU));
	
	if(p == NULL) { return p; }
	
	p->flagRegister = (uint8_t)0xC0; //Upper 2 bits are always set under normal processor arch
	p->accumulatorA = (uint8_t)0x00;
	p->accumulatorB = (uint8_t)0x00;
	
	// accumulatorD is a pointer to the beginning of accumulatorA.
	// accumulator is 16 bits, so it's value is that of the double accumulator (AB).
	p->accumulatorD = (uint16_t *)&p->accumulatorA;
	
	p->indexRegister = (uint16_t)0x0000;
	p->stackPointer = (uint16_t)0x0000;
	
	// Clear the memory map.
	int i;
	for(i=0; i<0x10000; i++) { MemoryWrite(p, i, 0x00); }
	
	// The program counter should point to the bootloader address.
	p->pc = (uint16_t)0x0000;
	
	// Make sure the last Command Mneunomic null to prevent issues on startup
	p->lastCommandMneunomic = NULL;
	p->lastCommandMneunomicLen = 0;
	return p;
}

MC6803E_API void MC6803E_MPU_Free(MC6803E_MPU * p)
{
	free(p);
}

MC6803E_API void MC6803E_MPU_PrintRegisters(MC6803E_MPU * p)
{
	char * str;
	printf("Reg\tHex\tBinary\n");
	printf("---\t----\t----------------\n");
	str = _uint16_ToString(p->pc);
	printf("PC:\t%04X\t%s\n",	p->pc, str);
	free(str);
	str = _uint8_ToString(p->flagRegister);
	printf("CCR:\t  %02X\t%s\n",	p->flagRegister, str);
	free(str);
	str = _uint8_ToString(p->accumulatorA);
	printf("A:\t  %02X\t%s\n", 	p->accumulatorA, str);
	free(str);
	str = _uint8_ToString(p->accumulatorB);
	printf("B:\t  %02X\t%s\n", 	p->accumulatorB, str);
	free(str);
	str = _uint16_ToString(*(p->accumulatorD));
	printf("D:\t%04X\t%s\n", 	*(p->accumulatorD), str);
	free(str);
	str = _uint16_ToString(p->indexRegister);
	printf("X:\t%04X\t%s\n", 	p->indexRegister, str);
	free(str);
	str = _uint16_ToString(p->stackPointer);
	printf("SP:\t%04X\t%s\n", 	p->stackPointer, str);
	free(str);
	
}

/*
	Cheeky Functions
*/
char * _uint_ToString(unsigned int i, unsigned int len)
{
	char * r = calloc(len+1, sizeof(char));
	for (int b = len; b > 0; --b) {
        r[len-b] = ((i >> b-1) & 1) ? '1' : '0';
    }
    r[len] = '\0';
    return r;
}

char * _uint16_ToString(uint16_t i)	{ return _uint_ToString(i, 16);	}
char * _uint8_ToString(uint8_t i)	{ return _uint_ToString(i, 8);	}

uint16_t uint16_From_uint8s(uint8_t chunk1, uint8_t chunk2)
{
	uint16_t address = chunk1;
	address <<= 8;
	return (address |= chunk2);
}

