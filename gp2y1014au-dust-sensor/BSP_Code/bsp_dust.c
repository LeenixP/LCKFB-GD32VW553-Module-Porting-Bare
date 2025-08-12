/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */
#include "bsp_dust.h"
#include "stdio.h"


/**********************************************************
 * 函 数 名 称：GP2Y1014AU_Init
 * 函 数 功 能：初始化GP2Y1014AU传感器
 * 传 入 参 数：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：LP
**********************************************************/
void GP2Y1014AU_Init(void)
{
    /* 使能ADC和GPIO时钟 */
    MODULE_BSP_RCU_ENABLE();

    // 配置LED引脚为输出模式
    gpio_mode_set(BSP_LED_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, BSP_LED_GPIO_PIN);
    gpio_output_options_set(BSP_LED_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, BSP_LED_GPIO_PIN);

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


/******************************************************************
 * 函 数 名 称：Get_ADC_Value
 * 函 数 说 明：对ADC值进行平均值计算后输出
 * 函 数 形 参：num采集次数
 * 函 数 返 回：对应扫描的ADC值
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
int Get_ADC_Value(void)
{
    int Data = 0;
    int i;

    for(i = 0; i < SAMPLES; i++)
    {
        Data += ADC_GET();

        delay_ms(2);
    }

    Data = Data / SAMPLES;

    return Data;
}

int Filter(int m)
{
    static int flag_first = 0, _buff[10], sum;
    const int _buff_max = 10;
    int i;

    if (flag_first == 0)
    {
        flag_first = 1;
        for (i = 0, sum = 0; i < _buff_max; i++)
        {
            _buff[i] = m;
            sum += _buff[i];
        }
        return m;
    }
    else
    {
        sum -= _buff[0];
        for (i = 0; i < (_buff_max - 1); i++)
        {
            _buff[i] = _buff[i + 1];
        }
        _buff[9] = m;
        sum += _buff[9];

        i = sum / 10.0;
        return i;
    }
}
/******************************************************************
 * 函 数 名 称：Read_dust_concentration
 * 函 数 说 明：读取粉尘浓度
 * 函 数 形 参：粉尘浓度
 * 函 数 返 回：0成功 其他失败
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
char Read_dust_concentration(float *d_dat)
{
    int value = 0;

    GP2Y1014AU_VO(0);

    delay_us(280);
    value = Get_ADC_Value();
    delay_us(40);

    GP2Y1014AU_VO(1);

    delay_us(9680);

    value = Filter(value);
    *d_dat = 0.17f * value - 0.1f; //转换公式

    return 0;
}


