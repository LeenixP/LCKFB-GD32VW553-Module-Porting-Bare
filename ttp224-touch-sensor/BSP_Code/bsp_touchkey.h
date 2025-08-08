/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_TOUCHKEY_H_
#define BSP_CODE_BSP_TOUCHKEY_H_

#include "gd32vw55x.h"

/* TTP224触摸按键引脚定义 */
#define TTP224_GPIO_RCU_ENABLE() \
    rcu_periph_clock_enable(RCU_GPIOA);

#define TTP224_KEY_IN1_GPIO_PORT    GPIOA
#define TTP224_KEY_IN1_GPIO_PIN     GPIO_PIN_4
#define TTP224_KEY_IN1_READ()       gpio_input_bit_get(TTP224_KEY_IN1_GPIO_PORT, TTP224_KEY_IN1_GPIO_PIN)

#define TTP224_KEY_IN2_GPIO_PORT    GPIOA
#define TTP224_KEY_IN2_GPIO_PIN     GPIO_PIN_5
#define TTP224_KEY_IN2_READ()       gpio_input_bit_get(TTP224_KEY_IN2_GPIO_PORT, TTP224_KEY_IN2_GPIO_PIN)

#define TTP224_KEY_IN3_GPIO_PORT    GPIOA
#define TTP224_KEY_IN3_GPIO_PIN     GPIO_PIN_6
#define TTP224_KEY_IN3_READ()       gpio_input_bit_get(TTP224_KEY_IN3_GPIO_PORT, TTP224_KEY_IN3_GPIO_PIN)

#define TTP224_KEY_IN4_GPIO_PORT    GPIOA
#define TTP224_KEY_IN4_GPIO_PIN     GPIO_PIN_7
#define TTP224_KEY_IN4_READ()       gpio_input_bit_get(TTP224_KEY_IN4_GPIO_PORT, TTP224_KEY_IN4_GPIO_PIN)

void TTP224_GPIO_Init(void);//初始化TTP224触摸按键GPIO
char Key_IN1_Scan(void);//触摸按键1的输入状态
char Key_IN2_Scan(void);//触摸按键2的输入状态
char Key_IN3_Scan(void);//触摸按键3的输入状态
char Key_IN4_Scan(void);//触摸按键4的输入状态

#endif /* BSP_CODE_BSP_TOUCHKEY_H_ */
