/**
  ******************************************************************************
  * @file       uart_processor_hal.c
  * @author     MXuan_Zero
  * @brief      串口接受、处理函数
  * @note       采用串口中断接受处理，波特率为 115200，目前只支持 STM32_HAL 库
  ******************************************************************************
  */

#include "uart_processor_hal.h"

/**
  * @brief  初始化函数
  * @param  mx_uart     指向 MX_UART_DataTypeDef 结构的指针。
  * @param  uart        指向 UART_HandleTypeDef 结构的指针，该结构包含指定UART模块的配置信息。
  * @param  mx_uart_data 指向 MX_UART_DataTypeDef 结构的指针，该结构保存接收数据。
  * @param  mx_uart_task 数据处理函数
  * @retval None
  */
void MX_UART_Processor_Init(MX_UART_HandleTypeDef *mx_uart,
                            UART_HandleTypeDef *uart,
                            MX_UART_DataTypeDef *mx_uart_data,
                            void (*mx_uart_task)(MX_UART_DataTypeDef *))
{
    mx_uart->uart = uart;                   //串口定义
    mx_uart->mx_uart_data = mx_uart_data;   //串口数据接受
    mx_uart->mx_uart_task = mx_uart_task;   //任务函数
    HAL_UART_Receive_IT(mx_uart->uart, &mx_uart->mx_uart_data->RxByte, 1);
}

/**
  * @brief  数据接收函数
  * @note   该函数一般放在串口接收中断中，特殊情况下可重定义该函数。
  * @param  mx_uart     指向 MX_UART_DataTypeDef 结构的指针。
  * @param  uart        指向 UART_HandleTypeDef 结构的指针，该结构包含指定 UART 模块的配置信息。
  * @retval None
  */
__weak void MX_UART_RxData(MX_UART_HandleTypeDef *mx_uart, UART_HandleTypeDef *uart)
{
    if (mx_uart->uart == uart)
    {
        mx_uart->mx_uart_data->RxData[mx_uart->mx_uart_data->RxFlag++] = mx_uart->mx_uart_data->RxByte;
        HAL_UART_Receive_IT(uart, &mx_uart->mx_uart_data->RxByte, 1);
        if (mx_uart->mx_uart_data->RxFlag >= MX_UART_RxDATA_MAX)
        {
            mx_uart->mx_uart_data->RxFlag = 0;
        }
    }
}

/**
  * @brief  数据处理函数
  * @note   该函数一般放在循环中,需根据需求修改 MX_UART_DELAY。
  * @param  mx_uart     指向 MX_UART_DataTypeDef 结构的指针。
  * @retval None
  */
void MX_UART_Handler(MX_UART_HandleTypeDef *mx_uart)
{
    if (mx_uart->mx_uart_data->RxFlag != 0)
    {
        uint8_t temp = mx_uart->mx_uart_data->RxFlag;
        MX_UART_DELAY;//自定义延时函数，默认为HAL_Delay(1);
        if (mx_uart->mx_uart_data->RxFlag == temp)
        {
            mx_uart->mx_uart_task(mx_uart->mx_uart_data);
            MX_UART_RxData_Clear(mx_uart->mx_uart_data);
        }
    }
}

/**
  * @brief  接收数据清理函数
  * @param  uart_data   指向 MX_UART_DataTypeDef 结构的指针，该结构保存接收数据。
  * @retval None
  */
void MX_UART_RxData_Clear(MX_UART_DataTypeDef *uart_data)
{
    memset(uart_data->RxData, 0, 30);
    uart_data->RxFlag = 0;
}
