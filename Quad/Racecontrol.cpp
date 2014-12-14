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
uint8_t currentRaceNumber = 0;

bool firstLap_1 = true;
uint16_t lapCounter_1 = 0;
uint32_t lapTimes_1[MAX_LAPS];
uint32_t lastLapTime1 =0;

bool firstLap_2 = true;
uint16_t lapCounter_2= 0;
uint32_t lapTimes_2[MAX_LAPS];
uint32_t lastLapTime2 =0;

bool race_starting = false;
bool race_started = false;

//static TimeMeasurement TimeMonitor1;
//static TimeMeasurement TimeMonitor2;
static struct VirtualTimer raceStartTimer;

/*
 * GPT2 callback.
 *      Every time the timer fires send a new sample to the output port
 */
uint32_t ms_count = 0;
static void gpt2_callback(GPTDriver *gptp)
{
    /* counter to waste some time...  */
	ms_count++;
}
	

/*
 * GPT2 configuration.
 *   This configuration block defines a time with a 200kHz counting clock,
 *   and our callback function named sample_output_callback.  When we start
 *   the timer we will specify the numbers of clock ticks we want to elapse
 *   between callback execution.
 *
 *   NOTE:  Be sure the execution of the callback is done before calling it
 *            again.  Otherwise, strange things may happen....
 *          Generally, you will want to define the callback function above
 *            this or the compiler will complain about it being undefined.
 */
static GPTConfig gpt2cfg =
{
    100000,                    /* timer clock.*/
    gpt2_callback     				/* Timer callback.*/
};


bool greenLightToggle = false;

void race_start_timer_handler(void *arg)
{
	if(race_starting == true)
	{
		if(raceCountdown == 5)
		{
			palClearPad(GPIOD, GPIOD_LED3);
			raceCountdown--;
			send_race_status(race_started, raceCountdown);
			chSysLockFromIsr();
			chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
			chSysUnlockFromIsr();
		}
		else if(raceCountdown == 4)
		{
			palClearPad(GPIOD, GPIOD_LED4);
			raceCountdown--;
			send_race_status(race_started, raceCountdown);
			chSysLockFromIsr();
			chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
			chSysUnlockFromIsr();
		}
		else if(raceCountdown == 3)
		{
			palClearPad(GPIOD, GPIOD_LED6);
			raceCountdown--;
			send_race_status(race_started, raceCountdown);
			chSysLockFromIsr();
			chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
			chSysUnlockFromIsr();
		}
		else if(raceCountdown == 2)
		{
			palClearPad(GPIOD, GPIOD_LED5);
			raceCountdown--;
			send_race_status(race_started, raceCountdown);
			chSysLockFromIsr();
			chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
			chSysUnlockFromIsr();
		}
		else if(raceCountdown == 1)
		{
			raceCountdown--;
			send_race_status(race_started, raceCountdown);
			chSysLockFromIsr();
			chVTSetI(&raceStartTimer, MS2ST(1500), race_start_timer_handler, 0);
			chSysUnlockFromIsr();
		}
		else if(raceCountdown == 0)
		{
			if(race_started !=true)
			{
				lastLapTime1 =ms_count;
				lastLapTime2 =ms_count;
				race_started = true;
			}
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
			send_race_status(race_started, raceCountdown);
			chSysLockFromIsr();
			chVTSetI(&raceStartTimer, MS2ST(100), race_start_timer_handler, 0);
			chSysUnlockFromIsr();
		}
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
				chSysUnlockFromIsr();
			}	
			else
			{
				lapTimes_1[lapCounter_1] = ms_count-lastLapTime1;
				lastLapTime1 = ms_count;
				lapCounter_1++;
				chSysUnlockFromIsr();
				send_laptime(lapTimes_1[lapCounter_1-1],0,1,lapCounter_1);
			}
			
		}
		else
		{
			chSysUnlockFromIsr();
			//Fehlstart Handling tbd.
		}
		
}

void rx_channel2_interrupt(EXTDriver *extp, expchannel_t channel) {
		(void)extp;
		(void)channel;
		 	chSysLockFromIsr();
		if (race_started == true)
		{
			if (firstLap_2 == true)
			{
				firstLap_2 = false;
				chSysUnlockFromIsr();
			}	
			else
			{
				lapTimes_2[lapCounter_2] = ms_count-lastLapTime2;
				lastLapTime2 = ms_count;
				lapCounter_2++;
				chSysUnlockFromIsr();
				send_laptime(lapTimes_2[lapCounter_2-1],0,2,lapCounter_2);
			}
		}
		else
		{
			chSysUnlockFromIsr(); 
			//Fehlstart Handling tbd.
		}
		
}


void button_interrupt(EXTDriver *extp, expchannel_t channel)
{
	if(race_started==false && race_starting == false)
	{
		raceCountdown = 5;
		race_starting = true;
		palSetPad(GPIOD, GPIOD_LED5);
		palSetPad(GPIOD, GPIOD_LED3);
		palSetPad(GPIOD, GPIOD_LED4);
		palSetPad(GPIOD, GPIOD_LED6);
		chSysLock();
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
		chSysUnlock();
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
	/*
	else
	{
		race_started = false;
		race_starting = false;
		palClearPad(GPIOD, GPIOD_LED5);
		palClearPad(GPIOD, GPIOD_LED3);
		palClearPad(GPIOD, GPIOD_LED4);
		palClearPad(GPIOD, GPIOD_LED6);
	}
	*/
	
}
void startRace(uint8_t racenumber)
{
	currentRaceNumber = racenumber;
	if(race_started==false && race_starting == false)
	{
		raceCountdown = 5;
		send_race_status(race_started, raceCountdown);
		race_starting = true;
		palSetPad(GPIOD, GPIOD_LED5);
		palSetPad(GPIOD, GPIOD_LED3);
		palSetPad(GPIOD, GPIOD_LED4);
		palSetPad(GPIOD, GPIOD_LED6);
		chSysLock();
		chVTSetI(&raceStartTimer, MS2ST(1000), race_start_timer_handler, 0);
		chSysUnlock();
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
}

void stopRace(uint8_t racenumber)
{
	race_started=false;
	race_starting = false;
	raceCountdown = 5;
}
/*
 * Working area for MavlinkHeartbeatThread
 */
static WORKING_AREA(MavlinkRaceStatusThreadWorkingArea, 2048);
/*
 * MavlinkHeartbeatThread
 */

static msg_t MavlinkRaceStatusThread(void *arg) 
{
  while (TRUE) 
  {
		send_race_status(race_started, raceCountdown);
		chThdSleepMilliseconds(100);
  }
}

void init_Racecontrol(void)
{
	  // configure the GPT timer
    gptStart(&GPTD2, &gpt2cfg);
			// start the GPT in continuous mode.  dT is the time between triggers
    //   Here, we have set the timer clock to 200,000Hz, and we want
    //   to call the callback function every 25 GPT clock cycles.  This
    //   means we call the callback function every 125uS or 8,000 time
    //   per second
    gptStartContinuous(&GPTD2, 100); // dT = 100,000 / 100 = 1,000Hz
	chThdCreateStatic(MavlinkRaceStatusThreadWorkingArea, sizeof(MavlinkRaceStatusThreadWorkingArea), NORMALPRIO, MavlinkRaceStatusThread, NULL);
}
