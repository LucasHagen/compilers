#include "stack_frame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "iloc.h"
#include "scope.h"
#include "stack.h"

extern int main_flag;
extern int start_reg;
extern int return_flag;
extern Stack* scope_stack;
extern ILOC* main_label;
extern Scope* scope_list;
extern int scope_list_size;

ST_FRAME* create_stack_frame(ST_LINE* function_header){
    ST_FRAME* frame = (ST_FRAME *) malloc(sizeof(struct stack_frame));

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
 *  Variáveis locais
 *  Parâmetros
 */
void push_stack_frame(ILOC_List* code, ST_LINE* function_header, Node* parameters){
    int dl_address              = function_header->frame->local_variables_size;
    int sl_address              = function_header->frame->local_variables_size + SIZE_INT;
    int return_value_address    = function_header->frame->local_variables_size + 2 * SIZE_INT;
    int return_address          = function_header->frame->local_variables_size + 3 * SIZE_INT;

    char* temp_rpc = new_register();
    char* zero = new_register();
    add_iloc(code, create_iloc(ILOC_LOADI, "0", zero, NULL));

    // estado
    int hops = 7 + function_header->num_function_args;
    // Return Address
    add_iloc(code, create_iloc(ILOC_ADDI, "rpc", int_to_char(hops), temp_rpc));
    add_iloc(code, create_iloc(ILOC_STOREAI, temp_rpc, "rsp", int_to_char(return_address)));
    // Static Link
    add_iloc(code, create_iloc(ILOC_STOREAI,  zero, "rsp", int_to_char(sl_address)));
    // Dynamic Link
    add_iloc(code, create_iloc(ILOC_STOREAI, "rfp", "rsp", int_to_char(dl_address)));
    // param

    // locals

    // INCREMENT RFP AND RSP
    add_iloc(code, create_iloc(ILOC_I2I,  "rsp", "rfp", NULL));
    add_iloc(code, create_iloc(ILOC_ADDI, "rsp", int_to_char(get_frame_size(function_header->frame)), "rsp"));

    copy_parameters(code, function_header, parameters);

    add_iloc(code,create_iloc(ILOC_JUMPI, function_header->function_label->param1, NULL, NULL));
    define_function_frame(function_header, code);
}

void pop_stack_frame(ST_FRAME* frame){
}

int get_frame_size(ST_FRAME* frame){
    int size = 0;
    size += sizeof(frame->dynamic_link);
    size += sizeof(frame->static_link);
    size += sizeof(frame->local_variables_size);
    size += sizeof(frame->return_value);
    size += sizeof(frame->return_address);
    size += MACHINE_STATE_SIZE;
    size += scope_stack->children[scope_stack->size - 1]->used_size;
    return size;
}

void adjust_main_rsp(ST_LINE* main_register, ILOC_List* code){
    int size = get_frame_size(main_register->frame);
    if(!main_flag)
    {
        add_all_beg(code, save_registers(start_reg, get_last_register_number() + 1));
    }
    add_iloc_beg(code, create_iloc(ILOC_ADDI, "rfp", int_to_char(size),"rsp"));
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

    //add_iloc(new_code, create_iloc(ILOC_STOREAI, "rfp", "rfp", int_to_char(dl_address)));
    //add_iloc(new_code, create_iloc(ILOC_STOREAI, "rfp", "rfp", int_to_char(sl_address)));
    add_all_beg(code,new_code);
    free(new_code);
}

void copy_parameters(ILOC_List* code, ST_LINE* function_register, Node* parameters){
    ST_LINE* line;
    int i;
    Node* aux = parameters;

    for(i=0;i<function_register->num_function_args;i++){
        add_iloc(code,create_iloc(ILOC_STOREAI,
                                    aux->temp,
                                    "rfp",
                                    int_to_char(get_parameter_address(function_register,i))));
        aux = aux->seq;
    }
}

int get_parameters_size(ST_LINE* function_register){
    int size = 0;
    for(int i = 0; i < function_register->local_variables_size; i++){
        if(function_register->function_args[i].type == INT)
            size += SIZE_INT;
        else if(function_register->function_args[i].type == BOOL){
            size += SIZE_BOOL;
        }
    }
    return size;
}

int get_parameter_address(ST_LINE* function_register, int argument_number){
    //int local_variables_size = function_register->local_variables_size;
    //int parameters_size = get_parameters_size(function_register);
    int address = 0;
    for(int i=0;i<=argument_number;i++){
        if(i>0){
            if(function_register->function_args[i-1].type == INT)
                address += SIZE_INT;
            else if(function_register->function_args[i-1].type == BOOL){
                address += SIZE_BOOL;
            }
        }
    }
    return address;
}

void print_parameters_code(ILOC_List* code, Node* parameters){
    int i;
    Node* aux = parameters;
    for(i=0;i<count_params(parameters);i++){
        add_all_end(code,aux->code);
        aux=aux->seq;
    }
}


void stack_func_exit(Node* function)
{
    ST_LINE* line = identifier_in_scope(scope_stack->children[0], function->n_func_decl.identifier->token_value.v_string);
    add_iloc(function->code, line->exit_label);
    if(main_flag){
        if(line) {
            line->local_variables_size = top(scope_stack)->used_size;
            line->frame = create_stack_frame(line);
        }

        add_iloc(function->code, create_iloc(ILOC_HALT, NULL, NULL, NULL));
        main_flag = 0;
    }
    else
    {
        if(return_flag != 0){
    		add_iloc(function->code,
                    create_iloc(ILOC_STOREAI,
    					        line->return_reg,
    					        "rfp",
    					        int_to_char(line->frame->local_variables_size + 2 * SIZE_INT)));
    		return_flag = 0;
    	}
        int dl_address = line->frame->local_variables_size;
        int return_address = line->frame->local_variables_size + 3 * SIZE_INT;
        char* return_addr = new_register();

        add_all_end(function->code, load_registers(start_reg, get_last_register_number()));

        add_iloc(function->code, create_iloc(ILOC_LOADAI, "rfp", int_to_char(return_address), return_addr)); //obtém o valor do endereço de retorno
        add_iloc(function->code, create_iloc(ILOC_I2I,  "rfp", "rsp", NULL)); //obtém o antigo RSP
        add_iloc(function->code, create_iloc(ILOC_LOADAI, "rfp", int_to_char(dl_address), "rfp")); //obtém o antigo RFP
        add_iloc(function->code, create_iloc(ILOC_JUMP, return_addr, NULL, NULL));
    }
}
