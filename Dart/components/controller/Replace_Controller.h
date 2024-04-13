#ifndef _REPLACE_CONTROLLER
#define _REPLACE_CONTROLLER

/* includes */
#include "struct_typedef.h"
#include "remoteMiddleware.h"
#include "pid.h"
#include "user_lib.h"
#include "RMotors_Controller.h"


/* define */


/* Function */
void replace_motors_PID_Filter_init(void);
void replace_motors_control(replace_pid_control_t* replace_motor_controller,fp32 setpoint);


#endif 
