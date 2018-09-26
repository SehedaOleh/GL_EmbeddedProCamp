/******************************************************************************

Stack library based on linked list 

*******************************************************************************/
# include <stdint.h>
# include <stdlib.h>

struct Stack
{
    uint8_t data;
    struct Stack *new_element;
};

typedef struct Stack stack_t; //

stack_t *stack_pointer; // creation of the init stack pointer.

/******************************************************************************
 
Stack init function

******************************************************************************/

void stack_init()
{
    stack_pointer = NULL; // initialize the stack by making the init stack pointer = NULL
}

/******************************************************************************
 
Stack push function

******************************************************************************/

void stack_push (uint8_t number)
{
    stack_t *tmp;
    tmp = malloc(sizeof(stack_t));
    tmp -> data = number; //cteate new element
    
    tmp -> new_element = stack_pointer; // pointer to previous position
    
    stack_pointer = tmp; // pointer to top of the stack
   
}

/******************************************************************************
 
Stack pop function

******************************************************************************/

uint8_t stack_pop ()
{
    stack_t *tmp;
    uint8_t data_temp;
    
    tmp = stack_pointer;
    data_temp = tmp -> data;
    stack_pointer = stack_pointer -> new_element;
    free(tmp);
    return data_temp;  
}
/******************************************************************************
 
Stack read function

******************************************************************************/
uint8_t stack_read ()
{
     return stack_pointer -> data;
}