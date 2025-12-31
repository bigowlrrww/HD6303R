
#include "HD6303R_ALU.h"
#include <stdbool.h>

// Cheeky overload to debug easier
#define ALU_HD6303R_SetCurrentMneunomicWithPayload(p, instr, x) _Generic((x), \
    uint8_t:  ALU_HD6303R_SetCurrentMneunomicWithPayload8, \
    uint16_t: ALU_HD6303R_SetCurrentMneunomicWithPayload16 \
)(p, instr, x)

/*
	Debug Instructions
*/

HD6303R_API char * ALU_HD6303R_GetCurrentMneunomic(HD6303R_MPU * p)
	{ return p->lastCommandMneunomic; }
HD6303R_API void ALU_HD6303R_PrintCurrentMneunomic(HD6303R_MPU * p)
	{ printf("%s\n", ALU_HD6303R_GetCurrentMneunomic(p)); }
void ALU_HD6303R_FreeCurrentMneunomic(HD6303R_MPU * p)
	{ if(p->lastCommandMneunomic != NULL) { free(p->lastCommandMneunomic); } }

char * ALU_HD6303R_SetCurrentMneunomic(HD6303R_MPU * p, char * instruction)
{
	ALU_HD6303R_FreeCurrentMneunomic(p);
	p->lastCommandMneunomic = calloc(128, sizeof(char));
	sprintf(p->lastCommandMneunomic, "%04X:(%02x)\t%s", p->pc, 
		(uint8_t)p->MemoryMap[p->pc],
		 instruction);
	p->lastCommandMneunomicLen = 0;
	return p->lastCommandMneunomic;
}

char * ALU_HD6303R_SetCurrentMneunomicWithPayload8(HD6303R_MPU * p, char * instruction, uint8_t payload)
{
	ALU_HD6303R_FreeCurrentMneunomic(p);
	p->lastCommandMneunomic = calloc(128, sizeof(char));
	
	char * format_string = calloc(sizeof(char), strlen(instruction) + 0xff);
	sprintf(format_string, "%04X:(%02x %02x)\t%s", p->pc,
		(uint8_t)p->MemoryMap[p->pc],
		(uint8_t)p->MemoryMap[p->pc+1],
		instruction);
	
	sprintf(p->lastCommandMneunomic, format_string, payload);

	free(format_string);
	p->lastCommandMneunomicLen = 1;
	return p->lastCommandMneunomic;
}

char * ALU_HD6303R_SetCurrentMneunomicWithPayload16(HD6303R_MPU * p, char * instruction, uint16_t payload)
{
	ALU_HD6303R_FreeCurrentMneunomic(p);
	p->lastCommandMneunomic = calloc(128, sizeof(char));
	
	char * format_string = calloc(sizeof(char), strlen(instruction) + 0xff);
	sprintf(format_string, "%04X:(%02x %02x %02x)\t%s", p->pc,
		(uint8_t)p->MemoryMap[p->pc],
		(uint8_t)p->MemoryMap[p->pc+1], 
		(uint8_t)p->MemoryMap[p->pc+2], 
		instruction);
	
	sprintf(p->lastCommandMneunomic, format_string, payload);

	free(format_string);
	p->lastCommandMneunomicLen = 2;
	return p->lastCommandMneunomic;
}
/*
	Convenience Functions.
*/
uint16_t ALU_HD6303R_IncrementPC(HD6303R_MPU * p, uint16_t ammount)
	{ return p->pc += ammount; }

uint8_t ALU_HD6303R_GetFlag(HD6303R_MPU * p, uint8_t flag)
	{ if(p->flagRegister & flag) { return (uint8_t)1; } else { return (uint8_t)0; } }
uint8_t ALU_HD6303R_SetFlag(HD6303R_MPU * p, uint8_t flag)
	{ return (p->flagRegister = (p->flagRegister | flag)); }
uint8_t ALU_HD6303R_UnsetFlag(HD6303R_MPU * p, uint8_t flag)
	{ return (p->flagRegister = (p->flagRegister & ~flag)); }
uint8_t ALU_HD6303R_SetFlagIfZero(HD6303R_MPU * p, uint8_t flag, uint8_t val)
	{ if(val == 0) { return ALU_HD6303R_SetFlag(p, flag); } else { return ALU_HD6303R_UnsetFlag(p, flag); } }
uint8_t ALU_HD6303R_SetFlagIfNonZero(HD6303R_MPU * p, uint8_t flag, uint8_t val)
	{ if(val != 0) { return ALU_HD6303R_SetFlag(p, flag); } else { return ALU_HD6303R_UnsetFlag(p, flag); } }

/*
	Implement the Fetch/Execute cycle.
*/
HD6303R_API uint8_t ALU_HD6303R_Fetch(HD6303R_MPU * p)
	{ return (uint8_t)MemoryRead(p, p->pc); }

