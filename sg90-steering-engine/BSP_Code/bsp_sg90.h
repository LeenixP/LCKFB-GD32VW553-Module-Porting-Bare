/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_SG90_H_
#define BSP_CODE_BSP_SG90_H_

#include "gd32vw55x.h"
#include "systick.h"

#define Module_RCU_Enable() \
    rcu_periph_clock_enable(RCU_GPIOA); \
    rcu_periph_clock_enable(RCU_TIMER1);

/* TIMER */
#define BSP_PWM_TIMER_RCU   RCU_TIMER1  // 定时器时钟
#define BSP_PWM_TIMER       TIMER1      // 定时器
#define BSP_PWM_TIMER_CH    TIMER_CH_1  // 定时器通道

/* PA5  TIMER1_CH1 */
#define BSP_PWM_RCU         RCU_GPIOA
#define BSP_PWM_PORT        GPIOA
#define BSP_PWM_PIN         GPIO_PIN_1
#define BSP_PWM_AF          GPIO_AF_1

void SG90_Init(void);
void Set_SG90_Servo_Angle(uint32_t angle);
uint8_t Get_SG90_Servo_Angle(void);

#endif /* BSP_CODE_BSP_SG90_H_ */
