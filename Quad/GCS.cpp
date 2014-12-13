#include "GCS.h"
#include "Racecontrol.h"
#include "flash.h"


 
mavlink_system_t mavlink_system;
struct global_struct global_data;
bool request_new_sd_log = false;

void read_param_from_eeprom()
{
	uint16_t i;
	for (i=0;i<number_flash_parameter;i++)	// dann alle Kalibrationswerte lesen
	{
		global_data.param[i]=EE_read_Float(VirtAddVarTab[i+offset_flash_parameter],VirtAddVarTab[i+offset_flash_parameter]+1);
	}
}
void write_param_to_eeprom()
{
	uint16_t i;
	for (i=0;i<number_flash_parameter;i++)	// dann alle Kalibrationswerte lesen
	{
		EE_write_Float(VirtAddVarTab[i+offset_flash_parameter],VirtAddVarTab[i+offset_flash_parameter]+1,global_data.param[i]);
	}
}


/**
 * @brief reset all parameters to default
 * @warning DO NOT USE THIS IN FLIGHT!
 */
static inline void global_data_reset_param_defaults(void)
{
	int offset_Param = 0;

	global_data.param[0] = 20;
	strcpy(global_data.param_name[0+offset_Param], "Rundenzahl");
	
	global_data.param[1+offset_Param] = 0;
	strcpy(global_data.param_name[1+offset_Param], "Rennstrecke");
} 

uint16_t m_parameter_i = 0;

/**
* @brief Send low-priority messages at a maximum rate of xx Hertz
*
* This function sends messages at a lower rate to not exceed the wireless
* bandwidth. It sends one message each time it is called until the buffer is empty.
* Call this function with xx Hertz to increase/decrease the bandwidth.
*/
static void communication_queued_send(void)
{
	//send parameters one by one
	if (m_parameter_i < ONBOARD_PARAM_COUNT)
	{
   // Initialize the required buffers
		mavlink_message_t msg;
		uint8_t buf[MAVLINK_MAX_PACKET_LEN];
		mavlink_msg_param_value_pack(mavlink_system.sysid, mavlink_system.compid, &msg,(char*) global_data.param_name[m_parameter_i],
				         global_data.param[m_parameter_i], MAVLINK_TYPE_FLOAT,
                                         ONBOARD_PARAM_COUNT, m_parameter_i);
		// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    
	// Send the message with the standard UART send function
	sdWrite(&SD2, buf, len);
	//uartStartSend(&UARTD2, len, buf);
		m_parameter_i++;
	}
}

/*
 * Working area for MavlinkHeartbeatThread
 */
static WORKING_AREA(MavlinkParamlistThreadWorkingArea, 2048);
/*
 * MavlinkHeartbeatThread
 */

static msg_t MavlinkParamlistThread(void *arg)
{
    while (TRUE)
    {
		communication_queued_send();
		chThdSleepMilliseconds(3);
    }
}
uint8_t buf[MAVLINK_MAX_PACKET_LEN];
void send_heartbeat(void)
{
	// Define the system type, in this case an airplane
	uint8_t system_type = MAV_TYPE_QUADROTOR;
	uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;
	 
	uint8_t system_mode = MAV_MODE_PREFLIGHT; ///< Booting up
	uint32_t custom_mode = 0;                 ///< Custom mode, can be defined by user/adopter
	uint8_t system_state = MAV_STATE_ACTIVE; ///< System ready for flight
	 
	// Initialize the required buffers
	mavlink_message_t msg;
	
	 
	// Pack the message
	mavlink_msg_heartbeat_pack(mavlink_system.sysid, mavlink_system.compid, &msg, system_type, autopilot_type, system_mode, custom_mode, system_state);
	 
	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    
	// Send the message with the standard UART send function
	sdWrite(&SD2, buf, len);
	//uartStartSend(&UARTD2, len, buf);
}

/*
 * Working area for MavlinkHeartbeatThread
 */
static WORKING_AREA(MavlinkHeartbeatThreadWorkingArea, 2048);
/*
 * MavlinkHeartbeatThread
 */

static msg_t MavlinkHeartbeatThread(void *arg) 
{
  while (TRUE) 
  {
		send_heartbeat();	 
		chThdSleepMilliseconds(100);
  }
}


