/******************************************************************************

Create linked list library with functions (ListAdd(), ListIs(), ListRemove()).
New elements in list should be dynamically allocated.


*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ListLib.h"



int main()
{
    link_list_t *list_init = NULL;
    link_list_t *for_debug = NULL;
    int index_in_list;
    
    list_init = malloc(sizeof(link_list_t));
    
    if (list_init == NULL)
    {
        printf("Malloc error\n");
        return -1;
    }
    list_init -> number = 1;
    list_init -> digit = 0.5;
    list_init -> next_element = NULL;
    
    for (int i = 0; i < 10; i++)
    {
        ListAdd (list_init, rand()%10, rand()%10/1.0);
        
    }
    printf("\n");
    
    /* * * * * * debug * * * * * * * * * * * * * * * * * *
    for_debug = list_init;
    while (for_debug->new_element != NULL)
    {
        for_debug = for_debug->new_element;
    }

    printf("Actual int value in the list is: %d\n",for_debug ->number);
     * * * * * * * * * * * * * * * * * * * * * * * * * */
    ListShows(list_init);
    
    index_in_list = ListIs (list_init, 2, 1.5);
    if (index_in_list == -1)
    {
        printf("Didn't found item in the list\n");
    }
    else
    {
        printf("Item found. Item has index %d\n", index_in_list);
    }
    
    ListRemove (list_init);
    
    return 0;
    
}
