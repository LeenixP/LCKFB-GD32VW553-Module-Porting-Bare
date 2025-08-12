/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_HUMANIR_H_
#define BSP_CODE_BSP_HUMANIR_H_

#include "gd32vw55x.h"

#define HunmanIR_GPIO_RCU_ENABLE() \
        rcu_periph_clock_enable(HunmanIR_GPIO_RCU);

#define HunmanIR_GPIO_RCU       RCU_GPIOA
#define HunmanIR_GPIO_PORT      GPIOA
#define HunmanIR_GPIO_PIN       GPIO_PIN_2
    
#define HunmanIR_GPIO_READ()    gpio_input_bit_get(HunmanIR_GPIO_PORT, HunmanIR_GPIO_PIN)

void HumanIR_Init(void);
char Get_HumanIR(void);

#endif /* BSP_CODE_BSP_HUMANIR_H_ */
