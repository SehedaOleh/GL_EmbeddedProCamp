/******************************************************************************

Create function, that receives pointer to other function as a parameter

*******************************************************************************/
#include <stdio.h>
int add (int a, int b);
int sub (int a, int b);

int test_func ( int (*ptr_func)(int, int), int, int);
int main()
{
    int number_1 = 5;
    int number_2 = 3;
    int result_of_test_function = 0;
    
    printf("add trougth fuction pointer %d\n", add(4, 5));
    
    result_of_test_function = test_func(add, number_1, number_2);
    
    printf("First Test functions results is: %d\n", result_of_test_function);
    
    result_of_test_function = test_func(sub, number_1, number_2);
    
    printf("Second Test functions results is: %d\n", result_of_test_function);
    return 0;
}

int test_func ( int (*ptr_func)(int, int), int a, int b)
{
    int result = ptr_func (a, b);
    return result;
}

int add (int a, int b) 
{
    return a + b;
}
int sub (int a, int b)
{
    return a - b;
}