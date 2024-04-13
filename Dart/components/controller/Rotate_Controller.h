#ifndef _ROTATE_CONTROLLER
#define _ROTATE_CONTROLLER

/* includes */
#include "struct_typedef.h"
#include "remoteMiddleware.h"
#include "pid.h"
#include "user_lib.h"
#include "RMotors_Controller.h"


/* define */


/* Function */
void rotate_motors_PID_Filter_init(void);
void rotate_motors_control(rotate_pid_control_t* rotate_motor_controller,fp32 setpoint);


#endif 
