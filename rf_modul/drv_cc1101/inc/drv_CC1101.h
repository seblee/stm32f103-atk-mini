/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   CC1101配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */

#ifndef __DRV_CC1101_H__
#define __DRV_CC1101_H__

#include "rf_spi.h"
#include "drv_CC1101_Reg.h"
#if defined(__CC_ARM)
#pragma anon_unions
#endif
#define PA_TABLE                                        \
    {                                                   \
        0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    }

/** CC1101硬件接口定义 */

#define CC1101_GDO0_GPIO_PIN GET_PIN(C, 4)
#define CC1101_GDO2_GPIO_PIN GET_PIN(C, 0)
#define CC1101_CSN_GPIO_PIN SPI_NSS_GPIO_PIN

/** 口线操作函数定义 */
#define CC1101_SET_CSN_HIGH() spi_set_nss_high()
#define CC1101_SET_CSN_LOW() spi_set_nss_low()

#define CC1101_GET_GDO0_STATUS() rt_pin_read(CC1101_GDO0_GPIO_PIN) //GDO0状态
#define CC1101_GET_GDO2_STATUS() rt_pin_read(CC1101_GDO2_GPIO_PIN) //GDO2状态

/** 枚举量定义 */
typedef enum
{
    IDLE_MODE,
    TX_MODE,
    RX_MODE
} CC1101_ModeType;

typedef enum
{
    BROAD_ALL,
    BROAD_NO,
    BROAD_0,
    BROAD_0AND255
} CC1101_AddrModeType;

typedef enum
{
    BROADCAST,
    ADDRESS_CHECK
} CC1101_TxDataModeType;

typedef struct
{
    CC1101_ModeType radioMode;

} CC1101_Modul_t;

//      --------------------------------------------------------------------------------
//      |          |            |                                                      |
//      | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (available bytes in the RX FIFO |
//      |          |            |                                                      |
//      --------------------------------------------------------------------------------
typedef enum
{
    STATE_Idle,
    STATE_RX,
    STATE_TX,
    STATE_FSTXON,
    STATE_CALIBRATE,
    STATE_SETTLING,
    STATE_RXFIFO_OVERFLOW,
    STATE_TX_FIFO_UNDERFLOW,
} CC1101_state;

typedef union {
    unsigned char BYTE;
    struct
    {
        unsigned char FIFO_BYTES_AVAILABLE : 4; // Bit 0:3;
        unsigned char STATE : 3;                // Bit 4:6;
        unsigned char CHIP_RDY : 1;             // Bit7;
    };
} CC1101_Status_t;

extern CC1101_Modul_t g_Modul_state;

void CC1101_Write_Cmd(uint8_t Command);
void CC1101_Write_Reg(uint8_t Addr, uint8_t WriteValue);
void CC1101_Write_Multi_Reg(uint8_t Addr, uint8_t *pWriteBuff, uint8_t WriteSize);
uint8_t CC1101_Read_Reg(uint8_t Addr);
void CC1101_Read_Multi_Reg(uint8_t Addr, uint8_t *pReadBuff, uint8_t ReadSize);
uint8_t CC1101_Read_Status(uint8_t Addr);
void CC1101_Set_Mode(CC1101_ModeType Mode);
void CC1101_Set_RX_Mode(void);
void CC1101_Set_Idle_Mode(void);
void C1101_WOR_Init(void);
void CC1101_Set_Address(uint8_t Address, CC1101_AddrModeType AddressMode);
void CC1101_Set_Sync(uint16_t Sync);
void CC1101_Clear_TxBuffer(void);
void CC1101_Clear_RxBuffer(void);
void CC1101_Tx_Packet(uint8_t *pTxBuff, uint8_t TxSize, CC1101_TxDataModeType DataMode);
uint8_t CC1101_Get_RxCounter(void);
uint8_t CC1101_Rx_Packet(uint8_t *RxBuff);
void CC1101_Reset(void);
void CC1101_Init(void);
CC1101_Status_t CC1101_GetRxStatus(void);

#endif
