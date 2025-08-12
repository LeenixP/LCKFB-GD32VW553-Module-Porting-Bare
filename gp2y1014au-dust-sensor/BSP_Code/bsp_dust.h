/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_DUST_H_
#define BSP_CODE_BSP_DUST_H_

#include "gd32vw55x.h"
#include "systick.h"

#ifndef delay_ms
#define delay_ms(x)    delay_1ms(x)
#endif
#ifndef delay_us
#define delay_us(x)    delay_1us(x)
#endif

#define MODULE_BSP_RCU_ENABLE()   \
            rcu_periph_clock_enable(BSP_ADC_GPIO_RCU); \
            rcu_periph_clock_enable(BSP_LED_GPIO_RCU); \
            rcu_periph_clock_enable(BSP_ADC_RCU);

/* PB0 ADC_IN8 */
#define BSP_ADC_GPIO_RCU     RCU_GPIOB
#define BSP_ADC_GPIO_PORT    GPIOB
#define BSP_ADC_GPIO_PIN     GPIO_PIN_0

/* PB0 ADC_IN8 */
#define BSP_ADC_RCU         RCU_ADC
#define BSP_ADC             ADC
#define BSP_ADC_CHANNEL     ADC_CHANNEL_8

#define BSP_LED_GPIO_RCU     RCU_GPIOB
#define BSP_LED_GPIO_PORT    GPIOB
#define BSP_LED_GPIO_PIN     GPIO_PIN_2

#define GP2Y1014AU_VO(x)   gpio_bit_write(BSP_LED_GPIO_PORT, BSP_LED_GPIO_PIN, x)

// 采样次数
#define SAMPLES   5

void GP2Y1014AU_Init(void);
char Read_dust_concentration(float *d_dat);

#endif /* BSP_CODE_BSP_DUST_H_ */
