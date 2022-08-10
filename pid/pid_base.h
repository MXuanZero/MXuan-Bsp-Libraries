#ifndef __PID_BASE_H__
#define __PID_BASE_H__

class PID_Base{
protected:
    float                kp;                //P
    float                ki;                //I
    float                kd;                //D
public:
    float                out;               //pid输出
    float                imax;              //积分限幅

    float                out_p;             //KP输出
    float                out_i;             //KI输出
    float                out_d;             //KD输出

    float                integrator;        //积分值
    float                last_error;        //上次误差
    float                last_derivative;   //上次误差与上上次误差之差
    unsigned long        last_t;            //上次时间
    /*函数*/
    PID_Base(float _kp,float _ki, float _kd);
    void Clear();
    virtual float Ctrl(float error) = 0;

    void    PID_set_kp(float _kp);          //设置kp的值
    void    PID_set_ki(float _kp);          //设置ki的值
    void    PID_set_kd(float _kp);          //设置kd的值
    float   PID_get_kp() const;             //设置kp的值
    float   PID_get_ki() const;             //设置ki的值
    float   PID_get_kd() const;             //设置kd的值
};



#endif //__PID_BASE_H__
