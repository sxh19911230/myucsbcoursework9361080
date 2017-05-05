#include "DecodeCode.h"


mipsinstruction decode(int value)
{
	mipsinstruction instr;
	int w;

	// TODO: fill in the fields
	
	instr.opcode = value >> 26;
	
	instr.func = (value << 26) >> 26;
	
	w = (value & 0x8000) >> 15;
	w = w | w << 1;
	w = w | w << 2;
	w = w | w << 4;
	w = w | w << 8;
	w = w | w << 16;
	w = w & 0xFFFF0000;
	instr.imm = (value & 0xFFFF) | w;

	
	instr.rs = (value << 6) >> 27;

	instr.rt = (value << 11) >> 27;

	instr.rd = (value << 16) >> 27;

	return instr;
}


