/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       motor_CAN_task.c/h
  * @brief      �������-����
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Nov-11-2019     RM              1. done
  *
  @verbatim
  ==============================================================================

  ================== ============================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "canbus_send_task.h"
#include "main.h"
#include "can.h"
#include "cmsis_os.h"
#include "RMotors_Controller.h"


extern rmotor_control_t  ;

/**
  * @brief          test����
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void canbus_send_task(void const * argument)
{
		static CAN_TxHeaderTypeDef TxHeader;
		static uint32_t TxMailbox;
		static uint8_t TxData[8] = {0};
		// ���÷�����Ϣ
		TxHeader.StdId = 0x200;  // ��׼ID
		//TxHeader.ExtId = 0x01;   // ��չID�����ʹ��
		TxHeader.RTR = CAN_RTR_DATA; // ����֡
		TxHeader.IDE = CAN_ID_STD;   // ��׼��ʶ��
		TxHeader.DLC = 0x08;        // ���ݳ���Ϊ8λ
		TxHeader.TransmitGlobalTime = DISABLE; // ������Ҫ���û����
    while(1)
    {
//				TxData[0] = (unsigned char)((tempX >> 8) & 0xff);
//				TxData[1] = (unsigned char)(tempX & 0xff);
				

        osDelay(10);
    }
}
/**
	* @brief          ���Ͳ�����
  * @param[in]      none
  * @retval         none
  */
void canbus_send_Combine(void)
{
	
}
