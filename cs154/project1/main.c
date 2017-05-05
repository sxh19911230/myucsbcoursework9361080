
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"

void pipe(InstInfo*);
void dataHandler(InstInfo*);
int stall = 0;
//int bstall = 0;
int main(int argc, char *argv[])
{
	int count = 0;
	InstInfo curInst[6];
	InstInfo *fetchInst = &curInst[0],
		*decodeInst = &curInst[1],
		*executeInst = &curInst[2],
		*memoryInst = &curInst[3],
		*writebackInst = &curInst[4],
		*delayedInst = &curInst[5];
	int i;
	for ( i = 0; i < 6; i++) {
		curInst[i].inst = 0;
		curInst[i].string[0] = 0;
	}
	int cycle = 0;
	int maxpc;
	FILE *program;
	if (argc != 2) 
	{
		printf("Usage: sim filename\n");
		exit(0);
	}

	maxpc = load(argv[1]);
//	printLoad(maxpc);
	//if (pc < maxpc) fetch(fetchInst);
	while (pc < maxpc || fetchInst->inst||decodeInst->inst||executeInst->inst||memoryInst->inst||writebackInst->inst)
	{
		if (stall) {
			stall = 0;
			printf("wocaowocao\n");
		}
//		else if (bstall) bstall = 0;
		else {
			if (pc < maxpc) {
				fetch(fetchInst);
				decode(fetchInst);
				count++;
			}
			else fetchInst->inst = 0;
		}
		if (memoryInst->inst) memory(memoryInst);
		if (writebackInst->inst) {
			writeback(writebackInst);

				if (writebackInst->fields.rt == fetchInst->fields.rs)
                                        fetchInst->s1data = regfile[writebackInst->fields.rt];
                                if (writebackInst->fields.rt == fetchInst->fields.rt)
                                        fetchInst->s2data = regfile[writebackInst->fields.rt];
				if (writebackInst->fields.rt == decodeInst->fields.rs)
					decodeInst->s1data = regfile[writebackInst->fields.rt];
				if (writebackInst->fields.rt == decodeInst->fields.rt)
					decodeInst->s2data = regfile[writebackInst->fields.rt];
				if (writebackInst->fields.rt == executeInst->fields.rs) 
					executeInst->s1data = regfile[writebackInst->fields.rt];
				if (writebackInst->fields.rt == executeInst->fields.rt) 
					executeInst->s2data = regfile[writebackInst->fields.rt];
		}
/*
		if (decodeInst->inst && decodeInst->signals.btype == 3
                        && decodeInst->fields.rs != executeInst->destreg
                        && decodeInst->fields.rt != executeInst->destreg
			&& decodeInst->fields.rs != memoryInst->destreg
                        && decodeInst->fields.rt != memoryInst->destreg) {
				fetchInst->inst = 0;
                                        fetchInst->string[0] = 0;
                                        fetchInst->fields.rs = -1;
                                        fetchInst->fields.rt = -1;
                                        fetchInst->destreg = -1;
				
				setPCWithInfo(decodeInst);
				decodeInst->inst = 0;

                }

*/
		if (executeInst->inst) {
                        dataHandler(curInst);
                        if (!stall) {
				execute(executeInst);
				setPCWithInfo(executeInst);
				
				if (executeInst->signals.btype == 3 && !executeInst->aluout) {
//					printf("test\n");
					/*
					if (pc < maxpc) {
                				fetch(fetchInst);
                				decode(fetchInst);
						count--;
        				}

	        			else fetchInst->inst = 0;
*/
					count--;
					//fetchInst->inst = 0;
        			        fetchInst->string[0] = 0;
        			        fetchInst->fields.rs = -1;
        			        fetchInst->fields.rt = -1;
	        		        fetchInst->destreg = -1;
				} else if (executeInst->signals.btype == 1 || executeInst->signals.btype == 2) {
/*					if (pc < maxpc) {
                                                fetch(fetchInst);
                                                decode(fetchInst);
                                            }
                                        else fetchInst->inst = 0;
					count--;
*/                                      //fetchInst->inst = 0;
                                        fetchInst->string[0] = 0;
                                        fetchInst->fields.rs = -1;
                                        fetchInst->fields.rt = -1;
                                        fetchInst->destreg = -1;
				}
				
			}
                }

		printP2(fetchInst, decodeInst, executeInst, memoryInst, writebackInst, cycle++);
		
		if (decodeInst->inst && decodeInst->signals.btype == 3
                        && decodeInst->fields.rs != executeInst->destreg
                        && decodeInst->fields.rt != executeInst->destreg
                        && decodeInst->fields.rs != memoryInst->destreg
                        && decodeInst->fields.rt != memoryInst->destreg) {
                                /*fetchInst->inst = 0;
				//if(stall) printf("wocaowcao\n\n\n");
                                        fetchInst->string[0] = 0;
                                        fetchInst->fields.rs = -1;
                                        fetchInst->fields.rt = -1;
                                        fetchInst->destreg = -1;

                                setPCWithInfo(decodeInst);
                                decodeInst->inst = 0;
				count--;
				*/
				stall = 1;
                }

		
		pipe(curInst);
	}
	printf("Cycles: %i\nInstructions Executed: %i\n",cycle, count);
	exit(0);
}


