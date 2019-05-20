#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Creates a empty stack
 */
Stack* create_empty_stack()
{
    Stack* s = (Stack*) malloc(sizeof(Stack));

    s->children = (Scope**) malloc(sizeof(Scope**));
    s->max_size = 1;
    s->size = 0;

    return s;
}

/**
 * Creates a stack with one element
 */
Stack* create_stack(Scope* value)
{
    Stack* s = (Stack*) malloc(sizeof(Stack));

    s->children = (Scope**) malloc(sizeof(Scope**));
    s->max_size = 1;
    s->size = 1;

    s->children[0] = value;

    return s;
}

/**
 * Pushes a value on top of the stack
 */
void push(Stack* stack, Scope* value)
{
    if(stack->size >= stack->max_size)
    {
        stack->max_size++;

        stack->children = (Scope**) realloc(stack->children,
            stack->max_size * sizeof(Scope**));
    }

    stack->children[stack->size] = value;
    stack->size++;
}

/**
 * Pops the top element from the stack and saves it to the value_out pointer,
 * the value_out pointer must be allocated previously.
 */
int pop(Stack* stack, Scope** value_out)
{
    int result = 0;

    if(!is_empty(stack) && value_out != NULL)
    {
        stack->size--;
        *value_out = stack->children[stack->size];

        result = 1;
    }

    return result;
}

/**
 * Checks if the stack is empty
 */
int is_empty(Stack* stack)
{

    int empty = 1;

    if(stack != NULL && stack->size > 0)
    {
        empty = 0;
    }

    return empty;
}

/**
 * Gets the top element of the stack without removing it from the stack and
 * saves it to the value_out pointer, the value_out pointer must be allocated
 * previously.
 */
int top(Stack* stack, Scope** value_out)
{
    int result = 0;

    if(!is_empty(stack) && value_out != NULL)
    {
        *value_out = stack->children[stack->size - 1];
    }

    return result;
}
