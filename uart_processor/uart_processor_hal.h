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
    例：
    1. 初始化
        MX_UART_DataTypeDef MX_UART1_DATA = {0};
        MX_UART_HandleTypeDef MX_UART1 = {0};
        MX_UART_Processor_Init(&MX_UART1, &huart1, &MX_UART1_DATA, MX_UART1_Task);
    2.接收中断
        MX_UART_RxData(&MX_UART1, huart);
    3.循环
        MX_UART_Handler(&MX_UART1);
    4.添加任务函数
        void MX_UART1_Task(MX_UART_DataTypeDef *mx_uart_data);

  @endverbatim
  ******************************************************************************
  */

#ifndef __MX_UART_PROCESSOR_H__
#define __MX_UART_PROCESSOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <string.h>

#define MX_UART_DELAY           HAL_Delay(1);   //自定义延时函数，默认为HAL_Delay(1);

/*数据最大收发字符数*/
#define MX_UART_TxDATA_MAX      30
#define MX_UART_RxDATA_MAX      30



typedef struct
{
    uint8_t TxData[MX_UART_TxDATA_MAX];    //发送数据
    uint8_t RxData[MX_UART_RxDATA_MAX];    //接收数据
    uint8_t RxFlag;        //接收标志位
    uint8_t RxByte;        //每次接收8位数据
} MX_UART_DataTypeDef;

typedef struct
{
    MX_UART_DataTypeDef *mx_uart_data;
    UART_HandleTypeDef *uart;
    void (*mx_uart_task)(MX_UART_DataTypeDef *);
} MX_UART_HandleTypeDef;

void MX_UART_Processor_Init(MX_UART_HandleTypeDef *mx_uart,
                            UART_HandleTypeDef *uart,
                            MX_UART_DataTypeDef *mx_uart_data,
                            void mx_uart_task(MX_UART_DataTypeDef *));  //初始化

__weak void MX_UART_RxData(MX_UART_HandleTypeDef *mx_uart,UART_HandleTypeDef *uart);   //数据接收
void MX_UART_Handler(MX_UART_HandleTypeDef *mx_uart);                   //数据处理
void MX_UART_RxData_Clear(MX_UART_DataTypeDef *uart_data);              //接收输入清除

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__MX_UART_PROCESSOR_H__
