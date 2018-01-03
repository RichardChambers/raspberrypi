/********************************************************************************************
*Filename      : i2c1602_lcd.c
*Description   : test iic 1602 lcd
*Author        : Alan
*Website       : www.osoyoo.com
*Update        : 2017/07/03
********************************************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>

int BLEN = 1;//1--open backlight.0--close backlight
int fd;//linux file descriptor

//writ a word(16 bits) to LCD
void write_word(int data){
    int temp = data;
    if ( BLEN == 1 )
        temp |= 0x08;
    else
        temp &= 0xF7;
    wiringPiI2CWrite(fd, temp);
}

void sendNibble (int rs, int rw, int data)
{
    int buf = (data & 0x0F) << 4;  // data nibble in upper nibble of byte

    // set the command pins data in the lower nibble of byte
    buf |= 0x04;            // EN = 1, RW = 0, RS = 0
    buf |= (rs) ? 0x01 : 0; // set RS value
    buf |= (rw) ? 0x02 : 0; // set RW value
    write_word(buf);

    delay(2);

    buf &= 0xFB;            // Make EN = 0
    write_word(buf);
}

//send command to lcd
void send_command(int comm){
    // Send bit7-4 firstly
    sendNibble (0, 0, comm >> 4);

    // Send bit3-0 secondly
    sendNibble (0, 0, comm);
}

//send data to lcd
void send_data(int data){
    // Send bit7-4 firstly
    sendNibble (1, 0, data >> 4);

    // Send bit3-0 secondly
    sendNibble (1, 0, data);
}

//initialize the lcd
void init1602 (void)
{
    send_command(0x33); // Must initialize to 8-line mode at first
    delay(5);
    send_command(0x32); // Then initialize to 4-line mode
    delay(5);
    send_command(0x28); // 2 Lines & 5*7 dots
    delay(5);
    send_command(0x0C); // Enable display without cursor
    delay(5);
    send_command(0x01); // Clear Screen
    wiringPiI2CWrite(fd, 0x08);
}

//clear screen
void clear1602(void)
{
    send_command(0x01); //clear Screen
}

//Print the message on the lcd
void write(int xCol, int yRow, const char data[])
{
    int addr, i;
    int tmp;
    if (xCol < 0)  xCol = 0;
    if (xCol > 15) xCol = 15;
    if (yRow < 0)  yRow = 0;
    if (yRow > 1)  yRow = 1;

    // Move cursor to either line 1 or line 2
    // line 1 -> 0x80 + xCol, line 2 -> 0xC0 + xCol
    addr = 0x80 + 0x40 * yRow + xCol;
    send_command(addr);
    
    tmp = strlen(data);
    for (i = 0; i < tmp; i++){
        send_data(data[i]);
    }
}

void print_info()
{
    printf("\n");
    printf("|***************************|\n");
    printf("|    IIC 1602 LCD test      |\n");
    printf("| --------------------------|\n");
    printf("| | LCD |            | Pi   |\n");
    printf("| --------------------------|\n");
    printf("| | GND | connect to | GND  |\n");
    printf("| | VCC | connect to | 5V   |\n");
    printf("| | SDA | connect to | SDA.1|\n");
    printf("| | SCL | connect to | SCL.1|\n");
    printf("| --------------------------|\n");
    printf("|                     OSOYOO|\n");
    printf("|***************************|\n");
    printf("Program is running...\n");
    printf("Press Ctrl+C to end the program\n");
}

int main(int argc, char *argv[])
{
    int LCDAddr = 0x27;//IIc LCD address

    //init I2C 
    fd = wiringPiI2CSetup(LCDAddr);
    if (fd < 0) {
        printf ("Error: I2C setup for 1602 LCD failed.\n");
        return 1;
    }

    init1602();

    print_info();

    write(0, 0, "Hi man.Welcome ");
    write(0, 1, "to osoyoo.com");
    delay(3000);
    clear1602();

    int iCount = 0;
    while(1){
	char buf[24];

        iCount++;
	sprintf (buf, "Lesson13 cnt %d", iCount);
        write(0, 0, buf);
        write(0, 1, "IIC LCD Test");
        delay(2000);
    }
    return 0;
}
