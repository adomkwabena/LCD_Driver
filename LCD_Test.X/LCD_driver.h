/**
  @Author
    Adom Kwabena

  @File Name 
    LCD_driver.h
  
  @Summary
    This source file provides APIs for interfacing with the HD44780 LCD controller chip
 
  @Description
    This code supports 2x16 LCD only and the interface used is the 4-bit interface
    This code was tested on a PIC18F46K22 and compiled using MPLABX v3.60
    This code was built with the XC8 compiler v1.42
 */

#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

/** 
  Section: Module Definitions
 */

// Operating frequency - needed for delay routines
#define _XTAL_FREQ 8000000

// Register select modes
#define CMD  0
#define DATA 1

// Hardware abstraction
#define LCD_RS  LATB4
#define LCD_EN  LATB5
#define LCD_D4  LATB0
#define LCD_D5  LATB1
#define LCD_D6  LATB2
#define LCD_D7  LATB3

#define LCD_RS_Tris TRISB4
#define LCD_EN_Tris TRISB5
#define LCD_D4_Tris TRISB0
#define LCD_D5_Tris TRISB1
#define LCD_D6_Tris TRISB2
#define LCD_D7_Tris TRISB3

#define LCD_RS_ANSEL  ANSELBbits.ANSB4
#define LCD_EN_ANSEL  ANSELBbits.ANSB5
#define LCD_D4_ANSEL  ANSELBbits.ANSB3
#define LCD_D5_ANSEL  ANSELBbits.ANSB2
#define LCD_D6_ANSEL  ANSELBbits.ANSB1
#define LCD_D7_ANSEL  ANSELBbits.ANSB0

// Some handy LCD commands
#define _LCD_CLEAR      0x01
#define _LCD_CURSOR_OFF 0x0C
#define _LCD_CURSOR_ON  0x0D
#define _LCD_HOME       0x02

/** 
  Section: Module APIs
 */

/**
  @Summary
    This function writes 4 bits to the LCD
 
  @Param 
    nibble - data to be sent
 
  @Param
    register_select - selects register to which data is written
  
  @Returns
    none 
 */
static void LCD_Write(const char nibble, uint8_t register_select);

/**
  @Summary
    This function initializes the LCD
 
  @Param 
    None
 
  @Returns
    none 
 */
void LCD_Init(void);

/**
  @Summary
    This function sends a single byte command to the LCD
 
  @Param 
    c - command to be sent
  
  @Returns
    none 
 */
void LCD_PutCmd(const char c);

/**
  @Summary
    This function displays a character at the current cursor position
 
  @Param 
    c - character to be displayed
 
  @Returns
    none 
 */
void LCD_PutChar_Cp(const char c);

/**
  @Summary
    This function displays a string on the LCD
    The string is displayed at the current cursor position
 
  @Param 
    s - pointer to the string to be displayed
 
  @Returns
    none 
 */
void LCD_PutString_Cp(const char *s);

/**
  @Summary
    This function displays a character on the LCD
    The character is displayed at a user specified location
 
  @Param 
    row - select row to display data
 
  @Param
    column - select column to display data

  @Param
    c - character to be displayed
 
  @Returns
    none 
 */
void LCD_PutChar(uint8_t row, uint8_t column, const char c);

/**
  @Summary
    This function displays a string of characters on the LCD
    The user specifies the location at which to begin displaying data
 
  @Param 
    row - select row to begin displaying data
 
  @Param
    column - select column to begin displaying data

  @Param
    s - pointer to the string to be displayed
 
  @Returns
    none 
 */
void LCD_PutString(uint8_t row, uint8_t column, const char *s);

#endif	/* LCD_DRIVER_H */


