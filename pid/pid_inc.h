#ifndef __PID_INC_H__
#define __PID_INC_H__


#include "pid_base.h"

class PID_Inc : public PID_Base{

    float Ctrl(float error);

};

#endif //__PID_INC_H__
