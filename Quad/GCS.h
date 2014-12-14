#include "ch.h"
#include "hal.h"
#include "mavlink.h"
					  
void setup_Mavlink(void);
void send_statustext(uint8_t severity, const char *text);
void send_laptime(uint32_t time, uint8_t racenumber, uint8_t racetrack, uint8_t lapnumber);
void send_race_status(uint8_t raceStarted, uint8_t raceCountdown);