#include "iloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

char* get_op_string(int op)
{
    char* str;

    switch (op) {
        case ILOC_NOP:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "nop");
        	break;
        case ILOC_ADD:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "add");
        	break;
        case ILOC_SUB:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "sub");
        	break;
        case ILOC_MULT:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "mult");
        	break;
        case ILOC_DIV:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "div");
        	break;
        case ILOC_ADDI:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "addI");
        	break;
        case ILOC_SUBI:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "subI");
        	break;
        case ILOC_RSUBI:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "rsubI");
        	break;
        case ILOC_MULTI:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "multI");
        	break;
        case ILOC_DIVI:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "divI");
        	break;
        case ILOC_RDIVI:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "rdivI");
        	break;
        case ILOC_LSHIFT:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "lshift");
        	break;
        case ILOC_LSHIFTI:
        	str = (char*) malloc(sizeof(char) * 8);
        	strcpy(str, "lshiftI");
        	break;
        case ILOC_RSHIFT:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "rshift");
        	break;
        case ILOC_RSHIFTI:
        	str = (char*) malloc(sizeof(char) * 8);
        	strcpy(str, "rshiftI");
        	break;
        case ILOC_AND:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "and");
        	break;
        case ILOC_ANDI:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "andI");
        	break;
        case ILOC_OR:
        	str = (char*) malloc(sizeof(char) * 3);
        	strcpy(str, "or");
        	break;
        case ILOC_ORI:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "orI");
        	break;
        case ILOC_XOR:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "xor");
        	break;
        case ILOC_XORI:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "xorI");
        	break;
        case ILOC_LOADI:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "loadI");
        	break;
        case ILOC_LOAD:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "load");
        	break;
        case ILOC_LOADAI:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "loadAI");
        	break;
        case ILOC_LOADA0:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "loadA0");
        	break;
        case ILOC_CLOAD:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "cload");
        	break;
        case ILOC_CLOADAI:
        	str = (char*) malloc(sizeof(char) * 8);
        	strcpy(str, "cloadAI");
        	break;
        case ILOC_CLOADA0:
        	str = (char*) malloc(sizeof(char) * 8);
        	strcpy(str, "cloadA0");
        	break;
        case ILOC_STORE:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "store");
        	break;
        case ILOC_STOREAI:
        	str = (char*) malloc(sizeof(char) * 8);
        	strcpy(str, "storeAI");
        	break;
        case ILOC_STOREA0:
        	str = (char*) malloc(sizeof(char) * 8);
        	strcpy(str, "storeA0");
        	break;
        case ILOC_CSTORE:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cstore");
        	break;
        case ILOC_CSTOREAI:
        	str = (char*) malloc(sizeof(char) * 9);
        	strcpy(str, "cstoreAI");
        	break;
        case ILOC_CSTOREA0:
        	str = (char*) malloc(sizeof(char) * 9);
        	strcpy(str, "cstoreA0");
        	break;
        case ILOC_I2I:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "i2i");
        	break;
        case ILOC_C2C:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "c2c");
        	break;
        case ILOC_C2I:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "c2i");
        	break;
        case ILOC_I2C:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "i2c");
        	break;
        case ILOC_JUMPI:
        	str = (char*) malloc(sizeof(char) * 6);
        	strcpy(str, "jumpI");
        	break;
        case ILOC_JUMP:
        	str = (char*) malloc(sizeof(char) * 5);
        	strcpy(str, "jump");
        	break;
        case ILOC_CBR:
        	str = (char*) malloc(sizeof(char) * 4);
        	strcpy(str, "cbr");
        	break;
        case ILOC_CMP_LT:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cmp_LT");
        	break;
        case ILOC_CMP_LE:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cmp_LE");
        	break;
        case ILOC_CMP_EQ:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cmp_EQ");
        	break;
        case ILOC_CMP_GE:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cmp_GE");
        	break;
        case ILOC_CMP_GT:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cmp_GT");
        	break;
        case ILOC_CMP_NE:
        	str = (char*) malloc(sizeof(char) * 7);
        	strcpy(str, "cmp_NE");
        	break;
        default:
            str = NULL;
    }

    return str;
}

void print_instuction(ILOC* inst)
{
    if (inst == ILOC_NOP)
    {
        printf("nop\n");
    }
    else if (inst->op_code >= ILOC_ADD && inst->op_code <= ILOC_CLOADA0)
    {
        char* inst_str = get_op_string(inst->op_code);
        printf("%s %s, %s => %s\n", inst_str, inst->param1, inst->param2, inst->param3);
        free(inst_str);
    }
}
