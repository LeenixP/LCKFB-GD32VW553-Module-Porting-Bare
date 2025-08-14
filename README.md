# LCKFB-GD32VW553-Module-Porting-Bare


模块移植手册【裸机】代码 - 适用于立创推出的开发板：【立创·GD32VW553开发板】

## GD32官方IDE版本说明

> [!note] IDE版本说明
>
> 下载地址：https://www.gd32mcu.com/cn/download?kw=GD32+Embedded+Builder&lan=cn
> 
> IDE包名称: `GD32EmbeddedBuilder_1.5.3.31964.7z`
> 
> 版    本：`1.5.3.31964`
> 
> 发布日期：`2025-07-18`

## 模块代码与文档目录


> [!IMPORTANT]【1.47寸彩屏】
>
> **代码**：`1-47-color-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/1-47-color-screen

> [!IMPORTANT]【1.69寸彩屏】
>
> **代码**：`1-69-color-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/1-69-color-screen

> [!IMPORTANT]【0.96寸SPI单色屏】
>
> **代码**：`0-96-single-spi-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/0-96-single-spi-screen

> [!IMPORTANT]【0.96寸IIC单色屏】
>
> **代码**：`0-96-iic-single-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/0-96-iic-single-screen

> [!IMPORTANT]【0.91寸IIC单色屏幕】
>
> **代码**：`0-91-iic-single-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/0-91-iic-single-screen

> [!IMPORTANT]【1.28寸圆屏LCD彩屏】
>
> **代码**：`1-28-round-color-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/1-28-round-color-screen

> [!IMPORTANT]【1.3寸单色OLED显示屏】
>
> **代码**：`1-3-single-oled-screen` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/screen/1-3-single-oled-screen

> [!IMPORTANT]【DHT11温湿度传感器】
>
> **代码**：`dht11-temp-humi-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/dht11-temp-humi-sensor

> [!IMPORTANT]【光敏电阻光照传感器】
>
> **代码**：`photoresistance-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/photoresistance-sensor

> [!IMPORTANT]【红外测距传感器】
>
> **代码**：`Infrared-distance-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/Infrared-distance-sensor

> [!IMPORTANT]【MQ-2烟雾检测传感器】
>
> **代码**：`mq-2-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-2-sensor

> [!IMPORTANT]【红外循迹传感器】
>
> **代码**：`Infrared-tracking-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/Infrared-tracking-sensor

> [!IMPORTANT]【指纹识别传感器】
>
> **代码**：`fingerprint-recognition-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/fingerprint-recognition-sensor

> [!IMPORTANT]【TTP224触摸传感器】
>
> **代码**：`ttp224-touch-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/ttp224-touch-sensor

> [!IMPORTANT]【ADS1115多路模数转换器】
>
> **代码**：`ads1115-multichannel-a-to-d-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/ads1115-multichannel-a-to-d-sensor

> [!IMPORTANT]【SR04超声波测距传感器】
>
> **代码**：`sr04-ultrasonic-ranging-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/sr04-ultrasonic-ranging-sensor

> [!IMPORTANT]【SHT30温湿度传感器】
>
> **代码**：`sht30-temp-humi-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/sht30-temp-humi-sensor

> [!IMPORTANT]【MLX90614测温传感器】
>
> **代码**：`mlx90614-non-contact-temp-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mlx90614-non-contact-temp-sensor

> [!IMPORTANT]【MPU6050六轴传感器】
>
> **代码**：`mpu6050-six-axis-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mpu6050-six-axis-sensor

> [!IMPORTANT]【DS18B20温度传感器】
>
> **代码**：`ds18b20-temp-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/ds18b20-temp-sensor

> [!IMPORTANT]【火焰传感器】
>
> **代码**：`flame-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/flame-sensor

> [!IMPORTANT]【雨滴传感器】
>
> **代码**：`rain-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/rain-sensor

> [!IMPORTANT]【US-016超声波测距传感器】
>
> **代码**：`us-016-ultrasonic-ranging-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/us-016-ultrasonic-ranging-sensor

> [!IMPORTANT]【HX711称重传感器】
>
> **代码**：`hx711-weighing-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/hx711-weighing-sensor

> [!IMPORTANT]【微波多普勒无线雷达传感器】
>
> **代码**：`microwave-doppler-radar-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/microwave-doppler-radar-sensor