HD6303R_API uint16_t ALU_HD6303R_Execute(HD6303R_MPU * p, uint8_t instruction)
{
	switch (instruction) {
		case 0x8C: // CPX Immediate
		case 0x9C: // CPX Direct
		case 0xAC: // CPX Index
		case 0xBC: // CPX Extended
			ALU_HD6303R_CPX(p);
			break;
		case 0x09: // DEX Inherent
			ALU_HD6303R_DEX(p);
			break;
		case 0x34: // DES Inherent
			ALU_HD6303R_DES(p);
			break;
		case 0x08: // INX Inherent
			ALU_HD6303R_INX(p);
			break;
		case 0x31: // INS Inherent
			ALU_HD6303R_INS(p);
			break;
		case 0xCE: // LDX Immediate
		case 0xDE: // LDX Direct
		case 0xEE: // LDX Index
		case 0xFE: // LDX Extended
			ALU_HD6303R_LDX(p);
			break;
		case 0x8E: // LDS Immediate
		case 0x9E: // LDS Direct
		case 0xAE: // LDS Index
		case 0xBE: // LDS Extended
			ALU_HD6303R_LDS(p);
			break;
		case 0xDF: // STX Direct
		case 0xEF: // STX Index
		case 0xFF: // STX Extended
			ALU_HD6303R_STX(p);
			break;
		case 0x9F: // STS Direct
		case 0xAF: // STS Index
		case 0xBF: // STS Extended
			ALU_HD6303R_STS(p);
			break;
		case 0x35: // TXS Inherent
			ALU_HD6303R_TXS(p);
			break;
		case 0x30: // TSX Inherent
			ALU_HD6303R_TSX(p);
			break;
		case 0x3C: // PSHX Inherent
			ALU_HD6303R_PSHX(p);
			break;
		case 0x38: // PULX Inherent
			ALU_HD6303R_PULX(p);
			break;
		case 0x1A:
			ALU_HD6303R_SLP(p);
			break;
		case 0x1B: // ABA Inherent
			ALU_HD6303R_ABA(p);
			break;
		case 0x3A: // ABX Inherent
			ALU_HD6303R_ABX(p);
			break;
		case 0x89: // ADCA Immediate
		case 0x99: // ADCA Direct
		case 0xA9: // ADCA Index
		case 0xB9: // ADCA Extended
			ALU_HD6303R_ADCA(p);
			break;
		case 0xC9: // ADCB Immediate
		case 0xD9: // ADCB Direct
		case 0xE9: // ADCB Index
		case 0xF9: // ADCB Extended
			ALU_HD6303R_ADCB(p);
			break;
		case 0x8B: // ADDA Immediate
		case 0x9B: // ADDA Direct
		case 0xAB: // ADDA Index
		case 0xBB: // ADDA Extended
			ALU_HD6303R_ADDA(p);
			break;
		case 0xCB: // ADDB Immediate
		case 0xDB: // ADDB Direct
		case 0xEB: // ADDB Index
		case 0xFB: // ADDB Extended
			ALU_HD6303R_ADDB(p);
			break;
		case 0xC3: // ADDD Immediate
		case 0xD3: // ADDD Direct
		case 0xE3: // ADDD Index
		case 0xF3: // ADDD Extended
			ALU_HD6303R_ADDD(p);
			break;
		case 0x84: // ANDA Immediate
		case 0x94: // ANDA Direct
		case 0xA4: // ANDA Index
		case 0xB4: // ANDA Extended
			ALU_HD6303R_ANDA(p);
			break;
		case 0xC4: // ANDB Immediate
		case 0xD4: // ANDB Direct
		case 0xE4: // ANDB Index
		case 0xF4: // ANDB Extended
			ALU_HD6303R_ANDB(p);
			break;
		case 0x68: // ASL/LSL Index
		case 0x78: // ASL/LSL Extended
			ALU_HD6303R_ASL(p);
			//ALU_HD6303R_LSL(p);
			break;
		case 0x48: // ASLA/LSLA Inherent
			ALU_HD6303R_ASLA(p);
			//ALU_HD6303R_LSLA(p);
			break;
		case 0x58: // ASLB/LSLB Inherent
			ALU_HD6303R_ASLB(p);
			//ALU_HD6303R_LSLB(p);
			break;
		case 0x05: // ASLD/LSLD Inherent
			ALU_HD6303R_ASLD(p);
			//ALU_HD6303R_LSLD(p);
			break;
		case 0x67: // ASR Index
		case 0x77: // ASR Extended
			ALU_HD6303R_ASR(p);
			break;
		case 0x47: // ASRA Inherent
			ALU_HD6303R_ASRA(p);
			break;
		case 0x57: // ASRB Inherent
			ALU_HD6303R_ASRB(p);
			break;
		case 0x85: // BITA Immediate
		case 0x95: // BITA Direct
		case 0xA5: // BITA Index
		case 0xB5: // BITA Extended
			ALU_HD6303R_BITA(p);
			break;
		case 0xC5: // BITB Immediate
		case 0xD5: // BITB Direct
		case 0xE5: // BITB Index
		case 0xF5: // BITB Extended
			ALU_HD6303R_BITB(p);
			break;
		case 0x11: // CBA Inherent
			ALU_HD6303R_CBA(p);
			break;
		case 0x6F: // CLR Index
		case 0x7F: // CLR Extended
			ALU_HD6303R_CLR(p);
			break;
		case 0x4F: // CLRA Inherent
			ALU_HD6303R_CLRA(p);
			break;
		case 0x5F: // CLRB Inherent
			ALU_HD6303R_CLRB(p);
			break;
		case 0x81: // CMPA Immediate
		case 0x91: // CMPA Direct
		case 0xA1: // CMPA Index
		case 0xB1: // CMPA Extended
			ALU_HD6303R_CMPA(p);
			break;
		case 0xC1: // CMPB Immediate
		case 0xD1: // CMPB Direct
		case 0xE1: // CMPB Index
		case 0xF1: // CMPB Extended
			ALU_HD6303R_CMPB(p);
			break;
		case 0x63: // COM Index
		case 0x73: // COM Extended
			ALU_HD6303R_COM(p);
			break;
		case 0x43: // COMA Inherent
			ALU_HD6303R_COMA(p);
			break;
		case 0x53: // COMB Inherent
			ALU_HD6303R_COMB(p);
			break;
		case 0x19: // DAA Inherent
			ALU_HD6303R_DAA(p);
			break;
		case 0x6A: // DEC Index
		case 0x7A: // DEC Extended
			ALU_HD6303R_DEC(p);
			break;
		case 0x4A: // DECA Inherent
			ALU_HD6303R_DECA(p);
			break;
		case 0x5A: // DECB Inherent
			ALU_HD6303R_DECB(p);
			break;
		case 0x88: // EORA Immediate
		case 0x98: // EORA Direct
		case 0xA8: // EORA Index
		case 0xB8: // EORA Extended
			ALU_HD6303R_EORA(p);
			break;
		case 0xC8: // EORB Immediate
		case 0xD8: // EORB Direct
		case 0xE8: // EORB Index
		case 0xF8: // EORB Extended
			ALU_HD6303R_EORB(p);
			break;
		case 0x6C: // INC Index
		case 0x7C: // INC Extended
			ALU_HD6303R_INC(p);
			break;
		case 0x4C: // INCA Inherent
			ALU_HD6303R_INCA(p);
			break;
		case 0x5C: // INCB Inherent
			ALU_HD6303R_INCB(p);
			break;
		case 0x86: // LDAA Immediate
		case 0x96: // LDAA Direct
		case 0xA6: // LDAA Index
		case 0xB6: // LDAA Extended
			ALU_HD6303R_LDAA(p);
			break;
		case 0xC6: // LDAB Immediate
		case 0xD6: // LDAB Direct
		case 0xE6: // LDAB Index
		case 0xF6: // LDAB Extended
			ALU_HD6303R_LDAB(p);
			break;
		case 0xCC: // LDD Immediate
		case 0xDC: // LDD Direct
		case 0xEC: // LDD Index
		case 0xFC: // LDD Extended
			ALU_HD6303R_LDD(p);
			break;
		case 0x64: // LSR Index
		case 0x74: // LSR Extended
			ALU_HD6303R_LSR(p);
			break;
		case 0x44: // LSRA Inherent
			ALU_HD6303R_LSRA(p);
			break;
		case 0x54: // LSRB Inherent
			ALU_HD6303R_LSRB(p);
			break;
		case 0x04: // LSRD Inherent
			ALU_HD6303R_LSRD(p);
			break;
		case 0x3D: // MUL Inherent
			ALU_HD6303R_MUL(p);
			break;
		case 0x60: // NEG Index
		case 0x70: // NEG Extended
			ALU_HD6303R_NEG(p);
			break;
		case 0x40: // NEGA Inherent
			ALU_HD6303R_NEGA(p);
			break;
		case 0x50: // NEGB Inherent
			ALU_HD6303R_NEGB(p);
			break;
		case 0x01: // NOP Inherent
			ALU_HD6303R_NOP(p);
			break;
		case 0x8A: // ORAA Immediate
		case 0x9A: // ORAA Direct
		case 0xAA: // ORAA Index
		case 0xBA: // ORAA Extended
			ALU_HD6303R_ORAA(p);
			break;
		case 0xCA: // ORAB Immediate
		case 0xDA: // ORAB Direct
		case 0xEA: // ORAB Index
		case 0xFA: // ORAB Extended
			ALU_HD6303R_ORAB(p);
			break;
		case 0x36: // PSHA Inherent
			ALU_HD6303R_PSHA(p);
			break;
		case 0x37: // PSHB Inherent
			ALU_HD6303R_PSHB(p);
			break;
		case 0x32: // PULA Inherent
			ALU_HD6303R_PULA(p);
			break;
		case 0x33: // PULB Inherent
			ALU_HD6303R_PULB(p);
			break;
		case 0x69: // ROL Index
		case 0x79: // ROL Extended
			ALU_HD6303R_ROL(p);
			break;
		case 0x49: // ROLA Inherent
			ALU_HD6303R_ROLA(p);
			break;
		case 0x59: // ROLB Inherent
			ALU_HD6303R_ROLB(p);
			break;
		case 0x66: // ROR Index
		case 0x76: // ROR Extended
			ALU_HD6303R_ROR(p);
			break;
		case 0x46: // RORA Inherent
			ALU_HD6303R_RORA(p);
			break;
		case 0x56: // RORB Inherent
			ALU_HD6303R_RORB(p);
			break;
		case 0x10: // SBA Inherent
			ALU_HD6303R_SBA(p);
			break;
		case 0x82: // SBCA Immediate
		case 0x92: // SBCA Direct
		case 0xA2: // SBCA Index
		case 0xB2: // SBCA Extended
			ALU_HD6303R_SBCA(p);
			break;
		case 0xC2: // SBCB Immediate
		case 0xD2: // SBCB Direct
		case 0xE2: // SBCB Index
		case 0xF2: // SBCB Extended
			ALU_HD6303R_SBCB(p);
			break;
		case 0x97: // STAA Direct
		case 0xA7: // STAA Index
		case 0xB7: // STAA Extended
			ALU_HD6303R_STAA(p);
			break;
		case 0xD7: // STAB Direct
		case 0xE7: // STAB Index
		case 0xF7: // STAB Extended
			ALU_HD6303R_STAB(p);
			break;
		case 0xDD: // STD Direct
		case 0xED: // STD Index
		case 0xFD: // STD Extended
			ALU_HD6303R_STD(p);
			break;
		case 0x80: // SUBA Immediate
		case 0x90: // SUBA Direct
		case 0xA0: // SUBA Index
		case 0xB0: // SUBA Extended
			ALU_HD6303R_SUBA(p);
			break;
		case 0xC0: // SUBB Immediate
		case 0xD0: // SUBB Direct
		case 0xE0: // SUBB Index
		case 0xF0: // SUBB Extended
			ALU_HD6303R_SUBB(p);
			break;
		case 0x83: // SUBD Immediate
		case 0x93: // SUBD Direct
		case 0xA3: // SUBD Index
		case 0xB3: // SUBD Extended
			ALU_HD6303R_SUBD(p);
			break;
		case 0x16: // TAB Inherent
			ALU_HD6303R_TAB(p);
			break;
		case 0x17: // TBA Inherent
			ALU_HD6303R_TBA(p);
			break;
		case 0x18: // XGDX Inherent
			ALU_HD6303R_XGDX(p);
			break;
		case 0x6D: // TST Index
		case 0x7D: // TST Extended
			ALU_HD6303R_TST(p);
			break;
		case 0x4D: // TSTA Inherent
			ALU_HD6303R_TSTA(p);
			break;
		case 0x5D: // TSTB Inherent
			ALU_HD6303R_TSTB(p);
			break;
		case 0x20: // BRA Immediate
			ALU_HD6303R_BRA(p);
			break;
		case 0x21: // BRN Immediate
			ALU_HD6303R_BRN(p);
			break;
		case 0x24: // BCC Immediate
			ALU_HD6303R_BCC(p);
			//ALU_HD6303R_BHS(p);
			break;
		case 0x25: // BCS Immediate
			ALU_HD6303R_BCS(p);
			//ALU_HD6303R_BLO(p);
			break;
		case 0x27: // BEQ Immediate
			ALU_HD6303R_BEQ(p);
			break;
		case 0x2C: // BGE Immediate
			ALU_HD6303R_BGE(p);
			break;
		case 0x2E: // BGT Immediate
			ALU_HD6303R_BGT(p);
			break;
		case 0x22: // BHI Immediate
			ALU_HD6303R_BHI(p);
			break;
		case 0x2F: // BLE Immediate
			ALU_HD6303R_BLE(p);
			break;
		case 0x23: // BLS Immediate
			ALU_HD6303R_BLS(p);
			break;
		case 0x2D: // BLT Immediate
			ALU_HD6303R_BLT(p);
			break;
		case 0x2B: // BMI Immediate
			ALU_HD6303R_BMI(p);
			break;
		case 0x26: // BNE Immediate
			ALU_HD6303R_BNE(p);
			break;
		case 0x28: // BVC Immediate
			ALU_HD6303R_BVC(p);
			break;
		case 0x29: // BVS Immediate
			ALU_HD6303R_BVS(p);
			break;
		case 0x2A: // BPL Immediate
			ALU_HD6303R_BPL(p);
			break;
		case 0x8D: // BSR Immediate
			ALU_HD6303R_BSR(p);
			break;
		case 0x6E: // JMP Index
		case 0x7E: // JMP Extended
			ALU_HD6303R_JMP(p);
			break;
		case 0x9D: // JSR Immediate
		case 0xAD: // JSR Index
		case 0xBD: // JSR Extended
			ALU_HD6303R_JSR(p);
			break;
		case 0x3B: // RTI Inherent
			ALU_HD6303R_RTI(p);
			break;
		case 0x39: // RTS Inherent
			ALU_HD6303R_RTS(p);
			break;
		case 0x3F: // SWI Inherent
			ALU_HD6303R_SWI(p);
			break;
		case 0x3E: // WAI Inherent
			ALU_HD6303R_WAI(p);
			break;
		case 0x0C: // CLC Inherent
			ALU_HD6303R_CLC(p);
			break;
		case 0x0E: // CLI Inherent
			ALU_HD6303R_CLI(p);
			break;
		case 0x0A: // CLV Inherent
			ALU_HD6303R_CLV(p);
			break;
		case 0x0D: // SEC Inherent
			ALU_HD6303R_SEC(p);
			break;
		case 0x0F: // SEI Inherent
			ALU_HD6303R_SEI(p);
			break;
		case 0x0B: // SEV Inherent
			ALU_HD6303R_SEV(p);
			break;
		case 0x06: // TAP Inherent
			ALU_HD6303R_TAP(p);
			break;
		case 0x07: // TPA Inherent
			ALU_HD6303R_TPA(p);
			break;
		default:
			printf("Unknown instruction (%X) at PC -> %X.\n", instruction, p->pc);
			ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
			ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
			return 0xFFFF; //INVALID PC LOCATION Intentionally
			break;
	}
	
	// Return the incremented program counter.
	return (uint16_t)ALU_HD6303R_IncrementPC(p, 1);
}

