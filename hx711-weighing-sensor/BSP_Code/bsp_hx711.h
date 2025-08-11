/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_HX711_H_
#define BSP_CODE_BSP_HX711_H_

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

#define Module_RCU_ENABLE() \
        rcu_periph_clock_enable(Module_SCL_RCU); \
        rcu_periph_clock_enable(Module_DT_RCU);

#define Module_SCL_RCU            RCU_GPIOA
#define Module_SCL_PORT           GPIOA
#define Module_SCL_PIN            GPIO_PIN_2 //SCL

#define Module_DT_RCU             RCU_GPIOA
#define Module_DT_PORT            GPIOA
#define Module_DT_PIN             GPIO_PIN_3 //SDA

//设置SDA输出模式
#define DT_OUT() \
        gpio_mode_set(Module_DT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, Module_DT_PIN); \
        gpio_output_options_set(Module_DT_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, Module_DT_PIN);

//设置SDA输入模式
#define DT_IN() \
        gpio_mode_set(Module_DT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, Module_DT_PIN);


//获取DT引脚的电平变化
#define DT_GET()   gpio_input_bit_get(Module_DT_PORT, Module_DT_PIN)


//DT与SCK输出
#define DT(x)      gpio_bit_write(Module_DT_PORT, Module_DT_PIN, x)
#define SCK(x)     gpio_bit_write(Module_SCL_PORT, Module_SCL_PIN, x)

void HX711_Init(void);
void HX711_Get_InitValue(void);
float HX711_Get_Weight(void);

#endif /* BSP_CODE_BSP_HX711_H_ */
