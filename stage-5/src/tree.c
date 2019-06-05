#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "printer.h"
#include "defines.h"

/*
	Authors:
		- Gabriel Pakulski da Silva - 00274701
		- Lucas Sonntag Hagen       - 00274698
*/

// To show debug messages, uncomment the line bellow and compile again
//#define COMP_DEBUG

/**
 * Creates a new node structure and allocates the nedded memory
 *
 * @param token Operation Identifier
 */
Node* new_node(int type)
{
    Node* node      = (Node*) malloc(sizeof(Node));
    node->val_type  = NO_TYPE;
    node->type      = type;
    node->seq       = NULL;
    node->code      = NULL;
    node->temp      = NULL;

    return node;
}

/**
 * Frees memory previously allocated to the AST structure
 *
 * @param root AST Pointer
 */
void free_tree(Node* root)
{
    #ifdef COMP_DEBUG
    printf("========== START FREE TREE ==========\n");
    #endif

    if(root != NULL)
    {
        free_node(root);
    }

    #ifdef COMP_DEBUG
    printf("Memory alocated for tree is now free!\n");
    #endif
}

void free_node(Node* node){
    if(node != NULL){
#ifdef COMP_DEBUG
        int seq_type = -1;
#endif
        if(node->seq != NULL) {
#ifdef COMP_DEBUG
            seq_type = node->seq->type;
#endif
            free_node(node->seq);
            node->seq = NULL;
        }

#ifdef COMP_DEBUG
        printf("Node entrou na free_node()\n");
        printf("- Tipo: %d\n",     node->type);
        printf("- Tipo seq: %d\n", seq_type);
#endif

        switch(node->type){
          case NODE_TYPE_COMMAND_BLOCK:
            free_node(node->n_cmd_block.command);
            free(node);
            break;

          case NODE_TYPE_TER_OP:
            free_node(node->n_if.condition);
            free_node(node->n_if.n_true);
            free_node(node->n_if.n_false);
            free(node);
          break;

          case NODE_TYPE_BIN_OP:
            free_lexeme(node->n_bin_op.op);
            free_node(node->n_bin_op.left);
            free_node(node->n_bin_op.right);
            free(node);
          break;

          case NODE_TYPE_UN_OP:
            free_lexeme(node->n_un_op.op);
            free_node(node->n_un_op.operand);
            free(node);
          break;

          case NODE_TYPE_IF:
            free_node(node->n_if.condition);
            free_node(node->n_if.n_true);
            free_node(node->n_if.n_false);
            free(node);
          break;

          case NODE_TYPE_FOR:
            free_node(node->n_for.setup);
            free_node(node->n_for.condition);
            free_node(node->n_for.increment);
            free_node(node->n_for.code);
            free(node);
          break;

          case NODE_TYPE_WHILE:
            free_node(node->n_while.condition);
            free_node(node->n_while.code);
            free(node);
          break;

          case NODE_TYPE_FUNC_CALL:
            free_lexeme(node->n_call_or_access.identifier);
            free_node(node->n_call_or_access.index_or_param);
            free(node);
          break;

          case NODE_TYPE_FUNC_DECL:
            free_lexeme(node->n_func_decl.identifier);
            free_node(node->n_func_decl.param);
            free_node(node->n_func_decl.code);
            free_lexeme(node->n_func_decl.type);
            free(node);
          break;

          case NODE_TYPE_FUNC_PARAM:
            free_lexeme(node->n_var_decl.identifier);
            free_lexeme(node->n_var_decl.type);
            free(node);
          break;

          case NODE_TYPE_VAR_ACCESS:
            free_lexeme(node->n_call_or_access.identifier);
            free_node(node->n_call_or_access.index_or_param);
            free(node);
          break;

          case NODE_TYPE_VAR_DECL:
            free_lexeme(node->n_var_decl.identifier);
            free_lexeme(node->n_var_decl.type);
            free_node(node->n_var_decl.size);
            free_node(node->n_var_decl.value);
            free(node);
          break;

          case NODE_TYPE_GLOBAL_VAR_DECL:
            free_lexeme(node->n_var_decl.identifier);
            free_lexeme(node->n_var_decl.type);
            free_node(node->n_var_decl.size);
            free_node(node->n_var_decl.value);
            free(node);
          break;

          case NODE_TYPE_VAR_ATTR:
            free_lexeme(node->n_var_attr.identifier);
            free_node(node->n_var_attr.index);
            free_node(node->n_var_attr.value);
            free(node);
          break;

          case NODE_TYPE_INPUT:
            free_node(node->n_io.params);
            free(node);
          break;

          case NODE_TYPE_OUTPUT:
            free_node(node->n_io.params);
            free(node);
          break;

          case NODE_TYPE_SHIFT_LEFT:
            free_node(node->n_shift.count);
            free_node(node->n_shift.var);
            free(node);
          break;

          case NODE_TYPE_SHIFT_RIGHT:
            free_node(node->n_shift.count);
            free_node(node->n_shift.var);
            free(node);
          break;

          case NODE_TYPE_RETURN:
            free_node(node->n_io.params);
            free(node);
          break;

          case NODE_TYPE_BREAK:
            free(node);
          break;

          case NODE_TYPE_CONTINUE:
            free(node);
          break;

          case NODE_TYPE_LITERAL:
            free_lexeme(node->n_literal.literal);
            free(node);
          break;

          default:
            #ifdef COMP_DEBUG
            printf(" - [ERROR] NODE TYPE NOT FOUND!\n");
            printf(" - [ERROR] NODE TYPE NOT FOUND!\n");
            printf(" - [ERROR] NODE TYPE NOT FOUND!\n");
            #endif
            free(node);


          break;
        }
    }
}

