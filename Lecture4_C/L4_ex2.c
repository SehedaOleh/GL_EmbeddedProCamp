/******************************************************************************

Create stack library based on linked list 

*******************************************************************************/
#include <stdio.h>
#include "Stack_lib.h"

int main()
{
   // Stack initialization
    stack_init();
    
    stack_push(1);
    stack_push(2);
    stack_push(4);
    stack_push(7);
    
    printf("reading from stack %d\n", stack_read ());
    stack_pop();
    
    printf("reading from stack %d\n", stack_read ());
    
    printf("Pop from stack %d\n", stack_pop());
    return 0;
}