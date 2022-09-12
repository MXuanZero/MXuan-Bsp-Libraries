# uart-processor

参照 UART_Task.c 创建开始函数、FIFO前指针更新函数、错误检查、处理函数、任务处理函数、初始
化函数。调用 MX_UART_Processor_Init() 初始化，将 MX_UART_Running() 放入循环中既可。

### 例程

1. 开始函数
    ```c
    void UART_Start(void)
    ```
2. FIFO前指针更新函数
    ```C
    void UART_setNewRcvFlag(MX_UART_FIFOTypeDef *uart_fifo)
    ```
3. 错误检查、处理函数
    ```C
    _Bool UART_checkErrors(void)
    ```
4. 任务处理函数
    ```C
    void UART_Start(void)
    ```
5. 初始化
    ```C
    MX_UART_HandleTypeDef mx_uart_handle = {0};
    MX_UART_Processor_Init(&mx_uart_handle, UART_Start,UART_setNewRcvFlag, UART_checkErrors, UART_Task);
    ```
6. 循环调用
    ```c
    MX_UART_Running(&mx_uart_handle);
    ```

**注意：**使用前需确定延时函数 `MX_UART_DELAY`，该函数默认为 `HAL_Delay(1)`。

