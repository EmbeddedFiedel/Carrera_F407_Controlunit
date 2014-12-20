#include "GCS.h"
#include "Racecontrol.h"
#include "flash.h"


 
mavlink_system_t mavlink_system;

uint8_t buf[MAVLINK_MAX_PACKET_LEN];
void send_heartbeat(void)
{
	// Initialize the required buffers
	mavlink_message_t msg;
	
	 
	// Pack the message
	mavlink_msg_heartbeat_pack(1,0,&msg,0);
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
		chThdSleepMilliseconds(1000);
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
							else if (msg.msgid == MAVLINK_MSG_ID_RACE_SETUP)
							{
								uint8_t i = 0;
								i++;
							}
							else if (msg.msgid == MAVLINK_MSG_ID_RACE_START)
							{
								startRace(0);
							}
							else if (msg.msgid == MAVLINK_MSG_ID_RACE_STOP)
							{
								stopRace(0);
							}
							else if (msg.msgid == MAVLINK_MSG_ID_LAP)
							{
								mavlink_lap_t lap_msg;
                mavlink_msg_lap_decode(&msg, &lap_msg);
								resendLapTime(lap_msg.racetrack,lap_msg.lapNumber);
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
void send_laptime(uint32_t time, uint8_t racenumber, uint8_t racetrack, uint8_t lapnumber)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	mavlink_msg_lap_pack(1,0,&msg,0,racenumber,racetrack,lapnumber, time);
	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    
	// Send the message with the standard UART send function
	sdWrite(&SD2, buf, len);
	//uartStartSend(&UARTD2, len, buf);
}
void send_race_status(uint8_t raceStarted, uint8_t raceCountdown)
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	mavlink_msg_race_status_pack(1,0,&msg,0,raceStarted, raceCountdown);
	// Copy the message to the send buffer
	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    
	// Send the message with the standard UART send function
	sdWrite(&SD2, buf, len);
	//uartStartSend(&UARTD2, len, buf);
}

void setup_Mavlink(void)
{
		/*
		* Activates the serial driver 2 using the driver default configuration.
		* PA2(TX) and PA3(RX) are routed to USART2.
		*/
		sdStart(&SD2, NULL);
		//uartStart(&UARTD2, &uart_cfg_1);
		palSetPadMode(GPIOD, 5, PAL_MODE_ALTERNATE(7));
		palSetPadMode(GPIOD, 6, PAL_MODE_ALTERNATE(7));
	
		mavlink_system.sysid = 0;                   ///< ID 1 for this airplane
		mavlink_system.compid = 0;     ///< The component sending the message is the IMU, it could be also a Linux process

		chThdCreateStatic(waThreadRadio, sizeof(waThreadRadio), ABSPRIO, ThreadRadio, NULL);
	chThdSleepMilliseconds(20);
		chThdCreateStatic(MavlinkHeartbeatThreadWorkingArea, sizeof(MavlinkHeartbeatThreadWorkingArea), NORMALPRIO, MavlinkHeartbeatThread, NULL);
}



