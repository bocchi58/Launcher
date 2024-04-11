#include "main.h"
#include "tim.h"

#include "servoMiddleware.h"


/* @brief:inition
 * @param[in]:
 * @param[out]:
 */
void servo_PWM_init( TIM_HandleTypeDef* htim )
{
	HAL_TIM_PWM_Start( htim,TIM_CHANNEL_3 );
}	


/* @brief:change CCR
 * @param[in]:
 * @param[out]:
 */
void servo_CCR_set( uint16_t num )
{
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, num);
}
 
 
