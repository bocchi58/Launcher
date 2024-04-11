/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       test_task.c/h
  * @brief      buzzer warning task.蜂鸣器报警任务
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Nov-11-2019     RM              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "test_task.h"
#include "main.h"
#include "can.h"
#include "cmsis_os.h"


/**
  * @brief          test task
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
/**
  * @brief          test任务
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void test_task(void const * argument)
{
  CAN_TxHeaderTypeDef TxHeader;
  uint8_t TxData[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  uint32_t TxMailbox;
	
	

    while(1)
    {
				// 配置发送消息
				TxHeader.StdId = 0x105;  // 标准ID
				//TxHeader.ExtId = 0x01;   // 扩展ID，如果使用
				TxHeader.RTR = CAN_RTR_DATA; // 数据帧
				TxHeader.IDE = CAN_ID_STD;   // 标准标识符
				TxHeader.DLC = 0x08;        // 数据长度为8位
				TxHeader.TransmitGlobalTime = DISABLE; // 根据需要启用或禁用
				if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
				{
					// 发送失败处理
					Error_Handler();
				}			
				
				

        osDelay(10);
    }
}



