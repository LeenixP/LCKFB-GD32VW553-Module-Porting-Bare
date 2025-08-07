/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 文档网站：wiki.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 嘉立创社区问答：https://www.jlc-bbs.com/lckfb
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 */
#include "bsp_as608.h"
#include "stdio.h"
#include "string.h"

volatile unsigned char FPM10A_RECEICE_BUFFER[32];
unsigned int finger_id = 0;

const unsigned char FPM10A_Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//口令验证
const unsigned char FPM10A_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头
const unsigned char FPM10A_Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //获得指纹图像
const unsigned char FPM10A_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数
const unsigned char FPM10A_Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //搜索指纹搜索范围0 - 999,使用BUFFER1中的特征码搜索
const unsigned char FPM10A_Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //搜索0-9号指纹
const unsigned char FPM10A_Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //将图像放入到BUFFER1
const unsigned char FPM10A_Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //将图像放入到BUFFER2
const unsigned char FPM10A_Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //将BUFFER1跟BUFFER2合成特征模版
const unsigned char FPM10A_Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版
volatile unsigned char  FPM10A_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置

uint8_t  module_recv_buff[SERIAL_RECEIVE_LENGTH]; // module串口 接收缓冲区
uint16_t module_recv_length;                      // module串口 接收数据长度
uint8_t  module_recv_flag;                        // module串口 接收完成标志位

uint8_t  debug_recv_buff[SERIAL_RECEIVE_LENGTH]={0}; // 接收缓冲区
uint16_t debug_recv_length = 0;   // 接收数据长度
uint8_t  debug_recv_flag = 0;  // 接收完成标志位

/************************************************
函数名称 ： AS608_Init
功    能 ： 初始化AS608模块
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void AS608_Init(void)
{
    rcu_periph_clock_enable(BSP_UART_TX_RCU); // 开启端口时钟
    rcu_periph_clock_enable(BSP_UART_RX_RCU); // 开启端口时钟
    rcu_periph_clock_enable(BSP_AS608_WAK_RCU); // 开启端口时钟 
    rcu_periph_clock_enable(BSP_UART_RCU); // 开启串口时钟

    /* 配置AS608唤醒引脚为输入模式 */
    gpio_mode_set(BSP_AS608_WAK_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, BSP_AS608_WAK_PIN);

    /* connect port to USARTx_Tx */
    gpio_af_set(BSP_UART_TX_PORT, BSP_UART_TX_AF, BSP_UART_TX_PIN);

    /* connect port to USARTx_Rx */
    gpio_af_set(BSP_UART_RX_PORT, BSP_UART_RX_AF, BSP_UART_RX_PIN);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(BSP_UART_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_UART_TX_PIN);
    gpio_output_options_set(BSP_UART_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, BSP_UART_TX_PIN);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(BSP_UART_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_UART_RX_PIN);
    gpio_output_options_set(BSP_UART_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, BSP_UART_RX_PIN);

    /* USART configure */
    usart_deinit(BSP_UART);
    usart_baudrate_set(BSP_UART, 57600U);
    usart_parity_config(BSP_UART, USART_PM_NONE);
    usart_word_length_set(BSP_UART,USART_WL_8BIT);
    usart_stop_bit_set(BSP_UART,USART_STB_1BIT);
    usart_receive_config(BSP_UART, USART_RECEIVE_ENABLE);
    usart_transmit_config(BSP_UART, USART_TRANSMIT_ENABLE);
    usart_interrupt_enable(BSP_UART, USART_INT_RBNE);
    eclic_irq_enable(BSP_UART_IRQ, 2, 2);
    usart_enable(BSP_UART);

    printf("\r\nAS608 Init OK\r\n");
}


/************************************************
函数名称 ： moduleSerial_send_byte
功    能 ： 串口发送一个字节
参    数 ： ucch：要发送的字节
返 回 值 ：
作    者 ： LC
*************************************************/
void moduleSerial_send_byte(uint8_t ucch)
{
    //发送单个字符
    usart_data_transmit(BSP_UART, (uint8_t)ucch);
    while(RESET == usart_flag_get(BSP_UART, USART_FLAG_TBE)); // 等待发送数据缓冲区标志置位
}

