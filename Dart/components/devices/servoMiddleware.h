#ifndef SERVO_MIDDLEWARE_H
#define SERVO_MIDDLEWARE_H


#include "struct_typedef.h"
#include "stm32f4xx_hal_tim.h"


void servo_PWM_init( TIM_HandleTypeDef* htim );
void servo_CCR_set( uint16_t num );


#endif
