#ifndef STACK_H
#define STACK_H

#include "scope.h"

typedef struct stack_struct {

    Scope** children;
    int           max_size;
    int           size    ;

} Stack;

/**
 * Creates a empty stack
 */
Stack* create_empty_stack();

/**
 * Creates a stack with one element
 */
Stack* create_stack(Scope* value);

/**
 * Pushes a value on top of the stack
 */
void push(Stack* stack, Scope* value);

/**
 * Pops the top element from the stack and saves it to the value_out pointer,
 * the value_out pointer must be allocated previously.
 */
int pop(Stack* stack, Scope** value_out);

/**
 * Checks if the stack is empty
 */
int is_empty(Stack* stack);

/**
 * Gets the top element of the stack without removing it from the stack and
 * saves it to the value_out pointer, the value_out pointer must be allocated
 * previously.
 */
int top(Stack* stack, Scope** value_out);

#endif
