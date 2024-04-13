///**
// ******************************************************************************
// * @file    Start_Task.c
// * @brief   ��ʼ�����񴴽�
// ******************************************************************************
// * @attention
// ******************************************************************************
// */

//#include "Start_Task.h"

///*�������ȼ���ֵԽ�ͣ����ȼ�Խ��*/

//// ��ʼ������
//#define START_TASK_PRIO 1       // �������ȼ�
//#define START_TASK_STK_SIZE 128 // �����ջ
//static TaskHandle_t StartTask_Handler;



//TaskHandle_t User_Tasks[TASK_NUM];

///**
// * @brief ��ʼ������,������������
// * @param[in] void
// */
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();
//#if TEST_TASK_ON
//    xTaskCreate((TaskFunction_t)Test_task,               // ������
//                (const char *)"Test_task",               // ��������
//                (uint16_t)TEST_TASK_STK_SIZE,            // �����ջ��С
//                (void *)NULL,                            // ���ݸ��������Ĳ���
//                (UBaseType_t)TEST_TASK_PRIO,             // �������ȼ�
//                (TaskHandle_t *)&User_Tasks[TEST_TASK]); // ������
//#elif MF9025_IDENTIFY_ON
//    xTaskCreate((TaskFunction_t)MF9025_IdentifyTask,                       // ������
//                (const char *)"MF9025_IdentifyTask",                       // ��������
//                (uint16_t)MF9025_SYS_IDEN_TASK_STK_SIZE,                   // �����ջ��С
//                (void *)NULL,                                              // ���ݸ��������Ĳ���
//                (UBaseType_t)MF9025_SYS_IDEN_TASK_PRIO,                    // �������ȼ�
//                (TaskHandle_t *)&User_Tasks[MF9025_SYSTEM_IDENTIFY_TASK]); // ������
//#else

//    xTaskCreate((TaskFunction_t)ChasisEstimate_task,               // ������
//                (const char *)"ChasisEstimate_task",               // ��������
//                (uint16_t)ChasisEstimate_TASK_STK_SIZE,            // �����ջ��С
//                (void *)NULL,                                      // ���ݸ��������Ĳ���
//                (UBaseType_t)ChasisEstimate_TASK_PRIO,             // �������ȼ�
//                (TaskHandle_t *)&User_Tasks[CHASISESTIMATE_TASK]); // ������

//    // ����ƽ�ⲽ����������
//	 xTaskCreate((TaskFunction_t)ChasisControl_task,               // ������
//							 (const char *)"ChasisControl_task",               // ��������
//							 (uint16_t)CHASIS_CONTROL_TASK_STK_SIZE,           // �����ջ��С
//							 (void *)NULL,                                     // ���ݸ��������Ĳ���
//							 (UBaseType_t)CHASIS_CONTROL_TASK_PRIO,            // �������ȼ�
//							 (TaskHandle_t *)&User_Tasks[CHASISCONTROL_TASK]); // ������

//    // �������߼������
////    xTaskCreate((TaskFunction_t)Offline_task,               // ������
////                (const char *)"Offline_task",               // ��������
////                (uint16_t)OFFLINE_TASK_STK_SIZE,            // �����ջ��С
////                (void *)NULL,                               // ���ݸ��������Ĳ���
////                (UBaseType_t)OFFLINE_TASK_PRIO,             // �������ȼ�
////                (TaskHandle_t *)&User_Tasks[OFFLINE_TASK]); // ������

//	 //������������(����λ��ͨ�ţ��쳣״̬��Ⲣ����ģʽ)
//		xTaskCreate((TaskFunction_t)Action_task,               //������
//								(const char *)"Action_task",               //��������
//								(uint16_t)ACTION_TASK_STK_SIZE,            //�����ջ��С
//								(void *)NULL,                              //���ݸ��������Ĳ���
//								(UBaseType_t)ACTION_TASK_PRIO,             //�������ȼ�
//								(TaskHandle_t *)&User_Tasks[ACTION_TASK]); //������

//    // xTaskCreate((TaskFunction_t)SDCard_task,               //������
//    //             (const char *)"SDCard_task",               //��������
//    //             (uint16_t)SD_CARD_TASK_STK_SIZE,           //�����ջ��С
//    //             (void *)NULL,                              //���ݸ��������Ĳ���
//    //             (UBaseType_t)SD_CARD_TASK_PRIO,            //�������ȼ�
//    //             (TaskHandle_t *)&User_Tasks[SDCARD_TASK]); //������

//    //��������
//    xTaskCreate((TaskFunction_t)Debug_Task,                 // ������
//                (const char *)"Debug_Task",                 // ��������
//                (uint16_t)DEBUG_TASK_STK_SIZE,            // �����ջ��С
//                (void *)NULL,                                  // ���ݸ��������Ĳ���
//                (UBaseType_t)DEBUG_TASK_PRIO,             // �������ȼ�
//                (TaskHandle_t *)&User_Tasks[DEBUG_TASK]); // ������

//#if IWDG_TASK_ON
////    xTaskCreate((TaskFunction_t)Iwdg_task,                     // ������
////                (const char *)"Iwdg_task",                     // ��������
////                (uint16_t)IWDG_TASK_STK_SIZE,                  // �����ջ��С
////                (void *)NULL,                                  // ���ݸ��������Ĳ���
////                (UBaseType_t)IWDG_TASK_PRIO,                   // �������ȼ�
////                (TaskHandle_t *)&User_Tasks[IWDG_TASK]);       // ������

//#endif // IWDG_TASK_ON

//    // //������ʽ��̼�����ٶȼ������ں�����
//    // xTaskCreate((TaskFunction_t)WheelsAccelFusion_task,           //������
//    //             (const char *)"WheelsAccelFusion_task",           //��������
//    //             (uint16_t)CHASIS_CONTROL_TASK_STK_SIZE,           //�����ջ��С
//    //             (void *)NULL,                                     //���ݸ��������Ĳ���
//    //             (UBaseType_t)CHASIS_CONTROL_TASK_PRIO,            //�������ȼ�
//    //             (TaskHandle_t *)&User_Tasks[CHASISCONTROL_TASK]); //������

//    /* ��󴴽�  */
//#ifdef DEBUG_MODE_FREERTOS
////    xTaskCreate((TaskFunction_t)CPU_task,               // ������
////                (const char *)"CPU_task",               // ��������
////                (uint16_t)CPU_TASK_STK_SIZE,            // �����ջ��С
////                (void *)NULL,                           // ���ݸ��������Ĳ���
////                (UBaseType_t)CPU_TASK_PRIO,             // �������ȼ�
////                (TaskHandle_t *)&User_Tasks[CPU_TASK]); // ������
//#endif // DEBUG_MODE_FREERTOS
//#endif // TEST_TASK_ON

//    xCreatedEventGroup = xEventGroupCreate(); // ����������

//    vTaskDelete(StartTask_Handler); // ɾ����ʼ����
//    taskEXIT_CRITICAL();            // �˳��ٽ���
//}

///**
// * @brief ������ʼ������
// * @param[in] void
// */
//void startTask(void)
//{
//    xTaskCreate((TaskFunction_t)start_task,          // ������
//                (const char *)"start_task",          // ��������
//                (uint16_t)START_TASK_STK_SIZE,       // �����ջ��С
//                (void *)NULL,                        // ���ݸ��������Ĳ���
//                (UBaseType_t)START_TASK_PRIO,        // �������ȼ�
//                (TaskHandle_t *)&StartTask_Handler); // ������
//}
