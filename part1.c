#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"

void decode_instruction(Instruction instruction) {
    
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    switch(instruction.opcode) {
        case 0x0: // opcode == 0x0 (SPECIAL)
            switch(instruction.rtype.funct) {
				case 0x0: //SHIFT LEFT LOGICAL
					printf("sll\t$%d,$%d,%u\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
					break;
				case 0x2: //SHIFT RIGHT LOGICAL
					printf("srl\t$%d,$%d,%u\n",instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
					break;
				case 0x3: //SHIFT RIGHT ARITHMETIC
					printf("sra\t$%d,$%d,%u\n", instruction.rtype.rd,instruction.rtype.rt,instruction.rtype.shamt);
					break;
				case 0x8: //JUMP REGISTER
					printf("jr\t$%d\n",instruction.rtype.rs);
					break;
				case 0x9: //JUMP AND LINK REGISTER
					printf("jalr\t$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs);
					break;
                case 0xc: //SYSCALL
                    printf("syscall\n");
                    break; 
				case 0x10: //MOVE FROM HI
					 printf("mfhi\t$%d\n",instruction.rtype.rd);
					 break;
				case 0x12: //MOVE FROM LO
					 printf("mflo\t$%d\n",instruction.rtype.rd);
					 break;
				case 0x18: //MULTIPLY
					 printf("mult\t$%d,$%d\n",instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x19: //MULTIPLE UNSIGNED
					 printf("multu\t$%d,$%d\n",instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x21: //ADDITION UNSIGNED
					 printf("addu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x23: //SUBTRACTION UNSIGNED
					 printf("subu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
                case 0x24: //AND
                    printf("and\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
                    break;
				case 0x25: //OR
					 printf("or\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x26: //XOR
					 printf("xor\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x27: //NOR
					 printf("nor\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x2a: //SLT
					 printf("slt\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
				case 0x2b: //SLTU
					 printf("sltu\t$%d,$%d,$%d\n",instruction.rtype.rd,instruction.rtype.rs,instruction.rtype.rt);
					 break;
                default: //undefined funct
                    fprintf(stderr,"%s: illegal function: %08x\n",__FUNCTION__,instruction.bits);
                    exit(-1);
                    break;
            }
			break;
        case 0x2: // opcode == 0x2 (J)
            printf("j\t0x%x\n",instruction.jtype.addr*4);
            break;
		case 0x3: //JAL
			printf("jal\t0x%x\n",instruction.jtype.addr*4);
			break;
		case 0x4: //BEQ
			printf("beq\t$%d,$%d,%d\n", instruction.itype.rs,instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm)*4);
			break;
		case 0x5: //BNE
			printf("bne\t$%d,$%d,%d\n", instruction.itype.rs,instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm)*4);
			break;
		case 0x9: //ADDIU
			printf("addiu\t$%d,$%d,%d\n", instruction.itype.rt,instruction.itype.rs,(int32_t)((int16_t)instruction.itype.imm));
			break;
		case 0xa: //SLTI
			printf("slti\t$%d,$%d,%d\n", instruction.itype.rt,instruction.itype.rs,(int32_t)((int16_t)instruction.itype.imm));
			break;
		case 0xb: //SLTIU
			printf("sltiu\t$%d,$%d,%d\n", instruction.itype.rt,instruction.itype.rs,(int32_t)((int16_t)instruction.itype.imm));
			break;
		case 0xc: //ANDI
			printf("andi\t$%d,$%d,0x%x\n", instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0xd: // opcode == 0xd (ORI)
            printf("ori\t$%d,$%d,0x%x\n",instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
            break;
		case 0xe: //XORI
			printf("xori\t$%d,$%d,0x%x\n", instruction.itype.rt,instruction.itype.rs,instruction.itype.imm);
			break;
		case 0xf: //LUI
			printf("lui\t$%d,0x%x\n", instruction.itype.rt,instruction.itype.imm);
			break;
        case 0x20: //LB
            printf("lb\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x21: //LH
            printf("lh\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x23: //LW
            printf("lw\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x24: //LBU
            printf("lbu\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x25: //LHU
            printf("lhu\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x28:  //SB
            printf("sb\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x29:  //SH
            printf("sh\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        case 0x2b:  //SW
            printf("sw\t$%d,%d($%d)\n",instruction.itype.rt,(int32_t)((int16_t)instruction.itype.imm),instruction.itype.rs);
            break;
        default: // undefined opcode
            fprintf(stderr,"%s: illegal instruction: %08x\n",__FUNCTION__,instruction.bits);
            exit(-1);
            break;
    }
}
