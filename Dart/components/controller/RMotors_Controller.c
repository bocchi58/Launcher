/**
 ******************************************************************************
 * @file    RMotors_Controller.c
 * @brief   电机控制函数
 ******************************************************************************
 * @attention
 ******************************************************************************
 */

#include "RMotors_Controller.h"
#include "main.h"
#include "can.h"
#include "remoteMiddleware.h"
#include "motorsMiddleware.h"
#include "user_lib.h"

#include "Charge_Controller.h"
#include "Rotate_Controller.h"
#include "Replace_Controller.h"


rmotor_control_t MotorsController;


extern RC_Ctl_t RC_Ctl;
extern RMotor_t charge_motor_receive[2];// 0:左 1:右


/**
 * @brief:	遥控初始化
 * @param[in]:
 * @param[out]:
 */
void MotorController_combine(void)
{
	/*遥控*/
	MotorsController.rc_ctrl = &RC_Ctl;
	/*拉力电机*/
//	charge_motor_controller.mode = PID_C;
//	charge_motor_controller.c0 = &charge_motors_c_pid[0];
//	charge_motor_controller.c1 = &charge_motors_c_pid[1];
//	MotorsController.charge_motors_controller = &charge_motor_controller;//charge_motor_Enable
	
}

/**
 * @brief:	RM 所有电机pid和filter初始化
 * @param[in]:
 * @param[out]:
 */
 void motors_PID_Filter_init(void)
 {
		charger_motors_PID_Filter_init();
		rotate_motors_PID_Filter_init();
		replace_motors_PID_Filter_init();
 }

/**
 * @brief:	RM 所有电机pid控制
 * @param[in]:
 * @param[out]:
 */
charge_pid_control_t charge_motor_controller; 
rotate_pid_control_t rotate_motor_controller;
replace_pid_control_t replace_motor_controller;

 void motors_Controller(void)
 {
		charge_motors_control(&charge_motor_controller,1);
		rotate_motors_control(&rotate_motor_controller,1);
		replace_motors_control(&replace_motor_controller,1);
 }



