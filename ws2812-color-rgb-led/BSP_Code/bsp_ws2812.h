/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#ifndef BSP_CODE_BSP_WS2812_H_
#define BSP_CODE_BSP_WS2812_H_

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

/* * * * * * * WS2812颜色和数量定义 * * * * * */

#define WS2812_MAX        8             // 彩灯最大个数
#define WS2812_NUMBERS    8             // 彩灯个数

#define WS2812_RED        0xff0000      // 红色
#define WS2812_GREEN      0x00ff00      // 绿色
#define WS2812_BLUE       0x0000ff      // 蓝色
#define WS2812_BLACK      0x000000      // 熄灭
#define WS2812_WHITE      0xffffff      // 白色

/* * * * * * * 引脚和SPI定义 * * * * * */

#define Module_RCU_Enable() \
    rcu_periph_clock_enable(RCU_GPIOA); \
    rcu_periph_clock_enable(RCU_SPI);

#define WS2812_MOSI_GPIO_PORT    GPIOA
#define WS2812_MOSI_GPIO_PIN     GPIO_PIN_9
#define WS2812_MOSI_GPIO_AF      GPIO_AF_0

void WS2812_Init(void);// 初始化
int WS2812_RESET(void);
int WS2812_Set_Color(uint8_t LED_NUM, uint64_t Color);  // 设置彩灯颜色
int WS2812_Send_Array(void);    // 发送彩灯数据

#endif /* BSP_CODE_BSP_WS2812_H_ */