void UsartSendString(uint8_t *ucstr)
{
    while(ucstr && *ucstr)  // 地址为空或者值为空跳出
    {
        moduleSerial_send_byte(*ucstr++);
    }
}

/************************************************
函数名称 ： moduleSerial_receive_clear
功    能 ： 清除串口接收的全部数据
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void moduleSerial_receive_clear(void)
{
    unsigned int i = 0;
    for( i = 0; i < SERIAL_RECEIVE_LENGTH; i++ )
    {
        module_recv_buff[ i ] = 0;
    }
    module_recv_length = 0;
	module_recv_flag = 0;
}

/******************************************************************
 * 函 数 名 称：get_as608_touch
 * 函 数 说 明：获取是否有手指触摸识别区
 * 函 数 形 参：无
 * 函 数 返 回：0没有触摸    1有触摸
 * 作       者：LC
 * 备       注：无
******************************************************************/
char get_as608_touch(void)
{
	if( TOUCH_IN == SET )//触摸为1
	{
		// printf("Touch - OK\r\n");
		return 1;
	}
	else
	{
		// printf("Touch - NO\r\n");
        return 0;
	}
}

/******************************************************************
 * 函 数 名 称：FPM10A_Cmd_Send_Pack_Head
 * 函 数 说 明：发送包头
 * 函 数 形 参：无
 * 函 数 返 回：wu
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Cmd_Send_Pack_Head(void)
{
	int i;
	for(i=0;i<6;i++) //包头
	{
		moduleSerial_send_byte(FPM10A_Pack_Head[i]);
	}
}
/******************************************************************
 * 函 数 名 称：FPM10A_Cmd_Check
 * 函 数 说 明：发送指令
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Cmd_Check(void)
{
	int i=0;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

	for(i=0;i<10;i++)
	{
		moduleSerial_send_byte(FPM10A_Get_Device[i]);
	}
}
/******************************************************************
 * 函 数 名 称：FPM10A_Receive_Data
 * 函 数 说 明：接收反馈数据缓冲
 * 函 数 形 参：ucLength 接收长度
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Receive_Data(unsigned char ucLength)
{
	unsigned char i = 0;
	unsigned int timeout = 1000;//超时时间,单位Ms
	//等待数据接收完毕
	while(module_recv_flag==0 && timeout > 0 )
	{
		delay_ms(1);
		timeout--;
	}
    delay_ms(500); // 等待数据接收完成

	if( module_recv_flag == 1 )
	{
		module_recv_flag = 0;
		for (i=0;i<ucLength;i++)
		{
			FPM10A_RECEICE_BUFFER[i] = module_recv_buff[i];
		}
		moduleSerial_receive_clear();
	}
	else
	{
	  //Error, no data received
	}

}
/******************************************************************
 * 函 数 名 称：FPM10A_Cmd_Get_Img
 * 函 数 说 明：获得指纹图像命令
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Cmd_Get_Img(void)
{
    unsigned char i;
    FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头
    for(i=0;i<6;i++) //发送命令 0x1d
	{
		moduleSerial_send_byte(FPM10A_Get_Img[i]);
	}
}
/******************************************************************
 * 函 数 名 称：FINGERPRINT_Cmd_Img_To_Buffer1
 * 函 数 说 明：将图像转换成特征码存放在Buffer1中
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

	for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
	{
		moduleSerial_send_byte(FPM10A_Img_To_Buffer1[i]);
	}
}
/******************************************************************
 * 函 数 名 称：FINGERPRINT_Cmd_Img_To_Buffer2
 * 函 数 说 明：将图像转换成特征码存放在Buffer2中
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
	unsigned char i;
	for(i=0;i<6;i++)    //发送包头
	{
		moduleSerial_send_byte(FPM10A_Pack_Head[i]);
	}
	for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
	{
		moduleSerial_send_byte(FPM10A_Img_To_Buffer2[i]);
	}
}
/******************************************************************
 * 函 数 名 称：FPM10A_Cmd_Search_Finger
 * 函 数 说 明：搜索全部用户999枚
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Cmd_Search_Finger(void)
{
    unsigned char i;
    FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

    for(i=0;i<11;i++)
    {
        moduleSerial_send_byte(FPM10A_Search[i]);
    }
}
/******************************************************************
 * 函 数 名 称：FPM10A_Cmd_Reg_Model
 * 函 数 说 明：将BUFFER1跟BUFFER2合成特征模版
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Cmd_Reg_Model(void)
{
    unsigned char i;
    FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

    for(i=0;i<6;i++)
    {
        moduleSerial_send_byte(FPM10A_Reg_Model[i]);
    }
}
/******************************************************************
 * 函 数 名 称：FINGERPRINT_Cmd_Delete_All_Model
 * 函 数 说 明：删除指纹模块里的所有指纹模版
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
	unsigned char i;

	for(i=0;i<6;i++) //包头
	{
		moduleSerial_send_byte(FPM10A_Pack_Head[i]);
	}

	for(i=0;i<6;i++) //命令合并指纹模版
	{
		moduleSerial_send_byte(FPM10A_Delete_All_Model[i]);
	}
}
/******************************************************************
 * 函 数 名 称：FPM10A_Cmd_Save_Finger
 * 函 数 说 明：保存指纹
 * 函 数 形 参：保存指纹的位置（ID号）
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Cmd_Save_Finger( unsigned int storeID )
{
    unsigned long temp = 0;
    unsigned char i;
    FPM10A_Save_Finger[5] =(storeID&0xFF00)>>8;
    FPM10A_Save_Finger[6] = (storeID&0x00FF);

    for(i=0;i<7;i++)   //计算校验和
    {
        temp = temp + FPM10A_Save_Finger[i];
    }

    FPM10A_Save_Finger[7]=(temp & 0x00FF00) >> 8; //存放校验数据
    FPM10A_Save_Finger[8]= temp & 0x0000FF;
    FPM10A_Cmd_Send_Pack_Head(); //发送通信协议包头

    for(i=0;i<9;i++)
    {
        //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
        moduleSerial_send_byte(FPM10A_Save_Finger[i]);
    }
}




/************************************************
函数名称 ： debugSerial_clear_buff
功    能 ： 清除串口接收的全部数据
参    数 ： 无
返 回 值 ： 无
作    者 ： LC
*************************************************/
void debugSerial_clear_buff()
{
    int i;
	for(i = 0; i < SERIAL_RECEIVE_LENGTH; i++)
	{
		debug_recv_buff[i] = 0;
	}

	debug_recv_length = 0;
	debug_recv_flag = 0;
}

