#include "pid_base.h"

PID_Base::PID_Base(float _kp,float _ki, float _kd)
{
    this->kp = _kp;
    this->ki = _ki;
    this->kd = _kd;
    this->imax              = 0;
    this->out_p             = 0;
    this->out_i             = 0;
    this->out_d             = 0;
    this->out               = 0;
    this->integrator        = 0;
    this->last_error        = 0;
    this->last_derivative   = 0;
    this->last_t            = 0;
}

void PID_Base::Clear()
{
    this->imax              = 0;
    this->out_p             = 0;
    this->out_i             = 0;
    this->out_d             = 0;
    this->out               = 0;
    this->integrator        = 0;
    this->last_error        = 0;
    this->last_derivative   = 0;
    this->last_t            = 0;
}

void PID_Base::PID_set_kp(const float _kp)
{
    this->kp = _kp;
}

void PID_Base::PID_set_ki(const float _ki)
{
    this->ki = _ki;
}

void PID_Base::PID_set_kd(const float _kd)
{
    this->kd = _kd;
}

float PID_Base::PID_get_kp() const
{
    return this->kp;
}

float PID_Base::PID_get_ki() const
{
    return this->ki;
}

float PID_Base::PID_get_kd() const
{
    return this->kd;
}

