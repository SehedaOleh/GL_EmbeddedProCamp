#ifndef LIST_LIB_H

#define LIST_LIB_H

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
void ListAdd (link_list_t *ptr_list, int input_num, float input_dig);

/**************************************

function ListIs: finding item in the list

If item is in the list, function returns his index in the list. 
If not function returns -1.

**************************************/
int ListIs (link_list_t *ptr_list, int input_num, float input_dig);
/**************************************

function ListShows: shows all items in the list

***************************************/
void ListShows (link_list_t *ptr_list);
/**************************************

function ListRemove: remove last items in the list

***************************************/
void ListRemove (link_list_t *ptr_list);
#endif
