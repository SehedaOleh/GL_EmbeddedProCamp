/******************************************************************************

Create function to copy all digits from input string to output string

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

void only_digits (char* intup_string, char *output_string);
int main()
{
    char initial_string[256];
    char digital_string[256] = { 0 };
    uint8_t str_length = 0;
    
    gets(initial_string);
    
    only_digits (initial_string, digital_string);
    str_length = strlen (digital_string);
    
    for (int i = 0; i < str_length; i++)
    {
        printf("%c", digital_string[i]);
    }
    return 0;
}

void only_digits (char *intup_string, char *output_string)
{
    uint8_t string_length = 0;
    uint8_t str_index = 0;
    
    string_length = strlen (intup_string);
    
    for (int i = 0; i < string_length; i++)
    {
        if (intup_string[i] <= '9' && intup_string[i] >= '0')
        {
            output_string[str_index] = intup_string[i];
            str_index++;
        }
    }
}