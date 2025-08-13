/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */

#include "bsp_ws2812.h"

#define WS2812_0_CODE           0xC0    // 0码
#define WS2812_1_CODE           0xFC    // 1码
#define WS2812_RESET_CODE       0x00    // 复位码


static uint8_t   LedsArray[WS2812_MAX * 3];      // 定义颜色数据存储数组
static uint32_t  ledsCount   = WS2812_NUMBERS;   // 定义实际彩灯默认个数
static uint32_t  nbLedsBytes = WS2812_NUMBERS*3; // 定义实际彩灯颜色数据个数

static uint8_t spi_read_write_byte(uint8_t dat)
{
    uint8_t data = 0;

	//等待发送缓冲区为空
	while(RESET == spi_flag_get(SPI_FLAG_TBE) );
	//通过SPI发送一个字节数据
	spi_data_transmit(dat);

	//等待接收缓冲区不空标志
	while(RESET == spi_flag_get(SPI_FLAG_RBNE) );
	data = spi_data_receive();

    return data;
}


/******************************************************************
 * 函 数 名 称：WS2812_WriteData
 * 函 数 说 明：向WS2812写入len长度的字节
 * 函 数 形 参：send_buff数据地址   len字节长度
 * 函 数 返 回：0成功  -1失败
 * 作       者：LCKFB
 * 备       注：1码的时序 = 高电平580ns~1us    再低电平220ns~420ns
 *              0码的时序 = 高电平220ns~380ns  再低电平580ns~1us
******************************************************************/
static int WS2812_WriteData(uint8_t *send_buff, uint32_t len)
{
    int i, bit;

    // 熄灭信号
    spi_read_write_byte(0x00);

    for (i = 0; i < len; i++)
    {
        for (bit = 0; bit < 8; bit++)
        {
            if (send_buff[i] & (0x80 >> bit)) // 当前位为1
            {
                //发送1码
                spi_read_write_byte(WS2812_1_CODE);
            }
            else // 当前位为0
            {
                //发送0码
                spi_read_write_byte(WS2812_0_CODE);
            }
        }
    }
    return 0;
}


/******************************************************************
 * 函 数 名 称：WS2812_RESET
 * 函 数 说 明：复位ws2812
 * 函 数 形 参：无
 * 函 数 返 回：0成功  -1失败
 * 作       者：LCKFB
 * 备       注：低电平280us以上
******************************************************************/
int WS2812_RESET(void)
{
    int i;

    for(i = 0; i < 20; i++)
    {
        //发送复位码
        spi_read_write_byte(WS2812_RESET_CODE);
    }

    return 0;
}


/******************************************************************
 * 函 数 名 称：WS2812_Set_Color
 * 函 数 说 明：设置彩灯颜色
 * 函 数 形 参：LED_NUM控制的第几个灯  Color颜色数据
 * 函 数 返 回：0成功  -1失败
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
int WS2812_Set_Color(uint8_t LED_NUM, uint64_t Color)
{
    if( LED_NUM >= ledsCount )
    {
        return -1;    //to avoid overflow
    }

    LedsArray[LED_NUM * 3]     = 0;
    LedsArray[LED_NUM * 3 + 1] = 0;
    LedsArray[LED_NUM * 3 + 2] = 0;

    LedsArray[LED_NUM * 3]     = (Color>>8)  & 0xff;
    LedsArray[LED_NUM * 3 + 1] = (Color>>16) & 0xff;
    LedsArray[LED_NUM * 3 + 2] = (Color>>0)  & 0xff;

    return 0;
}

/******************************************************************
 * 函 数 名 称：WS2812_Send_Array
 * 函 数 说 明：发送彩灯数据
 * 函 数 形 参：无
 * 函 数 返 回：0成功  -1失败
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
int WS2812_Send_Array(void)
{
    WS2812_RESET();

    delay_ms(10);

    int ret = WS2812_WriteData(LedsArray, nbLedsBytes);
    if(ret != 0)
    {
        return -1;
    }

    return 0;
}

/******************************************************************
 * 函 数 名 称：WS2812_Init
 * 函 数 说 明：初始化WS2812
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：
******************************************************************/
void WS2812_Init(void)
{
	//使能时钟
	Module_RCU_Enable();

	//引脚复用
	gpio_af_set(WS2812_MOSI_GPIO_PORT, WS2812_MOSI_GPIO_AF, WS2812_MOSI_GPIO_PIN);
	//引脚模式
	gpio_mode_set(WS2812_MOSI_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, WS2812_MOSI_GPIO_PIN);
	//输出模式
	gpio_output_options_set(WS2812_MOSI_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, WS2812_MOSI_GPIO_PIN);

	//SPI参数定义结构体
	spi_parameter_struct spi_init_struct;
	/* 配置 SPI 参数 */
	spi_init_struct.trans_mode             = SPI_TRANSMODE_FULLDUPLEX;  // 传输模式全双工
	spi_init_struct.device_mode            = SPI_MASTER;   // 配置为主机
	spi_init_struct.frame_size             = SPI_FRAMESIZE_8BIT; // 8位数据
	spi_init_struct.clock_polarity_phase   = SPI_CK_PL_HIGH_PH_2EDGE;
	spi_init_struct.nss                    = SPI_NSS_SOFT;  // 软件cs
	spi_init_struct.prescale               = SPI_PSC_16;//16分频,频率=160MHz/16=10MHz
	spi_init_struct.endian                 = SPI_ENDIAN_MSB;//高位在前

	//将参数填入SPI
	spi_init(&spi_init_struct);

	/* 使能 SPI */
	spi_enable();
}

