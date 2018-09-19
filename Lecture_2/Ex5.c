/******************************************************************************

  Write a C program to compute factorial of 10 

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t fact_base_number = 10;
    uint32_t result = 1;
   
    for (int i = 1; i <= fact_base_number; i++)
    {
       result*=i;
    }
    
    printf("Factorial of %d is %d", fact_base_number, result);
    return 0;
}
