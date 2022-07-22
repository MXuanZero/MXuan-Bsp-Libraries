# uart_processor

```c
//1.初始化
MX_UART_DataTypeDef MX_UART1_DATA = {0};
MX_UART_HandleTypeDef MX_UART1 = {0};
MX_UART_Processor_Init(&MX_UART1, &huart1,
                       &MX_UART1_DATA, MX_UART1_Task);
//2.接收中断
MX_UART_RxData(&MX_UART1, huart);
//3.循环
MX_UART_Handler(&MX_UART1);
//4.添加任务函数
void MX_UART1_Task(MX_UART_DataTypeDef *mx_uart_data)
{
    
}
```

**注意：**使用前需确定延时函数 `MX_UART_DELAY`，该函数默认为 `HAL_Delay(1)`。
