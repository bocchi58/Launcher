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

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "controller_task.h"
#include "main.h"
#include "can.h"
#include "cmsis_os.h"
#include "RMotors_Controller.h"


extern rmotor_control_t MotorsController;

/**
  * @brief          电机控制任务
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
 
void Controller_task(void const * argument)
{
		motors_PID_Filter_init();
		MotorController_combine();
    while(1)
    {
		motors_Controller();		
        osDelay(4);//250HZ
    }
}
