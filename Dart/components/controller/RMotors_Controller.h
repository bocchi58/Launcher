#ifndef RMOTORS_CONTROLLER_H
#define RMOTORS_CONTROLLER_H


#include "struct_typedef.h"
#include "remoteMiddleware.h"
#include "pid.h"
#include "user_lib.h"


enum MOTOR_CONTROL_MODE
{
    PID_P2C = 0,
    PID_V2C,
		PID_C,
};

typedef struct
{
	uint8_t mode; //ģʽ
	fp32 setpoint; //Ŀ������
	const pid_type_def *c0; //0�ŵ��pid�ṹ��
	const pid_type_def *c1;//1�ŵ��...
	fp32 current0;//�������
	fp32 current1;
	/* ��ʱû���� */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
	
}charge_pid_control_t;

typedef struct
{
	first_order_filter_type_t charge_motors_fst_order_filter[2];
	fp32 output_trust[2];// �Թ�ȥ��������̶�
}first_order_filt_type;


typedef struct
{
    const RC_Ctl_t *rc_ctrl;
		const charge_pid_control_t *charge_motors_controller;
	
	
} rmotor_control_t;


void MotorController_combine(void);
void motors_PID_Filter_init(void);

void charge_motors_control(charge_pid_control_t* charge_motor_controller,fp32 setpoint);


#endif

