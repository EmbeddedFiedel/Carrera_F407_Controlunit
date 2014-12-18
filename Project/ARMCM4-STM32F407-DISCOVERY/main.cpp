/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "lis302dl.h"
#include "chprintf.h"
#include "Racecontrol.h"
#include "ExternalInterrupt.h"
#include "GCS.h"
#include "flash.h"


bool ledToggle = 0;
/*
 * Application entry point.
 */
int main(void) 
{
	/*
	* System initializations.
	* - HAL initialization, this also initializes the configured device drivers
	*   and performs the board-specific initializations.
	* - Kernel initialization, the main() function becomes a thread and the
	*   RTOS is active.
	*/
	halInit();	   
	chSysInit();
	setup_FLASH();
	setup_ExternalInterrupt();
	setup_Mavlink();
	init_Racecontrol();
	//setup_Motoren();

	//send_statustext(MAV_SEVERITY_ALERT, "Initialization finished");
		palClearPad(GPIOD, GPIOD_LED5);
		palClearPad(GPIOD, GPIOD_LED3);
		palClearPad(GPIOD, GPIOD_LED4);
		palClearPad(GPIOD, GPIOD_LED6);
	
		palSetPad(GPIOE, GPIOE_Start_LED1);
		palSetPad(GPIOE, GPIOE_Start_LED2);
		palSetPad(GPIOE, GPIOE_Start_LED3);
		palSetPad(GPIOE, GPIOE_Start_LED4);
		palSetPad(GPIOE, GPIOE_Start_LED5);
		ledToggle = true;
		
	while (TRUE) 
	{
// 		//update_IMU();
// 		palSetPad(GPIOD, GPIOD_LED3);
// 		chThdSleepMilliseconds(200);
		
			if(!getRaceStartedOrStarting())
			{
				if(ledToggle == true)
				{
					palClearPad(GPIOE, GPIOE_Start_LED1);
					palClearPad(GPIOE, GPIOE_Start_LED2);
					palClearPad(GPIOE, GPIOE_Start_LED3);
					palClearPad(GPIOE, GPIOE_Start_LED4);
					palClearPad(GPIOE, GPIOE_Start_LED5);
					ledToggle = false;
				}
				else
				{
					palSetPad(GPIOE, GPIOE_Start_LED1);
					palSetPad(GPIOE, GPIOE_Start_LED2);
					palSetPad(GPIOE, GPIOE_Start_LED3);
					palSetPad(GPIOE, GPIOE_Start_LED4);
					palSetPad(GPIOE, GPIOE_Start_LED5);	
					ledToggle = true;
				}
			}// 		}
// 		chThdSleepMilliseconds(200);

// 		//if(get_rc_calibration_ready())
// 		{
// 			palSetPad(GPIOD, GPIOD_LED6);
// 		}
// 		chThdSleepMilliseconds(200);

// 		//if(get_datalog_ready())
// 		{
// 			palSetPad(GPIOD, GPIOD_LED5);
// 		}
// 		chThdSleepMilliseconds(500);

// 		palClearPad(GPIOD, GPIOD_LED5);
// 		palClearPad(GPIOD, GPIOD_LED3);
// 		palClearPad(GPIOD, GPIOD_LED4);
// 		palClearPad(GPIOD, GPIOD_LED6);
		chThdSleepMilliseconds(1000);
  }
}


