#include "stack_frame.h"
#include "iloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int main_flag;
extern ILOC* main_label;

ST_FRAME* create_stack_frame(ST_LINE* function_header){
    ST_FRAME* frame = (ST_FRAME *) malloc(sizeof(struct stack_frame));
    int i;

    frame->dynamic_link         = -1;
    frame->static_link          = -1;
    frame->local_variables_size = function_header->local_variables_size;
    frame->function_args        = function_header->function_args;
    frame->return_value         = -1;
    frame->return_address       = -1;
    memset(frame->machine_state,0,MACHINE_STATE_SIZE);

    #ifdef COMP_DEBUG
        printf("Function: %s -> Local variables size: %d\n",function_header->id, function_header->local_variables_size);
    #endif

    return frame;
}
/** Formato do Frame:
 *
 *  Estado da máquina
 *  Endereço de Retorno
 *  Valor de Retorno
 *  Link Estático
 *  Link Dinâmico
 *  Parâmetros
 *  Variáveis locais
 *
 *  TODO:
 *
 *  get the link addresses and update the registers (rfp, rsp
 *
 */
void push_stack_frame(ILOC_List* code, ST_LINE* function_header){
    int dl_address              = function_header->frame->local_variables_size;
    int sl_address              = function_header->frame->local_variables_size+SIZE_INT;
    int return_value_address    = function_header->frame->local_variables_size+2*SIZE_INT;
    int return_address          = function_header->frame->local_variables_size+3*SIZE_INT;
    int machine_state_address   = function_header->frame->local_variables_size+4*SIZE_INT;

    char* temp_rpc = new_register();
    char* zero = new_register();
    add_iloc(code, create_iloc(ILOC_LOADI, "0", zero, NULL));

    // estado
    // Return Address
    add_iloc(code, create_iloc(ILOC_ADDI, "rpc", "7", temp_rpc));
    add_iloc(code, create_iloc(ILOC_STOREAI, temp_rpc, "rsp", "0"));
    // Static Link
    add_iloc(code, create_iloc(ILOC_STOREAI,  zero, "rsp", "4"));
    // Dynamic Link
    add_iloc(code, create_iloc(ILOC_STOREAI, "rfp", "rsp", "8"));
    // param

    // locals

    // INCREMENT RFP AND RSP
    add_iloc(code, create_iloc(ILOC_I2I,  "rsp", "rfp", NULL));
    add_iloc(code, create_iloc(ILOC_ADDI, "rsp", "12", "rsp"));

    add_iloc(code,create_iloc(ILOC_JUMPI, function_header->function_label->param1, NULL, NULL));
    define_function_frame(function_header, code);
}

void pop_stack_frame(ST_FRAME* frame){
}

int get_frame_size(ST_FRAME* frame){
    int size = 0;
    size+=sizeof(frame->dynamic_link);
    size+=sizeof(frame->static_link);
    size+=frame->local_variables_size;
    size+=frame->return_value;
    size+=frame->return_address;
    size+=MACHINE_STATE_SIZE;
    return size;
}

void adjust_main_rsp(ST_LINE* main_register, ILOC_List* code){
    ILOC_List* new_code = create_empty_list();

    int size = get_frame_size(main_register->frame);
    add_iloc(new_code,create_iloc(ILOC_ADDI,"rfp",int_to_char(size),"rsp"));
    add_all_beg(code,new_code);

    define_function_frame(main_register, code);

    free(new_code);
}

/**
 *  TODO:
 *
 *  adjust the frame values main_register->frame
 *  and write them trough ILOC instructions
 *
 *  figure out a way to get the return_address
 *  and what to do with return_value
 */
void define_function_frame(ST_LINE* function_register, ILOC_List* code){
    ILOC_List* new_code = create_empty_list();

    int dl_address              = function_register->frame->local_variables_size;
    int sl_address              = function_register->frame->local_variables_size + SIZE_INT;
    int return_value_address    = function_register->frame->local_variables_size + 2 * SIZE_INT;
    int return_address          = function_register->frame->local_variables_size + 3 * SIZE_INT;
    int machine_state_address   = function_register->frame->local_variables_size + 4 * SIZE_INT;

    add_iloc(new_code, create_iloc(ILOC_STOREAI, "rfp", "rfp", int_to_char(dl_address)));
    add_iloc(new_code, create_iloc(ILOC_STOREAI, "rfp", "rfp", int_to_char(sl_address)));
    add_all_beg(code,new_code);
    free(new_code);
}
