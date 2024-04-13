#ifndef RMOTORS_CONTROLLER_H
#define RMOTORS_CONTROLLER_H

/*-------------------includes -------------------*/
#include "struct_typedef.h"
#include "remoteMiddleware.h"
#include "pid.h"
#include "user_lib.h"

/*-------------------ENUM -------------------*/
enum MOTOR_CONTROL_MODE	//电机控制模式
{
    PID_P2C = 0, //位置控制模式
    PID_V2C, //速度控制模式
	PID_C, //电流控制模式
};

/*-------------------DEFINE STRUCT -------------------*/
typedef struct	//拉簧蓄能电机的相关参数
{
	uint8_t mode; //模式
	fp32 setpoint; //目标输入
	const pid_type_def *c0; //0号电机pid结构体
	const pid_type_def *c1; //1号电机pid结构体
	fp32 current0;//输出电流
	fp32 current1;
	/* 暂时没有用 */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
}charge_pid_control_t;

typedef struct	//旋转装置电机的相关参数
{
	uint8_t mode; //模式
	fp32 setpoint; //目标输入
	const pid_type_def *c; 
	fp32 current;//输出电流
	/* 暂时没有用 */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
}rotate_pid_control_t;


typedef struct	//换弹装置电机的相关参数
{
	uint8_t mode; //模式
	fp32 setpoint; //目标输入
	const pid_type_def *c; 
	fp32 current;//输出电流
	/* 暂时没有用 */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
}replace_pid_control_t;


typedef struct	//一阶滤波器
{
	first_order_filter_type_t motors_fst_order_filter;
	fp32 output_trust;// 对过去项的依赖程度
}first_order_filt_type;



typedef struct	//电机驱动结构体指针
{
    const RC_Ctl_t *rc_ctrl;	//遥控器控制
	const charge_pid_control_t *charge_motors_controller; //拉簧蓄能电机
	//					//换弹结构电机
	//					//旋转结构电机
} rmotor_control_t;

/*-------------------FUNCTION -------------------*/
void MotorController_combine(void);
void motors_PID_Filter_init(void);
void motors_Controller(void);


#endif

