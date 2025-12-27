
#include "HD6303R_Memory.h"

HD6303R_API uint8_t MemoryRead(HD6303R_MPU * p, uint16_t address)
	{ return (uint8_t)(p->MemoryMap[address]); }

HD6303R_API uint8_t MemoryWrite(HD6303R_MPU * p, uint16_t address, uint8_t value)
	{ return (uint8_t)(p->MemoryMap[address] = (uint8_t)value); }

uint8_t MemoryWrite16(HD6303R_MPU*p, uint16_t address, uint16_t value)
{
	uint8_t ret;
	ret = (p->MemoryMap[address] = (uint8_t)(value >> 8 &0xFF));
	ret &= (p->MemoryMap[address+1] = (uint8_t)(value &0xFF));
	return(ret);
}

uint8_t MemoryReadIndexValue(HD6303R_MPU * p, uint8_t offset)
	{ return (uint8_t)(MemoryRead(p, (p->indexRegister + offset))); }

uint8_t MemoryWriteIndexValue(HD6303R_MPU * p, uint8_t offset, uint8_t value)
	{ return (uint8_t)(MemoryWrite(p, (p->indexRegister + offset), value)); }

uint8_t MemoryWriteIndexValue16(HD6303R_MPU * p, uint8_t offset, uint16_t value)
	{ return (uint8_t)(MemoryWrite16(p, (p->indexRegister + offset), value)); }
