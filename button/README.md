# 按键检测

### 初始化

```c
MX_Button button1 = {0};
MX_Button_Init(&button1, 1, 1000, Button1_Event);
MX_Button_Hardware_Init 硬件初始化函数
```

### 按键检测

```c
_Bool MX_Button_ReadPinIO(uint8_t _id)
```

==需根据模板重写此函数==

### 定时器

```c
MX_Button_Tick(&button1, 10);//将该函数放入定时器中即可，10为定时器内延时时间。
```

### 按键任务

```c
void Button1_Event(MX_Button_Event _event)
{
    switch (_event)
    {
        case UP:
        {
            break;
        }
        case DOWN:
        {
            break;
        }
        case CLICK:
        {
            break;
        }
        case LONG_PRESS:
        {
            break;
        }
        case DOUBLE_CLICK:
        {
            break;
        }
    }
}
```

### 双击

双击并未完善，请勿使用。

取消 `mx_button_base` 中 `DOUBLE_CLICK_BUFFER_TIME` 的注释开启双击检测。

CLICK 为松手事件，尽量不要与 DOUBLE_CLICK 同时使用。

