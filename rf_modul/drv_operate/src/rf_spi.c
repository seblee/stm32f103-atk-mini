/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   SPI配置C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#include "rf_spi.h"
#include "drv_spi.h"
#include "rf_delay.h"

#define DBG_TAG "rf.spi"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#ifndef __USE_SOFT_SPI_INTERFACE__
SPI_HandleTypeDef hspi1;

/** 硬件SPI */
#define SPI_WAIT_TIMEOUT ((uint16_t)0xFFFF)
struct rt_spi_device *spi_dev_cc1101; /* SPI 设备句柄 */
/**
  * @brief :SPI初始化(硬件)
  * @param :无
  * @note  :无
  * @retval:无
  */
void rf_spi_init(void)
{
#define CC1101_SPI_DEVICE_NAME "spi10" /* SPI 设备名称 */

    //	rt_hw_spi_device_attach("spi1", CC1101_SPI_DEVICE_NAME, GPIOA, GPIO_PIN_4);
    //	spi_dev_cc1101 = (struct rt_spi_device *)rt_device_find(CC1101_SPI_DEVICE_NAME);
    //	if (!spi_dev_cc1101)
    //	{
    //		rt_kprintf("spi run failed! can't find %s device!\n", CC1101_SPI_DEVICE_NAME);
    //	}

    //	struct rt_spi_configuration cfg;
    //	cfg.data_width = 8;
    //	cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB | RT_SPI_NO_CS;
    //	cfg.max_hz = 2 * 1000 * 1000;
    //	rt_spi_configure(spi_dev_cc1101, &cfg);

    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }

    rt_pin_mode(SPI_NSS_GPIO_PIN, PIN_MODE_OUTPUT);
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t rf_spi_read_write_byte(uint8_t TxByte)
{
    HAL_StatusTypeDef state;
    uint8_t l_Data = 0;
    state = HAL_SPI_TransmitReceive(&hspi1, (unsigned char *)&TxByte, (uint8_t *)&l_Data, 1, 1000);

    if (state != HAL_OK)
    {
        LOG_I("spi byte error : %d", state);

        hspi1.State = HAL_SPI_STATE_READY;
    }
    else
    {
        // LOG_D("spi byte done");
    }

    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
        ;

    return l_Data; //返回
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void rf_spi_read_write_string(uint8_t *ReadBuffer, uint8_t *WriteBuffer, uint16_t Length)
{
    HAL_StatusTypeDef state;

    spi_set_nss_low(); //拉低片选

    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
        ;
    state = HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)WriteBuffer, (uint8_t *)ReadBuffer, Length, 1000);

    if (state != HAL_OK)
    {
        LOG_I("spi string error : %d", state);

        hspi1.State = HAL_SPI_STATE_READY;
    }
    else
    {
        // LOG_D("spi byte done");
    }

    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
        ;

    spi_set_nss_high(); //拉高片选
}

/** 硬件SPI */
#endif

#ifdef __USE_SOFT_SPI_INTERFACE__

/** 软件SPI */

/**
  * @brief :SPI初始化(软件)
  * @param :无
  * @note  :无
  * @retval:无
  */
void rf_spi_init(void)
{
    GPIO_InitTypeDef SpiGpioInitStructer;

    /** SPI引脚配置 */
    RCC_APB2PeriphClockCmd(SPI_CLK_GPIO_CLK | SPI_MISO_GPIO_CLK | SPI_MOSI_GPIO_CLK | SPI_NSS_GPIO_CLK, ENABLE); //打开端口时钟

    //SCK MOSI NSS配置为推挽输出
    SpiGpioInitStructer.GPIO_Speed = GPIO_Speed_10MHz;
    SpiGpioInitStructer.GPIO_Mode = GPIO_Mode_Out_PP;

    SpiGpioInitStructer.GPIO_Pin = SPI_CLK_GPIO_PIN;
    GPIO_Init(SPI_CLK_GPIO_PORT, &SpiGpioInitStructer);  //初始化SCK
    GPIO_ResetBits(SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN); //初始化状态设置为低

    SpiGpioInitStructer.GPIO_Pin = SPI_MOSI_GPIO_PIN;
    GPIO_Init(SPI_MOSI_GPIO_PORT, &SpiGpioInitStructer); //初始化MOSI
    GPIO_SetBits(SPI_MOSI_GPIO_PORT, SPI_MOSI_GPIO_PIN); //初始化状态设置为高

    SpiGpioInitStructer.GPIO_Pin = SPI_NSS_GPIO_PIN;
    GPIO_Init(SPI_NSS_GPIO_PORT, &SpiGpioInitStructer); //初始化NSS
    GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);  //初始化状态设置为高

    //初始化MISO 上拉输入
    SpiGpioInitStructer.GPIO_Mode = GPIO_Mode_IPU;
    SpiGpioInitStructer.GPIO_Pin = SPI_MISO_GPIO_PIN;
    GPIO_Init(SPI_MISO_GPIO_PORT, &SpiGpioInitStructer);
    GPIO_SetBits(SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN); //初始化状态设置为高
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t rf_spi_read_write_byte(uint8_t TxByte)
{
    uint8_t i = 0, Data = 0;

    spi_set_clk_low();

    for (i = 0; i < 8; i++) //一个字节8byte需要循环8次
    {
        /** 发送 */
        if (0x80 == (TxByte & 0x80))
        {
            spi_set_mosi_hight(); //如果即将要发送的位为 1 则置高IO引脚
        }
        else
        {
            spi_set_mosi_low(); //如果即将要发送的位为 0 则置低IO引脚
        }
        TxByte <<= 1; //数据左移一位，先发送的是最高位

        spi_set_clk_high(); //时钟线置高
        __nop();
        __nop();

        /** 接收 */
        Data <<= 1; //接收数据左移一位，先接收到的是最高位
        if (1 == spi_get_miso())
        {
            Data |= 0x01; //如果接收时IO引脚为高则认为接收到 1
        }

        spi_set_clk_low(); //时钟线置低
        __nop();
        __nop();
    }

    return Data; //返回接收到的字节
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void rf_spi_read_write_string(uint8_t *ReadBuffer, uint8_t *WriteBuffer, uint16_t Length)
{
    spi_set_nss_low(); //片选拉低

    while (Length--)
    {
        *ReadBuffer = rf_spi_read_write_byte(*WriteBuffer); //收发数据
        ReadBuffer++;
        WriteBuffer++; //读写地址加1
    }

    spi_set_nss_high(); //片选拉高
}

/** 软件SPI */
#endif