/******************************************************************
 * 函 数 名 称：key_scanf
 * 函 数 说 明：按键功能  确定-取消
 * 函 数 形 参：
 * 函 数 返 回：0=未动作  1=确定  2=取消
 * 作       者：LC
 * 备       注：当前是使用串口来模拟按键，如果你有按键请自行修改
 *              修改要求：按下确定键时返回1；按下取消键时，返回2。
******************************************************************/
char key_scanf(void)
{

    /***************    你的代码    ***************/
    if(strstr( (const char*)debug_recv_buff, "Yes") != NULL )
    {
        // printf("key_scanf-YES\r\n");

		debugSerial_clear_buff();

        return 1;//返回 确定键被按下
    }
    if(strstr( (const char*)debug_recv_buff, "No") != NULL )
    {
        // printf("key_scanf-NO\r\n");

		debugSerial_clear_buff();

        return 2;//返回 取消键被按下
    }
     /***************    你的代码    ***************/

    return 0;
}


/******************************************************************
 * 函 数 名 称：FPM10A_Add_Fingerprint
 * 函 数 说 明：添加指纹
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Add_Fingerprint(void)
{
//        unsigned char id_show[3]={0,0,0};
        unsigned char key_num= key_scanf();
        finger_id=0;

        printf("Do you want to add fingerprints? [Yes/No]\r\n");

        while( key_num != 2 )//按返回键直接回到主菜单
        {
			key_num= key_scanf();

			 //按确认键开始录入指纹信息
			 if( key_num == 1 )
			 {
				printf("start add\r\n");

				while( key_num != 2 )//按下返回键退出录入返回fingerID调整状态
				{
                    // printf("\r\nADD finger [1]\r\n");
					key_num= key_scanf();
					FPM10A_Cmd_Get_Img(); //获得指纹图像
					FPM10A_Receive_Data(12);
					//判断接收到的确认码,等于0指纹获取成功
					if(FPM10A_RECEICE_BUFFER[9]==0)
					{
                        // printf("\r\nADD finger [2]\r\n");
						delay_ms(100);
						FINGERPRINT_Cmd_Img_To_Buffer1();
						FPM10A_Receive_Data(12);
						delay_ms(1000);
						while( key_num != 2 )
						{
                            // printf("\r\nADD finger [3]\r\n");
							key_num= key_scanf();
							FPM10A_Cmd_Get_Img(); //获得指纹图像
							FPM10A_Receive_Data(12);
							//判断接收到的确认码,等于0指纹获取成功
							if(FPM10A_RECEICE_BUFFER[9]==0)
							{
								delay_ms(200);
								printf("successfully added, ID = %d\r\n",finger_id);
								FINGERPRINT_Cmd_Img_To_Buffer2();
								FPM10A_Receive_Data(12);
								FPM10A_Cmd_Reg_Model();//转换成特征码
								FPM10A_Receive_Data(12);
								//保存指纹
								FPM10A_Cmd_Save_Finger(finger_id);
								FPM10A_Receive_Data(12);
								delay_ms(1000);
								finger_id=finger_id+1;
								break;
							}
						}

						break;
					}
				}
			}
        }
}
/******************************************************************
 * 函 数 名 称：FPM10A_Find_Fingerprint
 * 函 数 说 明：搜索指纹
 * 函 数 形 参：无
 * 函 数 返 回：指纹ID号
 * 作       者：LC
 * 备       注：255：未查到  其他：查找到了
******************************************************************/
unsigned int FPM10A_Find_Fingerprint(void)
{
	unsigned int find_fingerid = 255;

    // printf("Please put your finger in\r\n");

    if( get_as608_touch() == 1 )//有手指触摸识别区
    {
        FPM10A_Cmd_Get_Img(); //获得指纹图像
        FPM10A_Receive_Data(12);
        //判断接收到的确认码,等于0指纹获取成功
        if(FPM10A_RECEICE_BUFFER[9]==0)
        {
            delay_ms(100);
            FINGERPRINT_Cmd_Img_To_Buffer1();
            FPM10A_Receive_Data(12);
            FPM10A_Cmd_Search_Finger();
            FPM10A_Receive_Data(16);
            if(FPM10A_RECEICE_BUFFER[9] == 0) //搜索成功
            {
                //拼接指纹ID数
                find_fingerid = FPM10A_RECEICE_BUFFER[10]*256 + FPM10A_RECEICE_BUFFER[11];
                printf("ID = %d\r\n",find_fingerid);
                delay_ms(500);
            }
            else //没有找到
            {
                printf("not found\r\n");
            }
        }
    }
    return find_fingerid;
}
/******************************************************************
 * 函 数 名 称：FPM10A_Delete_All_Fingerprint
 * 函 数 说 明：删除所有存贮的指纹库
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void FPM10A_Delete_All_Fingerprint(void)
{
	unsigned char key_num=0;
	printf("Whether to delete fingerprint ?  [Yes/No]\r\n");

	do{
		key_num = key_scanf();
		if(key_num == 1 )//点击确定键
		{
			printf("deleting\r\n");
			delay_ms(300);
			FINGERPRINT_Cmd_Delete_All_Model();
			FPM10A_Receive_Data(12);
			printf("Have all been cleared\r\n");
			break;
		}
		if( module_recv_flag == 1 )
		{
			module_recv_flag = 0;
			printf("rev = %s\r\n", module_recv_buff);
		}
	}while( key_num != 2 );//没有点击取消键，则继续循环
}

/******************************************************************
 * 函 数 名 称：Device_Check
 * 函 数 说 明：模块检查
 * 函 数 形 参：无
 * 函 数 返 回：0未检测到模块或者模块异常  1检测到模块并且通信成功
 * 作       者：LC
 * 备       注：返回0时要注意接线是否正确、串口配置是否可用
******************************************************************/
char Device_Check(void)
{
    FPM10A_RECEICE_BUFFER[9]=1; //串口数组第九位可判断是否通信正常

    FPM10A_Cmd_Check();    //单片机向指纹模块发送校对命令
    FPM10A_Receive_Data(12);     //将串口接收到的数据转存

    if(FPM10A_RECEICE_BUFFER[9] == 0)  //判断数据低第9位是否接收到0
    {
        return 1;
    }
    return 0;
}

