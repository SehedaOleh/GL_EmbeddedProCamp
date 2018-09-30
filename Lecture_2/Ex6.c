/******************************************************************************

  Write a C program to print all numbers between 1 to 500 
  which divided by a number specified by user

*******************************************************************************/

#include <stdio.h>

int main()
{
    int user_number = 1;
    int start = 1, stop = 500;
    do {
        printf("Please insert number betwen %d and %d\n",start,stop);
        scanf("%d", &user_number);
    }
    while ((user_number > 500)&&(user_number < 1));
    
    for(int i = start; i < stop; i++)
    {
       if ( i % user_number == 0) 
        printf(" %d", i);
    }
    return 0;
}
