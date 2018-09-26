/******************************************************************************

Create queue library based on array

*******************************************************************************/
#include <stdio.h>
# include "Queue_lib.h"
int main()
{
    printf("Queue library based on array testing\n");
    
    queue_push (2);
    queue_push (3);
    queue_push (4);
    queue_push (5);
    
    printf("first number in queue is: %d\n",queue_pop());
    
    printf("second number in queue is: %d\n",queue_pop());
    
    printf("Readed number in queue is: %d\n",queue_read());
    printf("Readed number in queue is: %d\n",queue_read());
    return 0;
}
