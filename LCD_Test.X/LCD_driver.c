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
#include "mcc_generated_files/mcc.h"
#include "LCD_driver.h"

/**
  Section: Private Function Prototypes
 */

/**
  @Summary
    This function writes 4 bits to the LCD
 
  @Param 
    nibble - data to be sent
 
  @Param
    register_select - selects register to which data is written
  
  @Returns
    None 
 */
static void LCD_Write(const char nibble, uint8_t register_select);

/**
  @Summary
    Initializes module specific GPIO
   
  @Param
    None
   
  @Returns
    None
 */
static void GPIO_Init(void);

/** 
  Section: Module APIs
 */

static void LCD_Write(const char nibble, uint8_t register_select)
{
    if (nibble & BIT_3_MASK || nibble & BIT_7_MASK)
    {
        LCD_D7_ON();
    }
    else
    {
        LCD_D7_OFF();
    }
    if (nibble & BIT_2_MASK || nibble & BIT_6_MASK)
    {
        LCD_D6_ON();
    }
    else
    {
        LCD_D6_OFF();
    }
    if (nibble & BIT_1_MASK || nibble & BIT_5_MASK)
    {
        LCD_D5_ON();
    }
    else
    {
        LCD_D5_OFF();
    }
    if (nibble & BIT_0_MASK || nibble & BIT_4_MASK)
    {
        LCD_D4_ON();
    }
    else
    {
        LCD_D4_OFF();
    }
    
    // Select appropriate register to write data
    if (register_select == CMD)
    {
        // Write into the command register
        LCD_RS_OFF();
    }
    else
    {
        // Write into the data register
        LCD_RS_ON();
    }
    
    // Clock data into LCD
    __delay_us(1);
    LCD_EN_ON();
    __delay_us(1);
    LCD_EN_OFF();
}

static void GPIO_Init(void)
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
}

void LCD_Init(void)
{
    // Initialize GPIO
    GPIO_Init();
    // Default value of the LCD enable pin
    LCD_EN = 0;
    
    // ~15 milliseconds delay
    __delay_ms(15);     
    
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
    if (row == FIRST_ROW)
    {
        // HD44780 first row addressing starts from zero hence the need to subtract 2
        LCD_PutCmd((row + column -  ROW_1_ADDRESS_OFFSET) | SET_DDRAM_ADDRESS);
    }
    else if (row == SECOND_ROW)
    {
        // HD44780 second row addressing starts from 64 hence the need to add 61
        LCD_PutCmd((row + column + ROW_2_ADDRESS_OFFSET) | SET_DDRAM_ADDRESS);
    }
    LCD_PutChar_Cp(c);
}

void LCD_PutString(uint8_t row, uint8_t column, const char *s)
{
    if (row == FIRST_ROW)
    {
        // HD44780 first row addressing starts from zero hence the need to subtract 2
        LCD_PutCmd((row + column - ROW_1_ADDRESS_OFFSET) | SET_DDRAM_ADDRESS);
    }
    else if (row == SECOND_ROW)
    {
        // HD44780 second row addressing starts from 64 hence the need to add 61
        LCD_PutCmd((row + column + ROW_2_ADDRESS_OFFSET) | SET_DDRAM_ADDRESS);
    }
    while (*s)
    {
        LCD_PutChar_Cp(*s++);
    }
}

