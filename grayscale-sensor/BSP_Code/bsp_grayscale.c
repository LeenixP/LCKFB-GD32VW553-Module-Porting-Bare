/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#include "bsp_grayscale.h"
#include "stdio.h"

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
/******************************************************************
 * 函 数 名 称：Get_Adc_GRAYSCALE_Value
 * 函 数 说 明：对保存的数据进行平均值计算后输出
 * 函 数 形 参：
 * 函 数 返 回：对应扫描的ADC值
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
int Get_Adc_GRAYSCALE_Value(void)
{
    int Data = 0;
    int i;

    for(i = 0; i < SAMPLES; i++)
    {
        Data += ADC_GET();

        delay_ms(5);
    }

    Data = Data / SAMPLES;

    return Data;
}

/******************************************************************
 * 函 数 名 称：Get_Grayscale_Percentage_value
 * 函 数 说 明：读取灰度传感器的值，并且返回百分比
 * 函 数 形 参：无
 * 函 数 返 回：返回百分比
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
uint8_t Get_Grayscale_Percentage_Value(void)
{
    int adc_max = 4095;
    int adc_new = 0;
    uint8_t Percentage_value = 0;

    adc_new = Get_Adc_GRAYSCALE_Value();
    Percentage_value = ((float)adc_new/(float)adc_max) * 100.f;
    return Percentage_value;
}

/******************************************************************
 * 函 数 名 称：Init_Grayscale_Sensor
 * 函 数 说 明：初始化灰度传感器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
void Init_Grayscale_Sensor(void)
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
