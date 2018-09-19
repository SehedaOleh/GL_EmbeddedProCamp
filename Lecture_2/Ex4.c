/******************************************************************************

 Write a C program to compute the perimeter and 
 area of a circle with a radius of 6 meters;

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>

#define M_PI 3.14159265358979323846

int main()
{
    uint8_t circle_radius = 6; //in meters
    float circle_perimeter = -1;
    float circle_area = -1;
   
    circle_perimeter = 2 * M_PI * circle_radius;
    circle_area = M_PI * circle_radius * circle_radius;
   
    printf("Perimeter of the circle with a radius %d meters is %.3f meters\n", circle_radius, circle_perimeter);
    printf("Area of the circle with a radius %d meters is %.4f square meters", circle_radius, circle_area);
    return 0;
}