/**
 * Frees memory allocated for a Lexeme
 *
 * @param lex Lexeme Pointer
 * @return Allways 0, to override old pointer
 */
int free_lexeme(Lexeme* lex)
{
#ifdef COMP_DEBUG
    printf("- in free lexeme\n");
#endif

    if(lex != NULL)
    {
        // Free string value if allocated
        if(lex->token_type != SPECIAL_CHAR &&
            lex->literal_type != INT &&
            lex->literal_type != FLOAT &&
            lex->literal_type != BOOL &&
            lex->literal_type != CHAR )
        {
#ifdef COMP_DEBUG
            printf("- String: '%s';\n",lex->token_value.v_string);
#endif
            free(lex->token_value.v_string);
        }

        free(lex);
    }
    #ifdef COMP_DEBUG
    printf("- out free lexeme\n");
    #endif

    return 1;
}

struct node* create_node_ter_op(Node* condition, Node* ifTrue, Node* ifFalse, int line)
{
    struct node* node = new_node(NODE_TYPE_TER_OP);

    node->n_if.condition = condition;
    node->n_if.n_true    = ifTrue;
    node->n_if.n_false   = ifFalse;

    can_set_type(BOOL, condition->val_type, line);

    if(ifTrue != NULL && ifFalse != NULL)
    {
        if(ifTrue->val_type == NO_TYPE || ifFalse->val_type == NO_TYPE)
        {
            throw_error(ERR_WRONG_TYPE, line);
        }
        else if(ifTrue->val_type == ifFalse->val_type)
        {
            node->val_type = ifTrue->val_type;
        }
        else
        {
            node->val_type = type_infer(ifTrue->val_type, ifFalse->val_type, line);
        }
    }


    return node;
}

struct node* create_node_bin_op(Lexeme* op, Node* left, Node* right)
{
    struct node* node = new_node(NODE_TYPE_BIN_OP);

    node->n_bin_op.op = op;
    node->n_bin_op.left = left;
    node->n_bin_op.right = right;

    node->val_type = type_infer(left->val_type, right->val_type, op->line_number);

    return node;
}

struct node* create_node_un_op(Lexeme* op, Node* operand)
{
    struct node* node = new_node(NODE_TYPE_UN_OP);

