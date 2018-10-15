/******************************************************************************

Create stack library based on linked list 

*******************************************************************************/
#include <stdio.h>
#include "Stack_lib.h"

int main()
{
   // Stack initialization
    stack_t *stack_p1 = NULL; // creation of the init stack pointer.
    
    stack_push(&stack_p1, 1);
    stack_push(&stack_p1, 2);
    stack_push(&stack_p1, 4);
    stack_push(&stack_p1, 7);
    
    printf("reading from stack %d\n", stack_read (&stack_p1));
    stack_pop(&stack_p1);
    
    printf("reading from stack %d\n", stack_read (&stack_p1));
    
    printf("Pop from stack %d\n", stack_pop(&stack_p1));
    return 0;
}