> [!IMPORTANT]【AHT10温湿度传感器】
>
> **代码**：`aht10-temp-humi-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/aht10-temp-humi-sensor

> [!IMPORTANT]【MS5611气压传感器】
>
> **代码**：`ms5611-pressure-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/ms5611-pressure-sensor

> [!IMPORTANT]【BMP180气压传感器】
>
> **代码**：`bmp180-pressure-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/bmp180-pressure-sensor

> [!IMPORTANT]【SHT20温湿度传感器】
>
> **代码**：`sht20-temp-humi-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/sht20-temp-humi-sensor

> [!IMPORTANT]【人体红外传感器】
>
> **代码**：`human-body-infrared-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/human-body-infrared-sensor

> [!IMPORTANT]【MS1100气体传感器】
>
> **代码**：`ms1100-gas-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/ms1100-gas-sensor

> [!IMPORTANT]【SGP30气体传感器】
>
> **代码**：`sgp30-gas-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/sgp30-gas-sensor

> [!IMPORTANT]【S12SD紫外线传感器】
>
> **代码**：`s12sd-uv-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/s12sd-uv-sensor

> [!IMPORTANT]【BH1750光照强度传感器】
>
> **代码**：`bh1750-light-intensity-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/bh1750-light-intensity-sensor

> [!IMPORTANT]【TCS34725颜色识别传感器】
>
> **代码**：`tcs34725-color-recognition-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/tcs34725-color-recognition-sensor

> [!IMPORTANT]【MQ-3酒精检测传感器】
>
> **代码**：`mq-3-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-3-sensor

> [!IMPORTANT]【MQ-4甲烷检测传感器】
>
> **代码**：`mq-4-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-4-sensor

> [!IMPORTANT]【MQ-5液化气检测传感器】
>
> **代码**：`mq-5-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-5-sensor

> [!IMPORTANT]【MQ-6丙烷检测传感器】
>
> **代码**：`mq-6-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-6-sensor

> [!IMPORTANT]【MQ-7一氧化碳检测传感器】
>
> **代码**：`mq-7-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-7-sensor

> [!IMPORTANT]【MQ-8氢气检测传感器】
>
> **代码**：`mq-8-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-8-sensor

> [!IMPORTANT]【MQ-9可燃气体检测传感器】
>
> **代码**：`mq-9-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-9-sensor

> [!IMPORTANT]【MQ-135空气质量传感器】
>
> **代码**：`mq-135-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/mq-135-sensor

> [!IMPORTANT]【灰度传感器】
>
> **代码**：`grayscale-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/grayscale-sensor

> [!IMPORTANT]【GP2Y1014AU粉尘传感器】
>
> **代码**：`gp2y1014au-dust-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/gp2y1014au-dust-sensor

> [!IMPORTANT]【土壤湿度传感器】
>
> **代码**：`soil-moisture-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/soil-moisture-sensor

> [!IMPORTANT]【AGS10有害气体传感器】
>
> **代码**：`ags10-harmful-gas-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/ags10-harmful-gas-sensor

> [!IMPORTANT]【JY61P三维姿态测量传感器】
>
> **代码**：`jy61p-measurement-sensor` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/sensor/jy61p-measurement-sensor

> [!IMPORTANT]【继电器模块】
>
> **代码**：`relay-module` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/control/relay-module

> [!IMPORTANT]【WS2812彩灯】
>
> **代码**：`ws2812-color-rgb-led` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/control/ws2812-color-rgb-led

> [!IMPORTANT]【SG90舵机】
>
> **代码**：`sg90-steering-engine` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/control/sg90-steering-engine

> [!IMPORTANT]【双轴按键摇杆模块】
>
> **代码**：`two-axis-keystroke-rocker-module` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/control/two-axis-keystroke-rocker-module

> [!IMPORTANT]【AT24C02-EEPROM存储器】
>
> **代码**：`at24c02-eeprom-memory` 文件夹
>
> **文档链接**: https://wiki.lckfb.com/zh-hans/gd32vw553/module/control/at24c02-eeprom-memory