    if(operand != NULL)
    {
        node->val_type = operand->val_type;
    }
    node->n_un_op.op = op;
    node->n_un_op.operand = operand;

    return node;
}

struct node* create_node_if(Node* condition, Node* ifTrue, Node* ifFalse, int line)
{
    struct node* node = new_node(NODE_TYPE_IF);

    node->n_if.condition = condition;
    node->n_if.n_true = ifTrue;
    node->n_if.n_false = ifFalse;

    can_set_type(BOOL, condition->val_type, line);

    return node;
}

struct node* create_node_for(Node* setup, Node* condition, Node* increment, Node* code, int line)
{
    struct node* node = new_node(NODE_TYPE_FOR);

    node->n_for.setup       = setup;
    node->n_for.condition   = condition;
    node->n_for.increment   = increment;
    node->n_for.code        = code;

    can_set_type(BOOL, condition->val_type, line);

    return node;
}


struct node* create_node_while(Node* condition, Node* code, int line)
{
    struct node* node = new_node(NODE_TYPE_WHILE);

    node->n_while.condition = condition;
    node->n_while.code      = code;

    can_set_type(BOOL, condition->val_type, line);

    return node;
}


struct node* create_node_func_call(Lexeme* identifier, Node* parameters, int type)
{
    struct node* node = new_node(NODE_TYPE_FUNC_CALL);

    node->val_type = type;
    node->n_call_or_access.identifier       = identifier;
    node->n_call_or_access.index_or_param   = parameters;

    return node;
}

struct node* create_node_func_decl(Lexeme* identifier, Lexeme* type, int is_static, Node* parameters, Node* code)
{
    struct node* node = new_node(NODE_TYPE_FUNC_DECL);

    node->val_type                = get_type_id(type);
    node->n_func_decl.identifier  = identifier;
    node->n_func_decl.param       = parameters;
    node->n_func_decl.code        = code;
    node->n_func_decl.type        = type;
    node->n_func_decl.is_static   = is_static;

    return node;
}

struct node* create_node_func_param(Lexeme* identifier, Lexeme* type, int is_const)
{
    struct node* node = new_node(NODE_TYPE_FUNC_PARAM);

    node->val_type               = get_type_id(type);
    node->n_var_decl.identifier  = identifier;
    node->n_var_decl.size        = NULL;
    node->n_var_decl.type        = type;
    node->n_var_decl.is_static   = FALSE;
    node->n_var_decl.is_const    = is_const;
    node->n_var_decl.value       = NULL;

    return node;
}

struct node* create_node_var_access(Lexeme* identifier, Node* index, int type)
{
    struct node* node = new_node(NODE_TYPE_VAR_ACCESS);

    node->val_type = type;
    node->n_call_or_access.identifier     = identifier;
    node->n_call_or_access.index_or_param = index;

    if(index != NULL)
    {
        can_set_type(INT, index->val_type, identifier->line_number);
    }

    return node;
}

struct node* create_node_var_decl(Lexeme* identifier, Lexeme* type, int is_static, int is_const, Node* value)
{
    struct node* node = new_node(NODE_TYPE_VAR_DECL);

    node->val_type                = get_type_id(type);
    node->n_var_decl.identifier   = identifier;
    node->n_var_decl.size         = NULL;
    node->n_var_decl.type         = type;
    node->n_var_decl.is_static    = is_static;
    node->n_var_decl.is_const     = is_const;
    node->n_var_decl.value        = value;

    if(value != NULL && value->val_type != get_type_id(type))
    {
        type_infer(node->val_type, value->val_type, identifier->line_number);
    }

    return node;
}

struct node* create_node_global_var_decl(Lexeme* identifier, Node* size, Lexeme* type, int is_static, Node* value)
{
    struct node* node = new_node(NODE_TYPE_GLOBAL_VAR_DECL);

    node->val_type                = get_type_id(type);
    node->n_var_decl.identifier   = identifier;
    node->n_var_decl.size         = size;
    node->n_var_decl.type         = type;
    node->n_var_decl.is_static    = is_static;
    node->n_var_decl.is_const     = 0;
    node->n_var_decl.value        = value;

