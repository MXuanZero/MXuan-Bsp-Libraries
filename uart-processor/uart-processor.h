/**
  ******************************************************************************
  * @file       uart-processor.h
  * @author     MXuan_Zero
  * @brief      串口接受、处理函数
  * @note       采用串口中断接受处理，波特率为 115200，目前只支持 STM32_HAL 库
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================

    参照 UART_Task.c 创建开始函数、FIFO前指针更新函数、错误检查、处理函数、任务处理函数、初始
    化函数。调用 MX_UART_Processor_Init() 初始化，将 MX_UART_Running() 放入循环中既可。
    例：
    1.开始函数
        void UART_Start(void)
    2.FIFO前指针更新函数
        void UART_setNewRcvFlag(MX_UART_FIFOTypeDef *uart_fifo)
    3.错误检查、处理函数
        _Bool UART_checkErrors(void)
    4.任务处理函数
        void UART_Start(void)
    5.初始化
        MX_UART_HandleTypeDef mx_uart_handle = {0};
        MX_UART_Processor_Init(&mx_uart_handle, UART_Start,
                        UART_setNewRcvFlag, UART_checkErrors, UART_Task);
    6.循环
    MX_UART_Running(&mx_uart_handle);
    7.可能需要修改默认延时函数 MX_UART_DELAY
  @endverbatim
  ******************************************************************************
  */

#ifndef __MX_UART_PROCESSOR_H__
#define __MX_UART_PROCESSOR_H__
/* START */

/* includes */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "usart.h"

/* define */
#define MX_UART_DELAY()                     HAL_Delay(1);   //自定义延时函数，默认为HAL_Delay(1);
#define MX_UART_TX_BUFFER_SIZE              32
#define MX_UART_RX_BUFFER_SIZE              32
#define MX_RX_MAX_LINE_LENGTH               64

/* typedef */
typedef enum
{
    MX_UART_OK,
    MX_UART_Buffer_Overflow
} MX_UART_STATE;

typedef struct
{
    uint8_t data[MX_UART_RX_BUFFER_SIZE]; // 接收环形队列
    uint8_t newRcvFlag;     //接收标志位
    uint8_t lastRcvFlag;    //接收标志位
    uint8_t state;
} MX_UART_FIFOTypeDef;

typedef struct
{
    uint8_t TxData[MX_RX_MAX_LINE_LENGTH + 1];    //发送数据
    uint8_t RxData[MX_RX_MAX_LINE_LENGTH + 1];    //接收数据
    uint8_t temp;
    uint8_t RxFlag;
    uint8_t state;
    _Bool delayFlag;        //是否需要延时
} MX_UART_DataTypeDef;

typedef struct
{
    MX_UART_DataTypeDef uart_data;                  //数据
    MX_UART_FIFOTypeDef uart_fifo;                  //环形接收队列

    _Bool (*checkErrors)(void);                     //检查错误
    void (*setRxFlag)(MX_UART_FIFOTypeDef *);       //设置标志位
    void (*protocol)(MX_UART_DataTypeDef *);        //任务函数
} MX_UART_HandleTypeDef;

/* Public function */
MX_UART_STATE MX_UART_Processor_Init(MX_UART_HandleTypeDef *uart_handle,
                                     void(*startFunc)(void),
                                     void (*setRxFlag)(MX_UART_FIFOTypeDef *),
                                     _Bool (*checkErrors)(void),
                                     void (*protocol)(MX_UART_DataTypeDef *));

void MX_UART_Running(MX_UART_HandleTypeDef *mx_uart_handle);

#endif //__MX_UART_PROCESSOR_H__
