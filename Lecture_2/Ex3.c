/******************************************************************************

Write program that get from user height and weight of rectangle (in meters)
and calculate perimeter and area (in inches);

*******************************************************************************/

#include <stdio.h>

int main()
{
    float rect_height = 1, rect_weight = 1; //rect dimension in meters
    
    float rect_perimeter = -1, rect_area = -1;
    float inch = 0.0254; //meters in one inch
   
    printf ("Insert please rectangle height in meters\n");
    scanf ("%f", &rect_height);
    printf ("Please insert rectangle weight in meters\n");
    scanf ("%f", &rect_weight);
   
    rect_perimeter = 2 * (rect_height + rect_weight) / inch;
    rect_area = (rect_height / inch) * (rect_weight / inch);
   
    printf ("Perimeter of the rectangle is %.3f inches\n", rect_perimeter);
    printf ("Area of the rectangle is %.4f square inches\n", rect_area);
    return 0;
}
