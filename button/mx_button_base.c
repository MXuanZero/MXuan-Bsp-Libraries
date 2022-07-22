/**
  ******************************************************************************
  * @file       uart-processor-hal.c
  * @author     MXuan_Zero
  * @brief      采用定时器中断完成检测按键，支持单击、长按、双击（待改进）检测。
  ******************************************************************************
  */
#include "mx_button_base.h"

/**
  * @brief  初始化函数
  * @param  MX_Button       指向 MX_Button 结构的指针
  * @param  _id             按钮id
  * @param  longPressTime   长按时间
  * @param  callback        按键任务执行函数
  * @retval None
  */
void MX_Button_Init(MX_Button *mx_btn, uint8_t _id,
                    uint32_t longPressTime,
                    void (*callback)(MX_Button_Event))
{
    mx_btn->id = _id;
    mx_btn->timer = 0;
    mx_btn->pressTime = 0;
    mx_btn->longPressTime = longPressTime;
    mx_btn->Event_Func = callback;
    mx_btn->lastPinIO = MX_Button_ReadPinIO(_id);

#ifdef DOUBLE_CLICK_BUFFER_TIME
    mx_btn->doubleCountDown = 0;
#endif
}

/**
  * @brief  定时器检测按键
  * @param  mx_btn          指向 MX_UART_DataTypeDef 结构的指针
  * @param  elapsed_time    定时器中断频率，单位ms
  * @retval None
  */
void MX_Button_Tick(MX_Button *mx_btn, uint32_t elapsed_time)
{
    mx_btn->timer += elapsed_time;
#ifdef DOUBLE_CLICK_BUFFER_TIME
    mx_btn->doubleCountDown = mx_btn->doubleCountDown > 0 ? mx_btn->doubleCountDown -elapsed_time : 0;
#endif
    _Bool nowPinIO = MX_Button_ReadPinIO(mx_btn->id);
    if (nowPinIO != mx_btn->lastPinIO)
    {
        mx_btn->lastPinIO = nowPinIO;
        if (nowPinIO)
        {
            //按下
            mx_btn->pressTime = mx_btn->timer;
#ifdef DOUBLE_CLICK_BUFFER_TIME
            //第二次按下执行任务
            if (mx_btn->doubleCountDown != 0)
            {
                mx_btn->Event_Func(DOUBLE_CLICK);
                mx_btn->doubleCountDown = 0;
                return;
            }
            mx_btn->doubleCountDown = DOUBLE_CLICK_BUFFER_TIME;
#endif
            mx_btn->Event_Func(DOWN);
        }
        else
        {
            //抬起
            mx_btn->Event_Func(UP);
            if (mx_btn->timer - mx_btn->pressTime > mx_btn->longPressTime && mx_btn->longPressTime != 0)
                mx_btn->Event_Func(LONG_PRESS);
#ifndef DOUBLE_CLICK_BUFFER_TIME
            else
                mx_btn->Event_Func(CLICK);
#endif
        }
    }
}

/**
  * @brief  按键检测函数
  * @note   默认为 STM32 的按键检测，若使用其他 MCU 需重写此函数。
  * @param  _id     按键id
  * @retval None
  */
__weak _Bool MX_Button_ReadPinIO(uint8_t _id)
{
    switch (_id)
    {
        case 1:
            return HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == GPIO_PIN_SET;
        case 2:
            return HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == GPIO_PIN_SET;
        default:
            return 0;
    }
}


/**
  * @brief  按键任务处理函数模板
  * @param  _event  事件
  * @retval None
  */
//void ButtonX_Event(MX_Button_Event _event)
//{
//    switch (_event)
//    {
//        case UP:
//        {
//            break;
//        }
//        case DOWN:
//        {
//            break;
//        }
//        case CLICK:
//        {
//            break;
//        }
//        case LONG_PRESS:
//        {
//            break;
//        }
//        case DOUBLE_CLICK:
//        {
//            break;
//        }
//    }
//}
