/**
 ******************************************************************************
 * @file    Charge_Controller.c
 * @brief   拉簧蓄能装置电机控制函数
 ******************************************************************************
 * @attention
 ******************************************************************************
 */
 
#include "main.h"
#include "can.h"
#include "RMotors_Controller.h"
#include "Charge_Controller.h"
#include "remoteMiddleware.h"
#include "motorsMiddleware.h"
#include "user_lib.h"

pid_type_def charge_motors_c_pid[2]; //电流环
pid_type_def charge_motors_v2c_pid[2]; //速度环
pid_type_def charge_motors_p2v_pid[2]; //位置环

first_order_filt_type charge_motor_filter[2];

extern RC_Ctl_t RC_Ctl;
extern RMotor_t charge_motor_receive[2];// 0:左 1:右

/**
 * @brief:	拉簧蓄能机构电机pid和filer初始化
 * @param[in]:
 * @param[out]:
 */
 void charger_motors_PID_Filter_init(void)
 {
		//拉簧蓄能机构电机的pid参数
		fp32 charge_motor_c0_pidParam[3] = {1.0f,0.0f,0.0f};
		fp32 charge_motor_c1_pidParam[3] = {1.0f,0.0f,0.0f};
		
		PID_init((pid_type_def *)(&charge_motors_c_pid[0]),PID_POSITION,charge_motor_c0_pidParam,15000,200);
		PID_init((pid_type_def *)(&charge_motors_c_pid[1]),PID_POSITION,charge_motor_c1_pidParam,15000,200);
		
		/* 滤波器 */
		charge_motor_filter[0].output_trust = 55.0f;
		charge_motor_filter[1].output_trust = 55.0f;
		first_order_filter_init(&charge_motor_filter[0].motors_fst_order_filter,100,&charge_motor_filter[0].output_trust);
		first_order_filter_init(&charge_motor_filter[1].motors_fst_order_filter,100,&charge_motor_filter[1].output_trust);
 }
 
/**
 * @brief:	拉簧蓄能机构电机pid控制
 * @param[in]:
 * @param[out]:
 */
void charge_motors_control(charge_pid_control_t* charge_motor_controller,fp32 setpoint)
{
	if( charge_motor_controller->mode == PID_C ){
		first_order_filter_cali(&charge_motor_filter[0].motors_fst_order_filter,charge_motor_receive[0].current_inst);
		first_order_filter_cali(&charge_motor_filter[1].motors_fst_order_filter,charge_motor_receive[1].current_inst);
		charge_motor_controller->current0 = PID_calc(&charge_motors_c_pid[0],charge_motor_filter[0].motors_fst_order_filter.out,setpoint);
		charge_motor_controller->current1 = PID_calc(&charge_motors_c_pid[1],charge_motor_filter[1].motors_fst_order_filter.out,setpoint);
	}
	else if( charge_motor_controller->mode == PID_V2C ){
	/* 因为因为要保证两个电机输出电矩一样，所以我还没想好方法 */
		
	}
	
	if( charge_motor_controller->mode == PID_P2C ){
	/* 因为要保证两个电机输出力矩一样，所以我还没想好方法 */
		
	}
	
	//_Motor_ID_Cansend(charge_motor_controller->current0,0,charge_motor_controller->current1,0,0x200,);
	
}
