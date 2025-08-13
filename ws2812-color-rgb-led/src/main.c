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

#include "bsp_ws2812.h"

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

    /* initialize WS2812 */
    WS2812_Init();
    printf("\r\nWS2812 initialized successfully!\r\n");

    int i;
    int while_count = 1;
    uint32_t buff[4] = {WS2812_RED, WS2812_GREEN, WS2812_BLUE, WS2812_WHITE};

    for (i = 0; i < 4; i++)
    {
        WS2812_Set_Color(0, buff[i]);
        WS2812_Set_Color(1, buff[i]);
        WS2812_Set_Color(2, buff[i]);
        WS2812_Set_Color(3, buff[i]);
        WS2812_Set_Color(4, buff[i]);
        WS2812_Set_Color(5, buff[i]);
        WS2812_Set_Color(6, buff[i]);
        WS2812_Set_Color(7, buff[i]);

        WS2812_Send_Array(); // 立即发送更新
        delay_1ms(1000);
    }

    delay_1ms(1000);

    i = 0;

    while(1) 
    {
        WS2812_Set_Color((i + 0) % 8, buff[0]);
        WS2812_Set_Color((i + 1) % 8, buff[1]);
        WS2812_Set_Color((i + 2) % 8, buff[2]);
        WS2812_Set_Color((i + 3) % 8, buff[3]);
        WS2812_Send_Array(); // 发送更新

        // 清除其他LED
        WS2812_Set_Color((i + 4) % 8, WS2812_BLACK);
        WS2812_Set_Color((i + 5) % 8, WS2812_BLACK);
        WS2812_Set_Color((i + 6) % 8, WS2812_BLACK);
        WS2812_Set_Color((i + 7) % 8, WS2812_BLACK);
        WS2812_Send_Array(); // 发送更新

        i++;
        while_count++;

        delay_1ms(100);

        // 清除
        if(while_count >= 100)
        {
            while_count = 1;
            i = 0;
        }
    }
}
