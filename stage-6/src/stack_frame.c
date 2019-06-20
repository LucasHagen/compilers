#include "stack_frame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "iloc.h"
#include "scope.h"
#include "stack.h"

extern int main_flag;
extern int return_flag;
extern Stack* scope_stack;
extern ILOC* main_label;
extern Scope* scope_list;
extern int scope_list_size;

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
void push_stack_frame(ILOC_List* code, ST_LINE* function_header, Node* parameters){
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

    copy_parameters(code, function_header, parameters);

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

int get_parameter_address(ST_LINE* function_register, int argument_number){
    int local_variables_size = function_register->local_variables_size;
    int i;
    for(i=0;i<=argument_number;i++){
        if(function_register->function_args[i].type == INT)
            local_variables_size -= SIZE_INT;
        else if(function_register->function_args[i].type == BOOL){
            local_variables_size -= SIZE_BOOL;
        }
    }
    return local_variables_size;
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
    if(main_flag){
        ST_LINE* line = identifier_in_scope(scope_stack->children[0], "main");
        if(line) {
            line->local_variables_size = top(scope_stack)->used_size;
            line->frame = create_stack_frame(line);
        }

        add_iloc(function->code, create_iloc(ILOC_HALT, NULL, NULL, NULL));
        main_flag = 0;
    }
    else
    {
        ST_LINE* line = identifier_in_scope(scope_stack->children[0], function->n_func_decl.identifier->token_value.v_string);
        if(return_flag != 0){
    		add_iloc(function->code,
                    create_iloc(ILOC_CSTOREAI,
    					        get_return_register(return_flag),
    					        "rfp",
    					        int_to_char(line->frame->local_variables_size+2*SIZE_INT)));
    		return_flag = 0;
    	}
        char* return_addr = new_register();
        add_iloc(function->code, create_iloc(ILOC_LOAD, "rfp", return_addr, NULL));
        add_iloc(function->code, create_iloc(ILOC_I2I,  "rfp", "rsp", NULL));
        add_iloc(function->code, create_iloc(ILOC_LOADAI, "rfp", "8", "rfp"));
        add_iloc(function->code, create_iloc(ILOC_JUMP, return_addr, NULL, NULL));
    }
}
