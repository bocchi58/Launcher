#ifndef RMOTORS_CONTROLLER_H
#define RMOTORS_CONTROLLER_H

/*-------------------includes -------------------*/
#include "struct_typedef.h"
#include "remoteMiddleware.h"
#include "pid.h"
#include "user_lib.h"

/*-------------------ENUM -------------------*/
enum MOTOR_CONTROL_MODE	//�������ģʽ
{
    PID_P2C = 0, //λ�ÿ���ģʽ
    PID_V2C, //�ٶȿ���ģʽ
	PID_C, //��������ģʽ
};

/*-------------------DEFINE STRUCT -------------------*/
typedef struct	//�������ܵ������ز���
{
	uint8_t mode; //ģʽ
	fp32 setpoint; //Ŀ������
	const pid_type_def *c0; //0�ŵ��pid�ṹ��
	const pid_type_def *c1; //1�ŵ��pid�ṹ��
	fp32 current0;//�������
	fp32 current1;
	/* ��ʱû���� */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
}charge_pid_control_t;

typedef struct	//��תװ�õ������ز���
{
	uint8_t mode; //ģʽ
	fp32 setpoint; //Ŀ������
	const pid_type_def *c; 
	fp32 current;//�������
	/* ��ʱû���� */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
}rotate_pid_control_t;


typedef struct	//����װ�õ������ز���
{
	uint8_t mode; //ģʽ
	fp32 setpoint; //Ŀ������
	const pid_type_def *c; 
	fp32 current;//�������
	/* ��ʱû���� */
	const pid_type_def *p2v; 
	fp32 midparam;
	const pid_type_def *v2c;
	fp32 curparam;
	/*------------*/
}replace_pid_control_t;


typedef struct	//һ���˲���
{
	first_order_filter_type_t motors_fst_order_filter;
	fp32 output_trust;// �Թ�ȥ��������̶�
}first_order_filt_type;



typedef struct	//��������ṹ��ָ��
{
    const RC_Ctl_t *rc_ctrl;	//ң��������
	const charge_pid_control_t *charge_motors_controller; //�������ܵ��
	//					//�����ṹ���
	//					//��ת�ṹ���
} rmotor_control_t;

/*-------------------FUNCTION -------------------*/
void MotorController_combine(void);
void motors_PID_Filter_init(void);
void motors_Controller(void);


#endif

