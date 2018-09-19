/******************************************************************************

Write function that converts RGB 888 to RGB 565

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
uint16_t convert_RGB888_to_RGB565 (uint32_t RGB888_color);
int main()
{
    uint32_t color_RGB_888 = 0x00FF00;
    uint16_t color_RGB_565 = 0x0;
    
    color_RGB_565 = convert_RGB888_to_RGB565 (color_RGB_888);
    
    printf ("Color in RGB 888 was %X\n", color_RGB_888);
    printf ("Same color in RGB 565 is %X\n", color_RGB_565);
    return 0;
}
uint16_t convert_RGB888_to_RGB565 (uint32_t RGB888_color)
{
    uint16_t RGB565_colorR = 0x0;   
    uint16_t RGB565_colorG = 0x0;   
    uint16_t RGB565_colorB = 0x0;   
    uint16_t RGB565_color = 0x0FFF;
    
    RGB565_colorB = RGB888_color >> 3 & 0x001F; //5 last digits
    RGB565_colorG = RGB888_color >> 5 & 0x07e0; //6 diigts in the middle
    RGB565_colorR = RGB888_color >> 8 & 0xF800; // first 5 digitts

    RGB565_color = RGB565_colorR|RGB565_colorG|RGB565_colorB;
    
    return RGB565_color;
}