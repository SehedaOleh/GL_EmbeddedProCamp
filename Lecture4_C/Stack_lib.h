#ifndef STACK_LIB_H
#define STACK_LIB_H
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

void stack_init();

/******************************************************************************
 
Stack push function

******************************************************************************/

void stack_push (uint8_t number);

/******************************************************************************
 
Stack pop function

******************************************************************************/

uint8_t stack_pop ();

/******************************************************************************
 
Stack read function

******************************************************************************/
uint8_t stack_read ();
#endif