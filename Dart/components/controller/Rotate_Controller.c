/**
 ******************************************************************************
 * @file    Rotate_Controller.c
 * @brief   ��תװ�õ�����ƺ���
 ******************************************************************************
 * @attention
 ******************************************************************************
 */
 
#include "main.h"
#include "can.h"
#include "RMotors_Controller.h"
#include "Rotate_Controller.h"
#include "remoteMiddleware.h"
#include "motorsMiddleware.h"
#include "user_lib.h"

pid_type_def rotate_motors_c_pid; //������
pid_type_def rotate_motors_v2c_pid; //�ٶȻ�
pid_type_def rotate_motors_p2v_pid; //λ�û�

first_order_filt_type rotate_motor_filter;

extern RC_Ctl_t RC_Ctl;
extern RMotor_t rotate_motor_receive;

/**
 * @brief:	��תװ�õ��pid��filer��ʼ��
 * @param[in]:
 * @param[out]:
 */
 void rotate_motors_PID_Filter_init(void)
 {
		//��תװ�õ����pid����
		fp32 rotate_motor_c_pidParam[3] = {1.0f,0.0f,0.0f};
		
		PID_init((pid_type_def *)(&rotate_motors_c_pid),PID_POSITION,rotate_motor_c_pidParam,15000,200);
		
		/* �˲��� */
		rotate_motor_filter.output_trust = 55.0f;
		rotate_motor_filter.output_trust = 55.0f;
		first_order_filter_init(&rotate_motor_filter.motors_fst_order_filter,100,&rotate_motor_filter.output_trust);

 }
 
/**
 * @brief:	��תװ�õ��pid����
 * @param[in]:
 * @param[out]:
 */
void rotate_motors_control(rotate_pid_control_t* rotate_motor_controller,fp32 setpoint)
{
	//����������
	if( rotate_motor_controller->mode == PID_C ){
		first_order_filter_cali(&rotate_motor_filter.motors_fst_order_filter,rotate_motor_receive.current_inst);
		rotate_motor_controller->current = PID_calc(&rotate_motors_c_pid,rotate_motor_filter.motors_fst_order_filter.out,setpoint);
		//_Motor_ID_Cansend(rotate_motor_controller->current,0,0,0,0x1FF,);
	}
	//�ٶȻ�����
	else if( rotate_motor_controller->mode == PID_V2C ){
		first_order_filter_cali(&rotate_motor_filter.motors_fst_order_filter,rotate_motor_receive.speed_inst);
		rotate_motor_controller->midparam = PID_calc(&rotate_motors_v2c_pid,rotate_motor_filter.motors_fst_order_filter.out,setpoint);
		rotate_motor_controller->mode = PID_C;
//		rotate_motors_control(rotate_motor_controller,rotate_motor_controller->midparam);
	}
	//λ�û�����
	else if( rotate_motor_controller->mode == PID_P2C ){
		first_order_filter_cali(&rotate_motor_filter.motors_fst_order_filter,rotate_motor_receive.angle_inst);
		rotate_motor_controller->curparam = PID_calc(&rotate_motors_p2v_pid,rotate_motor_filter.motors_fst_order_filter.out,setpoint);
		rotate_motor_controller->mode = PID_P2C;
		rotate_motors_control(rotate_motor_controller,rotate_motor_controller->curparam);
	}
}
