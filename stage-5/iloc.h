#ifndef ILOC_H
#define ILOC_H

typedef struct iloc_instruction {

    int     op_code;
    int     param_cout;
    char*   param1;
    char*   param2;
    char*   param3;

} ILOC;

char* get_op_string(int op);

void print_instuction(ILOC* inst);

#endif