    if(size != NULL)
    {
        type_infer(size->val_type, INT, identifier->line_number);
    }

    if(value != NULL && value->val_type != get_type_id(type))
    {
        type_infer(node->val_type, value->val_type, identifier->line_number);
    }

    return node;
}

struct node* create_node_var_attr(Lexeme* identifier, Node* index, Node* value, int var_type)
{
    struct node* node = new_node(NODE_TYPE_VAR_ATTR);

    node->n_var_attr.identifier = identifier;
    node->n_var_attr.index = index;
    node->n_var_attr.value = value;

    if(index != NULL)
    {
        can_set_type(INT, index->val_type, identifier->line_number);
    }
    if(value->val_type != var_type)
    {
        can_set_type(var_type, value->val_type, identifier->line_number);
    }

    return node;
}

struct node* create_node_input(Node* input, int line)
{
    Node* node = new_node(NODE_TYPE_INPUT);

    node->n_io.params = input;

    if(input != NULL && input->type != NODE_TYPE_VAR_ACCESS)
    {
        throw_error(ERR_WRONG_PAR_INPUT, line);
    }

    return node;
}

struct node* create_node_output(Node* output, int line)
{
    struct node* node = new_node(NODE_TYPE_OUTPUT);

    node->n_io.params = output;

    Node* aux = output;
    while(aux != NULL)
    {
        if(aux->type != NODE_TYPE_BIN_OP && aux->type != NODE_TYPE_TER_OP && node->type != NODE_TYPE_UN_OP &&
           !(aux->type == NODE_TYPE_LITERAL && (aux->n_literal.literal->literal_type == STRING ||
                                                aux->n_literal.literal->literal_type == INT ||
                                                aux->n_literal.literal->literal_type == FLOAT ||
                                                aux->n_literal.literal->literal_type == BOOL)) &&
           !((aux->type == NODE_TYPE_VAR_ACCESS || aux->type == NODE_TYPE_FUNC_CALL) && (
                                                aux->val_type == INT ||
                                                aux->val_type == BOOL ||
                                                aux->val_type == FLOAT)))
        {
            throw_error(ERR_WRONG_PAR_OUTPUT, line);
        }
        aux = aux->seq;
    }

    return node;
}

struct node* create_node_shift_left()
{
    struct node* node = new_node(NODE_TYPE_SHIFT_LEFT);

    return node;
}

struct node* create_node_shift_right()
{
    struct node* node = new_node(NODE_TYPE_SHIFT_RIGHT);

    return node;
}

struct node* create_node_return(Node* expression)
{
    struct node* node = new_node(NODE_TYPE_RETURN);

    node->n_io.params = expression;

    return node;
}

struct node* create_node_break()
{
    struct node* node = new_node(NODE_TYPE_BREAK);

    return node;
}

struct node* create_node_continue()
{
    struct node* node = new_node(NODE_TYPE_CONTINUE);

    return node;
}

struct node* create_node_literal(Lexeme* value, ST_LINE* line)
{
    struct node* node = new_node(NODE_TYPE_LITERAL);

    node->n_literal.literal = value;
    node->n_literal.st_line = line;
    node->val_type = value->literal_type;

    return node;
}

struct node* create_node_command_block(Node* first_command)
{
    struct node* node = new_node(NODE_TYPE_COMMAND_BLOCK);

    node->n_cmd_block.command = first_command;
    node->code = create_empty_list();

    add_codes_rec(node->code, first_command);

    return node;
}

void add_codes_rec(ILOC_List* dest, Node* node)
{
    if(node != NULL)
    {
        if(node->seq != NULL)
        {
            add_codes_rec(dest, node->seq);
        }

        if(node->code != NULL)
        {
            add_all_end(dest, node->code);
        }
    }
}

