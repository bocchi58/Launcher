#include "main.h"
#include "usart.h"
#include "stm32f4xx_hal_uart.h"

#include "remoteMiddleware.h"


#define RX_USART_BUFFER 18U

uint8_t usart_rxbuffer[RX_USART_BUFFER];

RC_Ctl_t RC_Ctl;


static void DR16_process(volatile unsigned char rx_buffer[]);


/* @brief:cInit
 * @param[in]:
 * @param[out]:
 */
uint8_t DR16_DataInit(void)
{
	HAL_UART_Receive_DMA(&huart3, usart_rxbuffer, RX_USART_BUFFER);
	HAL_Delay(100);
	return 0;
}
/* @brief:callback
 * @param[in]:
 * @param[out]:
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		
	if (huart->Instance == USART3) {
		/* 暂时没有想到合适的校验方法 */
		HAL_UART_DMAStop(huart);

		// 处理数据
		DR16_process(usart_rxbuffer);

		// 重新启动DMA接收
		HAL_UART_Receive_DMA(huart, usart_rxbuffer, RX_USART_BUFFER);
	}

}
/* @brief:处理函数
 * @param[in]:
 * @param[out]:
 */
static void DR16_process(volatile unsigned char rx_buffer[])
{
	RC_Ctl.rc.ch0 = (rx_buffer[0] | (rx_buffer[1] << 8)) & 0x07ff;								 //!< Channel 0
	RC_Ctl.rc.ch1 = ((rx_buffer[1] >> 3) | (rx_buffer[2] << 5)) & 0x07ff;						 //!< Channel 1
	RC_Ctl.rc.ch2 = ((rx_buffer[2] >> 6) | (rx_buffer[3] << 2) | (rx_buffer[4] << 10)) & 0x07ff; //!< Channel 2
	RC_Ctl.rc.ch3 = ((rx_buffer[4] >> 1) | (rx_buffer[5] << 7)) & 0x07ff;						 //!< Channel 3
	RC_Ctl.rc.s1 = ((rx_buffer[5] >> 4) & 0x0003);												 //!< Switch left
	RC_Ctl.rc.s2 = ((rx_buffer[5] >> 6) & 0x0003);
	RC_Ctl.mouse.x = rx_buffer[6] | (rx_buffer[7] << 8);   //!< Mouse X axis
	RC_Ctl.mouse.y = rx_buffer[8] | (rx_buffer[9] << 8);   //!< Mouse Y axis
	RC_Ctl.mouse.z = rx_buffer[10] | (rx_buffer[11] << 8); //!< Mouse Z axis
	RC_Ctl.mouse.press_l = rx_buffer[12];				   //!< Mouse Left Is Press ?
	RC_Ctl.mouse.press_r = rx_buffer[13];				   //!< Mouse Right Is Press ?
	RC_Ctl.key.w = rx_buffer[14] & 0x01;				   // KeyBoard value
	RC_Ctl.key.s = (rx_buffer[14] >> 1) & 0x01;
	RC_Ctl.key.a = (rx_buffer[14] >> 2) & 0x01;
	RC_Ctl.key.d = (rx_buffer[14] >> 3) & 0x01;
	RC_Ctl.key.shift = (rx_buffer[14] >> 4) & 0x01;
	RC_Ctl.key.ctrl = (rx_buffer[14] >> 5) & 0x01;
	RC_Ctl.key.q = (rx_buffer[14] >> 6) & 0x01;
	RC_Ctl.key.e = (rx_buffer[14] >> 7) & 0x01;
	RC_Ctl.key.r = (rx_buffer[15]) & 0x01;
	RC_Ctl.key.f = (rx_buffer[15] >> 1) & 0x01;
	RC_Ctl.key.g = (rx_buffer[15] >> 2) & 0x01;
	RC_Ctl.key.z = (rx_buffer[15] >> 3) & 0x01;
	RC_Ctl.key.x = (rx_buffer[15] >> 4) & 0x01;
	RC_Ctl.key.c = (rx_buffer[15] >> 5) & 0x01;
	RC_Ctl.key.v = (rx_buffer[15] >> 6) & 0x01;
	RC_Ctl.key.b = (rx_buffer[15] >> 7) & 0x01;
	if ((RC_Ctl.rc.ch0 - 1024 < 20) && (RC_Ctl.rc.ch0 - 1024 > -20))
		RC_Ctl.rc.ch0 = 1024;
	if ((RC_Ctl.rc.ch1 - 1024 < 20) && (RC_Ctl.rc.ch1 - 1024 > -20))
		RC_Ctl.rc.ch1 = 1024;
	if ((RC_Ctl.rc.ch2 - 1024 < 20) && (RC_Ctl.rc.ch2 - 1024 > -20))
		RC_Ctl.rc.ch2 = 1024;
	if ((RC_Ctl.rc.ch3 - 1024 < 20) && (RC_Ctl.rc.ch3 - 1024 > -20))
		RC_Ctl.rc.ch3 = 1024;

}
