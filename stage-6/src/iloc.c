#include "iloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "tree.h"

/*
Authors:
- Gabriel Pakulski da Silva - 00274701
- Lucas Sonntag Hagen       - 00274698
*/

int next_iloc_label = 0;
int next_iloc_register = 0;

/**
 * Gets the string for the operation from the operation code
 *
 * @param op Operation Code
 * @return A pointer to the instruction string
 */
char* get_op_string(int op)
{
    switch (op) {
        case ILOC_NOP:
        	return "nop";
        case ILOC_ADD:
        	return "add";
        case ILOC_SUB:
        	return "sub";
        case ILOC_MULT:
        	return "mult";
        case ILOC_DIV:
        	return "div";
        case ILOC_ADDI:
        	return "addI";
        case ILOC_SUBI:
        	return "subI";
        case ILOC_RSUBI:
        	return "rsubI";
        case ILOC_MULTI:
        	return "multI";
        case ILOC_DIVI:
        	return "divI";
        case ILOC_RDIVI:
        	return "rdivI";
        case ILOC_LSHIFT:
        	return "lshift";
        case ILOC_LSHIFTI:
        	return "lshiftI";
        case ILOC_RSHIFT:
        	return "rshift";
        case ILOC_RSHIFTI:
        	return "rshiftI";
        case ILOC_AND:
        	return "and";
        case ILOC_ANDI:
        	return "andI";
        case ILOC_OR:
        	return "or";
        case ILOC_ORI:
        	return "orI";
        case ILOC_XOR:
        	return "xor";
        case ILOC_XORI:
        	return "xorI";
        case ILOC_LOADI:
        	return "loadI";
        case ILOC_LOAD:
        	return "load";
        case ILOC_LOADAI:
        	return "loadAI";
        case ILOC_LOADA0:
        	return "loadA0";
        case ILOC_CLOAD:
        	return "cload";
        case ILOC_CLOADAI:
        	return "cloadAI";
        case ILOC_CLOADA0:
        	return "cloadA0";
        case ILOC_STORE:
        	return "store";
        case ILOC_STOREAI:
        	return "storeAI";
        case ILOC_STOREA0:
        	return "storeA0";
        case ILOC_CSTORE:
        	return "cstore";
        case ILOC_CSTOREAI:
        	return "cstoreAI";
        case ILOC_CSTOREA0:
        	return "cstoreA0";
        case ILOC_I2I:
        	return "i2i";
        case ILOC_C2C:
        	return "c2c";
        case ILOC_C2I:
        	return "c2i";
        case ILOC_I2C:
        	return "i2c";
        case ILOC_JUMPI:
        	return "jumpI";
        case ILOC_JUMP:
        	return "jump";
        case ILOC_CBR:
        	return "cbr";
        case ILOC_CMP_LT:
        	return "cmp_LT";
        case ILOC_CMP_LE:
        	return "cmp_LE";
        case ILOC_CMP_EQ:
        	return "cmp_EQ";
        case ILOC_CMP_GE:
        	return "cmp_GE";
        case ILOC_CMP_GT:
        	return "cmp_GT";
        case ILOC_CMP_NE:
        	return "cmp_NE";
        case ILOC_HALT:
            return "halt";
    }

    return "";
}

/**
 * Prints a instruction with its parameters (including a line-break in the end)
 *
 * @param inst Pointer to a ILOC structure
 */
void print_instruction(ILOC* inst)
{
    if(inst == NULL)
    {
        return;
    }
    else if (inst->op_code == ILOC_NOP)
    {
        printf("nop\n");
    }
    else if (inst->op_code >= ILOC_ADD && inst->op_code <= ILOC_CLOADA0)
    {
        printf("%s %s, %s => %s\n", get_op_string(inst->op_code), inst->param1, inst->param2, inst->param3);
    }
    else if (inst->op_code >= ILOC_LOADI && inst->op_code <= ILOC_I2C)
    {
        printf("%s %s => %s\n", get_op_string(inst->op_code), inst->param1, inst->param2);
    }
    else if (inst->op_code >= ILOC_CSTOREAI && inst->op_code <= ILOC_STOREA0)
    {
        printf("%s %s => %s, %s\n", get_op_string(inst->op_code), inst->param1, inst->param2, inst->param3);
    }
    else if (inst->op_code >= ILOC_JUMPI && inst->op_code <= ILOC_JUMP)
    {
        printf("%s -> %s\n", get_op_string(inst->op_code), inst->param1);
    }
    else if (inst->op_code == ILOC_CBR)
    {
        printf("%s %s -> %s, %s\n", get_op_string(inst->op_code), inst->param1, inst->param2, inst->param3);
    }
    else if (inst->op_code >= ILOC_CMP_LT && inst->op_code <= ILOC_CMP_NE)
    {
        printf("%s %s, %s -> %s\n", get_op_string(inst->op_code), inst->param1, inst->param2, inst->param3);
    }
    else if (inst->op_code == ILOC_LABEL)
    {
        printf("%s:\n", inst->param1);
    }
    else if (inst->op_code == ILOC_HALT)
    {
        printf("%s\n", get_op_string(inst->op_code));
    }
    else if (inst->op_code == ILOC_COMMENT)
    {
        printf("// %s\n", inst->param1);
    }
}

void print_iloc_list(ILOC_List* list)
{
    if(list != NULL)
    {
        for(int i = 0; i < list->count; i++)
        {
            print_instruction(list->children[i]);
        }
    }
}

