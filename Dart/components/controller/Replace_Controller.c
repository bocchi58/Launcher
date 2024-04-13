/**
 ******************************************************************************
 * @file    Replace_Controller.c
 * @brief   ����װ�õ�����ƺ���
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

pid_type_def replace_motors_c_pid; //������
pid_type_def replace_motors_v2c_pid; //�ٶȻ�
pid_type_def replace_motors_p2v_pid; //λ�û�


first_order_filt_type replace_motor_filter;

extern RC_Ctl_t RC_Ctl;
extern RMotor_t replace_motor_receive;

/**
 * @brief:	����װ�õ��pid��filer��ʼ��
 * @param[in]:
 * @param[out]:
 */
 void replace_motors_PID_Filter_init(void)
 {
		//����װ�õ����pid����
		fp32 replace_motor_c_pidParam[3] = {1.0f,0.0f,0.0f};
		
		PID_init((pid_type_def *)(&replace_motors_c_pid),PID_POSITION,replace_motor_c_pidParam,15000,200);
		
		/* �˲��� */
		replace_motor_filter.output_trust = 55.0f;
		replace_motor_filter.output_trust = 55.0f;
		first_order_filter_init(&replace_motor_filter.motors_fst_order_filter,100,&replace_motor_filter.output_trust);

 }
 
/**
 * @brief:	����װ�õ��pid����
 * @param[in]:
 * @param[out]:
 */
void replace_motors_control(replace_pid_control_t* replace_motor_controller,fp32 setpoint)
{
	//����������
	if( replace_motor_controller->mode == PID_C ){
		first_order_filter_cali(&replace_motor_filter.motors_fst_order_filter,replace_motor_receive.current_inst);
		replace_motor_controller->current = PID_calc(&replace_motors_c_pid,replace_motor_filter.motors_fst_order_filter.out,setpoint);
	}
	//�ٶȻ�����
	else if( replace_motor_controller->mode == PID_V2C ){
	/* ��Ϊ��ΪҪ��֤�������������һ���������һ�û��÷��� */
		
	}
	//λ�û�����
	else if( replace_motor_controller->mode == PID_P2C ){
	/* ��ΪҪ��֤��������������һ���������һ�û��÷��� */
		
	}
	//_Motor_ID_Cansend(replace_motor_controller->current,0,0,0,0x1FF,);
}
