/**
 ******************************************************************************
 * @file    Replace_Controller.c
 * @brief   换弹装置电机控制函数
 ******************************************************************************
 * @attention
 ******************************************************************************
 */
 
#include "main.h"
#include "can.h"
#include "RMotors_Controller.h"
#include "Replace_Controller.h"
#include "remoteMiddleware.h"
#include "motorsMiddleware.h"
#include "user_lib.h"

pid_type_def replace_motors_c_pid; //电流环
pid_type_def replace_motors_v2c_pid; //速度环
pid_type_def replace_motors_p2v_pid; //位置环


first_order_filt_type replace_motor_filter;

extern RC_Ctl_t RC_Ctl;
extern RMotor_t replace_motor_receive;

/**
 * @brief:	换弹装置电机pid和filer初始化
 * @param[in]:
 * @param[out]:
 */
 void replace_motors_PID_Filter_init(void)
 {
		//换弹装置电机的pid参数
		fp32 replace_motor_c_pidParam[3] = {1.0f,0.0f,0.0f};
		
		PID_init((pid_type_def *)(&replace_motors_c_pid),PID_POSITION,replace_motor_c_pidParam,15000,200);
		
		/* 滤波器 */
		replace_motor_filter.output_trust = 55.0f;
		replace_motor_filter.output_trust = 55.0f;
		first_order_filter_init(&replace_motor_filter.motors_fst_order_filter,100,&replace_motor_filter.output_trust);

 }
 
/**
 * @brief:	换弹装置电机pid控制
 * @param[in]:
 * @param[out]:
 */
void replace_motors_control(replace_pid_control_t* replace_motor_controller,fp32 setpoint)
{
	//电流环控制
	if( replace_motor_controller->mode == PID_C ){
		first_order_filter_cali(&replace_motor_filter.motors_fst_order_filter,replace_motor_receive.current_inst);
		replace_motor_controller->current = PID_calc(&replace_motors_c_pid,replace_motor_filter.motors_fst_order_filter.out,setpoint);
	}
	//速度环控制
	else if( replace_motor_controller->mode == PID_V2C ){
	/* 因为因为要保证两个电机输出电矩一样，所以我还没想好方法 */
		
	}
	//位置环控制
	else if( replace_motor_controller->mode == PID_P2C ){
	/* 因为要保证两个电机输出力矩一样，所以我还没想好方法 */
		
	}
	//_Motor_ID_Cansend(replace_motor_controller->current,0,0,0,0x1FF,);
}
