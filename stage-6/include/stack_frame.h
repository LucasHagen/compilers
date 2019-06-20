#ifndef STACK_FRAME_H
#define STACK_FRAME_H

#include "iloc.h"

#include "stack.h"
#include "scope.h"
//struct stack_frame defined in lexeme.h

ST_FRAME* create_stack_frame(ST_LINE* function_header);
void push_stack_frame(ILOC_List* code, ST_LINE* function_header, Node* parameters);
void pop_stack_frame(ST_FRAME* frame);
int get_frame_size(ST_FRAME* frame);
void adjust_main_rsp(ST_LINE* main_register, ILOC_List* code);
void define_function_frame(ST_LINE* function_register, ILOC_List* code);
void print_parameters_code(ILOC_List* code, Node* parameters);
void copy_parameters(ILOC_List* code, ST_LINE* function_register, Node* parameters);
int get_parameter_address(ST_LINE* function_register, int argument_number);
#endif
