/******************************************************************************

  Write a C program to compute factorial of 10 

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
uint64_t factorial(uint8_t base);
int main()
{
    uint8_t fact_base_number = 10;
    uint64_t result = 0;
    
    result = factorial (fact_base_number);
    
    
    printf("Factorial of %d is %d", fact_base_number, result);
    return 0;
}
uint64_t factorial(uint8_t base)
{
    uint64_t result = 1;
    for (int i = 1; i <= base; i++)
    {
        result *= i;
    }
    return result;
}