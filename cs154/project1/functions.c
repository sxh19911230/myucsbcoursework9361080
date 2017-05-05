
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"

// these are the structures used in this simulator


// global variables
// register file
int regfile[32];
// instruction memory
int instmem[100];  // only support 100 static instructions
// data memory
int datamem[1024];
// program counter
int pc;

// these are the different functions you need to write
int load(char *filename);
void fetch(InstInfo *);
void decode(InstInfo *);
void execute(InstInfo *);
void memory(InstInfo *);
void writeback(InstInfo *);

/* load
 *
 * Given the filename, which is a text file that 
 * contains the instructions stored as integers 
 *
 * You will need to load it into your global structure that 
 * stores all of the instructions.
 *
 * The return value is the maxpc - the number of instructions
 * in the file
 */
int load(char *filename)
{
	FILE *file=fopen(filename,"r");
	int n = 0;
	while (!feof(file)) {	
		fscanf (file, "%d", &instmem[n++]);
	}
	fclose(file);
	return n-1;
}

/* fetch
 *
 * This fetches the next instruction and updates the program counter.
 * "fetching" means filling in the inst field of the instruction.
 */
void fetch(InstInfo *instruction)
{
	instruction->pc=pc;
	instruction->inst=instmem[pc++];
}

/* decode
 *
 * This decodes an instruction.  It looks at the inst field of the 
 * instruction.  Then it decodes the fields into the fields data 
 * member.  The first one is given to you.
 *
 * Then it checks the op code.  Depending on what the opcode is, it
 * fills in all of the signals for that instruction.
 */
void decode(InstInfo *instruction)
{
	// fill in the signals and fields
	int val = instruction->inst;
	int op, func;
	instruction->fields.op = (val >> 26) & 0x03f;
	// fill in the rest of the fields here
        instruction->fields.rt = (val >> 16) & 0x01f;
        instruction->fields.rs = (val >> 21) & 0x01f;

	instruction->fields.func = val & 0x03f;
	instruction->fields.rd = (val >> 11) & 0x01f;
	instruction->fields.imm = val  << 16 >> 16;
	// now fill in the signals

	// if it is an add (example only, please modify the code accordingly!)
	if (instruction->fields.op == 49){
		instruction->signals.aluop = 2;
		instruction->signals.mw = 0;
		instruction->signals.mr = 0;
		instruction->signals.mtr = 0;
		instruction->signals.asrc = 1;
		instruction->signals.btype = 0;
		instruction->signals.rdst = 0;
		instruction->signals.rw = 1;
		sprintf(instruction->string,"addi $%d, $%d, %d",
			instruction->fields.rt, instruction->fields.rs, 
			instruction->fields.imm);
		instruction->destreg = instruction->fields.rt;
	}

	if (instruction->fields.op == 17) {
                instruction->signals.aluop = 2;
                instruction->signals.mw = 0;
                instruction->signals.mr = 1;
                instruction->signals.mtr = 1;
                instruction->signals.asrc = 1;
                instruction->signals.btype = 0;
                instruction->signals.rdst = 0;
                instruction->signals.rw = 1;
                sprintf(instruction->string,"lw $%d, %d($%d)",
                        instruction->fields.rt, instruction->fields.imm,
                        instruction->fields.rs);
                instruction->destreg = instruction->fields.rt;

	}
	if (instruction->fields.op == 18) {
                instruction->signals.aluop = 2;
                instruction->signals.mw = 1;
                instruction->signals.mr = 0;
                instruction->signals.mtr = -1;
                instruction->signals.asrc = 1;
                instruction->signals.btype = 0;
                instruction->signals.rdst = -1;
                instruction->signals.rw = 0;
                sprintf(instruction->string,"sw $%d, %d($%d)",
                        instruction->fields.rt, instruction->fields.imm,
                        instruction->fields.rs);
                instruction->destreg = -1;

        }
	if (instruction->fields.op == 10) {
                instruction->signals.aluop = 3;
                instruction->signals.mw = 0;
                instruction->signals.mr = 0;
                instruction->signals.mtr = -1;
                instruction->signals.asrc = 0;
                instruction->signals.btype = 3;
                instruction->signals.rdst = -1;
                instruction->signals.rw = 0;
                sprintf(instruction->string,"beq $%d, $%d, %d",
                        instruction->fields.rs, instruction->fields.rt,
                        instruction->fields.imm);
                instruction->destreg = -1;

        }

	if (instruction->fields.op == 37) {
                instruction->signals.aluop = -1;
                instruction->signals.mw = 0;
                instruction->signals.mr = 0;
                instruction->signals.mtr = -1;
                instruction->signals.asrc = -1;
                instruction->signals.btype = 2;
                instruction->signals.rdst = -1;
                instruction->signals.rw = 0;
                sprintf(instruction->string,"jr $%d",
                        instruction->fields.rs);
                instruction->destreg = -1;

        }
	
	if (instruction->fields.op == 8) {
                instruction->signals.aluop = -1;
                instruction->signals.mw = 0;
                instruction->signals.mr = 0;
                instruction->signals.mtr = 2;
                instruction->signals.asrc = -1;
                instruction->signals.btype = 1;
                instruction->signals.rdst = 2;
                instruction->signals.rw = 1;
                sprintf(instruction->string,"jal %d",
                        instruction->fields.imm);
                instruction->destreg = -1;
        }

	if (instruction->fields.op == 32){
                instruction->signals.mw = 0;
                instruction->signals.mr = 0;
                instruction->signals.mtr = 0;
                instruction->signals.asrc = 0;
                instruction->signals.btype = 0;
                instruction->signals.rw = 1;
				instruction->signals.rdst = 1;
		if (instruction->fields.func == 32) {
			instruction->signals.aluop = 2;
			
                	sprintf(instruction->string,"add $%d, $%d, $%d",
                        	instruction->fields.rd, instruction->fields.rs,
                        	instruction->fields.rt);
		}
		if (instruction->fields.func == 36) {
                        instruction->signals.aluop = 0;

                        sprintf(instruction->string,"and $%d, $%d, $%d",
                                instruction->fields.rd, instruction->fields.rs,
                                instruction->fields.rt);
                }

		if (instruction->fields.func == 40) {
                        instruction->signals.aluop = 3;

                        sprintf(instruction->string,"sub $%d, $%d, $%d",
                                instruction->fields.rd, instruction->fields.rs,
                                instruction->fields.rt);
                }
		if (instruction->fields.func == 48) {
                        instruction->signals.aluop = 7;

                        sprintf(instruction->string,"sgt $%d, $%d, $%d",
                                instruction->fields.rd, instruction->fields.rs,
                                instruction->fields.rt);
                }

                instruction->destreg = instruction->fields.rd;
        }
	// fill in s1data and input2
	instruction->input1 = instruction->fields.rs;
	instruction->s1data = regfile[instruction->fields.rs];
	instruction->input2 = instruction->fields.rt;
	instruction->s2data = regfile[instruction->fields.rt];
}

