/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       test_task.c/h
  * @brief      buzzer warning task.��������������
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
  * @brief          test����
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
				// ���÷�����Ϣ
				TxHeader.StdId = 0x105;  // ��׼ID
				//TxHeader.ExtId = 0x01;   // ��չID�����ʹ��
				TxHeader.RTR = CAN_RTR_DATA; // ����֡
				TxHeader.IDE = CAN_ID_STD;   // ��׼��ʶ��
				TxHeader.DLC = 0x08;        // ���ݳ���Ϊ8λ
				TxHeader.TransmitGlobalTime = DISABLE; // ������Ҫ���û����
				if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
				{
					// ����ʧ�ܴ���
					Error_Handler();
				}			
				
				

        osDelay(10);
    }
}



