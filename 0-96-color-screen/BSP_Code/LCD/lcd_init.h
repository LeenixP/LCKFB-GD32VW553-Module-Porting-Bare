#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "gd32vw55x.h"

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 80
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 80
#endif

#ifndef u8
#define u8  uint8_t
#endif
#ifndef u16
#define u16 uint16_t
#endif
#ifndef u32
#define u32 uint32_t
#endif

//-----------------LCD端口定义----------------
#define LCD_RCU_ENABLE()    rcu_periph_clock_enable(RCU_GPIOA); \
                            rcu_periph_clock_enable(RCU_GPIOB); \
                            rcu_periph_clock_enable(RCU_SPI);

#define LCD_SCL_PORT    GPIOA
#define LCD_SCL_PIN     GPIO_PIN_11
#define LCD_SCL_AF      GPIO_AF_0

#define LCD_SDA_PORT    GPIOA
#define LCD_SDA_PIN     GPIO_PIN_9
#define LCD_SDA_AF      GPIO_AF_0

#define LCD_RES_PORT    GPIOA
#define LCD_RES_PIN     GPIO_PIN_7

#define LCD_DC_PORT     GPIOA
#define LCD_DC_PIN      GPIO_PIN_6

#define LCD_CS_PORT     GPIOB
#define LCD_CS_PIN      GPIO_PIN_11

#define LCD_BLK_PORT    GPIOB
#define LCD_BLK_PIN     GPIO_PIN_12

/* LCD信号控制宏定义 */
#define LCD_RES_Clr()  gpio_bit_write(LCD_RES_PORT,LCD_RES_PIN, 0)//RES
#define LCD_RES_Set()  gpio_bit_write(LCD_RES_PORT,LCD_RES_PIN, 1)

#define LCD_DC_Clr()   gpio_bit_write(LCD_DC_PORT,LCD_DC_PIN, 0)//DC
#define LCD_DC_Set()   gpio_bit_write(LCD_DC_PORT,LCD_DC_PIN, 1)

#define LCD_CS_Clr()   gpio_bit_write(LCD_CS_PORT,LCD_CS_PIN, 0)//CS
#define LCD_CS_Set()   gpio_bit_write(LCD_CS_PORT,LCD_CS_PIN, 1)

#define LCD_BLK_Clr()  gpio_bit_write(LCD_BLK_PORT,LCD_BLK_PIN, 0)//BLK
#define LCD_BLK_Set()  gpio_bit_write(LCD_BLK_PORT,LCD_BLK_PIN, 1)

void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