int get_type_id(Lexeme* type)
{
    if(strcmp(type->token_value.v_string, "int") == 0)
    {
        return INT;
    }
    else if(strcmp(type->token_value.v_string, "float") == 0)
    {
        return FLOAT;
    }
    else if(strcmp(type->token_value.v_string, "bool") == 0)
    {
        return BOOL;
    }
    else if(strcmp(type->token_value.v_string, "char") == 0)
    {
        return CHAR;
    }
    else if(strcmp(type->token_value.v_string, "string") == 0)
    {
        return STRING;
    }

    return -1;
}

void throw_error(int error_code, int line_number)
{
    const char* err_format = "Erro na linha %d: %s;\n";
    switch(error_code)
    {
        case ERR_UNDECLARED:
        	printf(err_format, line_number, "identificador não declarado");
        	break;

        case ERR_DECLARED:
        	printf(err_format, line_number, "identificador já declarado");
        	break;

        case ERR_VARIABLE:
        	printf(err_format, line_number, "identificador deve ser utilizado como variável");
        	break;

        case ERR_VECTOR:
        	printf(err_format, line_number, "identificador deve ser utilizado como vetor");
        	break;

        case ERR_FUNCTION:
        	printf(err_format, line_number, "identificador deve ser utilizado como função");
        	break;

        case ERR_WRONG_TYPE:
        	printf(err_format, line_number, "tipos incompatíveis");
        	break;

        case ERR_STRING_TO_X:
        	printf(err_format, line_number, "coerção impossível de var do tipo string");
        	break;

        case ERR_CHAR_TO_X:
        	printf(err_format, line_number, "coerção impossível de var do tipo char");
        	break;

        case ERR_MISSING_ARGS:
        	printf(err_format, line_number, "faltam argumentos");
        	break;

        case ERR_EXCESS_ARGS:
        	printf(err_format, line_number, "sobram argumentos");
        	break;

        case ERR_WRONG_TYPE_ARGS:
        	printf(err_format, line_number, "argumentos incompatíveis");
        	break;

        case ERR_WRONG_PAR_INPUT:
        	printf(err_format, line_number, "parâmetro não é identificador");
        	break;

        case ERR_WRONG_PAR_OUTPUT:
        	printf(err_format, line_number, "parâmetro não é literal string ou expressão");
        	break;

        case ERR_WRONG_PAR_RETURN:
        	printf(err_format, line_number, "parâmetro não é expressão compatível com tipo do retorno");
        	break;

        case ERR_NOT_IMPLEMENTED:
        	printf(err_format, line_number, "construção não implementada");
        	break;

        default:
            printf("Erro na linha %d;\n", line_number);
            break;
    }
    exit(error_code);
}

int type_infer(int type1, int type2, int line_number)
{
    if(type1 == NO_TYPE || type2 == NO_TYPE) {
        throw_error(ERR_WRONG_TYPE, line_number);
    }
    if(type1 == STRING || type2 == STRING) {
        throw_error(ERR_STRING_TO_X, line_number);
    }
    if(type1 == CHAR || type2 == CHAR) {
        throw_error(ERR_CHAR_TO_X, line_number);
    }

    if(type1 == type2){
        return type1;
    }

    if((type1 == FLOAT && (type2 == BOOL || type2 == INT)) ||
       (type2 == FLOAT && (type1 == BOOL || type1 == INT)))
    {
        return FLOAT;
    }

    if((type1 == INT && type2 == BOOL) ||
       (type2 == INT && type1 == BOOL))
    {
        return INT;
    }

    throw_error(ERR_WRONG_TYPE, line_number);
    return NO_TYPE;
}

int can_set_type(int var_type, int value_type, int line)
{
    int result = 0;
    switch(value_type)
    {
        case INT:
        case BOOL:
        case FLOAT:
            if(var_type != INT && var_type != FLOAT && var_type != BOOL) {
                throw_error(ERR_WRONG_TYPE, line);
            } else {
                result = 1;
            }
            break;
        case CHAR:
            if(var_type != CHAR)
            {
                throw_error(ERR_CHAR_TO_X, line);
            } else {
                result = 1;
            }
            break;
        case STRING:
            if(var_type != STRING)
            {
                throw_error(ERR_STRING_TO_X, line);
            } else {
                result = 1;
            }
            break;
        default:
            throw_error(ERR_WRONG_TYPE, line);
    }
    return result;
}

