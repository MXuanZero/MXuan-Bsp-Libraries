//位置式PID


#ifndef __PID_LOC_H__
#define __PID_LOC_H__

#include "pid_base.h"

class PID_Loc : public PID_Base{

    float Ctrl(float error);

};

#endif //__PID_LOC_H__
