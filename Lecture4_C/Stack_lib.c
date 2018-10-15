/******************************************************************************

Funcion for stack library based on linked list 

*******************************************************************************/
# include <stdint.h>
# include <stdlib.h>
# include <limits.h> 

#include "Stack_lib.h"
/******************************************************************************
 
Stack init function

******************************************************************************/
void stack_init(stack_t *stack_pointer)
{
    
    stack_pointer = NULL; // initialize the stack by making the init stack pointer = NULL
}
/******************************************************************************
 
Stack new node function

******************************************************************************/
 stack_t* stack_node ( uint8_t number)
{

     stack_t *tmp;
    
        tmp = (stack_t*)malloc(sizeof(stack_t));
        if (NULL == tmp)
        {
            printf("Malloc error\n");
        }
        tmp -> data = number; //cteate new element
        
        tmp -> new_element = NULL; 
        
       return tmp; 
    
}
/******************************************************************************
 
Stack push function

******************************************************************************/
void stack_push(stack_t** stack_pointer, uint8_t data) 
{ 
    stack_t* stackNode = stack_node(data); //add node
    
    stackNode -> new_element = *stack_pointer; // pointer to previous position
    
    *stack_pointer = stackNode;  // pointer to top of the stack
    printf("%d pushed to stack\n", data); 
} 

/******************************************************************************
 
Stack pop function

******************************************************************************/
uint8_t stack_pop (stack_t** stack_pointer)
{
    if (! (*stack_pointer))
    {
        return -1; //for case if there are no node
    }
    stack_t *tmp = *stack_pointer;
    uint8_t data_temp;
    
    *stack_pointer = (*stack_pointer) -> new_element;
    
    data_temp = tmp -> data;
    
    free(tmp);
    return data_temp;  
}
/******************************************************************************
 
Stack read function

******************************************************************************/
uint8_t stack_read (stack_t **stack_pointer)
{
     return (*stack_pointer) -> data;
}