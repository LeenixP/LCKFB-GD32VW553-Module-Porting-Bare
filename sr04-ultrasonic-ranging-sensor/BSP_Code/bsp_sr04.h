/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_SR04_H_
#define BSP_CODE_BSP_SR04_H_

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

#define SR04_Trig_GPIO_RCU    RCU_GPIOA
#define SR04_Echo_GPIO_RCU    RCU_GPIOA

#define SR04_Trig_GPIO_PORT    GPIOA
#define SR04_Echo_GPIO_PORT    GPIOA

#define SR04_Trig_GPIO_PIN    GPIO_PIN_2
#define SR04_Echo_GPIO_PIN    GPIO_PIN_3

/* 外部中断 */
#define SR04_Echo_EXTI_LINE          EXTI_3
#define SR04_Echo_EXTI_IRQn          EXTI3_IRQn
#define SR04_Echo_EXTI_PORT_SOURCE   EXTI_SOURCE_GPIOA
#define SR04_Echo_EXTI_PIN_SOURCE    EXTI_SOURCE_PIN3
#define SR04_Echo_EXTI_IRQHandler    EXTI3_IRQHandler

/* 定时器 */
#define SR04_Timer_RCU              RCU_TIMER5
#define SR04_Timer                  TIMER5
#define SR04_Timer_IRQn             TIMER5_IRQn
#define SR04_Timer_IRQHandler       TIMER5_IRQHandler


#define SR04_Module_CLK_ENABLE() \
    rcu_periph_clock_enable(SR04_Trig_GPIO_RCU); \
    rcu_periph_clock_enable(SR04_Echo_GPIO_RCU); \
    rcu_periph_clock_enable(SR04_Timer_RCU);

#define SR04_TRIG(x)    gpio_bit_write(SR04_Trig_GPIO_PORT, SR04_Trig_GPIO_PIN, x)
#define SR04_ECHO()     gpio_input_bit_get(SR04_Echo_GPIO_PORT, SR04_Echo_GPIO_PIN)

void SR04_Init(void);//超声波初始化
float SR04_GetLength(void );//获取超声波测距的距离

#endif /* BSP_CODE_BSP_SR04_H_ */
