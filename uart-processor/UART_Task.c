#include "usart.h"
#include "uart-processor.h"
#include "UART_Task.h"

/* Private variables */
MX_UART_HandleTypeDef mx_uart_handle = {0};

/* Private function prototypes */
void UART_Task(MX_UART_DataTypeDef *uart_data);

void UART_Start(void);

void UART_setNewRcvFlag(MX_UART_FIFOTypeDef *uart_fifo);

_Bool UART_checkErrors(void);


/* Public Function */
void UART_Init(void)
{
    MX_UART_Processor_Init(&mx_uart_handle, UART_Start, UART_setNewRcvFlag, UART_checkErrors, UART_Task);
}

void UART_Running(void)
{
    //循环运行
    MX_UART_Running(&mx_uart_handle);
}

/* Private Function */
void UART_Task(MX_UART_DataTypeDef *uart_data)
{
    HAL_UART_Transmit(&huart1, uart_data->RxData, strlen((char *) uart_data->RxData), 50);
    HAL_UART_Transmit(&huart1, (uint8_t *) "\r\n", 2, 50);
}

void UART_Start(void)
{
    HAL_UART_Receive_DMA(&huart1, mx_uart_handle.uart_fifo.data, sizeof(mx_uart_handle.uart_fifo.data));
    mx_uart_handle.uart_fifo.lastRcvFlag = MX_UART_RX_BUFFER_SIZE - huart1.hdmarx->Instance->CNDTR;
    /* 设置状态 */
    mx_uart_handle.uart_fifo.state = MX_UART_OK;
    mx_uart_handle.uart_data.state = MX_UART_OK;
    /* 关闭中断 */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel5_IRQn);
}

void UART_setNewRcvFlag(MX_UART_FIFOTypeDef *uart_fifo)
{
    uart_fifo->newRcvFlag = MX_UART_RX_BUFFER_SIZE - huart1.hdmarx->Instance->CNDTR;
}

_Bool UART_checkErrors(void)
{
    if (huart1.ErrorCode != HAL_UART_ERROR_NONE)
    {
        HAL_UART_AbortReceive(&huart1);
        HAL_UART_Receive_DMA(&huart1, mx_uart_handle.uart_fifo.data, sizeof(mx_uart_handle.uart_fifo.data));
        return false;
    }
    if(mx_uart_handle.uart_fifo.state != MX_UART_OK)
    {
        return false;
    }
    if(mx_uart_handle.uart_data.state != MX_UART_OK)
    {
        return false;
    }
    return true;
}