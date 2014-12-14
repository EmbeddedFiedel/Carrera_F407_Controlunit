#include "ExternalInterrupt.h"
#include "Racecontrol.h"
#include "ch.h"
#include "hal.h"


static const EXTConfig extcfg = {
	{
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, button_interrupt},			//JR
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, rx_channel1_interrupt},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART, rx_channel2_interrupt},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
	},
	EXT_MODE_EXTI(EXT_MODE_GPIOA, 				/* 0 */						//JR
	              0, 				/* 1 */
	              0,			 	/* 2 */
	              0, 				/* 3 */
	              0, 				/* 4 */
	              0, 				/* 5 */
	              0, 				/* 6 */
	              0, 				/* 7 */
	              0, 				/* 8 */
	              0, 				/* 9 */
	              EXT_MODE_GPIOE, 			/* 10 */
	              EXT_MODE_GPIOE, 			/* 11 */
	              EXT_MODE_GPIOE, 			/* 12 */
	              EXT_MODE_GPIOE, 			/* 13 */
	              0, 				/* 14 */
	              0) 				/* 15 */
};



void setup_ExternalInterrupt()
{
	extStart(&EXTD1, &extcfg); 
}
