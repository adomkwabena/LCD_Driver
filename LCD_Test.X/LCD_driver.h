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

// Register select modes
#define CMD                         0u
#define DATA                        1u

// LCD Data bit mask definitions
#define BIT_0_MASK                  0x01
#define BIT_1_MASK                  0x02
#define BIT_2_MASK                  0x04
#define BIT_3_MASK                  0x08
#define BIT_4_MASK                  0x10
#define BIT_5_MASK                  0x20
#define BIT_6_MASK                  0x40
#define BIT_7_MASK                  0x80

// Hardware abstraction
// PIC specific definitions for GPIO initialization
#define LCD_RS_Tris                 TRISB4
#define LCD_EN_Tris                 TRISB5
#define LCD_D4_Tris                 TRISB0
#define LCD_D5_Tris                 TRISB1
#define LCD_D6_Tris                 TRISB2
#define LCD_D7_Tris                 TRISB3

#define LCD_RS_ANSEL                ANSELBbits.ANSB4
#define LCD_EN_ANSEL                ANSELBbits.ANSB5
#define LCD_D4_ANSEL                ANSELBbits.ANSB3
#define LCD_D5_ANSEL                ANSELBbits.ANSB2
#define LCD_D6_ANSEL                ANSELBbits.ANSB1
#define LCD_D7_ANSEL                ANSELBbits.ANSB0

// GPIO Macros for single bit accesses
#define LCD_RS_ON()                 do {LATB4 = 1;} while (0)
#define LCD_RS_OFF()                do {LATB4 = 0;} while (0)
#define LCD_EN_ON()                 do {LATB5 = 1;} while (0)
#define LCD_EN_OFF()                do {LATB5 = 0;} while (0)
#define LCD_D4_ON()                 do {LATB0 = 1;} while (0)
#define LCD_D4_OFF()                do {LATB0 = 0;} while (0)
#define LCD_D5_ON()                 do {LATB1 = 1;} while (0)
#define LCD_D5_OFF()                do {LATB1 = 0;} while (0)
#define LCD_D6_ON()                 do {LATB2 = 1;} while (0)
#define LCD_D6_OFF()                do {LATB2 = 0;} while (0)
#define LCD_D7_ON()                 do {LATB3 = 1;} while (0)
#define LCD_D7_OFF()                do {LATB3 = 0;} while (0)

// Definitions for addressing Data Display RAM (DDRAM)
#define SET_DDRAM_ADDRESS           0x80
// The address for the first row starts at 0
// This requires a subtraction of 2 if using the sum
// of x and y coordinates which start counting at 1
#define ROW_1_ADDRESS_OFFSET        2u
// The address for the second row starts at 64
// This requires an addition of 61 if using the sum
// of x and y coordinates that start counting at 1
#define ROW_2_ADDRESS_OFFSET        61u
// Row definitions
#define FIRST_ROW                   1u
#define SECOND_ROW                  2u

// Some handy LCD commands
#define _LCD_CLEAR                  0x01
#define _LCD_CURSOR_OFF             0x0C
#define _LCD_CURSOR_ON              0x0D
#define _LCD_HOME                   0x02

/** 
  Section: Module APIs
 */

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


