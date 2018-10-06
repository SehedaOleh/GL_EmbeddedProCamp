/******************************************************************************

Create void function that copies one string to another

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void str_copy (char *, char *);
int main()
{
    char string [32];
    char *str_temp;
    uint8_t string_length = 0;
    
    printf ("Input string to copy\n");
    gets (string);
    
    string_length = strlen(string);
    
    str_temp = (char*)malloc(sizeof(char)*string_length);
    
    if (str_temp == NULL)
    {
        printf ("Malloc error\n");
        return -1;
    }
    
    str_copy (string, str_temp);
    
    printf("Initial string is: %s\n", string);
    printf("Copied string is: %s\n", str_temp);
    return 0;
}

void str_copy (char *string_to_copy, char *string_where_to_copy)
{
    uint8_t length = 0;
    
    length = sizeof (string_to_copy);
    for (uint8_t i = 0; i < length; i++)
    {
        string_where_to_copy[i] = string_to_copy[i];
    }
}