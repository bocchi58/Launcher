#ifndef MOTORS_MIDDLEWARE_H
#define MOTORS_MIDDLEWARE_H


#include "struct_typedef.h"
#include "can.h"


//3508���������ֵ
#define ENCODE_MAX_3508 8192
#define ENCODE_MAX_2006 8191

#define C610_MAX_CURRENT 10000   
#define C620_MAX_CURRENT 16000 

#define ENCODE2ANGLE 0.0439453125f
#define RPM2ANGLE 6.0f
#define RPM2RAD 0.01471974f
#define CURRENT_DEVIED_100 0.01f


/*DEFINE STRUCT ------------------------*/
typedef struct
{
  fp32 angle_inst;					//�Ƕȷ���ֵ
	int16_t speed_inst;					//ʵʱ�ٶ�
	int16_t cur_temp;				//����
	fp32 current_inst;			//ʵʱ����
	
	fp32 last_angle;				//ǰһ�νǶȷ���ֵ
	int32_t cycle_cnt;					//Ȧ��
	fp32 real_posion;			//ʵ��λ��
	
}RMotor_t;


void motor_can_filter_init(CAN_HandleTypeDef* hcan_1);

#endif

