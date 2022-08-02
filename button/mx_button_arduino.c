#include <Arduino.h>
#include "mx_button_base.h"

void MX_Button_Hardware_Init(MX_Button *mx_btn,uint8_t _id)
{
    if (mx_btn->id == _id)
    {
        pinMode(BUTTON, INPUT_PULLUP);
    }
}

_Bool MX_Button_ReadPinIO(uint8_t _id)
{
    if(BUTTON == _id)
    {
        return (digitalRead(BUTTON) == LOW);
    }
    else
    {
        return false;
    }
}
