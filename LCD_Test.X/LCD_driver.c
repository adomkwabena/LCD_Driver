/**
  @Author
    Adom Kwabena

  @File Name 
    LCD_driver.c
  
  @Summary
    This source file provides APIs for interfacing with the HD44780 LCD controller chip
  
  @Description
    This code supports 2x16 LCD only and the interface used is the 4-bit interface
    This code was tested on a PIC18F46K22 and compiled using MPLABX v3.60
    This code was built with the XC8 compiler v1.42
 */

/** 
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include "LCD_driver.h"

/** 
  Section: Module APIs
 */

static void LCD_Write(const char nibble, uint8_t register_select)
{
    (nibble & 0x08 || nibble & 0x80) ? LCD_D7 = 1 : LCD_D7 = 0;
    (nibble & 0x04 || nibble & 0x40) ? LCD_D6 = 1 : LCD_D6 = 0;
    (nibble & 0x02 || nibble & 0x20) ? LCD_D5 = 1 : LCD_D5 = 0;
    (nibble & 0x01 || nibble & 0x10) ? LCD_D4 = 1 : LCD_D4 = 0;
    
    // Register Selection
    LCD_RS = register_select;
    
    // Clock data into LCD
    __delay_us(1);
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;
}

void LCD_Init(void)
{
    // Configure LCD I/O pins as outputs
    LCD_RS_Tris = 0;
    LCD_EN_Tris = 0;
    LCD_D4_Tris = 0;
    LCD_D5_Tris = 0;
    LCD_D6_Tris = 0;
    LCD_D7_Tris = 0;
    
    // Configure LCD I/O pins as digital
    LCD_RS_ANSEL = 0;
    LCD_EN_ANSEL = 0;
    LCD_D4_ANSEL = 0;
    LCD_D5_ANSEL = 0;
    LCD_D6_ANSEL = 0;
    LCD_D7_ANSEL = 0;
    
    // Default value of the LCD enable pin
    LCD_EN = 0;
    
    // ~15 milliseconds delay
    uint8_t i;
    for (i = 0; i < 2; i++)
    {
        __delay_ms(5);     
    }
    
    // Function set
    LCD_Write(0x03, CMD);
    __delay_ms(5);
    LCD_Write(0x03, CMD);
    __delay_ms(1);
    LCD_Write(0x03, CMD);
    __delay_ms(1);
    
    // Start operation in 4 bit mode
    LCD_Write(0x02, CMD);   
    __delay_ms(1);
    // Number of display lines and character font
    LCD_Write(0x02, CMD);   
    LCD_Write(0x08, CMD);   
    __delay_ms(1);
    // Display off
    LCD_Write(0x00, CMD);
    LCD_Write(0x08, CMD);   
    __delay_ms(1);
    // Clear Display
    LCD_Write(0x00, CMD);
    LCD_Write(0x01, CMD);   
    __delay_ms(2);
    // Set Entry mode
    LCD_Write(0x00, CMD);
    LCD_Write(0x06, CMD);   
    __delay_ms(1);
    
    // Turn on LCD display
    LCD_Write(0x00, CMD);
    LCD_Write(0x0C, CMD);
    __delay_ms(1);
    // Return cursor home
    LCD_Write(0x00, CMD);
    LCD_Write(0x02, CMD);
    __delay_ms(3); 
}

void LCD_PutCmd(const char c)
{
    // Send upper nibble first
    LCD_Write((c & 0xF0), CMD);
    // Send lower nibble next
    LCD_Write((c & 0x0F), CMD);
    __delay_ms(3);
}

void LCD_PutChar_Cp(const char c)
{
    // Send upper nibble first
    LCD_Write((c & 0xF0), DATA);
    // Send lower nibble next
    LCD_Write((c & 0x0F), DATA);
    __delay_us(100);
}

void LCD_PutString_Cp(const char *s)
{
    while (*s)
    {
        LCD_PutChar_Cp(*s++);
    }
}

void LCD_PutChar(uint8_t row, uint8_t column, const char c)
{
    if (row == 1)
    {
        // HD44780 first row addressing starts from zero hence the need to subtract 2
        LCD_PutCmd((row + column -  2) | 0x80);
    }
    else if (row == 2)
    {
        // HD44780 second row addressing starts from 64 hence the need to add 61
        LCD_PutCmd((row + column + 62) | 0x80);
    }
    LCD_PutChar_Cp(c);
}

void LCD_PutString(uint8_t row, uint8_t column, const char *s)
{
    if (row == 1)
    {
        // HD44780 first row addressing starts from zero hence the need to subtract 2
        LCD_PutCmd((row + column -  2) | 0x80);
    }
    else if (row == 2)
    {
        // HD44780 second row addressing starts from 64 hence the need to add 61
        LCD_PutCmd((row + column + 61) | 0x80);
    }
    while (*s)
    {
        LCD_PutChar_Cp(*s++);
    }
}
