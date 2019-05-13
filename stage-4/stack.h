#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL 0
#endif

typedef int stack_value;

typedef struct stack_struct {

    stack_value* children = 0;
    int          max_size = 0;
    int          size     = 0;

} Stack;

/**
 * Creates a empty stack
 */
Stack* create_stack();

/**
 * Creates a stack with one element
 */
Stack* create_stack(stack_value value);

/**
 * Pushes a value on top of the stack
 */
void push(Stack* stack, stack_value value);

/**
 * Pops the top element from the stack and saves it to the value_out pointer,
 * the value_out pointer must be allocated previously.
 */
void pop(Stack* stack, stack_value* value_out);

/**
 * Checks if the stack is empty
 */
int is_empty(Stack* stack);

#endif
