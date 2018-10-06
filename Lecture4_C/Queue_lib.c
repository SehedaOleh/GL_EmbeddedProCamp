/******************************************************************************

Function for Queue library based on array

*******************************************************************************/

# include <stdio.h>
# include <stdint.h>

# include "Queue_lib.h"

# define MAXSIZE 32

int init_queue[MAXSIZE]; //init array

int8_t start_queue_index = -1;  // start index of the queue
int8_t length_queue_index = -1; // shows the actual number of items in the queue
int8_t end_queue_index = -1;   // end index in the queue
/******************************************************************************

Queue push function

*******************************************************************************/
void queue_push(int number)
{
    if(length_queue_index < MAXSIZE) // checking that the queue is not full
    {
        if(length_queue_index < 0) // for first init of the list (that's mean that list is not initialized yet)
        {
            init_queue[0] = number; // add value in queue
            start_queue_index = end_queue_index = 0; 
            length_queue_index = 1;
        }
        else if(end_queue_index == MAXSIZE-1) // in case if we have alrady work with queue and first part of the array is empty 
        {                                     // end in the end of array are couple ellements     
            init_queue[0] = number;           // than we should write number in the first position of the array
            end_queue_index = 0;
            length_queue_index++;
        }
        else
        {
            init_queue[end_queue_index + 1] = number;
            end_queue_index++;
            length_queue_index++;
        }
    }
    else
    {
        printf("Warning: Queue is full\n");
    }
}
/******************************************************************************

Queue pop function

*******************************************************************************/
int queue_pop()
{
    if(length_queue_index < 0) // check if queue is empty
    {
        printf("Warning: Queue is empty\n");
    }
    else
    {
        length_queue_index--;
        start_queue_index++;
    }
    return init_queue[start_queue_index - 1];
}
/******************************************************************************

Queue read function

*******************************************************************************/
int queue_read()
{
    return init_queue[start_queue_index];
}