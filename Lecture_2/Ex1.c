/******************************************************************************

Write swap16,  swap32, swap64 functions that swap, bytes in 
uint16_t, unit32_t, and uint64_t functions.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
uint16_t swap16 (uint16_t input16_number);
uint32_t swap32 (uint32_t input32_number);
uint64_t swap64 (uint64_t input64_number);
int main()
{
    uint16_t init_uint16_number = 0x93A1;
    uint16_t swap_result_uint16 = 0x0000;
    
    swap_result_uint16 = swap16(init_uint16_number);
    
    
    printf ("Number in uint16 befor swap 0x%X\n", init_uint16_number);
    printf ("Number in uint16 after swap 0x%X\n", swap_result_uint16);
    
    //-------------------------------------------------------------------
    uint32_t init_uint32_number = 0xC2F493A1;
    uint32_t swap_result_uint32 = 0x00000000;
    
    swap_result_uint32 = swap32(init_uint32_number);
    
    printf ("Number in uint32 befor swap 0x%X\n", init_uint32_number);
    printf ("Number in uint32 after swap 0x%X\n", swap_result_uint32);
    
    //-------------------------------------------------------------------
    uint64_t init_uint64_number = 0xC2F493A1EB56D780;
    uint64_t swap_result_uint64 = 0x0000000000000000;
    
    swap_result_uint64 = swap64(init_uint64_number);
    
    printf ("Number in uint64 befor swap 0x%lX\n", init_uint64_number);
    printf ("Number in uint64 after swap 0x%lX\n", swap_result_uint64);
    return 0;
}
uint16_t swap16 (uint16_t input16_number)
{
    uint16_t first_byte = 0x0, secound_byte = 0x0, result16 = 0x0;
    
    first_byte = input16_number << 8 & 0xFF00;
    secound_byte = input16_number >> 8 & 0x00FF;
    result16 = first_byte | secound_byte;
    return result16;
}
uint32_t swap32 (uint32_t input32_number)
{
    uint32_t first_byte = 0x0, secound_byte = 0x0, third_byte = 0x0,
                forth_byte = 0x0, result32 = 0x0;
    
    first_byte = input32_number << 24 & 0xFF000000;
    secound_byte = input32_number << 8 & 0x00FF0000;
    third_byte = input32_number >> 8 & 0x0000FF00;
    forth_byte = input32_number >> 24 & 0x000000FF;
    
    result32 = first_byte | secound_byte | third_byte | forth_byte;
    return result32;
}
uint64_t swap64 (uint64_t input64_number)
{
    uint64_t first_byte = 0x0, secound_byte = 0x0, third_byte = 0x0,
                forth_byte = 0x0, fifth_byte =0x0, sixth_byte = 0x0,
                seventh_byte = 0x0, eighth_byte = 0x0, result64 = 0x0;
    
    first_byte = input64_number << 56 & 0xFF00000000000000;
    secound_byte = input64_number << 40 & 0x00FF000000000000;
    third_byte = input64_number << 24 & 0x0000FF0000000000;
    forth_byte = input64_number << 8 & 0x000000FF00000000;
    fifth_byte = input64_number >> 8 & 0x00000000FF000000;
    sixth_byte = input64_number >> 24 & 0x0000000000FF0000;
    seventh_byte = input64_number >>40 &0x000000000000FF00;
    eighth_byte = input64_number >> 56 &0x00000000000000FF;

    result64 = first_byte | secound_byte | third_byte | forth_byte | fifth_byte |
                sixth_byte | seventh_byte |eighth_byte;
    return result64;
}