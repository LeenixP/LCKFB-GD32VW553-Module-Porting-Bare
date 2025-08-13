/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_ROCK_H_
#define BSP_CODE_BSP_ROCK_H_

#include "gd32vw55x.h"
#include "systick.h"

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


#define Module_RCU_Enable() \
    rcu_periph_clock_enable(BSP_ADC_RCU); \
    rcu_periph_clock_enable(BSP_ADC_GPIO_X_RCU); \
    rcu_periph_clock_enable(BSP_ADC_GPIO_Y_RCU); \
    rcu_periph_clock_enable(GPIO_SW_RCU);

/* PA1 ADC_IN1 */
#define BSP_ADC_GPIO_X_RCU     RCU_GPIOA
#define BSP_ADC_GPIO_X_PORT    GPIOA
#define BSP_ADC_GPIO_X_PIN     GPIO_PIN_1

/* PA2 ADC_IN2 */
#define BSP_ADC_GPIO_Y_RCU     RCU_GPIOA
#define BSP_ADC_GPIO_Y_PORT    GPIOA
#define BSP_ADC_GPIO_Y_PIN     GPIO_PIN_2

#define BSP_ADC_RCU            RCU_ADC
#define BSP_ADC                ADC
#define BSP_ADC_X_CHANNEL      ADC_CHANNEL_1
#define BSP_ADC_Y_CHANNEL      ADC_CHANNEL_2

/* PA7 SW GPIO */
#define GPIO_SW_RCU            RCU_GPIOA
#define GPIO_SW_PORT           GPIOA
#define GPIO_SW_PIN            GPIO_PIN_7

#define GET_SW      gpio_input_bit_get(GPIO_SW_PORT, GPIO_SW_PIN)  // 读取按键状态

// 采样次数
#define SAMPLES   5

void Joystick_Init(void);
int Get_Joystick_Percentage_value(uint8_t dir);
uint8_t Get_SW_state(void);

#endif /* BSP_CODE_BSP_ROCK_H_ */
