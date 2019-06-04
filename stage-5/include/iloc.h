#ifndef ILOC_H
#define ILOC_H

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

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
void print_instruction(ILOC* inst);

/**
 * Prints a list of instructions
 *
 * @param list pointer to the list
 */
void print_iloc_list(ILOC_List* list);

/**
 * Creates the ILOC with the parameters given
 *
 * @param op_code Instruction
 * @parma param1 Param 1 or NULL
 * @parma param2 Param 2 or NULL
 * @parma param3 Param 3 or NULL
 */
ILOC* create_iloc(int op_code, char* param1, char* param2, char* param3);

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
 * Creates a new ILOC_List containing all ILOCs from left + right
 *
 * ILOCs are NOT deep copied
 */
ILOC_List* concat_list(ILOC_List* left, ILOC_List* right);

/**
 * Adds all elements from src to the beggining of dest
 *
 * ILOCs are NOT deep copied
 */
void add_all_beg(ILOC_List* dest, ILOC_List* src);

/**
 * Adds all elements from src to the end of dest
 *
 * ILOCs are NOT deep copied
 */
void add_all_end(ILOC_List* dest, ILOC_List* src);

/**
 * Duplicates a ILOC (deep-copy)
 *
 * @param src Source
 * @return Pointer to new ILOC with same contents
 */
ILOC* copy_iloc(ILOC* src);

/**
 * Generates a new UNIQUE label
 */
ILOC* new_label();

/**
 * Generates a new UNIQUE register
 */
char* new_register();

/**
 * Allocates a new char* and writes the number on it
 */
char* int_to_char(int number);

/**
 * Adds the instructions needed to convert a integer (in register source) to a new register
 *
 * @param list List where the instructions will be Added
 * @param source Source Register
 * @return Register with the converted value
 */
char* reg_convert_int_to_bool(ILOC_List* list, char* source);

#endif
