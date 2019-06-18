#ifndef STACK_FRAME_H
#define STACK_FRAME_H

#include "iloc.h"
#include "lexeme.h"
#include "defines.h"

//struct stack_frame defined in lexeme.h

ST_FRAME* create_stack_frame(ST_LINE* function_header);
void push_stack_frame(ILOC_List* code, ST_LINE* function_header);
void pop_stack_frame(ST_FRAME* frame);
int get_frame_size(ST_FRAME* frame);
void adjust_main_rsp(ST_LINE* main_register, ILOC_List* code);
void define_function_frame(ST_LINE* function_register, ILOC_List* code);
#endif
