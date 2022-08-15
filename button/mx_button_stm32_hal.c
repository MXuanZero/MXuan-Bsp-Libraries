#include "main.h"
#include "mx_button_base.h"

void MX_Button_Hardware_Init(MX_Button *mx_btn,uint8_t _id)
{
    
}

_Bool MX_Button_ReadPinIO(uint8_t _id)
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
