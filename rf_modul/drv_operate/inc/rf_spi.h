/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   SPI配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#ifndef __RF_SPI_H__
#define __RF_SPI_H__

#include <rtthread.h>
#include <rthw.h>
#include "board.h"

//SPI引脚定义
#define SPI_CLK_GPIO_PORT GPIOA
#define SPI_CLK_GPIO_CLK RCC_APB2Periph_GPIOA
#define SPI_CLK_GPIO_PIN GPIO_Pin_5

#define SPI_MISO_GPIO_PORT GPIOA
#define SPI_MISO_GPIO_CLK RCC_APB2Periph_GPIOA
#define SPI_MISO_GPIO_PIN GPIO_Pin_6

#define SPI_MOSI_GPIO_PORT GPIOA
#define SPI_MOSI_GPIO_CLK RCC_APB2Periph_GPIOA
#define SPI_MOSI_GPIO_PIN GPIO_Pin_7

#define SPI_NSS_GPIO_PIN GET_PIN(A, 4)

#define spi_set_nss_high() rt_pin_write(SPI_NSS_GPIO_PIN, PIN_HIGH) //片选置高
#define spi_set_nss_low() rt_pin_write(SPI_NSS_GPIO_PIN, PIN_LOW)   //片选置低

#ifdef __USE_SOFT_SPI_INTERFACE__ /** 只有使用软件SPI才需要的封装 */

#define spi_set_clk_high() SPI_CLK_GPIO_PORT->ODR |= SPI_CLK_GPIO_PIN                         //时钟置高
#define spi_set_clk_low() SPI_CLK_GPIO_PORT->ODR &= (uint32_t)(~((uint32_t)SPI_CLK_GPIO_PIN)) //时钟置低

#define spi_set_mosi_hight() SPI_MOSI_GPIO_PORT->ODR |= SPI_MOSI_GPIO_PIN                        //发送脚置高
#define spi_set_mosi_low() SPI_MOSI_GPIO_PORT->ODR &= (uint32_t)(~((uint32_t)SPI_MOSI_GPIO_PIN)) //发送脚置低

#define spi_get_miso() ((SPI_MISO_GPIO_PORT->IDR & (uint32_t)SPI_MISO_GPIO_PIN) != SPI_MISO_GPIO_PIN) ? 0 : 1 // 若相应输入位为低则得到0，相应输入位为高则得到1

void rf_spi_init(void);
uint8_t rf_spi_read_write_byte(uint8_t TxByte);
void rf_spi_read_write_string(uint8_t *ReadBuffer, uint8_t *WriteBuffer, uint16_t Length);

#else                                    /** 只有使用硬件SPI时会使用 */

//SPI接口定义
#define SPI_PORT SPI1                    //SPI接口
#define SPI_PORT_CLK RCC_APB2Periph_SPI1 //SPI时钟

void rf_spi_init(void);
uint8_t rf_spi_read_write_byte(uint8_t TxByte);
void rf_spi_read_write_string(uint8_t *ReadBuffer, uint8_t *WriteBuffer, uint16_t Length);

#endif

#endif
