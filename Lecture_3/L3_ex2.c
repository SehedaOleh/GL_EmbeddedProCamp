/******************************************************************************

Create function to find the biggest element in integer array

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define array_length 25

int max_element (int *array_input, int length);
int main()
{
    //const uint8_t array_length = 25;
    int digit_array[array_length] = {};
    int max_number;
    
    srand(time(NULL));
   
    for(int i = 0; i < array_length; i++)
    {
        digit_array[i] = rand() % 90 + 10;
        printf("%d ", digit_array[i]);
    } 
    
    max_number = digit_array[0];
    
    max_number = max_element(digit_array, array_length);
    printf("\n Max number in array is %d",max_number);
    return 0;
}
int max_element (int *array_input, int length)
{
    int max;
    max = array_input[0];
    for (int i = 0; i < length; i++)
    {
        if (max < array_input[i])
        {
            max = array_input[i];
        }
        
    }
    return max;
}