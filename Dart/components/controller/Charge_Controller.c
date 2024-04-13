/**
 ******************************************************************************
 * @file    Charge_Controller.c
 * @brief   ��������װ�õ�����ƺ���
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

pid_type_def charge_motors_c_pid[2]; //������
pid_type_def charge_motors_v2c_pid[2]; //�ٶȻ�
pid_type_def charge_motors_p2v_pid[2]; //λ�û�

first_order_filt_type charge_motor_filter[2];

extern RC_Ctl_t RC_Ctl;
extern RMotor_t charge_motor_receive[2];// 0:�� 1:��

/**
 * @brief:	�������ܻ������pid��filer��ʼ��
 * @param[in]:
 * @param[out]:
 */
 void charger_motors_PID_Filter_init(void)
 {
		//�������ܻ��������pid����
		fp32 charge_motor_c0_pidParam[3] = {1.0f,0.0f,0.0f};
		fp32 charge_motor_c1_pidParam[3] = {1.0f,0.0f,0.0f};
		
		PID_init((pid_type_def *)(&charge_motors_c_pid[0]),PID_POSITION,charge_motor_c0_pidParam,15000,200);
		PID_init((pid_type_def *)(&charge_motors_c_pid[1]),PID_POSITION,charge_motor_c1_pidParam,15000,200);
		
		/* �˲��� */
		charge_motor_filter[0].output_trust = 55.0f;
		charge_motor_filter[1].output_trust = 55.0f;
		first_order_filter_init(&charge_motor_filter[0].motors_fst_order_filter,100,&charge_motor_filter[0].output_trust);
		first_order_filter_init(&charge_motor_filter[1].motors_fst_order_filter,100,&charge_motor_filter[1].output_trust);
 }
 
/**
 * @brief:	�������ܻ������pid����
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
	/* ��Ϊ��ΪҪ��֤�������������һ���������һ�û��÷��� */
		
	}
	
	if( charge_motor_controller->mode == PID_P2C ){
	/* ��ΪҪ��֤��������������һ���������һ�û��÷��� */
		
	}
	
	//_Motor_ID_Cansend(charge_motor_controller->current0,0,charge_motor_controller->current1,0,0x200,);
	
}