ILOC* create_iloc(int op_code, char* param1, char* param2, char* param3)
{
    ILOC* result = (ILOC*) malloc(sizeof(ILOC));

    result->op_code = op_code;
    result->param1  = param1 == NULL ? NULL : strdup(param1);
    result->param2  = param2 == NULL ? NULL : strdup(param2);
    result->param3  = param3 == NULL ? NULL : strdup(param3);

    return result;
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
        #ifdef COMP_DEBUG
        printf("[%p] FREE:", iloc);
        print_instruction(iloc);
        #endif

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

ILOC_List* free_iloc_list(ILOC_List* list)
{
    if(list != NULL)
    {
        for(int i = 0; i < list->count; i++)
        {
            list->children[i] = free_iloc(list->children[i]);
        }
        free(list->children);
        free(list);
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
 * Adds a value to the beginning ILOC_List
 */
void add_iloc_beg(ILOC_List* list, ILOC* value)
{
    if(list->count == 0)
    {
        list->count = 1;
        list->children = (ILOC**) malloc(sizeof(ILOC*));
        list->children[list->count - 1] = value;
    }
    else
    {
        ILOC** old = list->children;

        list->count++;
        list->children = (ILOC**) malloc(list->count * sizeof(ILOC*));

        list->children[0] = copy_iloc(value);
        memcpy(list->children + 1, old, (list->count - 1) * sizeof(ILOC*));

        free(old);
    }
}

ILOC_List* concat_list(ILOC_List* left, ILOC_List* right)
{
    ILOC_List* result = create_empty_list();

    for(int i = 0; i < left->count; i++)
    {
        add_iloc(result, copy_iloc(left->children[i]));
    }
    for(int i = 0; i < right->count; i++)
    {
        add_iloc(result, copy_iloc(right->children[i]));
    }

    return result;
}

ILOC_List* copy_list(ILOC_List* src)
{
    ILOC_List* result = create_empty_list();

    for(int i = 0; i < src->count; i++)
    {
        add_iloc(result, copy_iloc(src->children[i]));
    }

    return result;
}

/**
 * Adds all elements from src to the beggining of dest
 *
 * ILOCs are NOT deep copied
 */
void add_all_beg(ILOC_List* dest, ILOC_List* src)
{
    if(src != NULL && src->count > 0)
    {
        int oldSize = dest->count;
        ILOC** old = dest->children;

        dest->count += src->count;
        dest->children = (ILOC**) malloc(dest->count * sizeof(ILOC*));

        // memcpy(dest->children, src->children, src->count * sizeof(ILOC*));
        for(int i = 0; i < src->count; i++)
        {
            dest->children[i] = copy_iloc(src->children[i]);
        }

        memcpy(dest->children + src->count, old, oldSize * sizeof(ILOC*));

        free(old);
    }
}

/**
 * Adds all elements from src to the end of dest
 *
 * ILOCs are NOT deep copied
 */
void add_all_end(ILOC_List* dest, ILOC_List* src)
{
    if(src != NULL && src->count > 0)
    {
        for(int i = 0; i < src->count; i++)
        {
            add_iloc(dest, copy_iloc(src->children[i]));
        }
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
        dest->param1 = strdup(src->param1);
    } else {
        dest->param1 = NULL;
    }
    if(src->param2 != NULL) {
        dest->param2 = strdup(src->param2);
    } else {
        dest->param2 = NULL;
    }
    if(src->param3 != NULL) {
        dest->param3 = strdup(src->param3);
    } else {
        dest->param3 = NULL;
    }

    return dest;
}

/**
 * Generates a new UNIQUE label
 */
ILOC* new_label()
{
    int label = next_iloc_label++;
    char* lText = (char*) malloc(sizeof(char) * 16);

    sprintf(lText, "L%d", label);

    ILOC* iloc = create_iloc(ILOC_LABEL, lText, NULL, NULL);

    free(lText);
    return iloc;
}

/**
 * Generates a new UNIQUE register
 */
char* new_register()
{
    int reg = next_iloc_register++;
    char* rText = (char*) malloc(sizeof(char) * 16);

    sprintf(rText, "r%d", reg);

    return rText;
}

/**
 * Converts a integer to a char*.
 * The function allocates a new char* with 16 bytes.
 */
char* int_to_char(int number)
{
    char* text = (char*) malloc(sizeof(char) * 16);

    sprintf(text, "%d", number);

    return text;
}

char* reg_convert_int_to_bool(ILOC_List* list, char* source)
{
    char* reg = new_register();
    char* zero = new_register();
    add_iloc(list, create_iloc(ILOC_LOADI, "0", zero, NULL));
    add_iloc(list, create_iloc(ILOC_CMP_NE,
                        source,
                        zero,
                        reg));
    free(zero);

    return reg;
}

char* get_return_register (int num){
    int reg = num;
    char* rText = (char*) malloc(sizeof(char) * 16);

    sprintf(rText, "r%d", reg);

    return rText;
}

int get_last_register_number(){
    return next_iloc_register-1;
}

ILOC_List* save_registers(int start, int end)
{
    ILOC_List* list = create_empty_list();

    char reg[100];

    for(int i = start; i <= end; i++)
    {
        sprintf(reg, "r%d", i);
        add_iloc(list, create_iloc(ILOC_STORE, reg, "rsp", NULL));
        add_iloc(list, create_iloc(ILOC_ADDI, "rsp", "1", "rsp"));
    }

    return list;
}

ILOC_List* load_registers(int start, int end)
{
    ILOC_List* list = create_empty_list();
    char reg[100];

    for(int i = end; i >= start; i--)
    {
        sprintf(reg, "r%d", i);
        add_iloc(list, create_iloc(ILOC_SUBI, "rsp", "1", "rsp"));
        add_iloc(list, create_iloc(ILOC_LOAD, "rsp", reg, NULL));
    }

    return list;
}