/*
	This is the instruction set. Each command is responsible for the execute cycle, the program counter will be incremented by one byte after each command.
*/

/*
		void ALU_HD6303R_CPX(HD6303R_MPU * p)
		Boolean:	X - M:(M + 1)
		Flags:		N Z V C
*/
void ALU_HD6303R_CPX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result;


	switch (instruction) {
		case 0x8C: // CPX Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CPX #$%02X", unsigned_payload);
			result = (p->indexRegister - (uint16_t)unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x9C: // CPX Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CPX %02X", unsigned_payload);
			result = (p->indexRegister - MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xAC: // CPX Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CPX %02X(x)", unsigned_payload);
			result = (p->indexRegister - MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xBC: // CPX Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CPX %04X", unsigned_payload_double);
			result = (p->indexRegister - MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	//SUB C = X7'M7+M7R7+R7X7'
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, (result & 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_DEX(HD6303R_MPU * p)
		Boolean:	X - 1 -> X
		Flags:		Z
*/
void ALU_HD6303R_DEX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x09: // DEX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "DEX");
			p->indexRegister--;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->indexRegister);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_DES(HD6303R_MPU * p)
		Boolean:	SP - 1 -> SP
		Flags:		
*/
void ALU_HD6303R_DES(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x34: // DES Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "DES");
			p->stackPointer--;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_INX(HD6303R_MPU * p)
		Boolean:	X + 1 -> X
		Flags:		Z
*/
void ALU_HD6303R_INX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x08: // INX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "INX");
			p->indexRegister++;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->indexRegister);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_INS(HD6303R_MPU * p)
		Boolean:	SP + 1 -> SP
		Flags:		
*/
void ALU_HD6303R_INS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x31: // INS Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "INS");
			p->stackPointer++;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_LDX(HD6303R_MPU * p)
		Boolean:	M -> Xh; (M + 1) -> Xl
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_LDX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xCE: // LDX Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDX #$%04X", unsigned_payload_double);
			p->indexRegister = unsigned_payload_double;
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		case 0xDE: // LDX Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDX %02X", unsigned_payload);
			p->indexRegister = (MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xEE: // LDX Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDX %02X(x)", unsigned_payload);
			p->indexRegister = (MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xFE: // LDX Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDX %04X", unsigned_payload_double);
			p->indexRegister = (MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->indexRegister & 0x8000));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->indexRegister);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_LDS(HD6303R_MPU * p)
		Boolean:	M -> SPh; (M + 1) -> SPl
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_LDS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x8E: // LDS Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDS #$%04X", unsigned_payload_double);
			p->stackPointer = (unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		case 0x9E: // LDS Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDS %02X", unsigned_payload);
			p->stackPointer = (MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xAE: // LDS Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDS %02X(x)", unsigned_payload);
			p->stackPointer = (MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xBE: // LDS Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDS %04X", unsigned_payload_double);
			p->stackPointer = (MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->stackPointer & 0x8000));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->stackPointer);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_STX(HD6303R_MPU * p)
		Boolean:	Xh -> M; Xl -> (M + 1)
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_STX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint8_t xHigh, xLow;
		xHigh = (p->indexRegister >> 8);
		xLow = (p->indexRegister & 0xff);

	switch (instruction) {
		case 0xDF: // STX Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STX %02X", unsigned_payload);
			MemoryWrite(p, direct_address, xHigh);
			MemoryWrite(p, (direct_address + 1), xLow);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xEF: // STX Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STX %02X(x)", unsigned_payload);
			MemoryWrite(p, MemoryReadIndexValue(p, unsigned_payload), xHigh);
			MemoryWrite(p, (MemoryReadIndexValue(p, unsigned_payload) + 1), xLow);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xFF: // STX Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STX %04X", unsigned_payload_double);
			MemoryWrite(p, unsigned_payload_double, xHigh);
			MemoryWrite(p, unsigned_payload_double, xLow);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	// @CC: Can either part be negative to set the flag? (Bitmask: 0x8080)
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->indexRegister & 0x8000));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->indexRegister);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_STS(HD6303R_MPU * p)
		Boolean:	SPh -> M; SPl -> (M + 1)
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_STS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint8_t spHigh, spLow;
		spHigh = (p->stackPointer >> 8);
		spLow = (p->stackPointer & 0xff);

	switch (instruction) {
		case 0x9F: // STS Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STS %02X", unsigned_payload);
			MemoryWrite(p, direct_address, spHigh);
			MemoryWrite(p, (direct_address + 1), spLow);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xAF: // STS Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STS %02X(x)", unsigned_payload);
			MemoryWrite(p, MemoryReadIndexValue(p, unsigned_payload), spHigh);
			MemoryWrite(p, (MemoryReadIndexValue(p, unsigned_payload) + 1), spLow);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xBF: // STS Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STS %04X", unsigned_payload_double);
			MemoryWrite(p, unsigned_payload_double, spHigh);
			MemoryWrite(p, (unsigned_payload_double + 1), spLow);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->indexRegister & 0x8000));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->indexRegister);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_TXS(HD6303R_MPU * p)
		Boolean:	X - 1 -> SP
		Flags:		
*/
void ALU_HD6303R_TXS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x35: // TXS Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TXS");
			p->stackPointer = (p->indexRegister - 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_TSX(HD6303R_MPU * p)
		Boolean:	SP + 1 -> X
		Flags:		
*/
void ALU_HD6303R_TSX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x30: // TSX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TSX");
			p->indexRegister = (p->stackPointer + 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_PSHX(HD6303R_MPU * p)
		Boolean:	Xl -> Msp; SP - 1 -> SP
		Flags:		
*/
void ALU_HD6303R_PSHX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x3C: // PSHX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "PSHX");
			p->indexRegister = ((p->indexRegister & 0xff00) | MemoryRead(p, p->stackPointer));
			break;
		default:
			break;
	}
	
	p->stackPointer--;
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_PULX(HD6303R_MPU * p)
		Boolean:	SP +1 -> SP; Msp -> Xh; SP + 1 -> SP; Msp -> Xl
		Flags:		
*/
void ALU_HD6303R_PULX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x38: // PULX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "PULX");
			p->stackPointer++;
			p->indexRegister = (uint16_t)MemoryRead(p, p->stackPointer);
			p->indexRegister = ((p->indexRegister << 8) & 0xff00);
			p->stackPointer++;
			p->indexRegister = (p->indexRegister | (uint16_t)MemoryRead(p, p->stackPointer));
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
	
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SLP(HD6303R_MPU * p)
		Boolean:	A + B -> A
		Flags:		H N Z V C
*/
void ALU_HD6303R_SLP(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x1A: // SLP Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "SLP");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ABA(HD6303R_MPU * p)
		Boolean:	A + B -> A
		Flags:		H N Z V C
*/
void ALU_HD6303R_ABA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint16_t result = (p->accumulatorA + p->accumulatorB);

	bool A3 = p->accumulatorA & 0x08;
	bool B3 = p->accumulatorB & 0x08;
	bool R3 = result & 0x08;
	bool A7 = p->accumulatorA & 0x80;
	bool B7 = p->accumulatorB & 0x80;
	bool R7 = result & 0x80;

	switch (instruction) {
		case 0x1B: // ABA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ABA");
			
			p->accumulatorA = (uint8_t)result;
			break;
		default:
			break;
	}

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_H, (A3 & B3 | B3 & !R3 | !R3 & A3));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (R7));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (A7 & B7 & !R7 | !A7 & !B7 & R7));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, (A7 & B7 | B7 & !R7 | !R7 & A7));
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ABX(HD6303R_MPU * p)
		Boolean:	00:B + X -> X
		Flags:		
