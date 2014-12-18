
#include "ch.h"
#include "hal.h"


#define MAX_LAPS 255

void init_Racecontrol(void); 


void rx_channel1_interrupt(EXTDriver *extp, expchannel_t channel);
void rx_channel2_interrupt(EXTDriver *extp, expchannel_t channel);
void rx_channel3_interrupt(EXTDriver *extp, expchannel_t channel);
void rx_channel4_interrupt(EXTDriver *extp, expchannel_t channel);

void button_interrupt(EXTDriver *extp, expchannel_t channel);
void startRace(uint8_t racenumber);
void stopRace(uint8_t racenumber);
bool getRaceStartedOrStarting(void);
