
#include "MC6803E_Memory.h"

MC6803E_API uint8_t MemoryRead(MC6803E_MPU * p, uint16_t address)
	{ return (uint8_t)(p->MemoryMap[address]); }

MC6803E_API uint8_t MemoryWrite(MC6803E_MPU * p, uint16_t address, uint8_t value)
	{ return (uint8_t)(p->MemoryMap[address] = (uint8_t)value); }

uint8_t MemoryWrite16(MC6803E_MPU*p, uint16_t address, uint16_t value)
{
	uint8_t ret;
	ret = (p->MemoryMap[address] = (uint8_t)(value >> 8 &0xFF));
	ret &= (p->MemoryMap[address+1] = (uint8_t)(value &0xFF));
	return(ret);
}

uint8_t MemoryReadIndexValue(MC6803E_MPU * p, uint8_t offset)
	{ return (uint8_t)(MemoryRead(p, (p->indexRegister + offset))); }

uint8_t MemoryWriteIndexValue(MC6803E_MPU * p, uint8_t offset, uint8_t value)
	{ return (uint8_t)(MemoryWrite(p, (p->indexRegister + offset), value)); }

uint8_t MemoryWriteIndexValue16(MC6803E_MPU * p, uint8_t offset, uint16_t value)
	{ return (uint8_t)(MemoryWrite16(p, (p->indexRegister + offset), value)); }
