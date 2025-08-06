/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_DHT11_H_
#define BSP_CODE_BSP_DHT11_H_

#include "gd32vw55x.h"
#include "systick.h"

#ifndef delay_ms
#define delay_ms(x)    delay_1ms(x)
#endif
#ifndef delay_us
#define delay_us(x)    delay_1us(x)
#endif

#define DHT11_DAT_GPIO_RCU       RCU_GPIOA   // DHT11数据引脚
#define DHT11_DAT_GPIO_PORT      GPIOA       // DHT11数据端口
#define DHT11_DAT_GPIO_PIN       GPIO_PIN_5  // DHT11数据引脚

// 开启DHT11数据引脚时钟
#define DHT11_DAT_GPIO_CLK_ENABLE()   rcu_periph_clock_enable(DHT11_DAT_GPIO_RCU)

// 设置DHT11输出高或低电平
#define DATA_GPIO_OUT(x)    gpio_bit_write(DHT11_DAT_GPIO_PORT, DHT11_DAT_GPIO_PIN, x)

// 获取DHT11数据引脚高低电平状态
#define DATA_GPIO_IN        gpio_input_bit_get(DHT11_DAT_GPIO_PORT, DHT11_DAT_GPIO_PIN)

void DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(float *temperature, float *humidity);

#endif /* BSP_CODE_BSP_DHT11_H_ */
