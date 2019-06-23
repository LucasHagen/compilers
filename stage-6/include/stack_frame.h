#ifndef STACK_FRAME_H
#define STACK_FRAME_H

#include "iloc.h"

#include "stack.h"
#include "scope.h"
//struct stack_frame defined in lexeme.h

ST_FRAME* create_stack_frame(ST_LINE* function_header);


/** Formato do Frame:
 *
 *  Estado da máquina
 *  Endereço de Retorno
 *  Valor de Retorno
 *  Link Estático
 *  Link Dinâmico
 *  Variáveis locais
 *  Parâmetros
 */
void push_stack_frame(ILOC_List* code, ST_LINE* function_header, Node* parameters);

void pop_stack_frame(ST_FRAME* frame);

int get_frame_size(ST_FRAME* frame);

void adjust_main_rsp(ST_LINE* main_register, ILOC_List* code);

void define_function_frame(ST_LINE* function_register, ILOC_List* code);

void print_parameters_code(ILOC_List* code, Node* parameters);

int get_parameters_size(ST_LINE* function_register);

void copy_parameters(ILOC_List* code, ST_LINE* function_register, Node* parameters);

/**
 * get_parameter_address(ST_LINE* function_register, int argument_number)
 * The address rfp+0 corresponds to the last parameter
 *
 * Example: function(int x, int y)
 *          {
 *              int j;
 *              j = 2;
 *          }
 * x address: rfp+0
 * y address: rfp+4
 * j address: rfp+8
 */
int get_parameter_address(ST_LINE* function_register, int argument_number);


void stack_func_call();

void stack_func_entered();

void stack_func_exit(Node* function);

void stack_func_returned();

#endif
