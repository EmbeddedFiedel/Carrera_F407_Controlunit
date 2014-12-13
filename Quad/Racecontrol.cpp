/*
This file is part of Quadrocopter_F407_MPU6050 project.

TrunetCopter program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Racecontrol.h"
#include "chprintf.h"
#include "GCS.h"
#include "Flash.h"

uint8_t raceCountdown = 5;

bool firstLap_1 = true;
uint16_t lapCounter_1 = 0;
uint32_t lapTimes_1[MAX_LAPS];

bool firstLap_2 = true;
uint16_t lapCounter_2= 0;
uint32_t lapTimes_2[MAX_LAPS];

bool race_started = false;

static TimeMeasurement TimeMonitor1;
static struct VirtualTimer raceStartTimer;

bool greenLightToggle = false;

void race_start_timer_handler(void *arg)
{
	if(raceCountdown == 5)
	{
		palClearPad(GPIOD, GPIOD_LED3);
		raceCountdown--;
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
	}
	else if(raceCountdown == 4)
	{
		palClearPad(GPIOD, GPIOD_LED4);
		raceCountdown--;
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
	}
	else if(raceCountdown == 3)
	{
		palClearPad(GPIOD, GPIOD_LED6);
		raceCountdown--;
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
	}
	else if(raceCountdown == 2)
	{
		palClearPad(GPIOD, GPIOD_LED5);
		raceCountdown--;
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
	}
	else if(raceCountdown == 1)
	{
		
		raceCountdown--;
		chVTSetI(&raceStartTimer, MS2ST(1), race_start_timer_handler, 0);
	}
	else if(raceCountdown == 0)
	{
		race_started = true;
		if (greenLightToggle == true)
		{
			palClearPad(GPIOD, GPIOD_LED4);
			greenLightToggle=false;
		}
		else
		{
			palSetPad(GPIOD, GPIOD_LED4);
			greenLightToggle = true;
		}
		chVTSetI(&raceStartTimer, MS2ST(100), race_start_timer_handler, 0);
	}
	
}


/*
 *  _____       _                             _
 * |_   _|     | |                           | |
 *   | |  _ __ | |_ ___ _ __ _ __ _   _ _ __ | |_ ___
 *   | | | '_ \| __/ _ \ '__| '__| | | | '_ \| __/ __|
 *  _| |_| | | | ||  __/ |  | |  | |_| | |_) | |_\__ \
 * |_____|_| |_|\__\___|_|  |_|   \__,_| .__/ \__|___/
 *                                     | |
 *                                     |_|
 */




void rx_channel1_interrupt(EXTDriver *extp, expchannel_t channel) {
		(void)extp;
		(void)channel;
		chSysLockFromIsr();
		if (race_started == true)
		{
			if (firstLap_1 == true)
			{
				firstLap_1 = false;
			}	
			else
			{
				tmStopMeasurement(&TimeMonitor1);
				lapTimes_1[lapCounter_1] = RTT2US(TimeMonitor1.last);
				tmStartMeasurement(&TimeMonitor1);
				lapCounter_1++;
			}
		}
		else
		{
			//Fehlstart Handling tbd.
		}
		chSysUnlockFromIsr();
}

void rx_channel2_interrupt(EXTDriver *extp, expchannel_t channel) {
		(void)extp;
		(void)channel;
		  
}


void button_interrupt(EXTDriver *extp, expchannel_t channel)
{
	if(race_started==false)
	{
		raceCountdown = 5;
		palSetPad(GPIOD, GPIOD_LED5);
		palSetPad(GPIOD, GPIOD_LED3);
		palSetPad(GPIOD, GPIOD_LED4);
		palSetPad(GPIOD, GPIOD_LED6);
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
		
		firstLap_1 = true;
		firstLap_2 = true;
		lapCounter_1 = 0;
		lapCounter_2 = 0;
		for (uint16_t i = 0; i < MAX_LAPS; i++)
		{
			lapTimes_1[i]=0;
			lapTimes_2[i]=0;
		}
	}
	else
	{
		race_started = false;
		palClearPad(GPIOD, GPIOD_LED5);
		palClearPad(GPIOD, GPIOD_LED3);
		palClearPad(GPIOD, GPIOD_LED4);
		palClearPad(GPIOD, GPIOD_LED6);
	}
	
}

void init_Racecontrol(void)
{
	
}
