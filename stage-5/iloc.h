#ifndef ILOC_H
#define ILOC_H

typedef struct iloc_instruction {

    int     op_code;
    int     param_cout;
    char*   param1;
    char*   param2;
    char*   param3;

} ILOC;

/**
 * Gets the string for the operation from the operation code
 *
 * @param op Operation Code
 * @return A pointer to the instruction string
 */
char* get_op_string(int op);

/**
 * Prints a instruction with its parameters (including a line-break in the end)
 *
 * @param inst Pointer to a ILOC structure
 */
void print_instuction(ILOC* inst);

/**
 * Frees a ILOC structure (parameters and the structure itself)
 *
 * @param iloc Pointer to the structure
 * @return NULL
 */
ILOC* free_iloc(ILOC* iloc);

#endif
