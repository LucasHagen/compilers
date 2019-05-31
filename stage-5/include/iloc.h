#ifndef ILOC_H
#define ILOC_H

typedef struct iloc_instruction {

    int     op_code;
    char*   param1;
    char*   param2;
    char*   param3;

} ILOC;

typedef struct iloc_list {
    ILOC**  children;
    int     count;
} ILOC_List;

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

/**
 * Creates a empty iloc list
 */
ILOC_List* create_empty_list();

/**
 * Creates a list with one element
 */
ILOC_List* create_list(ILOC* value);

/**
 * Adds a value to the ILOC_List
 */
void add_iloc(ILOC_List* list, ILOC* value);

/**
 * Adds all elements from src to dest (deep-copy)
 *
 * @param dest Destination list
 * @param src Source list
 */
void concat_list(ILOC_List* dest, ILOC_List* src);

/**
 * Duplicates a ILOC (deep-copy)
 *
 * @param src Source
 * @return Pointer to new ILOC with same contents
 */
ILOC* copy_iloc(ILOC* src);

#endif
