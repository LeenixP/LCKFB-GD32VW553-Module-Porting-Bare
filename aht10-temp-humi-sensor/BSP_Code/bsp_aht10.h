/*
 * bsp_aht10.h
 *
 *  Created on: 2025年8月11日
 *      Author: lipeng
 */

#ifndef BSP_CODE_BSP_AHT10_H_
#define BSP_CODE_BSP_AHT10_H_

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
        rcu_periph_clock_enable(Module_SDA_RCU);

#define Module_SCL_RCU             RCU_GPIOA
#define Module_SCL_PORT            GPIOA
#define Module_SCL_PIN             GPIO_PIN_2 //SCL

#define Module_SDA_RCU             RCU_GPIOA
#define Module_SDA_PORT            GPIOA
#define Module_SDA_PIN             GPIO_PIN_3 //SDA

//SDA输入模式
#define SDA_IN() \
        gpio_mode_set(Module_SDA_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, Module_SDA_PIN);

//SDA输出模式
#define SDA_OUT() \
        gpio_mode_set(Module_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, Module_SDA_PIN); \
        gpio_output_options_set(Module_SDA_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, Module_SDA_PIN);

#define SCL(BIT)    gpio_bit_write(Module_SCL_PORT, Module_SCL_PIN, BIT)
#define SDA(BIT)    gpio_bit_write(Module_SDA_PORT, Module_SDA_PIN, BIT)
#define SDA_GET()   gpio_input_bit_get(Module_SDA_PORT, Module_SDA_PIN)


void AHT10_Init(void);
uint8_t AHT10_Get_TempHumi(float *Temperature, float *Humidity);

#endif /* BSP_CODE_BSP_AHT10_H_ */
