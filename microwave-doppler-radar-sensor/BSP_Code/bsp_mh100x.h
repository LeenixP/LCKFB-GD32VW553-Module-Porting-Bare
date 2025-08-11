/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_MH100X_H_
#define BSP_CODE_BSP_MH100X_H_

#include "gd32vw55x.h"
#include "systick.h"

#ifndef delay_ms
#define delay_ms(x)  delay_1ms(x)
#endif

#ifndef delay_us
#define delay_us(x)  delay_1us(x)
#endif

#define Module_RCU_ENABLE() \
        rcu_periph_clock_enable(BSP_Module_GPIO_OUT_RCU);


#define BSP_Module_GPIO_OUT_RCU		RCU_GPIOA
#define BSP_Module_GPIO_OUT_PORT	GPIOA
#define BSP_Module_GPIO_OUT_PIN		GPIO_PIN_2

#define OUT_IN   gpio_input_bit_get(BSP_Module_GPIO_OUT_PORT,BSP_Module_GPIO_OUT_PIN)

void MH100x_Init(void);
char OUTPIN_Scanf(void);//微波雷达的输入状态

#endif /* BSP_CODE_BSP_MH100X_H_ */
