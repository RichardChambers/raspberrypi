/********************************************************************************************
*Filename      : i2c1602_lcd.c
*Description   : test iic 1602 lcd
*Author        : Alan
*Website       : www.osoyoo.com
*Update        : 2017/07/03
********************************************************************************************/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

static int LCDAddr = 0x27;   // I2c LCD address, use sudo i2cdetect -y 1 after hooking up 1602
static int BLEN = 1;         // 1--open backlight. 0--close backlight
static int fd;               // I2C device linux file descriptor

static void sendNibble (int bl, int rs, int rw, int data)
{
    int buf = (data & 0x0F) << 4;  // data nibble in upper nibble of byte

    // set the command pins data in the lower nibble of byte
    buf |= (bl) ? 0x08 : 0;    // set backlight on/off value
    buf |= 0x04;               // EN = 1, RW = 0, RS = 0
    buf |= (rw) ? 0x02 : 0;    // set RW value
    buf |= (rs) ? 0x01 : 0;    // set RS value
    wiringPiI2CWrite (fd, buf);

    delay (2);

    buf &= 0xFB;               // Make EN = 0 to turn off latch
    wiringPiI2CWrite (fd, buf);
}

//send command to lcd
static void send_command(int comm)
{
    // Send upper nibble, bit 7-4 firstly
    sendNibble (BLEN, 0, 0, comm >> 4);

    // Send lower nibble, bit 3-0 secondly
    sendNibble (BLEN, 0, 0, comm);
}

//send data (text character) to lcd
static void send_data(int data){
    // Send upper nibble, bit 7-4 firstly
    sendNibble (BLEN, 1, 0, data >> 4);

    // Send lower nibble, bit 3-0 secondly
    sendNibble (BLEN, 1, 0, data);
}

//clear screen
void lcd1602Clear(void)
{
    send_command (0x01); //clear display, set cursor to home position
}

//Print the message on the lcd
//initialize the lcd
static void init1602 (void)
{
    send_command (0x33); // Must initialize to 8-line mode at first
    delay (5);

    send_command (0x32); // Then initialize to 4-line mode
    delay (5);

    send_command (0x28); // 4 bit mode, 2 Lines and 5x7 pixels character size
    delay (5);

    send_command (0x0C); // Enable display without cursor
    delay (5);

    lcd1602Clear ();
    wiringPiI2CWrite (fd, 0x08);  // turn on backlight of LCD
}

void lcd1602Write (int xCol, int yRow, const char data[])
{
    int len = strlen (data);

    // 16 columns per row
    if (xCol < 0)  xCol = 0;
    if (xCol > 15) xCol = 15;

    // only two rows or lines, row 0 and row 1
    if (yRow < 0)  yRow = 0;
    if (yRow > 1)  yRow = 1;

    // Move cursor to either row 0 or row 1
    // row 0 -> 0x80 + xCol, row 1 -> 0xC0 + xCol
    int addr = 0x80 + 0x40 * yRow + xCol;
    send_command (addr);
    
    int i;
    for (i = 0; i < len; i++){
        send_data (data[i]);
    }
}

void lcd1602Writef (int xCol, int yRow, const char *format, ... )
{
    char  buff[256];

    va_list  args;
    va_start (args, format);
    vsprintf (buff, format, args);
    va_end (args);

    lcd1602Write (xCol, yRow, buff);
}

int lcd1602Open(int lcdAddr)
{

    //init I2C 
    fd = wiringPiI2CSetup (lcdAddr);
    if (fd < 0) {
        return 1;
    }

    init1602 ();

    return 0;
}

int lcd1602Close (void)
{
    lcd1602Clear ();
    close (fd);
}
