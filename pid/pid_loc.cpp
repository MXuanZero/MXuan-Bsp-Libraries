#include "pid_loc.h"
/**
  * @brief  pid位置式控制器输出
  * @param  error   pid输入误差
  * @note   注意输出结果已经包涵了上次结果
  * @retval PID输出结果
  * @date 	2022-03-05
  */
float PID_Loc::Ctrl(float error)
{
    this->integrator += error;

    this->out_p = this->kp * error;
    this->out_i = this->ki * this->integrator;
    this->out_d = this->kd * (error - this->last_error);

    this->last_error = error;

    this->out = this->out_p + this->out_i + this->out_d;

    return this->out;
}
