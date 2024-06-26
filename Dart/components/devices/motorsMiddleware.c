#include "main.h"
#include "can.h"

#include "motorsMiddleware.h"


RMotor_t charge_motor_receive[2];// 0:左 1:右
RMotor_t rotate_motor_receive;
RMotor_t replace_motor_receive;

/**
 * @brief:		motor canfilter init
 * @param[in]:
 * @param[out]:
 */
void motor_can_filter_init(CAN_HandleTypeDef* hcan_1)
{
		CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
    can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
    can_filter_st.FilterIdHigh = 0x0201<<5;
    can_filter_st.FilterIdLow = 0x0203<<5;
    can_filter_st.FilterMaskIdHigh = 0x0000<<5;
    can_filter_st.FilterMaskIdLow = 0x0000<<5;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
		HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY); 
	
}
/**
 * @brief:		can回调函数
 * @param[in]:
 * @param[out]:
 */
static uint16_t replaceFirstPos;
static uint8_t 	replaceFirstPosFLAG;//过零检测标志位
static uint16_t rotateFirstPos;
static uint8_t 	rotateFirstPosFLAG;//过零检测标志位

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t rx_data[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, rx_data) == HAL_OK)
    {
			// 在这里处理接收到的消息
			__HAL_CAN_CLEAR_FLAG(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
			if (hcan->Instance == CAN1)
			{
				switch (RxHeader.StdId){
					case 0x201:
						charge_motor_receive[0].angle_inst				= 	((float)((rx_data[0]<<8) | rx_data[1])) * ENCODE2ANGLE ;
						charge_motor_receive[0].speed_inst				=   ((rx_data[2]<<8)| rx_data[3]);
						charge_motor_receive[0].cur_temp          		=    (rx_data[4]<<8) | rx_data[5];
						charge_motor_receive[0].current_inst			=    charge_motor_receive[0].cur_temp*CURRENT_DEVIED_100;
					break;
					
					case 0x203:
						charge_motor_receive[1].angle_inst				= 	((float)((rx_data[0]<<8) | rx_data[1])) * ENCODE2ANGLE ;
						charge_motor_receive[1].speed_inst				=   ((rx_data[2]<<8)| rx_data[3]);
						charge_motor_receive[1].cur_temp      			=    (rx_data[4]<<8) | rx_data[5];
						charge_motor_receive[1].current_inst			=    charge_motor_receive[1].cur_temp*CURRENT_DEVIED_100;					
					break;
					
					case 0x205://旋转装置
						rotate_motor_receive.angle_inst					=	((float)((rx_data[0]<<8) | rx_data[1])) * ENCODE2ANGLE ;
						rotate_motor_receive.speed_inst					=	((rx_data[2]<<8)| rx_data[3]);
						rotate_motor_receive.cur_temp					=	(rx_data[4]<<8) | rx_data[5];
						rotate_motor_receive.current_inst				=	rotate_motor_receive.cur_temp*CURRENT_DEVIED_100;
						rotate_motor_receive.real_speed = (float)rotate_motor_receive.speed_inst*9.549296585513720f;//rad/s
						if( !rotateFirstPosFLAG ){
							rotateFirstPos = rotate_motor_receive.angle_inst;
							rotateFirstPosFLAG = 1;
						}
						if( (rotate_motor_receive.angle_inst - rotate_motor_receive.last_angle)<-0.7*ENCODE_MAX_2006 )//待修改
							rotate_motor_receive.cycle_cnt++;
						else if( (rotate_motor_receive.angle_inst - rotate_motor_receive.last_angle)>+0.7*ENCODE_MAX_2006 )
							rotate_motor_receive.cycle_cnt--;
							rotate_motor_receive.real_posion = (ENCODE_MAX_2006*rotate_motor_receive.cycle_cnt+rotate_motor_receive.angle_inst - rotateFirstPos)*2.1307889781398236807760844444984e-6f;//rad
							rotate_motor_receive.last_angle = rotate_motor_receive.angle_inst;
						
				}
			}else if(hcan -> Instance == CAN2)
			{
				switch (RxHeader.StdId){
					case 0x201://丝杆
						replace_motor_receive.angle_inst				=	((float)((rx_data[0]<<8) | rx_data[1])) * ENCODE2ANGLE ;
						replace_motor_receive.speed_inst				=	((rx_data[2]<<8)| rx_data[3]);
						replace_motor_receive.cur_temp					=	(rx_data[4]<<8) | rx_data[5];
						replace_motor_receive.current_inst				=	rotate_motor_receive.cur_temp*CURRENT_DEVIED_100;
						replace_motor_receive.real_speed = (float)replace_motor_receive.speed_inst*9.549296585513720f;//rad/s
						if( !replaceFirstPosFLAG ){
							replaceFirstPos = replace_motor_receive.angle_inst;
							replaceFirstPosFLAG = 1;
						}
						if( (replace_motor_receive.angle_inst - replace_motor_receive.last_angle)<-0.7*ENCODE_MAX_2006 )
							replace_motor_receive.cycle_cnt++;
						else if( (replace_motor_receive.angle_inst - replace_motor_receive.last_angle)>+0.7*ENCODE_MAX_2006 )
							replace_motor_receive.cycle_cnt--;
							replace_motor_receive.real_posion = (ENCODE_MAX_2006*replace_motor_receive.cycle_cnt+replace_motor_receive.angle_inst - replaceFirstPos)*2.1307889781398236807760844444984e-6f;//rad
							replace_motor_receive.last_angle = replace_motor_receive.angle_inst;
				}
			}
    }	
}
/**
 * @brief:		motors can send 
 * @param[in]: 	3508 ID:200 201~204 ID:1FF 205~208
 *				6020 ID:1FF 201~204 ID:2FF 205~207
 * @param[out]:
 */
void _Motor_ID_Cansend(int a, int b, int c, int d,int ID,CAN_HandleTypeDef *hcan)
{
	
		static CAN_TxHeaderTypeDef TxHeader;
		static uint32_t TxMailbox;
		static uint8_t tx_buffer[8];
	
		TxHeader.RTR = CAN_RTR_DATA; // 数据帧
		TxHeader.IDE = CAN_ID_STD;   // 标准标识符
		TxHeader.DLC = 8;        // 数据长度为8位
		TxHeader.TransmitGlobalTime = DISABLE; // 根据需要启用或禁用	
		TxHeader.StdId = ID;  // 标准ID
	//TxHeader.ExtId = 0x01;   // 扩展ID，如果使用
	
	//限幅
    a = LIMIT_MAX_MIN(a, 15000, -15000);
    b = LIMIT_MAX_MIN(b, 15000, -15000);
    c = LIMIT_MAX_MIN(c, 15000, -15000);
    d = LIMIT_MAX_MIN(d, 15000, -15000);
	
    tx_buffer[0] = (unsigned char)((a >> 8) & 0xff);
    tx_buffer[1] = (unsigned char)(a & 0xff);  
    tx_buffer[2] = (unsigned char)((b >> 8) & 0xff);
    tx_buffer[3] = (unsigned char)(b & 0xff);
    tx_buffer[4] = (unsigned char)((c >> 8) & 0xff);
    tx_buffer[5] = (unsigned char)(c & 0xff);
    tx_buffer[6] = (unsigned char)((d >> 8) & 0xff); 
    tx_buffer[7] = (unsigned char)(d & 0xff);
		
		if (HAL_CAN_AddTxMessage(hcan, &TxHeader, tx_buffer, &TxMailbox) != HAL_OK)
		{
			// 发送失败处理
			Error_Handler();
		}		
}

		
