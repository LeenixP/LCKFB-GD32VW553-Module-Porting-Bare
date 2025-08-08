/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#include "bsp_touchkey.h"


/******************************************************************
 * 函 数 名 称：TTP224_GPIO_Init
 * 函 数 说 明：初始化TTP224触摸按键GPIO
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void TTP224_GPIO_Init(void)
{
    /* 使能GPIO时钟 */
    TTP224_GPIO_RCU_ENABLE();

    /* 配置触摸按键引脚为输入模式 */
    gpio_mode_set(TTP224_KEY_IN1_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, TTP224_KEY_IN1_GPIO_PIN);
    gpio_mode_set(TTP224_KEY_IN2_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, TTP224_KEY_IN2_GPIO_PIN);
    gpio_mode_set(TTP224_KEY_IN3_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, TTP224_KEY_IN3_GPIO_PIN);
    gpio_mode_set(TTP224_KEY_IN4_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, TTP224_KEY_IN4_GPIO_PIN);
}


/******************************************************************
 * 函 数 名 称：Key_IN1_Scan
 * 函 数 说 明：返回触摸键1引脚电平状态
 * 函 数 形 参：无
 * 函 数 返 回：0=未检测到有触摸  1=检测到触摸
 * 作       者：LC
 * 备       注：无
******************************************************************/
char Key_IN1_Scan(void)
{
    return TTP224_KEY_IN1_READ();
}
/******************************************************************
 * 函 数 名 称：Key_IN2_Scan
 * 函 数 说 明：返回触摸键2引脚电平状态
 * 函 数 形 参：无
 * 函 数 返 回：0=未检测到有触摸  1=检测到触摸
 * 作       者：LC
 * 备       注：无
******************************************************************/
char Key_IN2_Scan(void)
{
    return TTP224_KEY_IN2_READ();
}
/******************************************************************
 * 函 数 名 称：Key_IN3_Scan
 * 函 数 说 明：返回触摸键3引脚电平状态
 * 函 数 形 参：无
 * 函 数 返 回：0=未检测到有触摸  1=检测到触摸
 * 作       者：LC
 * 备       注：无
******************************************************************/

char Key_IN3_Scan(void)
{
    return TTP224_KEY_IN3_READ();
}
/******************************************************************
 * 函 数 名 称：Key_IN4_Scan
 * 函 数 说 明：返回触摸键4引脚电平状态
 * 函 数 形 参：无
 * 函 数 返 回：0=未检测到有触摸  1=检测到触摸
 * 作       者：LC
 * 备       注：无
******************************************************************/
char Key_IN4_Scan(void)
{
    return TTP224_KEY_IN4_READ();
}