void pipe(InstInfo *curInst) {
	int i;
/*
	if (bstall) {
		curInst[5] = curInst[4];
		curInst[4] = curInst[3];
		curInst[3] = curInst[2];
                curInst[2] = curInst[1];
		curInst[1].inst = 0;
                curInst[1].string[0] = 0;
		curInst[1].fields.rs = -1;
		curInst[1].fields.rt = -1;
		curInst[1].destreg = -1;
		curInst[1].signals.btype = -1;
	}
	else */if (stall) {
//		printf("test2\n");
		curInst[5] = curInst[4];
                curInst[4] = curInst[3];
		curInst[3] = curInst[2];
                curInst[2].inst = 0;
                curInst[2].string[0] = 0;
                curInst[2].fields.rs = -1;
                curInst[2].fields.rt = -1;
                curInst[2].destreg = -1;

	} else {
		for (i = 5; i > 0; i--) {
			curInst[i] = curInst[i - 1];
		}
		curInst[0].string[0] = 0;
	}
}

void dataHandler(InstInfo* ptr) {
//	if (ptr[1].signals.btype == 3) bstall = 1;
//	else {
	 //printf("test: %i, %i, %i, %i, %i, %i\n", ptr[2].fields.rs, ptr[2].fields.rd, ptr[3].fields.rs, ptr[3].fields.rd, ptr[4].fields.rs, ptr[4].fields.rd);
	if (ptr[2].inst && ptr[1].fields.rs == ptr[2].destreg && ptr[2].signals.mtr == 1) stall = 1;
	
	else if (ptr[3].inst && ptr[2].fields.rs == ptr[3].destreg) {
//		printf("test1: %i, %i\n", ptr[2].fields.rs, ptr[3].destreg);
		if (!ptr[3].signals.mtr)
			ptr[2].s1data =  ptr[3].aluout;
	}
	else if (ptr[4].inst && ptr[2].fields.rs == ptr[4].destreg) {
//		printf("test2: %i, %i\n", ptr[2].fields.rs, ptr[4].destreg);
		if (!ptr[4].signals.mtr)
                        ptr[2].s1data =  ptr[4].aluout;
                if (ptr[4].signals.mtr == 1)
			ptr[2].s1data = datamem[regfile[ptr[4].fields.rs] +  ptr[4].fields.imm];
		

	}
	
	if ((ptr[1].fields.op == 32 || ptr[1].fields.op == 10) && !stall && ptr[2].inst && ptr[1].fields.rt == ptr[2].destreg && ptr[2].signals.mtr == 1) stall = 1;
	else if ((ptr[2].fields.op == 32 || ptr[2].fields.op == 10) && !stall) {
		if (ptr[3].inst && ptr[2].fields.rt == ptr[3].destreg) {
//			printf("test3: %i, %i\n", ptr[2].fields.rt, ptr[3].destreg);
 	               if (!ptr[3].signals.mtr)
 	                       ptr[2].s2data =  ptr[3].aluout;
 	       }
 	       else if (ptr[4].inst && ptr[2].fields.rt == ptr[4].destreg) {
//			printf("test4: %i, %i\n", ptr[2].fields.rt, ptr[4].destreg);
 	               if (!ptr[4].signals.mtr)
 	                       ptr[2].s2data =  ptr[4].aluout;
 	               if (ptr[4].signals.mtr == 1)
 	                       ptr[2].s2data = datamem[regfile[ptr[4].fields.rs] +  ptr[4].fields.imm];


 	       }
	}
	
}
/* print
 *
 * prints out the state of the simulator after each instruction
 */
void print(InstInfo *inst, int count)
{
	int i, j;
	printf("Cycle %d: %d\n",count,inst->inst);
	printf("%s\n",inst->string);
	printf("Fields: {rd: %d, rs: %d, rt: %d, imm: %d}\n",
		inst->fields.rd, inst->fields.rs, inst->fields.rt, inst->fields.imm);
	printf("Control Bits:\n{alu: %d, mw: %d, mr: %d, mtr: %d, asrc: %d, bt: %d, rdst: %d, rw: %d}\n",
		inst->signals.aluop, inst->signals.mw, inst->signals.mr, inst->signals.mtr, inst->signals.asrc,
		inst->signals.btype, inst->signals.rdst, inst->signals.rw);
	printf("ALU Result: %d\n",inst->aluout);
	if (inst->signals.mr)
		printf("Mem Result: %d\n",inst->memout);
	else
		printf("Mem Result: X\n");
	for(i=0;i<8;i++)
	{
		for(j=0;j<32;j+=8)
			printf("$%d: %4d ",i+j,regfile[i+j]);
		printf("\n");
	}
	printf("\n");
}
/*
 * print out the loaded instructions.  This is to verify your loader
 * works.
 */
void printLoad(int max)
{
	int i;
	for(i=0;i<max;i++)
		printf("%d\n",instmem[i]);
}