*/
void ALU_HD6303R_ABX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x3A: // ABX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ABX");
			p->indexRegister = (p->indexRegister + (uint16_t)p->accumulatorB);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ADCA(HD6303R_MPU * p)
		Boolean:	A + M + C -> A
		Flags:		H N Z V C
*/
void ALU_HD6303R_ADCA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result; // We use uint16_t to see if we overflow in a uint8_t.

	switch (instruction) {
		case 0x89: // ADCA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCA #$%02X", unsigned_payload);
			result = (p->accumulatorA + unsigned_payload + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x99: // ADCA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCA %02X", unsigned_payload);
			result = (p->accumulatorA + MemoryRead(p, direct_address) + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA9: // ADCA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCA %02X(x)", unsigned_payload);
			result = (p->accumulatorA + MemoryRead(p, p->indexRegister + unsigned_payload) + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB9: // ADCA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCA %04X", unsigned_payload_double);
			result = (p->accumulatorA + MemoryRead(p, unsigned_payload_double) + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	p->accumulatorA = (uint8_t)result;

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_H, (p->accumulatorA & 0x10));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ADCB(HD6303R_MPU * p)
		Boolean:	B + M + C -> B
		Flags:		H N Z V C
*/
void ALU_HD6303R_ADCB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result; // We use uint16_t to see if we overflow in a uint8_t.
	
	switch (instruction) {
		case 0xC9: // ADCB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCB #$%02X", unsigned_payload);
			result = (p->accumulatorB + unsigned_payload + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD9: // ADCB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCB %02X", unsigned_payload);
			result = (p->accumulatorB + MemoryRead(p, direct_address) + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE9: // ADCB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCB %02X(x)", unsigned_payload);
			result = (p->accumulatorB + MemoryRead(p, p->indexRegister + unsigned_payload) + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF9: // ADCB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADCB %04X", unsigned_payload_double);
			result = (p->accumulatorB + MemoryRead(p, unsigned_payload_double) + ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	p->accumulatorB = (uint8_t)result;

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_H, (p->accumulatorB & 0x10));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff)); // result is a uint16_t.
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ADDA(HD6303R_MPU * p)
		Boolean:	A + M -> A
		Flags:		H N Z V C
*/
void ALU_HD6303R_ADDA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result;

	switch (instruction) {
		case 0x8B: // ADDA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDA #$%02X", unsigned_payload);
			result = (p->accumulatorA + unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x9B: // ADDA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDA %02X", unsigned_payload);
			result = (p->accumulatorA + MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xAB: // ADDA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDA %02X(x)", unsigned_payload);
			result = (p->accumulatorA + MemoryRead(p, p->indexRegister + unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xBB: // ADDA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDA %04X", unsigned_payload_double);
			result = (p->accumulatorA + MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	p->accumulatorA = (uint8_t)result;

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_H, (p->accumulatorA & 0x10));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ADDB(HD6303R_MPU * p)
		Boolean:	B + M -> A
		Flags:		H N Z V C
*/
void ALU_HD6303R_ADDB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result;

	switch (instruction) {
		case 0xCB: // ADDB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDB #$%02X", unsigned_payload);
			result = (p->accumulatorB + unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xDB: // ADDB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDB %02X", unsigned_payload);
			result = (p->accumulatorB + MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xEB: // ADDB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDB %02X(x)", unsigned_payload);
			result = (p->accumulatorB + MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xFB: // ADDB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDB %04X", unsigned_payload_double);
			result = (p->accumulatorB + MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	p->accumulatorB = (uint8_t)result;

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_H, (p->accumulatorB & 0x10));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ADDD(HD6303R_MPU * p)
		Boolean:	D + M:(M + 1) -> D
		Flags:		N Z V C
*/
void ALU_HD6303R_ADDD(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint32_t result;

	switch (instruction) {
		case 0xC3: // ADDD Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDD #$%02X", unsigned_payload);
			result = (*(p->accumulatorD) + unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD3: // ADDD Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDD %02X", unsigned_payload);
			result = (*(p->accumulatorD) + MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE3: // ADDD Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDD %02X(x)", unsigned_payload);
			result = (*(p->accumulatorD) + MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF3: // ADDD Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ADDD %04X", unsigned_payload_double);
			result = (*(p->accumulatorD) + MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	*(p->accumulatorD) = (uint16_t)result;

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (*(p->accumulatorD) & 0x8000));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, *(p->accumulatorD));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xffff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint32_t)0x10000)>>16));
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ANDA(HD6303R_MPU * p)
		Boolean:	A & M -> A
		Flags:		N Z (0 -> V) C
*/
void ALU_HD6303R_ANDA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x84: // ANDA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDA #$%02X", unsigned_payload);
			p->accumulatorA = (p->accumulatorA & unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x94: // ANDA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDA %02X", unsigned_payload);
			p->accumulatorA = (p->accumulatorA & MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA4: // ANDA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDA %02X(x)", unsigned_payload);
			p->accumulatorA = (p->accumulatorA & MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB4: // ANDA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDA %04X", unsigned_payload_double);
			p->accumulatorA = (p->accumulatorA & MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ANDB(HD6303R_MPU * p)
		Boolean:	B & M -> B
		Flags:		N Z (0 -> V) C
*/
void ALU_HD6303R_ANDB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xC4: // ANDB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDB #$%02X", unsigned_payload);
			p->accumulatorB = (p->accumulatorB & unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD4: // ANDB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDB %02X", unsigned_payload);
			p->accumulatorB = (p->accumulatorB & MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE4: // ANDB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDB %02X(x)", unsigned_payload);
			p->accumulatorB = (p->accumulatorB & MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF4: // ANDB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ANDB %04X", unsigned_payload_double);
			p->accumulatorB = (p->accumulatorB & MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ASL(HD6303R_MPU * p)
		Boolean:	b7 -> C; b6 b5 b4 b3 b2 b1 b0 0 -> M
		Flags:		N Z V C
*/
void ALU_HD6303R_ASL(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint8_t overflow, carry, value;

	switch (instruction) {
		case 0x68: // ASL Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ASL %02X(x)", unsigned_payload);
			value = MemoryReadIndexValue(p, unsigned_payload);
			overflow = (value & 0x80);
			value = ((value << 1) & 0xfe);
			MemoryWriteIndexValue(p, unsigned_payload, value);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x78: // ASL Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ASL %04X", unsigned_payload_double);
			value = MemoryRead(p, unsigned_payload_double);
			overflow = (value & 0x80);
			value = ((value << 1) & 0xfe);
			MemoryWrite(p, unsigned_payload_double, value);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (value & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, value);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, overflow);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, carry);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ASLA(HD6303R_MPU * p)
		Boolean:	b7 -> C; b6 b5 b4 b3 b2 b1 b0 0 -> A
		Flags:		N Z V C
*/
void ALU_HD6303R_ASLA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x48: // ASLA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ASLA");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ASLB(HD6303R_MPU * p)
		Boolean:	b7 -> C; b6 b5 b4 b3 b2 b1 b0 0 -> B
		Flags:		N Z V C
*/
void ALU_HD6303R_ASLB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x58: // ASLB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ASLB");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ASLD(HD6303R_MPU * p)
		Boolean:	b15 -> C; b14 b13 b12 b11 ... b3 b2 b1 b0 0 -> D
		Flags:		N Z V C
*/
void ALU_HD6303R_ASLD(HD6303R_MPU * p)
{
	
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint32_t result;

	switch (instruction) {
		case 0x05: // ASLD Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ASLD");
			ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, !!(*(p->accumulatorD) & 0x8000));
			result = ((*(p->accumulatorD)) << 1);
			break;
		default:
			break;
	}

	*(p->accumulatorD) = (uint16_t)result;

	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, !!(*(p->accumulatorD) & 0x8000));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, *p->accumulatorD);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) ^ ALU_HD6303R_GetFlag(p,HD6303R_FLAG_C));// N xor C == 1?

	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ASR(HD6303R_MPU * p)
		Boolean:	b0 -> C; b7 b7 b6 b5 b4 b3 b2 b1 -> M;
		Flags:		N Z V C
*/
void ALU_HD6303R_ASR(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x67: // ASR Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ASR %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x77: // ASR Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ASR %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ASRA(HD6303R_MPU * p)
		Boolean:	b0 -> C; b7 b7 b6 b5 b4 b3 b2 b1 -> A;
		Flags:		N Z V C
*/
void ALU_HD6303R_ASRA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x47: // ASRA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ASRA");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ASRB(HD6303R_MPU * p)
		Boolean:	b0 -> C; b7 b7 b6 b5 b4 b3 b2 b1 -> B;
		Flags:		N Z V C
*/
void ALU_HD6303R_ASRB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x57: // ASRB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ASRB");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_BITA(HD6303R_MPU * p)
		Boolean:	A & M
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_BITA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x85: // BITA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITA #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x95: // BITA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITA %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA5: // BITA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITA %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB5: // BITA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITA %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_BITB(HD6303R_MPU * p)
		Boolean:	B & M
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_BITB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xC5: // BITB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITB #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD5: // BITB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITB %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE5: // BITB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITB %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF5: // BITB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BITB %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CBA(HD6303R_MPU * p)
		Boolean:	A - B
		Flags:		N Z V C
		N = R7
		Z = R7'+R6'+ ... R1'+R0'
		V = A7B7'R7'|A7'B7R7
		C = A7'B7 | B7R7 | R7A7'
*/
void ALU_HD6303R_CBA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t result;

	switch (instruction) {
		case 0x11: // CBA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "CBA");
			result = (p->accumulatorA - p->accumulatorB);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, result);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, ((p->accumulatorA & ~p->accumulatorB & ~result) | (~p->accumulatorA & p->accumulatorB & result))&0x80);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((~p->accumulatorA & p->accumulatorB)|(p->accumulatorB&result)|(result&~p->accumulatorA))&0x80);

	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CLR(HD6303R_MPU * p)
		Boolean:	00 -> M
		Flags:		(0 -> N) (1 -> Z) (0 -> V) (0 -> C)
*/
void ALU_HD6303R_CLR(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x6F: // CLR Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CLR %02X(x)", unsigned_payload);
			MemoryWriteIndexValue(p, unsigned_payload, 0x00);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x7F: // CLR Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CLR %04X", unsigned_payload_double);
			MemoryWrite(p, unsigned_payload_double, 0x00);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_N);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_Z);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_C);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CLRA(HD6303R_MPU * p)
		Boolean:	00 -> A
		Flags:		(0 -> N) (1 -> Z) (0 -> V) (0 -> C)
*/
void ALU_HD6303R_CLRA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x4F: // CLRA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "CLRA");
			p->accumulatorA = 0x00;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_N);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_Z);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_C);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CLRB(HD6303R_MPU * p)
		Boolean:	00 -> B
		Flags:		(0 -> N) (1 -> Z) (0 -> V) (0 -> C)
*/
void ALU_HD6303R_CLRB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x5F: // CLRB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "CLRB");
			p->accumulatorB = 0x00;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_N);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_Z);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_C);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CMPA(HD6303R_MPU * p)
		Boolean:	A - M
		Flags:		N Z V C
*/
void ALU_HD6303R_CMPA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;
	
	uint16_t result;
	
	switch (instruction) {
		case 0x81: // CMPA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPA #$%02X", unsigned_payload);
			result = (p->accumulatorA - unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x91: // CMPA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPA %02X", unsigned_payload);
			result = (p->accumulatorA - MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA1: // CMPA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPA %02X(x)", unsigned_payload);
			result = (p->accumulatorA - MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB1: // CMPA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPA %04X", unsigned_payload_double);
			result = (p->accumulatorA - MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, result);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_CMPB(HD6303R_MPU * p)
		Boolean:	B - M
		Flags:		N Z V C
*/
void ALU_HD6303R_CMPB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result;

	switch (instruction) {
		case 0xC1: // CMPB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPB #$%02X", unsigned_payload);
			result = (p->accumulatorB - unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD1: // CMPB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPB %02X", unsigned_payload);
			result = (p->accumulatorB - MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE1: // CMPB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPB %02X(x)", unsigned_payload);
			result = (p->accumulatorB - MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF1: // CMPB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "CMPB %04X", unsigned_payload_double);
			result = (p->accumulatorB - MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, result);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((result & (uint16_t)0x100))>>8);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_COM(HD6303R_MPU * p)
		Boolean:	~M -> M
		Flags:		N Z (0 -> V) (1 -> C)
*/
void ALU_HD6303R_COM(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint8_t result;

	switch (instruction) {
		case 0x63: // COM Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "COM %02X(x)", unsigned_payload);
			result = MemoryWriteIndexValue(p, unsigned_payload, (~MemoryReadIndexValue(p, unsigned_payload)));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x73: // COM Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "COM %04X", unsigned_payload_double);
			result = MemoryWrite(p, unsigned_payload_double, (~MemoryRead(p, unsigned_payload_double)));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, result);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_C);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_COMA(HD6303R_MPU * p)
		Boolean:	~A -> A
		Flags:		N Z (0 -> V) (1 -> C)
*/
void ALU_HD6303R_COMA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x43: // COMA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "COMA");
			p->accumulatorA = (~p->accumulatorA);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_C);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_COMB(HD6303R_MPU * p)
		Boolean:	~B -> B
		Flags:		N Z (0 -> V) (1 -> C)
*/
void ALU_HD6303R_COMB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x53: // COMB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "COMB");
			p->accumulatorB = (~p->accumulatorB);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_C);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_DAA(HD6303R_MPU * p)
		Boolean:	BCD(Ah) + BCD(Al) -> A
		Flags:		N Z C
*/
void ALU_HD6303R_DAA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t adj = 0;

	switch (instruction) {
		case 0x19: // DAA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "DAA");

			if ((p->accumulatorA & 0x0F) > 9 || ALU_HD6303R_GetFlag(p, HD6303R_FLAG_H)) adj += 0x06;
			if ((p->accumulatorA > 0x99) || ALU_HD6303R_GetFlag(p,HD6303R_FLAG_C)) adj += 0x60;
			p->accumulatorA = p->accumulatorA + adj;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, p->accumulatorA & 0x80);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, adj & 0x60);

	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_DEC(HD6303R_MPU * p)
		Boolean:	M - 1 -> M
		Flags:		N Z V
*/
void ALU_HD6303R_DEC(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint16_t result;

	switch (instruction) {
		case 0x6A: // DEC Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "DEC %02X(x)", unsigned_payload);
			result = (MemoryWriteIndexValue(p, unsigned_payload, (MemoryReadIndexValue(p, unsigned_payload) - 1)));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x7A: // DEC Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "DEC %04X", unsigned_payload_double);
			result = (MemoryWrite(p, unsigned_payload_double, (MemoryRead(p, unsigned_payload_double) - 1)));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, (result & 0xff));
	// @CC how can this overflow...
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, (result > 0xff));
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_DECA(HD6303R_MPU * p)
		Boolean:	A - 1 -> A
		Flags:		N Z V
*/
void ALU_HD6303R_DECA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x4A: // DECA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "DECA");
			p->accumulatorA--;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	// @CC how can this overlow... see dec
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_DECB(HD6303R_MPU * p)
		Boolean:	B - 1 -> B
		Flags:		N Z V
*/
void ALU_HD6303R_DECB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x5A: // DECB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "DECB");
			p->accumulatorB--;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	// @CC how can this overflow... (see deca)
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_EORA(HD6303R_MPU * p)
		Boolean:	A ^ M -> A
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_EORA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x88: // EORA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORA #$%02X", unsigned_payload);
			p->accumulatorA = (p->accumulatorA ^ unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x98: // EORA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORA %02X", unsigned_payload);
			p->accumulatorA = (p->accumulatorA ^ MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA8: // EORA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORA %02X(x)", unsigned_payload);
			p->accumulatorA = (p->accumulatorA ^ MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB8: // EORA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORA %04X", unsigned_payload_double);
			p->accumulatorA = (p->accumulatorA ^ MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_EORB(HD6303R_MPU * p)
		Boolean:	B ^ M -> B
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_EORB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xC8: // EORB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORB #$%02X", unsigned_payload);
			p->accumulatorB = (p->accumulatorB ^ unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD8: // EORB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORB %02X", unsigned_payload);
			p->accumulatorB = (p->accumulatorB ^ MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE8: // EORB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORB %02X(x)", unsigned_payload);
			p->accumulatorB = (p->accumulatorB ^ MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF8: // EORB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "EORB %04X", unsigned_payload_double);
			p->accumulatorB = (p->accumulatorB ^ MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_INC(HD6303R_MPU * p)
		Boolean:	M + 1 -> M
		Flags:		N Z V
*/
void ALU_HD6303R_INC(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x6C: // INC Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "INC %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x7C: // INC Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "INC %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_INCA(HD6303R_MPU * p)
		Boolean:	A + 1 -> A
		Flags:		N Z V
*/
void ALU_HD6303R_INCA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x4C: // INCA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "INCA");
			p->accumulatorA++;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, p->accumulatorA);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_V, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_INCB(HD6303R_MPU * p)
		Boolean:	B + 1 -> B
		Flags:		N Z V
*/
void ALU_HD6303R_INCB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x5C: // INCB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "INCB");
			p->accumulatorB++;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, p->accumulatorB);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_V, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_LDAA(HD6303R_MPU * p)
		Boolean:	M -> A
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_LDAA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x86: // LDAA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAA #$%02X", unsigned_payload);
			p->accumulatorA = unsigned_payload;
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x96: // LDAA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAA %02X", unsigned_payload);
			p->accumulatorA = MemoryRead(p, direct_address);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA6: // LDAA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAA %02X(x)", unsigned_payload);
			p->accumulatorA = MemoryReadIndexValue(p, unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB6: // LDAA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAA %04X", unsigned_payload_double);
			p->accumulatorA = MemoryRead(p, unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_LDAB(HD6303R_MPU * p)
		Boolean:	M -> B
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_LDAB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xC6: // LDAB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAB #$%02X", unsigned_payload);
			p->accumulatorB = unsigned_payload;
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD6: // LDAB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAB %02X", unsigned_payload);
			p->accumulatorB = MemoryRead(p, direct_address);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE6: // LDAB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAB %02X(x)", unsigned_payload);
			p->accumulatorB = MemoryReadIndexValue(p, unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF6: // LDAB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDAB %04X", unsigned_payload_double);
			p->accumulatorB = MemoryRead(p, unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_LDD(HD6303R_MPU * p)
		Boolean:	M:(M + 1) -> D
		Flags:		H I N Z V C
*/
void ALU_HD6303R_LDD(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xCC: // LDD Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDD #$%04X", unsigned_payload_double);
			*(p->accumulatorD) = (uint16_t)unsigned_payload_double;
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		case 0xDC: // LDD Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDD %02X", unsigned_payload);
			*(p->accumulatorD) = uint16_From_uint8s(MemoryRead(p, direct_address), MemoryRead(p, (direct_address + 1)));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xEC: // LDD Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDD %02X(x)", unsigned_payload);
			*(p->accumulatorD) = uint16_From_uint8s(MemoryReadIndexValue(p, unsigned_payload), MemoryReadIndexValue(p, (unsigned_payload + 1)));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xFC: // LDD Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LDD %04X", unsigned_payload_double);
			*(p->accumulatorD) = unsigned_payload_double;
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_H, (*(p->accumulatorD) & 0x0100));
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (*(p->accumulatorD) & 0x0100));
	// @CC why set I?
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, *(p->accumulatorD));
	// @CC why set V?
	// @CC why set C?
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// The same as ASL.
//void ALU_HD6303R_LSL(HD6303R_MPU * p) { ; }
//void ALU_HD6303R_LSLA(HD6303R_MPU * p) { ; }
//void ALU_HD6303R_LSLB(HD6303R_MPU * p) { ; }
//void ALU_HD6303R_LSLD(HD6303R_MPU * p) { ; }

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_LSR(HD6303R_MPU * p)
		Boolean:	b0 -> C; 0 b7 b6 b5 b4 b3 b2 b1 -> M
		Flags:		(0 -> N) Z V C
*/
void ALU_HD6303R_LSR(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x64: // LSR Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LSR %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x74: // LSR Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "LSR %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_LSRA(HD6303R_MPU * p)
		Boolean:	b0 -> C; 0 b7 b6 b5 b4 b3 b2 b1 -> A
		Flags:		(0 -> N) Z V C
*/
void ALU_HD6303R_LSRA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x44: // LSRA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "LSRA");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_LSRB(HD6303R_MPU * p)
		Boolean:	b0 -> C; 0 b7 b6 b5 b4 b3 b2 b1 -> B
		Flags:		(0 -> N) Z V C
*/
void ALU_HD6303R_LSRB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x54: // LSRB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "LSRB");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_LSRD(HD6303R_MPU * p)
		Boolean:	b0 -> C; 0 b16 b15 b14 ... b3 b2 b1 -> D
		Flags:		(0 -> N) Z V C
*/
void ALU_HD6303R_LSRD(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint32_t result;

	switch (instruction) {
		case 0x04: // LSRD Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "LSRD");
			ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, *(p->accumulatorD) & 0x01);
			result = ((*(p->accumulatorD)) >> 1);
			break;
		default:
			break;
	}

	*(p->accumulatorD) = (uint16_t)result;

	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_N);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, *p->accumulatorD);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) ^ ALU_HD6303R_GetFlag(p,HD6303R_FLAG_C));// N xor C == 1?

	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_MUL(HD6303R_MPU * p)
		Boolean:	A * B -> D
		Flags:		C
*/
void ALU_HD6303R_MUL(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	
	// The instruction set says set the carry flag, but 0xff * 0xff is only 0xfe01 which doesn't carry...
	if((((int)p->accumulatorA * (int)p->accumulatorB) & 0xffff0000)) {
		ALU_HD6303R_SetFlag(p, HD6303R_FLAG_C);
	}
	
	switch (instruction) {
		case 0x3D: // MUL Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "MUL");
			*(p->accumulatorD) = ((uint16_t)p->accumulatorA * (uint16_t)p->accumulatorB);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_NEG(HD6303R_MPU * p)
		Boolean:	00 - M -> M
		Flags:		N Z V C
*/
void ALU_HD6303R_NEG(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x60: // NEG Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "NEG %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x70: // NEG Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "NEG %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_NEGA(HD6303R_MPU * p)
		Boolean:	00 - A -> A
		Flags:		N Z V C
*/
void ALU_HD6303R_NEGA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x40: // NEGA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "NEGA");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_NEGB(HD6303R_MPU * p)
		Boolean:	00 - B -> B
		Flags:		N Z V C
*/
void ALU_HD6303R_NEGB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x50: // NEGB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "NEGB");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_NOP(HD6303R_MPU * p)
		Boolean:	PC + 1 -> PC
		Flags:		
*/
void ALU_HD6303R_NOP(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x01: // NOP Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "NOP");
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ORRA(HD6303R_MPU * p)
		Boolean:	A | M -> A
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_ORAA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x8A: // ORAA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAA #$%02X", unsigned_payload);
			p->accumulatorA = (p->accumulatorA | unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x9A: // ORAA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAA %02X", unsigned_payload);
			p->accumulatorA = (p->accumulatorA | MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xAA: // ORAA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAA %02X(x)", unsigned_payload);
			p->accumulatorA = (p->accumulatorA | MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xBA: // ORAA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAA %04X", unsigned_payload_double);
			p->accumulatorA = (p->accumulatorA | MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ORRB(HD6303R_MPU * p)
		Boolean:	B | M -> B
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_ORAB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xCA: // ORAB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAB #$%02X", unsigned_payload);
			p->accumulatorB = (p->accumulatorB | unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xDA: // ORAB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAB %02X", unsigned_payload);
			p->accumulatorB = (p->accumulatorB | MemoryRead(p, direct_address));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xEA: // ORAB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAB %02X(x)", unsigned_payload);
			p->accumulatorB = (p->accumulatorB | MemoryReadIndexValue(p, unsigned_payload));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xFA: // ORAB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ORAB %04X", unsigned_payload_double);
			p->accumulatorB = (p->accumulatorB | MemoryRead(p, unsigned_payload_double));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_PSHA(HD6303R_MPU * p)
		Boolean:	A -> Stack
		Flags:		
*/
void ALU_HD6303R_PSHA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x36: // PSHA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "PSHA");
			p->stackPointer++;
			MemoryWrite(p, p->stackPointer, p->accumulatorA);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_PSHB(HD6303R_MPU * p)
		Boolean:	B -> Stack
		Flags:		
*/
void ALU_HD6303R_PSHB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x37: // PSHB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "PSHB");
			p->stackPointer++;
			MemoryWrite(p, p->stackPointer, p->accumulatorB);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_PULA(HD6303R_MPU * p)
		Boolean:	Stack -> A
		Flags:		
*/
void ALU_HD6303R_PULA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x32: // PULA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "PULA");
			p->stackPointer++;
			p->accumulatorA = MemoryRead(p, p->stackPointer);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_PULB(HD6303R_MPU * p)
		Boolean:	Stack -> B
		Flags:		
*/
void ALU_HD6303R_PULB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x33: // PULB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "PULB");
			p->stackPointer++;
			p->accumulatorB = MemoryRead(p, p->stackPointer);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ROL(HD6303R_MPU * p)
		Boolean:	b7 -> Temp; b6 b5 b4 b3 b2 b1 b0 C -> M; Temp -> C
		Flags:		N Z V C
*/
void ALU_HD6303R_ROL(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	uint8_t result, oldBit7;

	switch (instruction) {
		case 0x69: // ROL Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ROL %02X(x)", unsigned_payload);
			oldBit7 = (MemoryReadIndexValue(p, unsigned_payload) & 0x80);
			result = MemoryWriteIndexValue(p, unsigned_payload, (MemoryReadIndexValue(p, unsigned_payload) << 1));
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x79: // ROL Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ROL %04X", unsigned_payload_double);
			oldBit7 = (MemoryRead(p, unsigned_payload_double) & 0x80);
			result = MemoryWrite(p, unsigned_payload_double, (MemoryRead(p, unsigned_payload_double) << 1));
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, oldBit7);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, result);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ROLA(HD6303R_MPU * p)
		Boolean:	b7 -> Temp; b6 b5 b4 b3 b2 b1 b0 C -> A; Temp -> C
		Flags:		N Z V C
*/
void ALU_HD6303R_ROLA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	uint8_t oldBit7 = (p->accumulatorA & 0x80);

	switch (instruction) {
		case 0x49: // ROLA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ROLA");
			p->accumulatorA = (p->accumulatorA << 1);
			p->accumulatorA = (p->accumulatorA | ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, oldBit7);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_ROLB(HD6303R_MPU * p)
		Boolean:	b7 -> Temp; b6 b5 b4 b3 b2 b1 b0 C -> B; Temp -> C
		Flags:		N Z V C
*/
void ALU_HD6303R_ROLB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	
	uint8_t oldBit7 = (p->accumulatorB & 0x80);
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, (p->accumulatorB & 0x80));
	
	switch (instruction) {
		case 0x59: // ROLB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "ROLB");
			p->accumulatorA = (p->accumulatorB << 1);
			p->accumulatorA = (p->accumulatorB | ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C));
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, oldBit7);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_ROR(HD6303R_MPU * p)
		Boolean:	b0 -> Temp; C b7 b6 b5 b4 b3 b2 b1 b0 -> M; Temp -> C
		Flags:		N Z V C
*/
void ALU_HD6303R_ROR(HD6303R_MPU * p)
{
		uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x66: // ROR Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ROR %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x76: // ROR Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "ROR %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_RORA(HD6303R_MPU * p)
		Boolean:	b0 -> Temp; C b7 b6 b5 b4 b3 b2 b1 b0 -> A; Temp -> C
		Flags:		N Z V C
*/
void ALU_HD6303R_RORA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x46: // RORA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "RORA");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_RORB(HD6303R_MPU * p)
		Boolean:	b0 -> Temp; C b7 b6 b5 b4 b3 b2 b1 b0 -> B; Temp -> C
		Flags:		N Z V C
*/
void ALU_HD6303R_RORB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x56: // RORB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "RORB");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_SBA(HD6303R_MPU * p)
		Boolean:	A - B -> A
		Flags:		N Z V C
		N = R7
		Z = R7'+R6'+ ... R1'+R0'
		V = A7B7'R7'|A7'B7R7
		C = A7'B7 | B7R7 | R7A7'
*/
void ALU_HD6303R_SBA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t result;

	switch (instruction) {
		case 0x10: // SBA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "SBA");
			result = (p->accumulatorA - p->accumulatorB);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (result & 0x80));
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, result);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_V, ((p->accumulatorA & ~p->accumulatorB & ~result) | (~p->accumulatorA & p->accumulatorB & result))&0x80);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_C, ((~p->accumulatorA & p->accumulatorB)|(p->accumulatorB&result)|(result&~p->accumulatorA))&0x80);
	p->accumulatorA = result;
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SBCA(HD6303R_MPU * p)
		Boolean:	A - M - C -> A
		Flags:		N Z V C
*/
void ALU_HD6303R_SBCA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x82: // SBCA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCA #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x92: // SBCA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCA %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA2: // SBCA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCA %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB2: // SBCA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCA %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SBCB(HD6303R_MPU * p)
		Boolean:	B - M - C -> B
		Flags:		N Z V C
*/
void ALU_HD6303R_SBCB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xC2: // SBCB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCB #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD2: // SBCB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCB %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE2: // SBCB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCB %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF2: // SBCB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SBCB %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_STAA(HD6303R_MPU * p)
		Boolean:	A -> M
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_STAA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x97: // STAA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STAA %02X", unsigned_payload);
			MemoryWrite(p, direct_address, p->accumulatorA);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA7: // STAA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STAA %02X(x)", unsigned_payload);
			MemoryWriteIndexValue(p, unsigned_payload, p->accumulatorA);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB7: // STAA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STAA %04X", unsigned_payload_double);
			MemoryWrite(p, unsigned_payload_double, p->accumulatorA);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, p->accumulatorA);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_STAB(HD6303R_MPU * p)
		Boolean:	B -> M
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_STAB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xD7: // STAB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STAB %02X", unsigned_payload);
			MemoryWrite(p, direct_address, p->accumulatorB);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE7: // STAB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STAB %02X(x)", unsigned_payload);
			MemoryWriteIndexValue(p, unsigned_payload, p->accumulatorB);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF7: // STAB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STAB %04X", unsigned_payload_double);
			MemoryWrite(p, unsigned_payload_double, p->accumulatorB);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, p->accumulatorB);
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_STD(HD6303R_MPU * p)
		Boolean:	D -> M:(M + 1)
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_STD(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xDD: // STD Direct 00xx
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STD %02X", unsigned_payload);
			MemoryWrite16(p, unsigned_payload, *p->accumulatorD);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xED: // STD Index IX+u8
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STD %02X(x)", unsigned_payload);
			MemoryWriteIndexValue16(p, unsigned_payload, *p->accumulatorD);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xFD: // STD Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "STD %04X", unsigned_payload_double);
			MemoryWrite16(p, unsigned_payload_double, *p->accumulatorD);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SUBA(HD6303R_MPU * p)
		Boolean:	A - M -> A
		Flags:		N Z V C
*/
void ALU_HD6303R_SUBA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x80: // SUBA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBA #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x90: // SUBA Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBA %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA0: // SUBA Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBA %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB0: // SUBA Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBA %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SUBB(HD6303R_MPU * p)
		Boolean:	B - M -> B
		Flags:		N Z V C
*/
void ALU_HD6303R_SUBB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0xC0: // SUBB Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBB #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xD0: // SUBB Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBB %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xE0: // SUBB Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBB %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xF0: // SUBB Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBB %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SUBD(HD6303R_MPU * p)
		Boolean:	D - M:(M + 1) -> D
		Flags:		N Z V C
*/
void ALU_HD6303R_SUBD(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x83: // SUBD Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBD #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x93: // SUBD Direct
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBD %02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xA3: // SUBD Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBD %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xB3: // SUBD Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "SUBD %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_TAB(HD6303R_MPU * p)
		Boolean:	A -> B
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_TAB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x16: // TAB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TAB");
			p->accumulatorB = p->accumulatorA;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorB);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorB & 0x80));
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_TBA(HD6303R_MPU * p)
		Boolean:	B -> A
		Flags:		N Z (0 -> V)
*/
void ALU_HD6303R_TBA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x17: // TBA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TBA");
			p->accumulatorA = p->accumulatorB;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlagIfZero(p, HD6303R_FLAG_Z, p->accumulatorA);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
	ALU_HD6303R_SetFlagIfNonZero(p, HD6303R_FLAG_N, (p->accumulatorA & 0x80));
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_XGDX(HD6303R_MPU * p)
		Boolean:	D <-> IX
		Flags:		None
*/
void ALU_HD6303R_XGDX(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint16_t Swap1 = *p->accumulatorD;
	uint16_t Swap2 = p->indexRegister;

	switch (instruction) {
		case 0x18: // XGDX Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "XGDX");
			*p->accumulatorD = Swap2;
			p->indexRegister = Swap1;
			break;
		default:
			break;
	}
	
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}


// NOT IMPLEMENTED
/*
		void ALU_HD6303R_TST(HD6303R_MPU * p)
		Boolean:	M - 00
		Flags:		N Z (0 -> V) (0 -> C)
*/
void ALU_HD6303R_TST(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x6D: // TST Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "TST %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x7D: // TST Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "TST %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_TSTA(HD6303R_MPU * p)
		Boolean:	A - 00
		Flags:		N Z (0 -> V) (0 -> C)
*/
void ALU_HD6303R_TSTA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x4D: // TSTA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TSTA");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_TSTB(HD6303R_MPU * p)
		Boolean:	B - 00
		Flags:		N Z (0 -> V) (0 -> C)
*/
void ALU_HD6303R_TSTB(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x5D: // TSTB Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TSTB");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BRA(HD6303R_MPU * p)
		Branch Test:	None
*/
void ALU_HD6303R_BRA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;
	
	switch (instruction) {
		case 0x20: // BRA Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BRA #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BRN(HD6303R_MPU * p)
		Branch Test:	None
*/
void ALU_HD6303R_BRN(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x21: // BRN Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BRN #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BCC(HD6303R_MPU * p)
		Branch Test:	C = 0
*/
void ALU_HD6303R_BCC(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x24: // BCC Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BCC #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C) == 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BCS(HD6303R_MPU * p)
		Branch Test:	C = 1
*/
void ALU_HD6303R_BCS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x25: // BCS Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BCS #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C) != 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_BLO(HD6303R_MPU * p)
		Branch Test:	Z = 1
*/
void ALU_HD6303R_BLO(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x25: // BLO Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BLO #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BEQ(HD6303R_MPU * p)
		Branch Test:	Z = 0
*/
void ALU_HD6303R_BEQ(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x27: // BEQ Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BEQ #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_Z) != 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BGE(HD6303R_MPU * p)
		Branch Test:	N ^ V = 0
*/
void ALU_HD6303R_BGE(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x2C: // BGE Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BGE #$%02X", unsigned_payload);
			
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) ^ ALU_HD6303R_GetFlag(p, HD6303R_FLAG_V) == 0)
				p->pc += signed_payload;
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BGT(HD6303R_MPU * p)
		Branch Test:	Z | (N ^ V) = 1
*/
void ALU_HD6303R_BGT(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x2E: // BGT Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BGT #$%02X", unsigned_payload);
			if ((ALU_HD6303R_GetFlag(p,HD6303R_FLAG_Z) | ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) ^ ALU_HD6303R_GetFlag(p, HD6303R_FLAG_V)) == 0)
				p->pc += signed_payload;
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BHI(HD6303R_MPU * p)
		Branch Test:	C + Z = 0
*/
void ALU_HD6303R_BHI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x22: // BHI Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BHI #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if ((ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C) | ALU_HD6303R_GetFlag(p, HD6303R_FLAG_Z)) == 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_BHS(HD6303R_MPU * p)
		Branch Test:	C = 0
*/
void ALU_HD6303R_BHS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x24: // BHS Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BHS #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BLE(HD6303R_MPU * p)
		Branch Test:	Z + (N^V) = 1
*/
void ALU_HD6303R_BLE(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x2F: // BLE Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BLE #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if ((ALU_HD6303R_GetFlag(p,HD6303R_FLAG_Z) | ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) ^ ALU_HD6303R_GetFlag(p, HD6303R_FLAG_V)) != 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BLS(HD6303R_MPU * p)
		Branch Test:	C + Z = 1
*/
void ALU_HD6303R_BLS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x23: // BLS Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BLS #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if ((ALU_HD6303R_GetFlag(p, HD6303R_FLAG_C) | ALU_HD6303R_GetFlag(p, HD6303R_FLAG_Z)) != 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BLT(HD6303R_MPU * p)
		Branch Test:	N ^ V = 1
*/
void ALU_HD6303R_BLT(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x2D: // BLT Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BLT #$%02X", unsigned_payload);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) ^ ALU_HD6303R_GetFlag(p, HD6303R_FLAG_V) != 0)
				p->pc += signed_payload;
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BMI(HD6303R_MPU * p)
		Branch Test:	N = 1
*/
void ALU_HD6303R_BMI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x2B: // BMI Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BMI #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) != 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BNE(HD6303R_MPU * p)
		Branch Test:	Z = 0
*/
void ALU_HD6303R_BNE(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x26: // BNE Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BNE #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_Z) == 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BVC(HD6303R_MPU * p)
		Branch Test:	V = 0
*/
void ALU_HD6303R_BVC(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x28: // BVC Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BVC #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_V) == 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BVS(HD6303R_MPU * p)
		Branch Test:	V = 1
*/
void ALU_HD6303R_BVS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x29: // BVS Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BVS #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_V) != 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_BPL(HD6303R_MPU * p)
		Branch Test:	N = 0
*/
void ALU_HD6303R_BPL(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));

	switch (instruction) {
		case 0x2A: // BPL Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BPL #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			if (ALU_HD6303R_GetFlag(p, HD6303R_FLAG_N) == 0)
				p->pc += signed_payload;
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_BSR(HD6303R_MPU * p)
		Boolean:	
*/
void ALU_HD6303R_BSR(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x8D: // BSR Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "BSR #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_JMP(HD6303R_MPU * p)
		Boolean:	
		Flags:		
*/
void ALU_HD6303R_JMP(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));

	switch (instruction) {
		case 0x6E: // JMP Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "JMP %02X(x)", unsigned_payload);
			p->pc = (MemoryReadIndexValue(p, unsigned_payload) - 2);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0x7E: // JMP Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "JMP %04X", unsigned_payload_double);
			p->pc = (unsigned_payload_double - 3);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_JSR(HD6303R_MPU * p)
		Boolean:	
		Flags:		
*/
void ALU_HD6303R_JSR(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x9D: // JSR Immediate
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "JSR #$%02X", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xAD: // JSR Index
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "JSR %02X(x)", unsigned_payload);
			ALU_HD6303R_IncrementPC(p, 1);
			break;
		case 0xBD: // JSR Extended
			ALU_HD6303R_SetCurrentMneunomicWithPayload(p, "JSR %04X", unsigned_payload_double);
			ALU_HD6303R_IncrementPC(p, 2);
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_RTI(HD6303R_MPU * p)
		Boolean:	
		Flags:		H I N Z V C
*/
void ALU_HD6303R_RTI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x3B: // RTI Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "RTI");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_RTS(HD6303R_MPU * p)
		Boolean:	
		Flags:		
*/
void ALU_HD6303R_RTS(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x39: // RTS Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "RTS");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_SWI(HD6303R_MPU * p)
		Boolean:	
		Flags:		(1 -> I)
*/
void ALU_HD6303R_SWI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x3F: // SWI Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "SWI");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

// NOT IMPLEMENTED
/*
		void ALU_HD6303R_WAI(HD6303R_MPU * p)
		Boolean:	
		Flags:		
*/
void ALU_HD6303R_WAI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);
	uint8_t unsigned_payload = (uint8_t)MemoryRead(p, (p->pc+1));
	int8_t signed_payload = (int8_t)MemoryRead(p, (p->pc+1));
	uint16_t unsigned_payload_double = uint16_From_uint8s(MemoryRead(p, (p->pc+1)), MemoryRead(p, (p->pc+2)));
	uint16_t direct_address = (uint16_t)unsigned_payload;

	switch (instruction) {
		case 0x3E: // WAI Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "WAI");
			break;
		default:
			break;
	}
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CLC(HD6303R_MPU * p)
		Boolean:	0 -> C
		Flags:		(0 -> C)
*/
void ALU_HD6303R_CLC(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x0C: // CLC Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "CLC");
			ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_C);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CLI(HD6303R_MPU * p)
		Boolean:	0 -> I
		Flags:		(0 -> I)
*/
void ALU_HD6303R_CLI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x0E: // CLI Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "CLI");
			ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_I);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_CLV(HD6303R_MPU * p)
		Boolean:	0 -> V
		Flags:		(0 -> V)
*/
void ALU_HD6303R_CLV(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x0A: // CLV Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "CLV");
			ALU_HD6303R_UnsetFlag(p, HD6303R_FLAG_V);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_SEC(HD6303R_MPU * p)
		Boolean:	1 -> C
		Flags:		(1 -> C)
*/
void ALU_HD6303R_SEC(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x0D: // SEC Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "SEC");
			ALU_HD6303R_SetFlag(p, HD6303R_FLAG_C);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_SEI(HD6303R_MPU * p)
		Boolean:	1 -> I
		Flags:		(1 -> I)
*/
void ALU_HD6303R_SEI(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x0F: // SEI Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "SEI");
			ALU_HD6303R_SetFlag(p, HD6303R_FLAG_I);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_SEV(HD6303R_MPU * p)
		Boolean:	1 -> V
		Flags:		(1 -> V)
*/
void ALU_HD6303R_SEV(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x0B: // SEV Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "SEV");
			ALU_HD6303R_SetFlag(p, HD6303R_FLAG_V);
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_TAP(HD6303R_MPU * p)
		Boolean:	A -> CCR
		Flags:		H I N Z V C
*/
void ALU_HD6303R_TAP(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x06: // TAP Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TAP");
			p->flagRegister = p->accumulatorA | 0xC0; // Ensure the top is set like it should be
			break;
		default:
			break;
	}

	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}

/*
		void ALU_HD6303R_TPA(HD6303R_MPU * p)
		Boolean:	CCR -> A
		Flags:		
*/
void ALU_HD6303R_TPA(HD6303R_MPU * p)
{
	uint8_t instruction = (uint8_t)MemoryRead(p, p->pc);

	switch (instruction) {
		case 0x07: // TPA Inherent
			ALU_HD6303R_SetCurrentMneunomic(p, "TPA");
			p->accumulatorA = p->flagRegister | 0xC0; // Ensure the top is set like it should be
			break;
		default:
			break;
	}
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_VERIFIED);
	ALU_HD6303R_SetFlag(p, HD6303R_FLAG_IMP);
}
