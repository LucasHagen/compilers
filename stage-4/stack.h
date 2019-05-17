#ifndef STACK_H
#define STACK_H

typedef int stack_value;

typedef struct stack_struct {

    stack_value** children;
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
Stack* create_stack(stack_value* value);

/**
 * Pushes a value on top of the stack
 */
void push(Stack* stack, stack_value* value);

/**
 * Pops the top element from the stack and saves it to the value_out pointer,
 * the value_out pointer must be allocated previously.
 */
int pop(Stack* stack, stack_value** value_out);

/**
 * Checks if the stack is empty
 */
int is_empty(Stack* stack);

/**
 * Gets the top element of the stack without removing it from the stack and
 * saves it to the value_out pointer, the value_out pointer must be allocated
 * previously.
 */
int top(Stack* stack, stack_value** value_out);

#endif
