/** 
 * @file     lcd.c
 * @brief    COG12864液晶屏显示
 * @details  ST7565R驱动
 * @author   华兄
 * @email    591881218@qq.com
 * @date     2014
 * @version  vX.XX
 * @par Copyright (c):  
 *           深圳市合尔凯科技有限公司
 * @par History:          
 *   version: author, date, desc\n 
 */

#include "includes.h"


const unsigned char lcd_map_welcome[] =
{
    /*-- 宽度x高度=128x64 --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,
    0xF8,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFE,0xFC,0xF8,0xE0,0x80,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00,
    0x00,0x00,0x03,0x1E,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x07,0xFE,0xE0,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x80,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF0,0x78,0xF8,0xF8,0xFC,
    0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xE0,0x80,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x61,0x23,
    0x3E,0x1C,0x10,0x00,0x00,0x07,0x06,0x06,0x06,0x02,0x02,0x03,0x03,0x03,0x03,0x01,
    0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x03,0x03,0x02,0x06,0x06,0x0E,
    0x0C,0x1C,0x18,0x18,0x30,0x60,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x01,0x03,
    0x03,0x07,0x0F,0x0F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,
    0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0x3F,
    0x3E,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x38,0x1C,0x0E,0x07,0x83,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x40,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x3C,0xF0,0xC0,0x00,0x00,0x00,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x70,0x30,0x38,0x38,0x18,0x1C,0x1C,
    0x1C,0x0E,0x0F,0x3E,0xFE,0x86,0x06,0x07,0x07,0x03,0x02,0x70,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xFC,0x3F,0x03,0xC0,0x00,0xE0,0x78,0x8E,0xDF,0x6E,0x68,0x6C,0x6C,
    0xFC,0x8C,0x84,0x4C,0x24,0x04,0x04,0x07,0x04,0x07,0x07,0x04,0x64,0xC4,0xCC,0x74,
    0x34,0x34,0x34,0x34,0x7C,0xE4,0xC4,0x47,0x67,0x0C,0xFC,0xFC,0x00,0x00,0x00,0xFF,
    0x00,0x00,0x00,0x00,0x80,0x7E,0x00,0x00,0x00,0x00,0x00,0x87,0xFF,0x7E,0x00,0x00,
    0xAF,0xFF,0xFF,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,
    0xC0,0xE0,0x70,0x70,0x70,0x38,0x3C,0x1C,0x1C,0x0E,0x0E,0x07,0x07,0x07,0x03,0x03,
    0x03,0x0C,0x20,0x00,0x00,0x00,0x00,0x00,0x01,0x1E,0xC0,0x00,0x00,0x00,0x00,0xC0,
    0x60,0x20,0x00,0x00,0x07,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3F,0xF8,0x8E,0x78,0x8F,0xFF,0xA0,0x73,0xF0,0x00,0x00,0x00,0x00,
    0x00,0x03,0x07,0x00,0x00,0x00,0x00,0x04,0xC4,0x02,0x00,0x00,0x00,0x03,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xAE,0x10,0x00,0xFF,0xFF,0x00,0x00,0xE0,0x3F,
    0x00,0x80,0xE0,0x3C,0x07,0x00,0x00,0x80,0x40,0x20,0x18,0x07,0x03,0x00,0x00,0x00,
    0xFF,0xFF,0xFF,0xFF,0x78,0xF8,0x38,0x1C,0x1C,0x0E,0x0E,0x07,0x07,0x03,0x03,0x01,
    0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x87,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xA6,0x08,0x30,0x40,0x47,
    0x80,0x80,0x00,0x80,0xF0,0x3F,0x03,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x03,0x0E,0x1B,0x1C,0x73,0xEC,0xF8,0xF0,0x30,0x60,0x60,
    0x40,0xC0,0xC0,0x80,0x80,0x80,0x80,0x88,0x93,0x80,0x90,0x80,0x88,0x84,0x84,0x80,
    0x80,0x80,0xC0,0xC0,0x40,0x40,0x60,0x20,0x30,0x30,0x3F,0xF7,0xF0,0xFE,0x5B,0x2C,
    0x36,0x11,0x18,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x13,0x1F,0x18,0x31,0x26,0x38,0x23,0x2C,0x30,0x60,0xC0,0x80,0x80,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x07,0x00,0x00,0x03,0x0C,0x00,0x80,
    0x40,0x30,0x0C,0xC3,0xC0,0xC0,0xC0,0xE0,0x20,0x00,0x00,0x80,0xC0,0xC0,0x60,0x30,
    0x18,0x1C,0x0F,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x81,0xF1,0x39,0x1D,0xE5,0x7F,0x7F,0xFF,0xBC,0x58,0x7D,0xD7,
    0xFC,0x9C,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x86,0x86,
    0x84,0x84,0xFC,0xB8,0xF8,0x78,0xF8,0xD8,0x78,0x38,0xFC,0x54,0xCA,0x7A,0xF9,0xF8,
    0xF8,0xF8,0xFC,0xFC,0xFD,0x7D,0xFD,0xFE,0xFA,0xDF,0xFF,0xE1,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x7E,0x7F,0x01,0x40,0x4F,0x67,0x33,0x11,0x31,0x38,0x1C,0x34,0x22,
    0x65,0x47,0x00,0x1F,0x7E,0x7C,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char lcd_disp_buf[LCD_YSIZE / 8][LCD_XSIZE];

void lcd_delay(unsigned long dly)
{
    OSTimeDly(dly);
}

void lcd_send_byte(unsigned char byte)
{
    unsigned char i, temp;


    temp = byte;

    for(i = 0; i < 8; i++)
    {
        LCD_SCK_LOW();

        if(temp & 0x80)
        {
            LCD_MOSI_HIGH();
        }
        else
        {
            LCD_MOSI_LOW();
        }

        LCD_SCK_HIGH();

        temp <<= 1;
    }
}

void lcd_write_cmd(unsigned char cmd)
{   
    OS_CPU_SR_ALLOC();
    

    OS_ENTER_CRITICAL();
    
    LCD_RS_LOW();
    LCD_CS_LOW();
    lcd_send_byte(cmd);
    LCD_CS_HIGH();

    OS_EXIT_CRITICAL();
}

void lcd_write_data(unsigned char data)
{	
    OS_CPU_SR_ALLOC();
    

    OS_ENTER_CRITICAL();
    
    LCD_RS_HIGH();
    LCD_CS_LOW();
    lcd_send_byte(data);
    LCD_CS_HIGH();

    OS_EXIT_CRITICAL();
}

void lcd_clr_scr(void)
{
    unsigned char page, seg;

    
    for(page = 0xb0; page < 0xb8; page++)
    {
        lcd_write_cmd(page); //page
       
        lcd_write_cmd(0x10); //column
        
        lcd_write_cmd(0x00); //column

        for(seg = 0; seg < 128; seg++) //写128列
        {
            lcd_write_data(0x00);	
        }	
    }
}

void lcd_disp_map(unsigned char *map)
{
    unsigned char page, seg;

    
    for(page = 0xb0; page < 0xb8; page++)
    {
        lcd_write_cmd(page); //page
       
        lcd_write_cmd(0x10); //column
        
        lcd_write_cmd(0x00); //column

        for(seg = 0; seg < 128; seg++) //写128列
        {
            lcd_write_data(*map++);	
        }	
    }
}

void lcd_init(void)
{    
    LCD_Config();

    LCD_BACKLIGHT_OFF();    

    lcd_delay(2);

    LCD_RST_LOW();
    lcd_delay(2);
    LCD_RST_HIGH();
    lcd_delay(2);

    lcd_write_cmd(0xe2); /*软复位*/
    lcd_delay(2);
    lcd_write_cmd(0x2c); /*升压步聚1*/
    lcd_delay(2);
    lcd_write_cmd(0x2e); /*升压步聚2*/
    lcd_delay(2);
    lcd_write_cmd(0x2f); /*升压步聚3*/
    lcd_delay(2);
    lcd_write_cmd(0x25); /*粗调对比度，可设置范围0x20～0x27*/
    lcd_write_cmd(0x81); /*微调对比度*/
    lcd_write_cmd(0x16); /*微调对比度的值，可设置范围0x00～0x3f*/
    lcd_write_cmd(0xa2); /*1/9 偏压比（bias）*/
    lcd_write_cmd(0xc8); /*行扫描顺序：从上到下*/
    lcd_write_cmd(0xa0); /*列扫描顺序：从左到右*/ 
    lcd_write_cmd(0x40); /*起始行：从第一行开始*/
    lcd_write_cmd(0xaf); /*开显示*/

    lcd_delay(2);

    lcd_clr_scr();
}

