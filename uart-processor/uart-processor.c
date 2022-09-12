/**
  ******************************************************************************
  * @file       uart-processor.c
  * @author     MXuan_Zero
  * @brief      串口DMA接收数据处理
  ******************************************************************************
  */
#include "uart-processor.h"

/* Private function prototypes */
static void MX_UART_FIFO2RxBuffer(MX_UART_DataTypeDef *uart_data, const uint8_t *buffer, size_t len);

static void MX_UART_RxData_Clear(MX_UART_DataTypeDef *uart_data);

/* Public Function */
MX_UART_STATE MX_UART_Processor_Init(MX_UART_HandleTypeDef *uart_handle,
                                     void(*startFunc)(void),
                                     void (*setRxFlag)(MX_UART_FIFOTypeDef *),
                                     _Bool (*checkErrors)(void),
                                     void (*protocol)(MX_UART_DataTypeDef *))
{
    uart_handle->checkErrors = checkErrors;
    uart_handle->setRxFlag = setRxFlag;
    uart_handle->protocol = protocol;
    startFunc();
    return MX_UART_OK;
}

void MX_UART_Running(MX_UART_HandleTypeDef *mx_uart_handle)
{
    mx_uart_handle->checkErrors();  // 检查是否出现错误
    mx_uart_handle->setRxFlag(&mx_uart_handle->uart_fifo);
    /* 赋值的原因是让代码变简洁一些 */
    const uint8_t *const newRcvFlag = &mx_uart_handle->uart_fifo.newRcvFlag;
    uint8_t *const lastRcvFlag = &mx_uart_handle->uart_fifo.lastRcvFlag;
    uint8_t *buffer = mx_uart_handle->uart_fifo.data;

    /* FIFO 环形队列 */
    if (*newRcvFlag < *lastRcvFlag)    //溢出
    {
        MX_UART_FIFO2RxBuffer(&mx_uart_handle->uart_data, buffer + (*lastRcvFlag),
                              MX_UART_RX_BUFFER_SIZE - (*lastRcvFlag));
        *lastRcvFlag = 0;
    }
    if (*newRcvFlag > *lastRcvFlag)     //正常
    {
        MX_UART_FIFO2RxBuffer(&mx_uart_handle->uart_data, buffer + (*lastRcvFlag), *newRcvFlag - *lastRcvFlag);
        *lastRcvFlag = *newRcvFlag;
    }

    MX_UART_DELAY();
    /* 任务处理 */
    if (mx_uart_handle->uart_data.RxFlag != 0)
    {
        if (mx_uart_handle->uart_data.delayFlag == 0)
        {
            /* 直接返回，相当于延时一个MX_UART_DELAY */
            mx_uart_handle->uart_data.temp = mx_uart_handle->uart_data.RxFlag;
            mx_uart_handle->uart_data.delayFlag = true;
            return;
        }
        else
        {
            mx_uart_handle->uart_data.delayFlag = false;
        }

        if (mx_uart_handle->uart_data.RxFlag == mx_uart_handle->uart_data.temp)
        {
            mx_uart_handle->protocol(&mx_uart_handle->uart_data);
            MX_UART_RxData_Clear(&mx_uart_handle->uart_data);
        }
    }
}

/* Private Function */
/**
  * @brief  转移环形队列中的数据
  * @param  uart_data   指向 MX_UART_DataTypeDef 结构的指针，该结构保存接收数据。
  * @param  buffer      本次环形队列接收的数据
  * @param  len         数据长度
  * @retval None
  */
static void MX_UART_FIFO2RxBuffer(MX_UART_DataTypeDef *uart_data, const uint8_t *buffer, size_t len)
{
    while (len--)
    {
        // if the line becomes too long, reset buffer and wait for the next line
        if (uart_data->RxFlag >= MX_RX_MAX_LINE_LENGTH)
        {
            uart_data->state = MX_UART_Buffer_Overflow;
            uart_data->RxFlag = 0;
        }
        uart_data->RxData[uart_data->RxFlag++] = *(buffer++);
    }
}

/**
  * @brief  缓存区数据清理函数
  * @param  uart_data   指向 MX_UART_DataTypeDef 结构的指针，该结构保存接收数据。
  * @retval None
  */
static void MX_UART_RxData_Clear(MX_UART_DataTypeDef *uart_data)
{
    memset(uart_data->RxData, 0, MX_RX_MAX_LINE_LENGTH + 1);
    uart_data->RxFlag = 0;
}