/*!
    \brief     这个函数处理USART RBNE中断请求和空闲中断请求
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void)
{
    // 接收缓冲区不为空
    if(usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE) != RESET)
    {
        /* 清除接收中断标志位 */
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);
        /* 把接收到的数据放到缓冲区中 */
        debug_recv_buff[debug_recv_length] = usart_data_receive(USART0);

        // printf("%c", debug_recv_buff[debug_recv_length]); // 打印接收到的数据到终端

        /* 限制接收长度防止数据溢出 */
        debug_recv_length=( debug_recv_length + 1 ) % 255;

        //判断空闲中断是否开启，如果没有开启 （ USART_CTL0 的 第4位是否为0，为0说明当前没有开启空闲中断 ）
        if(  (USART_CTL0(USART0) & (1<<4) ) == 0  )
        {
            /* 使能IDLE线检测中断 */
            usart_interrupt_enable(USART0, USART_INT_IDLE);
            /* 清除空闲中断标志位 */
            usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);
        }
    }

     // 检测到空闲中断
    if(usart_interrupt_flag_get(USART0,USART_INT_FLAG_IDLE) != RESET)
    {
        /* 清除空闲中断标志位 */
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);
        /* 数据结尾加上字符串结束符 */
        debug_recv_buff[debug_recv_length] = '\0';
        /* 接收完成标志位 */
        debug_recv_flag = 1;
        /* 关闭空闲中断 */
        usart_interrupt_disable(USART0, USART_INT_IDLE);
    }
}

