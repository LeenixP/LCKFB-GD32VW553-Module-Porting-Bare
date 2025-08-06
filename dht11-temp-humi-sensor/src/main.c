#include "gd32vw55x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "gd32vw553h_eval.h"

#include "bsp_dht11.h"

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

    /* initialize DHT11 */
    DHT11_Init();

    /* 空读两次 */
    DHT11_Read_Data(NULL, NULL);
    delay_1ms(1000); // 等待DHT11稳定
    DHT11_Read_Data(NULL, NULL);
    delay_1ms(1000); // 等待DHT11稳定

    printf("\r\n= = = = = = = = = = = = DHT11 Demo Start = = = = = = = = = = =\r\n");

    while(1) 
    {
        float temperature = 0.0;
        float humidity = 0.0;

        if(DHT11_Read_Data(&temperature, &humidity))
        {
            printf("\n");
            printf("Temperature = %.2f\r\n", temperature);
            printf("Humidity    = %.2f\r\n", humidity);
        }
        else
        {
            printf("\r\nRead Error!!\r\n");
        }

        delay_ms(1000);
    }
}
