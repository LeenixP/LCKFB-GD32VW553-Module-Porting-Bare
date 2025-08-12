/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */


#include "bsp_humanir.h"


/******************************************************************
 * 函 数 名 称：Get_HumanIR
 * 函 数 说 明：获取人体红外输出引脚的电平状态
 * 函 数 形 参：无
 * 函 数 返 回：0=感应到人体红外    1=未感应到人体红外
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
char Get_HumanIR(void)
{
    return HunmanIR_GPIO_READ();
}


/******************************************************************
 * 函 数 名 称：HumanIR_Init
 * 函 数 说 明：初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
void HumanIR_Init(void)
{
    HunmanIR_GPIO_RCU_ENABLE();

    gpio_mode_set(HunmanIR_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, HunmanIR_GPIO_PIN);
}