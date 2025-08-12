/*!
    \file    systick.c
    \brief   the systick configuration file

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

volatile static uint32_t delay;

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void)
{
    SysTimer_SetControlValue(SysTimer_MTIMECTL_CMPCLREN_Msk);
    SysTimer_SetCompareValue(SystemCoreClock / 4000);
    __ECLIC_SetTrigIRQ(CLIC_INT_TMR, ECLIC_POSTIVE_EDGE_TRIGGER);
    eclic_irq_enable(CLIC_INT_TMR, 0, 0);
}

/*!
    \brief      delay a time in microseconds
    \param[in]  count: count in microseconds
    \param[out] none
    \retval     none
*/
void delay_1us(uint32_t count)
{
    uint64_t ticks;
    uint64_t told, tnow;
    uint64_t tcnt = 0;
    uint64_t reload = SysTimer_GetCompareValue(); // 获取比较值作为重载值

    /* 获得延时经过的 tick 数 */
    /* 注意：CPUTimer 时钟源是40MHz，是SystemCoreClock的1/4 */
    ticks = (uint64_t)count * ((SystemCoreClock / 4) / 1000000);

    /* 获取当前时间 */
    told = (uint64_t)SysTimer->MTIMER;

    while (1)
    {
        /* 循环获得当前时间，直到达到指定的时间后退出循环 */
        tnow = (uint64_t)SysTimer->MTIMER;

        if (tnow != told)
        {
            if (tnow < told)
            {
                /* 处理计数器回绕 */
                tcnt += (reload - told) + tnow;
            }
            else
            {
                tcnt += tnow - told;
            }

            told = tnow;

            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}


/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count)
{
    delay = count;
    while(0U != delay) {
    }
}

/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    if(0U != delay) {
        delay--;
    }
}
