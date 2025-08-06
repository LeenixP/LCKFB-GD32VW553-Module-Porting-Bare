/*!
    \file    main.c
    \brief   led spark with systick, USART print and key example

    \version 2025-01-16, V1.4.0, firmware for GD32VW55x
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32vw55x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "gd32vw553h_eval.h"

#include "oled.h"
#include "bmp.h"

/*!
    \brief      toggle the led every 500ms
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_spark(void)
{
    static __IO uint32_t timingdelaylocal = 0U;

    if(timingdelaylocal) {

        if(timingdelaylocal < 500U) {
            gd_eval_led_on(LED1);
        } else {
            gd_eval_led_off(LED1);
        }

        timingdelaylocal--;
    } else {
        timingdelaylocal = 1000U;
    }
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
#ifdef __FIRMWARE_VERSION_DEFINE
    uint32_t fw_ver = 0;
#endif /* __FIRMWARE_VERSION_DEFINE */

    /* configure systick */
    systick_config();
    eclic_priority_group_set(ECLIC_PRIGROUP_LEVEL3_PRIO1);
    /* initilize the LEDs, USART and key */
    gd_eval_led_init(LED1);
    gd_eval_com_init(EVAL_COM0);
    gd_eval_key_init(KEY_TAMPER_WAKEUP, KEY_MODE_GPIO);

#ifdef __FIRMWARE_VERSION_DEFINE
    fw_ver = gd32vw55x_firmware_version_get();
    printf("\r\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\r\n\n");
    printf("\r\n=== Welcome to use the LC-GD32VW553-HMQ6 development board ====\r\n\n");
    printf("\r\n======================= www.lckfb.com =========================\r\n\n");
    printf("\r\n======================= wiki.lckfb.com ========================\r\n\n");
    printf("\r\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\r\n");
    /* print firmware version */
    printf("\r\nGD32VW55X series firmware version: V%d.%d.%d", (uint8_t)(fw_ver >> 24), (uint8_t)(fw_ver >> 16), (uint8_t)(fw_ver >> 8));
#endif /* __FIRMWARE_VERSION_DEFINE */

    /* print out the clock frequency of system, AHB, APB1 and APB2 */
    printf("\r\nCK_SYS is %d\r\n", rcu_clock_freq_get(CK_SYS));
    printf("\r\nCK_AHB is %d\r\n", rcu_clock_freq_get(CK_AHB));
    printf("\r\nCK_APB1 is %d\r\n", rcu_clock_freq_get(CK_APB1));
    printf("\r\nCK_APB2 is %d\r\n", rcu_clock_freq_get(CK_APB2));

    u8 t=' ';
    OLED_Init();
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示

    while(1)
    {
        OLED_ShowPicture(0,0,128,64,BMP1,1);
        OLED_Refresh();
        delay_ms(500);
        OLED_Clear();
        OLED_ShowChinese(0,0,0,16,1);//中
        OLED_ShowChinese(18,0,1,16,1);//景
        OLED_ShowChinese(36,0,2,16,1);//园
        OLED_ShowChinese(54,0,3,16,1);//电
        OLED_ShowChinese(72,0,4,16,1);//子
        OLED_ShowChinese(90,0,5,16,1);//技
        OLED_ShowChinese(108,0,6,16,1);//术
        OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
        OLED_ShowString(20,32,"2014/05/01",16,1);
        OLED_ShowString(0,48,"ASCII:",16,1);
        OLED_ShowString(63,48,"CODE:",16,1);
        OLED_ShowChar(48,48,t,16,1);//显示ASCII字符
        t++;
        if(t>'~')t=' ';
        OLED_ShowNum(103,48,t,3,16,1);
        OLED_Refresh();
        delay_ms(500);
        OLED_Clear();
        OLED_ShowChinese(0,0,0,16,1);  //16*16 中
        OLED_ShowChinese(16,0,0,24,1); //24*24 中
        OLED_ShowChinese(24,20,0,32,1);//32*32 中
        OLED_ShowChinese(64,0,0,64,1); //64*64 中
        OLED_Refresh();
        delay_ms(500);
        OLED_Clear();
        OLED_ShowString(0,0,"ABC",8,1);//6*8 “ABC”
        OLED_ShowString(0,8,"ABC",12,1);//6*12 “ABC”
        OLED_ShowString(0,20,"ABC",16,1);//8*16 “ABC”
        OLED_ShowString(0,36,"ABC",24,1);//12*24 “ABC”
        OLED_Refresh();
        delay_ms(500);
        //OLED_ScrollDisplay(11,4,1);

        printf("\r\nrun [while end]\r\n");
    }
}