/*!
    \brief     这个函数处理UART RBNE中断请求和空闲中断请求
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UART1_IRQHandler(void)
{
    // 接收缓冲区不为空
    if(usart_interrupt_flag_get(BSP_UART,USART_INT_FLAG_RBNE) != RESET)
    {
        /* 清除接收中断标志位 */
        usart_interrupt_flag_clear(BSP_UART, USART_INT_FLAG_RBNE);
        /* 把接收到的数据放到缓冲区中 */
        module_recv_buff[module_recv_length] = usart_data_receive(BSP_UART);

        // printf("%c", module_recv_buff[module_recv_length]); // 打印接收到的数据到终端

        /* 限制接收长度防止数据溢出 */
        module_recv_length=( module_recv_length + 1 ) % SERIAL_RECEIVE_LENGTH;

        /* 数据结尾加上字符串结束符 */
        module_recv_buff[module_recv_length] = '\0';
        /* 接收完成标志位 */
        module_recv_flag = 1;

        //判断空闲中断是否开启，如果没有开启 （ USART_CTL0 的 第4位是否为0，为0说明当前没有开启空闲中断 ）
        if(  (USART_CTL0(BSP_UART) & (1<<4) ) == 0  )
        {
            /* 使能IDLE线检测中断 */
            usart_interrupt_enable(BSP_UART, USART_INT_IDLE);
            /* 清除空闲中断标志位 */
            usart_interrupt_flag_clear(BSP_UART, USART_INT_FLAG_IDLE);
        }
    }

     // 检测到空闲中断
    if(usart_interrupt_flag_get(BSP_UART,USART_INT_FLAG_IDLE) != RESET)
    {
        /* 清除空闲中断标志位 */
        usart_interrupt_flag_clear(BSP_UART, USART_INT_FLAG_IDLE);
        /* 数据结尾加上字符串结束符 */
        module_recv_buff[module_recv_length] = '\0';
        /* 接收完成标志位 */
        module_recv_flag = 1;
        /* 关闭空闲中断 */
        usart_interrupt_disable(BSP_UART, USART_INT_IDLE);
    }
}
