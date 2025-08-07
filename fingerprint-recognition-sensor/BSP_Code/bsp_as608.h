/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_AS608_H_
#define BSP_CODE_BSP_AS608_H_

#include "gd32vw55x.h"
#include "systick.h"

#ifndef delay_ms
#define delay_ms(x)    delay_1ms(x)
#endif
#ifndef delay_us
#define delay_us(x)    delay_1us(x)
#endif

//时钟定义
#define BSP_UART_RCU                       RCU_UART1
#define BSP_UART_TX_RCU                    RCU_GPIOB
#define BSP_UART_RX_RCU                    RCU_GPIOB

//串口发送引脚定义
#define BSP_UART_TX_PORT                   GPIOB
#define BSP_UART_TX_PIN                    GPIO_PIN_4
#define BSP_UART_TX_AF                     GPIO_AF_8
//串口接收引脚定义
#define BSP_UART_RX_PORT                   GPIOB
#define BSP_UART_RX_PIN                    GPIO_PIN_3
#define BSP_UART_RX_AF                     GPIO_AF_8

//串口定义
#define BSP_UART                           UART1
#define BSP_UART_IRQ                       UART1_IRQn
#define BSP_UART_IRQHandler                UART1_IRQHandler

#define BSP_AS608_WAK_RCU                  RCU_GPIOB
#define BSP_AS608_WAK_PORT                 GPIOB
#define BSP_AS608_WAK_PIN                  GPIO_PIN_2

/* 串口缓冲区的数据长度 */
#define SERIAL_RECEIVE_LENGTH  255
#define TOUCH_IN               gpio_input_bit_get(BSP_AS608_WAK_PORT, BSP_AS608_WAK_PIN)


void AS608_Init(void);
char get_as608_touch(void);

void UsartSendString(uint8_t *ucstr);
char Device_Check(void);
void FPM10A_Add_Fingerprint(void);//添加指纹
unsigned int FPM10A_Find_Fingerprint(void);//查找指纹
void FPM10A_Delete_All_Fingerprint(void);

#endif /* BSP_CODE_BSP_AS608_H_ */
