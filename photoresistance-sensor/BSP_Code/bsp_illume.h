/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_ILLUME_H_
#define BSP_CODE_BSP_ILLUME_H_

#include "gd32vw55x.h"
#include "systick.h"

#ifndef delay_ms
#define delay_ms(x)    delay_1ms(x)
#endif
#ifndef delay_us
#define delay_us(x)    delay_1us(x)
#endif

#define BSP_ILLUME_RCU_ENABLE()   \
            rcu_periph_clock_enable(BSP_ADC_GPIO_RCU); \
            rcu_periph_clock_enable(BSP_DO_GPIO_RCU); \
            rcu_periph_clock_enable(BSP_ADC_RCU);


/* PB0 ADC_IN8 */
#define BSP_ADC_GPIO_RCU     RCU_GPIOB
#define BSP_ADC_GPIO_PORT    GPIOB
#define BSP_ADC_GPIO_PIN     GPIO_PIN_0

/* PB0 ADC_IN8 */
#define BSP_ADC_RCU         RCU_ADC
#define BSP_ADC             ADC
#define BSP_ADC_CHANNEL     ADC_CHANNEL_8

#define BSP_DO_GPIO_RCU     RCU_GPIOB
#define BSP_DO_GPIO_PORT    GPIOB
#define BSP_DO_GPIO_PIN     GPIO_PIN_2

#define BSP_DO_READ()    gpio_input_bit_get(BSP_DO_GPIO_PORT, BSP_DO_GPIO_PIN)

void illume_Init(void);
int Get_illume_Adc_Value(uint8_t Count);
int Get_illume_Percentage_value(void);
uint8_t Get_illume_DO_In(void);

#endif /* BSP_CODE_BSP_ILLUME_H_ */
