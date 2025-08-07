/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */
#include "bsp_irdistance.h"
#include "stdio.h"
#include "math.h"


void Module_BSP_Init(void)
{
    /* 使能ADC和GPIO时钟 */
    MODULE_BSP_RCU_ENABLE();

    // 配置ADC时钟为4分频
    adc_clock_config(ADC_ADCCK_PCLK2_DIV4);

    // 配置引脚为模拟浮空输入模式
    gpio_mode_set(BSP_ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, BSP_ADC_GPIO_PIN);

    // 使能扫描模式
    adc_special_function_config(ADC_SCAN_MODE, ENABLE);

    // 数据右对齐
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);

    // ADC设置为12位分辨率
    adc_resolution_config(ADC_RESOLUTION_12B);

    // ADC设置为规则组  一共使用 1 个通道
    adc_channel_length_config(ADC_ROUTINE_CHANNEL, 1);

    // ADC外部触发禁用, 即只能使用软件触发
    adc_external_trigger_config(ADC_ROUTINE_CHANNEL,EXTERNAL_TRIGGER_DISABLE);
    // 使能软件触发
    adc_software_trigger_enable(ADC_ROUTINE_CHANNEL);

    // ADC使能
    adc_enable();
}


/**********************************************************
 * 函 数 名 称：ADC_GET
 * 函 数 功 能：读取一次ADC数据
 * 传 入 参 数：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：LP
**********************************************************/
static int ADC_GET(void)
{
    int gAdcResult = 0;
    int timeOut = 1000;

    // 设置采集通道
    adc_routine_channel_config(0, BSP_ADC_CHANNEL, ADC_SAMPLETIME_14POINT5);
    // 开始软件转换
    adc_software_trigger_enable(ADC_ROUTINE_CHANNEL);

    // 等待ADC总线处理完成
    while(!adc_flag_get(ADC_FLAG_EOC) && timeOut--)
    {
        delay_us(1);
    }

    // 清除ADC采样完成标志位
    adc_flag_clear(ADC_FLAG_EOC);

    if(!timeOut)
    {
        printf("ADC_GET Failed!!!\r\n");
        return 0;
    }

    // 获取通道的转换结果
    gAdcResult = adc_routine_data_read();
    // printf("gAdcResult = %d\r\n",gAdcResult);

    return gAdcResult;
}

/**********************************************************
 * 函 数 名 称：Get_Adc_Value
 * 函 数 功 能：获得某个通道的值
 * 传 入 参 数：Count：采集次数
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：LP
**********************************************************/
int Get_Adc_IRdistance_Value(uint8_t Count)
{
    int gAdcResult = 0;
    uint8_t i = 0;
    for(i = 0; i < Count; i++)
    {
        //获取数据
        gAdcResult += ADC_GET();
    }

    return (gAdcResult / Count);
}

/******************************************************************
 * 函 数 名 称：Get_illume_Percentage_value
 * 函 数 说 明：计算红外测距的测量距离
 * 函 数 形 参：无
 * 函 数 返 回：返回测量距离
 * 作       者：LC
 * 备       注：无
******************************************************************/
double Get_IRdistance_Distance(void)
{
    double adc_new = 0;
    double Distance = 0;

    adc_new = (((double)Get_Adc_IRdistance_Value(10) / 4095.f) * 3.3f);

    // 根据官方代码库链接：https://github.com/zoubworldArduino/ZSharpIR
    // 得到距离换算公式：
    //【GP2Y0A02YK0F：Using MS Excel, we can calculate function (For distance > 15cm) :
    // Distance = 60.374 X POW(Volt , -1.16)】

    Distance = 60.374f * pow(adc_new,-1.16);

    return Distance;
}


