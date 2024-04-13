#ifndef _CHARGE_CONTROLLER
#define _CHARGE_CONTROLLER

/* includes */
#include "struct_typedef.h"
#include "remoteMiddleware.h"
#include "pid.h"
#include "user_lib.h"
#include "RMotors_Controller.h"

/* define */


/* Function */
void charger_motors_PID_Filter_init(void);
void charge_motors_control(charge_pid_control_t* charge_motor_controller,fp32 setpoint);


#endif 