/* execute
 *
 * This fills in the aluout value into the instruction and destdata
 */

void execute(InstInfo *instruction)
{
        int v1, v2, result;
        v1 = instruction->s1data;
        if (instruction->signals.asrc == 1)
                v2 = instruction->fields.imm;
        else
                v2 = instruction->s2data;
        if (instruction->signals.aluop == 0)
                result = v1 & v2;
        else if (instruction->signals.aluop == 1)
                result = ~v1;
        else if (instruction->signals.aluop == 2)
                result = v1 + v2;
        else if (instruction->signals.aluop == 3)
                result = v1 - v2;
        else if (instruction->signals.aluop == 4)
                result = v1 ^ v2;
        else if (instruction->signals.aluop == 5)
                result = v1 | v2;
        else if (instruction->signals.aluop == 6)
                result = (v1 < v2)? 1:0;
        else if (instruction->signals.aluop == 7)
                result = (v1 > v2)? 1:0;
        instruction->aluout = result;
		
}


/* memory
 *
 * If this is a load or a store, perform the memory operation
 */
void memory(InstInfo *instruction)
{
        if (instruction->signals.mr == 1) {
		instruction->memout = datamem[regfile[instruction->fields.rs] + instruction->fields.imm];
		//regfile[instruction->destreg] = datamem[instruction->fields.rs + instruction->fields.imm];
//		printf("lw: datamem[%i] = %i\n", regfile[instruction->fields.rs] + instruction->fields.imm, datamem[regfile[instruction->fields.rs] + instruction->fields.imm]);
	}
	 if (instruction->signals.mw == 1) { 
                datamem[regfile[instruction->fields.rs] + instruction->fields.imm] = regfile[instruction->fields.rt];
//		printf("sw: datamem[%i] = %i\n",regfile[instruction->fields.rs] + instruction->fields.imm, datamem[regfile[instruction->fields.rs] + instruction->fields.imm]);
	}
}

/* writeback
 *
 * If a register file is supposed to be written, write to it now
 */
void writeback(InstInfo *instruction)
{
	if (instruction->signals.rw) {
		if (!instruction->signals.mtr) regfile[instruction->destreg] = instruction->aluout;
		if (instruction->signals.mtr == 1) regfile[instruction->fields.rt] = instruction->memout;
	}
}

/* setPCWithInfo
 *
 * branch instruction will overwrite PC
*/
void setPCWithInfo(InstInfo *instruction)
{
        if (instruction->signals.btype == 1) {

			regfile[31] = pc;
			pc = instruction->fields.imm;

		}
		if (instruction->signals.btype == 2) pc = regfile[instruction->fields.rs];

		if (instruction->signals.btype == 3 && instruction->s1data == instruction->s2data) {
		
			pc = pc + instruction->fields.imm - 1;
//			printf("test: %i\n", instruction->fields.imm);
		}
}

