#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "mips.h" // for execute_syscall()
#include "types.h"

void execute_instruction(Instruction instruction,Processor* processor,Byte *memory) {

	/* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
	switch(instruction.oPCode) {
	case 0x0: // oPCode == 0x0(SPECIAL)
		switch(instruction.rtype.funct) {
		case 0x0: // funct == 0x0 (SHIFT LEFT LOGICAL)
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] << instruction.rtype.shamt;
			processor->PC +=4;
			break;
		case 0x2: // funct == 0x2 (srl)
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] >> instruction.rtype.shamt;
			processor->PC += 4;
			break;

		case 0x3: // funct == 0x3 (sra)
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rt] >> instruction.rtype.shamt;
			processor->PC += 4;
			break;

		case 0x8: // funct == 0x8 (jr)
			processor->PC = processor->R[instruction.rtype.rs];
			break;

		case 0x9: // funct == 0x9 (jalr)
			processor->R[instruction.rtype.rd] = processor->PC + 4;
			processor->PC = processor->R[instruction.rtype.rs];
			break;
		case 0x10: //MOVE FROM HI
			processor->R[instruction.rtype.rd] = processor->RHI;
			break;
		case 0x12: //MOVE FROM LO
			processor->R[instruction.rtype.rd] = processor->RLO;
			break;
		case 0x18: //MULTIPLY
			int64_t tmp = ((int32_t) processor->R[instruction.rtype.rs]) * ((int32_t)processor->R[instruction.rtype.rt]);
			processor->RLO = (int32_t)(tmp >> 32);
			processor->RHI = (int32_t)tmp; //casting to 32bits will throw away upper 32bits and take lower 32bits
			break;
		case 0x19: //MULTIPLE UNSIGNED
			uint64_t tmp = processor->R[instruction.rtype.rs] * processor->R[instruction.rtype.rt];
			processor->RLO = (uint32_t)tmp >> 32;
			processor->RHI = (uint32_t)tmp;
			break;
		case 0x21: //ADDITION UNSIGNED
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] + processor->R[instruction.rtype.rt];
			processor->PC += 4;
			break;
		case 0x23: //SUBTRACTION UNSIGNED
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] - processor->R[instruction.rtype.rt];
			processor->PC += 4;
			break;
		case 0x24: // funct == 0x24 (AND)
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] & processor->R[instruction.rtype.rt];
			processor->PC += 4;
			break;
		case 0x25: //OR
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt];
			processor->PC += 4;
			break;
		case 0x26: //XOR
			processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs] ^ processor->R[instruction.rtype.rt];
			processor->PC += 4;
			break;
		case 0x27: //NOR
			processor->R[instruction.rtype.rd] = ~(processor->R[instruction.rtype.rs] | processor->R[instruction.rtype.rt]);
			processor->PC += 4;
			break;
		case 0x2a: //SLT
			if (processor->R[instruction.rtype.rs] < processor->R[instruction.rtype.rt]) {
				processor->R[instruction.rtype.rd] = 1;
			} else {
				processor->R[instruction.rtype.rs] = 0;
			}
			processor->PC += 4;
			break;
		case 0x2b: //SLTU
			if (processor->R[instruction.rtype.rs] < processor->R[instruction.rtype.rt]) {
				processor->R[instruction.rtype.rd] = 1;
			} else {
				processor->R[instruction.rtype.rs] = 0;
			}
			processor->PC += 4;
			break;
		case 0xc: // funct == 0xc (SYSCALL)
			execute_syscall(processor);
			processor->PC += 4;
			break;
		default: // undefined funct
			fprintf(stderr,"%s: PC=%08x,illegal function=%08x\n",__FUNCTION__,processor->PC,instruction.bits);
			exit(-1);
			break;
		}
		break;
		case 0x2: // oPCode == 0x2 (J)
			processor->PC = ((processor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
			break;
		case 0x3: // opcode == 0x3 (jal)
			processor->R[31] = processor->PC + 4;
			processor->PC = ((proessor->PC+4) & 0xf0000000) | (instruction.jtype.addr << 2);
			break;

		case 0x4: // opcode == 0x4 (beq)
			if (processor->R[instruction.itype.rs] == processor->R[instruction.itype.rt]) {
				processor->PC = processor->PC + 4 + ((int32_t)((int16_t)(instruction.itype.imm)))*4;
			} else {
				processor->PC += 4;
			}
			break;

		case 0x5: // opcode == 0x5 (bne)
			if (processor->R[instruction.itype.rs] != processor->R[instruction.itype.rt]) {
				processor->PC = processor->PC + 4 + ((int32_t)((int16_t)(instruction.itype.imm)))*4;
			} else {
				processor->PC += 4;
			}
			break;

		case 0x9: // opcode == 0x9 (addiu)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] + (uint32_t)((uint16_t)(instruction.itype.imm));
			processor->PC += 4;
			break;

		case 0xa: // opcode == 0xa (slti)
			if ((int) processor->R[instruction.itype.rt] < (uint32_t)((uint16_t)(instruction.itype.imm))) {
				processor->R[instruction.itype.rt] = 1;
			} else {
				processor->R[instruction.itype.rt] = 0;
			}
			processor->PC += 4;
			break;

		case 0xb: // opcode == 0xb (sltiu)
			if ((int)processor->R[instruction.itype.rt] < (uint32_t)((uint16_t)(instruction.itype.imm))) {
				processor->R[instruction.itype.rt] = 1;
			} else {
				processor->R[instruction.itype.rt] = 0;
			}
			processor->PC += 4;
			break;

		case 0xc: // opcode == 0xc (andi)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] & instruction.itype.imm;
			processor->PC += 4;
			break;
		case 0xd: // oPCode == 0xd (ORI)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] | instruction.itype.imm;
			processor->PC += 4;
			break;

		case 0xe: // opcode == 0xe (xori)
			processor->R[instruction.itype.rt] = processor->R[instruction.itype.rs] ^ instruction.itype.imm;
			processor->PC += 4;
			break;

		case 0xf: // opcode == 0xf (lui)
			processor->R[instruction.itype.rt] = instruction.itype.imm << 16;
			processor->PC += 4;
			break;

		case 0x20: // opcode == 0x20 (lb)
			processor->R[instruction.itype.rt] = (uint32_t)((uint16_t)load(processor->R[instruction.itype.rs] + (uint32_t)((uint16_t)instruction.itype.imm), LENGTH_BYTE));
			processor->PC += 4;
			break;

		case 0x23: // opcode == 0x23 (lw)
			processor->R[instruction.itype.rt] = load(processor->R[instruction.itype.rs]+ (uint32_t)((uint16_t)instruction.itype.imm), LENGTH_WORD);
			processor->PC += 4;
			break;

		case 0x24: // opcode == 0x24 (lbu)
			processor->R[instruction.itype.rt] = load(processor->R[instruction.itype.rs] + (uint32_t)((uint16_t)instruction.itype.imm), LENGTH_BYTE);
			processor->PC += 4;
			break;

			//void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value) {

		case 0x28: // opcode == 0x28 (sb)
			store(processor->R[instruction.itype.rs] + (uint32_t)((uint16_t)instruction.itype.imm), LENGTH_BYTE, processor->R[instruction.itype.rt]);
			processor->PC += 4;
			break;

		case 0x2b: // opcode == 0x2b (sw)
			store(processor->R[instruction.itype.rs] + (uint32_t)((uint16_t)instruction.itype.imm), LENGTH_WORD, processor->R[instruction.itype.rt]);
			processor->PC += 4;
			break;


		default: // undefined oPCode
			fprintf(stderr,"%s: PC=%08x,illegal instruction: %08x\n",__FUNCTION__,processor->PC,instruction.bits);
			exit(-1);
			break;
	}
}


int check(Address address,Alignment alignment) {

	if (address < 1 || address > MEMORY_SPACE || address % alignment != 0 || (address+alignment) > MEMORY_SPACE) { 
		return 0;
	}		//Should I worry about alignment? But we're always passing in positive values.
	else { 
		return 1;
	}
}

void store(Byte *memory,Address address,Alignment alignment,Word value) {
	if(!check(address,alignment)) {
		fprintf(stderr,"%s: bad write=%08x\n",__FUNCTION__,address);
		exit(-1);
	}

}

Word load(Byte *memory,Address address,Alignment alignment) {
	if(!check(address,alignment)) {
		fprintf(stderr,"%s: bad read=%08x\n",__FUNCTION__,address);
		exit(-1);
	}

	return *(Word*)(memory+address);
}
