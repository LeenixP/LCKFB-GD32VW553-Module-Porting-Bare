/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#include "bsp_sr04.h"

volatile uint32_t msHcCount = 0; // ms计数

float Distance_DAT = 0;
uint8_t SR04_Flag = 0; // SR04测距标志位

/******************************************************************
 * 函 数 名 称：SR04_Init
 * 函 数 说 明：初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
void SR04_Init(void)
{
    SR04_Module_CLK_ENABLE(); // 使能时钟

    // trig引脚配置
    gpio_mode_set(SR04_Trig_GPIO_PORT, 
                    GPIO_MODE_OUTPUT, 
                    GPIO_PUPD_NONE, 
                    SR04_Trig_GPIO_PIN);
    gpio_output_options_set(SR04_Trig_GPIO_PORT, 
                    GPIO_OTYPE_PP, 
                    GPIO_OSPEED_MAX, 
                    SR04_Trig_GPIO_PIN);
    SR04_TRIG(0); // trig拉低信号，默认状态

    // echo引脚配置
    gpio_mode_set(SR04_Echo_GPIO_PORT, 
                    GPIO_MODE_INPUT, 
                    GPIO_PUPD_NONE, 
                    SR04_Echo_GPIO_PIN);

    // 外部中断配置
    eclic_priority_group_set(ECLIC_PRIGROUP_LEVEL2_PRIO2);
    eclic_irq_enable(SR04_Echo_EXTI_IRQn, 1, 1);
    syscfg_exti_line_config(SR04_Echo_EXTI_PORT_SOURCE, SR04_Echo_EXTI_PIN_SOURCE);
    exti_init(SR04_Echo_EXTI_LINE, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    exti_interrupt_enable(SR04_Echo_EXTI_LINE);
    exti_interrupt_flag_clear(SR04_Echo_EXTI_LINE);

    // 定时器配置
    timer_parameter_struct timer_initpara; // 定义定时器结构体

    /* CK_TIMERx = 2 x CK_APB1  = 2x80M = 160MHZ */
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL2);// 配置定时器时钟
    timer_deinit(SR04_Timer); // 复位定时器

    /* 配置定时器参数 */
    timer_initpara.prescaler = 160 -1; //  时钟预分频值 0-65535  psc_clk = CK_TIMER / pre
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;        // 边缘对齐
    timer_initpara.counterdirection = TIMER_COUNTER_UP;     // 向上计数
    timer_initpara.period = 1000  - 1;                      // 周期
    /* 在输入捕获的时候使用  数字滤波器使用的采样频率之间的分频比例 */
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;        // 分频因子
    /* 只有高级定时器才有 配置为x，就重复x+1次进入中断 */
    timer_initpara.repetitioncounter = 0;                   // 重复计数器 0-255
    timer_init(SR04_Timer, &timer_initpara);                // 初始化定时器

    eclic_irq_enable(SR04_Timer_IRQn,2,2); // 设置中断优先级为 2,2断

    /* 使能中断 */
    timer_interrupt_enable(SR04_Timer, TIMER_INT_UP); // 使能更新事件中断

    msHcCount = 0;
    Distance_DAT = 0.0f; // 清零距离
}

/******************************************************************
 * 函 数 名 称：Open_Timer
 * 函 数 说 明：打开定时器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
void Open_Timer(void)
{
    msHcCount = 0;
    timer_counter_value_config(SR04_Timer, 0);   // 重载定时器计数
    timer_enable(SR04_Timer); /* 使能定时器 */
}

/******************************************************************
 * 函 数 名 称：Get_TIMER_Count
 * 函 数 说 明：获取定时器定时时间
 * 函 数 形 参：无
 * 函 数 返 回：数据
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
uint32_t Get_TIMER_Count(void)
{
    uint32_t time  = (msHcCount * 1000) + timer_counter_read(SR04_Timer); // 得到us
    timer_counter_value_config(SR04_Timer, 0);   // 重载定时器计数

    delay_1ms(10);

    return time ;
}

/******************************************************************
 * 函 数 名 称：Close_Timer
 * 函 数 说 明：关闭定时器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
void Close_Timer(void)
{
    timer_disable(SR04_Timer);;     // 关闭定时器
}
/******************************************************************
 * 函 数 名 称：SR04_GetLength
 * 函 数 说 明：获取测量距离
 * 函 数 形 参：无
 * 函 数 返 回：测量距离
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
float SR04_GetLength(void)
{
        /*测5次数据计算一次平均值*/
        float length = 0;
        float t = 0;
        float sum = 0;
        int i = 0;
        int j = 0;
        float distances[5] = {0}; // 用于存储测量结果

        while(i != 5)
        {
            SR04_TRIG(1);//trig拉高信号，发出高电平
            delay_1us(20);//持续时间超过10us
            SR04_TRIG(0);//trig拉低信号，发出低电平

            /*Echo发出信号 等待回响信号*/
            /*输入方波后，模块会自动发射8个40KHz的声波，与此同时回波引脚（echo）端的电平会由0变为1；
            （此时应该启动定时器计时）；当超声波返回被模块接收到时，回波引 脚端的电平会由1变为0；
            （此时应该停止定时器计数），定时器记下的这个时间即为
                    超声波由发射到返回的总时长；*/

            SR04_Flag = 0; // 清除标志位
            while(SR04_Flag == 1);

            /*获取Echo高电平时间时间*/
            t = Get_TIMER_Count();
            distances[i++] = (float)t/58;//单位时cm
        }

        // 排序以便去除最高值和最低值
        for (i = 0,j = 0; i < 5 - 1; i++)
        {
            for (j = i + 1; j < 5; j++)
            {
                if (distances[i] > distances[j])
                {
                    float temp = distances[i];
                    distances[i] = distances[j];
                    distances[j] = temp;
                }
            }
        }
        // 计算去掉最高值和最低值后的平均值
        for (i = 1; i < 5 - 1; i++)
        {
            sum += distances[i];
        }

        Distance_DAT = sum / 3; // 返回中间值的平均值

        return Distance_DAT;
}


// 外部中断服务函数
void SR04_Echo_EXTI_IRQHandler(void)
{
    if(exti_interrupt_flag_get(SR04_Echo_EXTI_LINE) == SET)
    {
        if(gpio_input_bit_get(SR04_Echo_GPIO_PORT,SR04_Echo_GPIO_PIN) == SET)
        {
            SR04_Flag = 0;
            Open_Timer();   //打开定时器
        }
        else // RESET
        {
            Close_Timer();   // 关闭定时器
            SR04_Flag = 1;
        }
        exti_interrupt_flag_clear(SR04_Echo_EXTI_LINE);
    }
}


void SR04_Timer_IRQHandler(void)
{
    if(timer_interrupt_flag_get(SR04_Timer, TIMER_INT_UP) == SET)
    {
        msHcCount++; // 每次中断计数加1
        timer_interrupt_flag_clear(SR04_Timer, TIMER_INT_UP); // 清除中断标志
    }
}

