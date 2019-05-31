#include "iloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

/**
 * Gets the string for the operation from the operation code
 *
 * @param op Operation Code
 * @return A pointer to the instruction string
 */
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

/**
 * Prints a instruction with its parameters (including a line-break in the end)
 *
 * @param inst Pointer to a ILOC structure
 */
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
    else if (inst->op_code >= ILOC_LOADI && inst->op_code <= ILOC_I2C)
    {
        char* inst_str = get_op_string(inst->op_code);
        printf("%s %s => %s\n", inst_str, inst->param1, inst->param2);
        free(inst_str);
    }
    else if (inst->op_code >= ILOC_CSTOREAI && inst->op_code <= ILOC_STOREA0)
    {
        char* inst_str = get_op_string(inst->op_code);
        printf("%s %s => %s, %s\n", inst_str, inst->param1, inst->param2, inst->param3);
        free(inst_str);
    }
    else if (inst->op_code >= ILOC_JUMPI && inst->op_code <= ILOC_JUMP)
    {
        char* inst_str = get_op_string(inst->op_code);
        printf("%s -> %s\n", inst_str, inst->param1);
        free(inst_str);
    }
    else if (inst->op_code == ILOC_CBR)
    {
        char* inst_str = get_op_string(inst->op_code);
        printf("%s %s -> %s, %s\n", inst_str, inst->param1, inst->param2, inst->param3);
        free(inst_str);
    }
    else if (inst->op_code >= ILOC_CMP_LT && inst->op_code <= ILOC_CMP_NE)
    {
        char* inst_str = get_op_string(inst->op_code);
        printf("%s %s, %s -> %s\n", inst_str, inst->param1, inst->param2, inst->param3);
        free(inst_str);
    }
    else if (inst->op_code == ILOC_LABEL)
    {
        printf("%s:\n", inst->param1);
    }
}

/**
 * Frees a ILOC structure (parameters and the structure itself)
 *
 * @param iloc Pointer to the structure
 * @return NULL
 */
ILOC* free_iloc(ILOC* iloc)
{
    if(iloc != NULL)
    {
        if(iloc->param1 != NULL)
        {
            free(iloc->param1);
        }
        if(iloc->param2 != NULL)
        {
            free(iloc->param2);
        }
        if(iloc->param3 != NULL)
        {
            free(iloc->param3);
        }
        free(iloc);
    }

    return NULL;
}

/**
 * Creates a empty iloc list
 */
ILOC_List* create_empty_list()
{
    ILOC_List* list = (ILOC_List*) malloc(sizeof(ILOC_List));

    list->children = NULL;
    list->count    = 0;

    return list;
}

/**
 * Creates a list with one element
 */
ILOC_List* create_list(ILOC* value)
{
    ILOC_List* list = (ILOC_List*) malloc(sizeof(ILOC_List));

    list->children = (ILOC**) malloc(sizeof(ILOC*));
    list->count = 1;

    list->children[0] = value;

    return list;
}

/**
 * Adds a value to the ILOC_List
 */
void add_iloc(ILOC_List* list, ILOC* value)
{
    if(list->count == 0)
    {
        list->count = 1;
        list->children = (ILOC**) malloc(sizeof(ILOC*));
    }
    else
    {
        list->count++;
        list->children = (ILOC**) realloc(list->children,
            list->count * sizeof(ILOC*));
    }

    list->children[list->count - 1] = value;
}

/**
 * Adds all elements from src to dest (deep-copy)
 */
void concat_list(ILOC_List* dest, ILOC_List* src)
{
    int size1 = dest->count;
    dest->count += src->count;
    dest->children = (ILOC**) realloc(dest->children, dest->count * sizeof(ILOC*));

    for(int i = 0; i < src->count; i++)
    {
        dest->children[i + size1] = copy_iloc(src->children[i]);
    }
}

/**
 * Duplicates a ILOC (allocates a new pointer)
 */
ILOC* copy_iloc(ILOC* src)
{
    ILOC* dest = (ILOC*) malloc(sizeof(ILOC));
    dest->op_code = src->op_code;

    if(src->param1 != NULL) {
        dest->param1 = strdup(dest->param1);
    } else {
        dest->param1 = NULL;
    }
    if(src->param2 != NULL) {
        dest->param2 = strdup(dest->param2);
    } else {
        dest->param2 = NULL;
    }
    if(src->param3 != NULL) {
        dest->param3 = strdup(dest->param3);
    } else {
        dest->param3 = NULL;
    }

    return dest;
}
