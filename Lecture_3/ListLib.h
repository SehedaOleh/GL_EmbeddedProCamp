/***************************************

Linked list library with functions (ListAdd(), ListIs(), ListRemove()). 
New elements in list is  dynamically allocate.

***************************************/

typedef struct link_list
{
    int number;
    float digit;
    struct link_list *next_element;
    
} link_list_t;

/**************************************

function ListAdd: adding new item in the end of the list

**************************************/
void ListAdd (link_list_t *ptr_list, int input_num, float input_dig)
{
    
    link_list_t * current_list = ptr_list;
    
     // go to the end of the current list
    while (current_list -> next_element != NULL)
    {
        current_list = current_list -> next_element;
    }

    // in the end of current list adding new item
    
    current_list -> next_element = malloc(sizeof(link_list_t));
    
    if (current_list -> next_element == NULL)
    {
        printf("Malloc error\n");
    }
    // item filling
    current_list -> next_element -> number = input_num;
    current_list -> next_element -> digit = input_dig;
    current_list -> next_element -> next_element = NULL;
}
/**************************************

function ListIs: finding item in the list

If item is in the list, function returns his index in the list. 
If not function returns -1.

**************************************/
int ListIs (link_list_t *ptr_list, int input_num, float input_dig)
{
    
    link_list_t * current_list = ptr_list;
    int index = 0;
     // go step by step to the end of the current list
    while (current_list -> next_element != NULL)
    {
        if (current_list -> number == input_num && 
            current_list -> digit == input_dig)
        {
            return index;
        }
        else
        {
            current_list = current_list -> next_element;
            index ++;
        }
    }

    return -1;
}
/**************************************

function ListShows: shows all items in the list

***************************************/
void ListShows (link_list_t *ptr_list)
{
    
    link_list_t * current_list = ptr_list;
    
    // go step by step and printing integer current item
    printf("\nInteger value in the list:\n");
    while (current_list -> next_element != NULL)
    {
        printf(" %d",current_list -> number);
        current_list = current_list -> next_element;
    }
    
    current_list = ptr_list;
    // go step by step and printing floating current item
    printf("\nFloat value in the list:\n");
    while (current_list -> next_element != NULL)
    {
        printf(" %.2f",current_list -> digit);
        current_list = current_list -> next_element;
    }
    printf("\n");
}
/**************************************

function ListRemove: remove last items in the list

***************************************/
void ListRemove (link_list_t *ptr_list)
{
    link_list_t * current_list = ptr_list;
    //int value_n;
    //float value_d;
    
     // go to the end of the current list
    while (current_list -> next_element != NULL)
    {
        current_list = current_list -> next_element;
    }

    // in the end of current list removing item
    //value_d = current_list -> digit;
    //value_n = current_list -> number;
    
    free(current_list -> next_element);
    
    current_list -> next_element = NULL;
}

