/**
  ******************************************************************************
  * @file       mx_button_base.h
  * @author     MXuan_Zero
  * @brief      采用定时器中断完成检测按键，支持单击、长按、双击（待改进）检测。
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    例：
    1.初始化
        MX_Button button1 = {0};
        MX_Button_Init(&button1, 1, 1000, Button1_Event, MX_Button_Hardware_Init);
        MX_Button_Hardware_Init 硬件初始化函数
    2.按键检测
        需重写此函数，mx_button_base.c 的最后有按键按键检测函数模板。
        _Bool MX_Button_ReadPinIO(uint8_t _id)
    3.定时器
        将该函数放入定时器中即可，10为定时中断频率，单位ms。
        MX_Button_Tick(&button1, 10);
    4.添加任务函数
        需自行添加执行任务，mx_button_base.c 的最后有按键任务处理函数模板。
        void Button1_Event(MX_Button_Event _event)
        {

        }
    5.双击
        双击并未完善，请勿使用。取消 DOUBLE_CLICK_BUFFER_TIME 的注释开启双击检测。
  @endverbatim
  ******************************************************************************
  */
#ifndef __MX_BUTTON_BASE_H__
#define __MX_BUTTON_BASE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//按键ID
#define BUTTON  0

//END


// 双击并未完善，请勿使用。取消 DOUBLE_CLICK_BUFFER_TIME 的注释开启双击检测。
// CLICK 为松手事件，尽量不要与 DOUBLE_CLICK 同时使用。
// #define DOUBLE_CLICK_BUFFER_TIME     650


typedef enum
{
    UP,             //抬起
    DOWN,           //按下
    CLICK,          //单击
    LONG_PRESS,     //长按
    DOUBLE_CLICK    //双击
} MX_Button_Event;

typedef struct
{
    uint32_t timer;
    uint32_t pressTime;
    uint32_t longPressTime;
#ifdef DOUBLE_CLICK_BUFFER_TIME
    uint16_t doubleCountDown;
#endif
    uint8_t id;
    _Bool lastPinIO;
    void (*Event_Func)(MX_Button_Event);  //按键任务
} MX_Button;

void MX_Button_Init(MX_Button *mx_btn,
                    uint8_t _id,
                    uint32_t longPressTime,
                    void (*_callback)(MX_Button_Event),
                    void (*button_hardware_init)(MX_Button *,uint8_t)
);
void MX_Button_Hardware_Init(MX_Button *mx_btn,uint8_t _id);
void MX_Button_Tick(MX_Button *mx_btn, uint32_t elapsedTime);
_Bool MX_Button_ReadPinIO(uint8_t _id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__MX_BUTTON_BASE_H__
