///**
// ******************************************************************************
// * @file    Start_Task.c
// * @brief   初始化任务创建
// ******************************************************************************
// * @attention
// ******************************************************************************
// */

//#include "Start_Task.h"

///*任务优先级数值越低，优先级越低*/

//// 初始化任务
//#define START_TASK_PRIO 1       // 任务优先级
//#define START_TASK_STK_SIZE 128 // 任务堆栈
//static TaskHandle_t StartTask_Handler;



//TaskHandle_t User_Tasks[TASK_NUM];

///**
// * @brief 初始化任务,创建其它任务
// * @param[in] void
// */
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();
//#if TEST_TASK_ON
//    xTaskCreate((TaskFunction_t)Test_task,               // 任务函数
//                (const char *)"Test_task",               // 任务名称
//                (uint16_t)TEST_TASK_STK_SIZE,            // 任务堆栈大小
//                (void *)NULL,                            // 传递给任务函数的参数
//                (UBaseType_t)TEST_TASK_PRIO,             // 任务优先级
//                (TaskHandle_t *)&User_Tasks[TEST_TASK]); // 任务句柄
//#elif MF9025_IDENTIFY_ON
//    xTaskCreate((TaskFunction_t)MF9025_IdentifyTask,                       // 任务函数
//                (const char *)"MF9025_IdentifyTask",                       // 任务名称
//                (uint16_t)MF9025_SYS_IDEN_TASK_STK_SIZE,                   // 任务堆栈大小
//                (void *)NULL,                                              // 传递给任务函数的参数
//                (UBaseType_t)MF9025_SYS_IDEN_TASK_PRIO,                    // 任务优先级
//                (TaskHandle_t *)&User_Tasks[MF9025_SYSTEM_IDENTIFY_TASK]); // 任务句柄
//#else

//    xTaskCreate((TaskFunction_t)ChasisEstimate_task,               // 任务函数
//                (const char *)"ChasisEstimate_task",               // 任务名称
//                (uint16_t)ChasisEstimate_TASK_STK_SIZE,            // 任务堆栈大小
//                (void *)NULL,                                      // 传递给任务函数的参数
//                (UBaseType_t)ChasisEstimate_TASK_PRIO,             // 任务优先级
//                (TaskHandle_t *)&User_Tasks[CHASISESTIMATE_TASK]); // 任务句柄

//    // 创建平衡步兵控制任务
//	 xTaskCreate((TaskFunction_t)ChasisControl_task,               // 任务函数
//							 (const char *)"ChasisControl_task",               // 任务名称
//							 (uint16_t)CHASIS_CONTROL_TASK_STK_SIZE,           // 任务堆栈大小
//							 (void *)NULL,                                     // 传递给任务函数的参数
//							 (UBaseType_t)CHASIS_CONTROL_TASK_PRIO,            // 任务优先级
//							 (TaskHandle_t *)&User_Tasks[CHASISCONTROL_TASK]); // 任务句柄

//    // 创建掉线检测任务
////    xTaskCreate((TaskFunction_t)Offline_task,               // 任务函数
////                (const char *)"Offline_task",               // 任务名称
////                (uint16_t)OFFLINE_TASK_STK_SIZE,            // 任务堆栈大小
////                (void *)NULL,                               // 传递给任务函数的参数
////                (UBaseType_t)OFFLINE_TASK_PRIO,             // 任务优先级
////                (TaskHandle_t *)&User_Tasks[OFFLINE_TASK]); // 任务句柄

//	 //创建动作任务(和上位机通信，异常状态检测并调整模式)
//		xTaskCreate((TaskFunction_t)Action_task,               //任务函数
//								(const char *)"Action_task",               //任务名称
//								(uint16_t)ACTION_TASK_STK_SIZE,            //任务堆栈大小
//								(void *)NULL,                              //传递给任务函数的参数
//								(UBaseType_t)ACTION_TASK_PRIO,             //任务优先级
//								(TaskHandle_t *)&User_Tasks[ACTION_TASK]); //任务句柄

//    // xTaskCreate((TaskFunction_t)SDCard_task,               //任务函数
//    //             (const char *)"SDCard_task",               //任务名称
//    //             (uint16_t)SD_CARD_TASK_STK_SIZE,           //任务堆栈大小
//    //             (void *)NULL,                              //传递给任务函数的参数
//    //             (UBaseType_t)SD_CARD_TASK_PRIO,            //任务优先级
//    //             (TaskHandle_t *)&User_Tasks[SDCARD_TASK]); //任务句柄

//    //调试任务
//    xTaskCreate((TaskFunction_t)Debug_Task,                 // 任务函数
//                (const char *)"Debug_Task",                 // 任务名称
//                (uint16_t)DEBUG_TASK_STK_SIZE,            // 任务堆栈大小
//                (void *)NULL,                                  // 传递给任务函数的参数
//                (UBaseType_t)DEBUG_TASK_PRIO,             // 任务优先级
//                (TaskHandle_t *)&User_Tasks[DEBUG_TASK]); // 任务句柄

//#if IWDG_TASK_ON
////    xTaskCreate((TaskFunction_t)Iwdg_task,                     // 任务函数
////                (const char *)"Iwdg_task",                     // 任务名称
////                (uint16_t)IWDG_TASK_STK_SIZE,                  // 任务堆栈大小
////                (void *)NULL,                                  // 传递给任务函数的参数
////                (UBaseType_t)IWDG_TASK_PRIO,                   // 任务优先级
////                (TaskHandle_t *)&User_Tasks[IWDG_TASK]);       // 任务句柄

//#endif // IWDG_TASK_ON

//    // //创建轮式里程计与加速度计数据融合任务
//    // xTaskCreate((TaskFunction_t)WheelsAccelFusion_task,           //任务函数
//    //             (const char *)"WheelsAccelFusion_task",           //任务名称
//    //             (uint16_t)CHASIS_CONTROL_TASK_STK_SIZE,           //任务堆栈大小
//    //             (void *)NULL,                                     //传递给任务函数的参数
//    //             (UBaseType_t)CHASIS_CONTROL_TASK_PRIO,            //任务优先级
//    //             (TaskHandle_t *)&User_Tasks[CHASISCONTROL_TASK]); //任务句柄

//    /* 最后创建  */
//#ifdef DEBUG_MODE_FREERTOS
////    xTaskCreate((TaskFunction_t)CPU_task,               // 任务函数
////                (const char *)"CPU_task",               // 任务名称
////                (uint16_t)CPU_TASK_STK_SIZE,            // 任务堆栈大小
////                (void *)NULL,                           // 传递给任务函数的参数
////                (UBaseType_t)CPU_TASK_PRIO,             // 任务优先级
////                (TaskHandle_t *)&User_Tasks[CPU_TASK]); // 任务句柄
//#endif // DEBUG_MODE_FREERTOS
//#endif // TEST_TASK_ON

//    xCreatedEventGroup = xEventGroupCreate(); // 创建任务组

//    vTaskDelete(StartTask_Handler); // 删除开始任务
//    taskEXIT_CRITICAL();            // 退出临界区
//}

///**
// * @brief 创建初始化任务
// * @param[in] void
// */
//void startTask(void)
//{
//    xTaskCreate((TaskFunction_t)start_task,          // 任务函数
//                (const char *)"start_task",          // 任务名称
//                (uint16_t)START_TASK_STK_SIZE,       // 任务堆栈大小
//                (void *)NULL,                        // 传递给任务函数的参数
//                (UBaseType_t)START_TASK_PRIO,        // 任务优先级
//                (TaskHandle_t *)&StartTask_Handler); // 任务句柄
//}