int can_convert(int var_type, int value_type, int line, int error)
{
    int result = 0;
    switch(value_type)
    {
        case INT:
        case BOOL:
        case FLOAT:
            if(var_type != INT && var_type != FLOAT && var_type != BOOL) {
                throw_error(error, line);
            } else {
                result = 1;
            }
            break;
        case CHAR:
            if(var_type != CHAR)
            {
                throw_error(error, line);
            } else {
                result = 1;
            }
            break;
        case STRING:
            if(var_type != STRING)
            {
                throw_error(error, line);
            } else {
                result = 1;
            }
            break;
        default:
            throw_error(error, line);
    }
    return result;
}

/**
 * Creates a ILOC_List with the instructions for the operation: left OPERATION right
 * This list is added to node
 */
void create_and_add_iloc_compare(Node* node, Node* left, Node* right, int operation)
{
    ILOC_List* list = create_empty_list();

    node->temp = new_register();
    node->code = list;

    add_all_end(list, left->code);
    add_all_end(list, right->code);

    add_iloc(list, create_iloc(operation, left->temp, right->temp, node->temp));
}

void create_and_add_iloc_and(Node* node, Node* left, Node* right)
{
    ILOC_List* list = create_empty_list();
    ILOC* t = new_label();
    ILOC* f = new_label();
    ILOC* next = new_label();

    node->temp = new_register();
    node->code = list;

    add_all_end(list, left->code);


    add_iloc(list, create_iloc(ILOC_CBR, left->temp, t->param1, f->param1));
    add_iloc(list, t);
    add_iloc(list, create_iloc(ILOC_AND, left->temp, right->temp, node->temp));
    add_iloc(list, create_iloc(ILOC_JUMP, next->param1, NULL, NULL));
    add_all_end(list, right->code);

    add_iloc(list, f);
    add_iloc(list, create_iloc(ILOC_STORE, node->temp, left->temp, NULL));
    add_iloc(list, next);
}

void create_and_add_iloc_or(Node* node, Node* left, Node* right)
{
    ILOC_List* list = create_empty_list();
    ILOC* t = new_label();
    ILOC* f = new_label();
    ILOC* next = new_label();

    node->temp = new_register();
    node->code = list;

    add_all_end(list, left->code);

    add_iloc(list, create_iloc(ILOC_CBR, left->temp, t->param1, f->param1));
    add_iloc(list, t);
    add_iloc(list, create_iloc(ILOC_STORE, node->temp, left->temp, NULL));
    add_iloc(list, create_iloc(ILOC_JUMP, next->param1, NULL, NULL));

    add_iloc(list, f);
    add_iloc(list, create_iloc(ILOC_OR, left->temp, right->temp, node->temp));
    add_all_end(list, right->code);
    add_iloc(list, next);
}

void create_and_add_iloc_if(Node* node_if, Node* expression, Node* s1, Node* s2)
{
    ILOC_List* list = create_empty_list();
    node_if->n_if.t = new_label();
    node_if->n_if.f = new_label();
    node_if->n_if.next = new_label();

    node_if->temp = new_register();
    node_if->code = list;

    add_all_end(list, expression->code);

    add_iloc(list, create_iloc(ILOC_CBR, expression->temp, node_if->n_if.t->param1, node_if->n_if.f->param1));
    add_iloc(list, node_if->n_if.t);
    add_all_end(list, s1->code);
    if(s2 != NULL){
    add_iloc(list, create_iloc(ILOC_JUMP, node_if->n_if.next->param1, NULL, NULL));
        add_iloc(list, node_if->n_if.f);
        add_all_end(list, s2->code);
        add_iloc(list, node_if->n_if.next);
    }
}
