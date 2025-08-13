/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#include "bsp_rock.h"
#include "stdio.h"

/**********************************************************
 * 函 数 名 称：ADC_GET
 * 函 数 功 能：读取一次ADC数据
 * 传 入 参 数：CHx:读取通道是X还是Y
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：LP
**********************************************************/
static int ADC_GET(uint8_t CHx)
{
    int gAdcResult = 0;
    int timeOut = 200;

    if(CHx == 0){ // x通道

        // 设置采集通道
        adc_routine_channel_config(0, BSP_ADC_X_CHANNEL, ADC_SAMPLETIME_14POINT5);

    }else if(CHx == 1){ // y通道

        // 设置采集通道
        adc_routine_channel_config(0, BSP_ADC_Y_CHANNEL, ADC_SAMPLETIME_14POINT5);

    }else{
        printf("\r\nCHx Error!!\r\n");
        return 1;
    }

    // 开始软件转换
    adc_software_trigger_enable(ADC_ROUTINE_CHANNEL);

    // 等待ADC总线处理完成
    while(!adc_flag_get(ADC_FLAG_EOC) && timeOut--)
    {
        delay_1us(1);
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
 * 函 数 名 称：Get_Adc_Joystick_Value
 * 函 数 说 明：对保存的数据进行平均值计算后输出
 * 函 数 形 参：CHx 那个通道值
 * 函 数 返 回：对应扫描的ADC值
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
int Get_Adc_Joystick_Value(uint8_t CHx)
{
    int Data = 0;
    int i;

    for(i = 0; i < SAMPLES; i++)
    {
        Data += ADC_GET(CHx);

        delay_ms(10);
    }

    Data = Data / SAMPLES;

    return Data;
}

/******************************************************************
 * 函 数 名 称：Get_MQ2_Percentage_value
 * 函 数 说 明：读取摇杆值，并且返回百分比
 * 函 数 形 参：0=读取摇杆左右值，1=读取摇杆上下值
 * 函 数 返 回：返回百分比
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
int Get_Joystick_Percentage_value(uint8_t dir)
{
    int adc_new = 0;
    int Percentage_value = 0;

    if( dir == 0 )
    {
        adc_new = Get_Adc_Joystick_Value(0); // 通道0：X的值
    }
    else if( dir == 1 )
    {
        adc_new = Get_Adc_Joystick_Value(1); // 通道1：Y的值
    }
    else
    {
        printf("\nCH Error!!\r\n");
    }

    Percentage_value = (uint16_t)(((float)adc_new/4095.0f) * 100.f);
    return Percentage_value;
}

/******************************************************************
 * 函 数 名 称：Get_SW_state
 * 函 数 说 明：读取摇杆是否有按下
 * 函 数 形 参：无
 * 函 数 返 回：0摇杆被按下   1摇杆没有按下
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
uint8_t Get_SW_state(void)
{
    //如果被按下
    if( GET_SW == 0 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/******************************************************************
 * 函 数 名 称：Joystick_Init
 * 函 数 说 明：初始化摇杆
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
void Joystick_Init(void)
{
    /* 使能ADC和GPIO时钟 */
    Module_RCU_Enable();

    /* 配置摇杆按键为输入模式 */
    gpio_mode_set(GPIO_SW_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_SW_PIN);

    // 配置ADC时钟为4分频
    adc_clock_config(ADC_ADCCK_PCLK2_DIV4);

    // 配置引脚为模拟浮空输入模式
    gpio_mode_set(BSP_ADC_GPIO_X_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, BSP_ADC_GPIO_X_PIN);
    gpio_mode_set(BSP_ADC_GPIO_Y_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, BSP_ADC_GPIO_Y_PIN);

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

