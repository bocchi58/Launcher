/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       motor_CAN_task.c/h
  * @brief      电机控制-发送
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
  * @brief          test任务
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void canbus_send_task(void const * argument)
{
		static CAN_TxHeaderTypeDef TxHeader;
		static uint32_t TxMailbox;
		static uint8_t TxData[8] = {0};
		// 配置发送消息
		TxHeader.StdId = 0x200;  // 标准ID
		//TxHeader.ExtId = 0x01;   // 扩展ID，如果使用
		TxHeader.RTR = CAN_RTR_DATA; // 数据帧
		TxHeader.IDE = CAN_ID_STD;   // 标准标识符
		TxHeader.DLC = 0x08;        // 数据长度为8位
		TxHeader.TransmitGlobalTime = DISABLE; // 根据需要启用或禁用
    while(1)
    {
//				TxData[0] = (unsigned char)((tempX >> 8) & 0xff);
//				TxData[1] = (unsigned char)(tempX & 0xff);
				

        osDelay(10);
    }
}
/**
	* @brief          发送参数绑定
  * @param[in]      none
  * @retval         none
  */
void canbus_send_Combine(void)
{
	
}
