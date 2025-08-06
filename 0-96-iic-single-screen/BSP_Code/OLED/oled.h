#ifndef __OLED_H
#define __OLED_H 

#include "gd32vw55x.h"
#include "systick.h"
#include "stdlib.h"	

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#ifndef delay_ms
#define delay_ms(x)  delay_1ms(x)
#endif

#ifndef delay_us
#define delay_us(x)  delay_1us(x)
#endif

//-----------------OLED端口定义---------------- 

#define SCREEN_GPIO_RCU_ENABLE()   rcu_periph_clock_enable(RCU_GPIOA)

#define SCREEN_SCL_PORT            GPIOA
#define SCREEN_SCL_PIN             GPIO_PIN_2 //SCL

#define SCREEN_SDA_PORT            GPIOA
#define SCREEN_SDA_PIN             GPIO_PIN_3 //SDA

#define OLED_SCL_Clr()  gpio_bit_write(SCREEN_SCL_PORT, SCREEN_SCL_PIN, 0)//SCL
#define OLED_SCL_Set()  gpio_bit_write(SCREEN_SCL_PORT, SCREEN_SCL_PIN, 1)

#define OLED_SDA_Clr()  gpio_bit_write(SCREEN_SDA_PORT, SCREEN_SDA_PIN, 0)//DIN
#define OLED_SDA_Set()  gpio_bit_write(SCREEN_SDA_PORT, SCREEN_SDA_PIN, 1)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);

void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

