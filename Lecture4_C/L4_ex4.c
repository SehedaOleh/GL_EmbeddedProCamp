/******************************************************************************

Create function, that receives pointer to other function as a parameter

*******************************************************************************/
#include <stdio.h>
int add (int a, int b);
int sub (int a, int b);

int test_func ( int (*ptr_func)(int, int), int, int);
int main()
{
    int (*p_f1)(int, int) = add;
    int number_1 = 5;
    int number_2 = 3;
    int result_of_test_function = 0;
    
    printf("add trougth fuction pointer %d\n", p_f1(4, 5));
    
    result_of_test_function = test_func(p_f1, number_1, number_2);
    
    printf("First Test functions results is: %d\n", result_of_test_function);
    
    p_f1 = sub;
    result_of_test_function = test_func(p_f1, number_1, number_2);
    
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