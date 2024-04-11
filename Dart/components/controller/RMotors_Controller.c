#include "RMotors_Controller.h"
#include "main.h"
#include "can.h"
#include "remoteMiddleware.h"
#include "motorsMiddleware.h"
#include "user_lib.h"


pid_type_def charge_motors_c_pid[2];
pid_type_def charge_motors_v2c_pid[2];
pid_type_def charge_motors_p2v_pid[2];
charge_pid_control_t charge_motor_controller;

first_order_filt_type charge_motor_filter;


rmotor_control_t MotorsController;


extern RC_Ctl_t RC_Ctl;
extern RMotor_t charge_motor_receive[2];// 0:左 1:右

/* @brief:charge controller control
 * @param[in]:
 * @param[out]:
 */
void charge_motors_control(charge_pid_control_t* charge_motor_controller,fp32 setpoint)
{
	if( charge_motor_controller->mode == PID_C ){
		first_order_filter_cali(&charge_motor_filter.charge_motors_fst_order_filter[0],charge_motor_receive[0].current_inst);
		first_order_filter_cali(&charge_motor_filter.charge_motors_fst_order_filter[1],charge_motor_receive[1].current_inst);
		charge_motor_controller->current0 = PID_calc(&charge_motors_c_pid[0],charge_motor_filter.charge_motors_fst_order_filter[0].out,setpoint);
		charge_motor_controller->current1 = PID_calc(&charge_motors_c_pid[1],charge_motor_filter.charge_motors_fst_order_filter[1].out,setpoint);
	}
	else if( charge_motor_controller->mode == PID_V2C ){
	/* 因为因为要保证两个电机输出电矩一样，所以我还没想好方法 */
		
	}
	
	if( charge_motor_controller->mode == PID_P2C ){
	/* 因为要保证两个电机输出力矩一样，所以我还没想好方法 */
		
	}
}

/* @brief:Controller init
 * @param[in]:
 * @param[out]:
 */
void MotorController_combine(void)
{
	/*遥控*/
	MotorsController.rc_ctrl = &RC_Ctl;
	/*拉力电机*/
	charge_motor_controller.mode = PID_C;
	charge_motor_controller.c0 = &charge_motors_c_pid[0];
	charge_motor_controller.c1 = &charge_motors_c_pid[1];
	MotorsController.charge_motors_controller = &charge_motor_controller;//charge_motor_Enable
	
}
 
/* @brief:RM motors PID and Filter init
 * @param[in]:
 * @param[out]:
 */
 void motors_PID_Filter_init(void)
 {
		fp32 charge_motor_c0_pidParam[3] = {1.0f,0.0f,0.0f};
		fp32 charge_motor_c1_pidParam[3] = {1.0f,0.0f,0.0f};
		
		PID_init((pid_type_def *)(&charge_motors_c_pid[0]),PID_POSITION,charge_motor_c0_pidParam,15000,200);
		PID_init((pid_type_def *)(&charge_motors_c_pid[1]),PID_POSITION,charge_motor_c1_pidParam,15000,200);
		
		/* filter */
		charge_motor_filter.output_trust[0] = 55.0f;
		charge_motor_filter.output_trust[1] = 55.0f;
		first_order_filter_init(&charge_motor_filter.charge_motors_fst_order_filter[0],100,&charge_motor_filter.output_trust[0]);
		first_order_filter_init(&charge_motor_filter.charge_motors_fst_order_filter[1],100,&charge_motor_filter.output_trust[1]);
 }









