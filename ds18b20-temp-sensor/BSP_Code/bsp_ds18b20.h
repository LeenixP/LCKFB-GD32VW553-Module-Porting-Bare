/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_DS18B20_H_
#define BSP_CODE_BSP_DS18B20_H_

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
        rcu_periph_clock_enable(Module_DQ_RCU);

#define Module_DQ_RCU             RCU_GPIOA
#define Module_DQ_PORT            GPIOA
#define Module_DQ_PIN             GPIO_PIN_2


//设置DQ输出模式
#define DQ_OUT() \
        gpio_mode_set(Module_DQ_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, Module_DQ_PIN); \
        gpio_output_options_set(Module_DQ_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, Module_DQ_PIN);

//设置DQ输入模式
#define DQ_IN() \
        gpio_mode_set(Module_DQ_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, Module_DQ_PIN);

//获取DQ引脚的电平变化
#define DQ_GET()    gpio_input_bit_get(Module_DQ_PORT, Module_DQ_PIN)
//DQ输出
#define DQ(x)       gpio_bit_write(Module_DQ_PORT, Module_DQ_PIN, x)

void DS18B20_Reset(void);
uint8_t DS18B20_Check(void);
char DS18B20_Init(void);
float DS18B20_GetTemperture(void);


#endif /* BSP_CODE_BSP_DS18B20_H_ */