char c;
uint16_t c_global;
uint16_t debug_param;
uint16_t debug_cmd;
static WORKING_AREA(waThreadRadio, 4096);
static msg_t ThreadRadio(void *arg) 
{
    (void)arg;
    chRegSetThreadName("radio");
	
	
	mavlink_message_t msg;
	mavlink_status_t status;

    EventListener elRadio;
    chEvtRegister(chIOGetEventSource(&SD2), &elRadio, 1);
    while (TRUE) 
			{
        ioflags_t flags;
        chEvtWaitOneTimeout(EVENT_MASK(1), TIME_INFINITE);
        flags = chIOGetAndClearFlags(&SD2);
        if (flags & IO_INPUT_AVAILABLE) 
				{

          c = chIOGetTimeout(&SD2, TIME_IMMEDIATE);
					if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status))
					{
							if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT)
							{
								//Heartbeat
							}
							
							else if (msg.msgid == MAVLINK_MSG_ID_COMMAND_LONG)
							{
								// Preflight Calibration
								debug_cmd = mavlink_msg_command_long_get_command(&msg);
								if (mavlink_msg_command_long_get_command(&msg) == MAV_CMD_PREFLIGHT_CALIBRATION)
								{
										if (mavlink_msg_command_long_get_param4(&msg) == 1)
										{
											//start_calib();
										}
										else if (mavlink_msg_command_long_get_param4(&msg) == 0)
										{
											//stop_calib();
										}
								}
								if (mavlink_msg_command_long_get_command(&msg) == MAV_CMD_PREFLIGHT_STORAGE)
								{
									debug_param = mavlink_msg_command_long_get_param1(&msg);
									if (mavlink_msg_command_long_get_param1(&msg) == 0)
										{
											read_param_from_eeprom();
										}
										else if (mavlink_msg_command_long_get_param1(&msg) == 1)
										{
											write_param_to_eeprom();
										}
								}
							}
							
							else if (msg.msgid == MAVLINK_MSG_ID_PARAM_REQUEST_LIST)
							{
								// Start sending parameters
								m_parameter_i = 0;
							}
							else if (msg.msgid == MAVLINK_MSG_ID_PARAM_SET)
							{
								mavlink_param_set_t set;
								mavlink_msg_param_set_decode(&msg, &set);
								{
									char* key = (char*) set.param_id;
						 
									for (uint16_t i = 0; i < ONBOARD_PARAM_COUNT; i++)
									{
										bool match = true;
										for (uint16_t j = 0; j < ONBOARD_PARAM_NAME_LENGTH; j++)
										{
											// Compare
											if (((char) (global_data.param_name[i][j]))
													!= (char) (key[j]))
											{
												match = false;
											}
										}
						 
										// Check if matched
										if (match)
										{
											{
												global_data.param[i] = set.param_value;
												
												
												// Initialize the required buffers
												mavlink_message_t msg;
												uint8_t buf[MAVLINK_MAX_PACKET_LEN];
												mavlink_msg_param_value_pack(mavlink_system.sysid, mavlink_system.compid, &msg,(char*) global_data.param_name[i], global_data.param[i], MAVLINK_TYPE_FLOAT, ONBOARD_PARAM_COUNT, m_parameter_i);
												// Copy the message to the send buffer
												uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

												// Send the message with the standard UART send function
												sdWrite(&SD2, buf, len);
												//uartStartSend(&UARTD2, len, buf);	 
												request_new_sd_log = true;

											}
										}
									}
								}
							}
					}
					////////////////////////////ECHO//////////////////////////////
					//uint8_t buf[1];
					//buf[0] = c;
					//uint16_t len = 1;
					//sdWrite(&SD2, buf, len);
					/////////////////////////////////////////////////////////////////
        }
    }
}


void send_statustext(uint8_t severity, const char *text)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	mavlink_msg_statustext_pack(mavlink_system.sysid, mavlink_system.compid, &msg, severity, text);
	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    
	// Send the message with the standard UART send function
	sdWrite(&SD2, buf, len);
	//uartStartSend(&UARTD2, len, buf);
}


void setup_Mavlink(void)
{
		global_data_reset_param_defaults();
	
		/*
		* Activates the serial driver 2 using the driver default configuration.
		* PA2(TX) and PA3(RX) are routed to USART2.
		*/
		sdStart(&SD2, NULL);
		//uartStart(&UARTD2, &uart_cfg_1);
		palSetPadMode(GPIOD, 5, PAL_MODE_ALTERNATE(7));
		palSetPadMode(GPIOD, 6, PAL_MODE_ALTERNATE(7));
	
		mavlink_system.sysid = 1;                   ///< ID 1 for this airplane
		mavlink_system.compid = MAV_COMP_ID_ALL;     ///< The component sending the message is the IMU, it could be also a Linux process

		chThdCreateStatic(waThreadRadio, sizeof(waThreadRadio), ABSPRIO, ThreadRadio, NULL);
	chThdSleepMilliseconds(20);
		chThdCreateStatic(MavlinkHeartbeatThreadWorkingArea, sizeof(MavlinkHeartbeatThreadWorkingArea), NORMALPRIO, MavlinkHeartbeatThread, NULL);
}



