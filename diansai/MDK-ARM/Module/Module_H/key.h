#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "BSP_H.h"

#include "stdbool.h"



#define KEY_NUMBER					4

struct keys
{
	uint8_t key_judge;
	uint8_t double_judge;
	bool key_flag;
	bool short_flag;
	bool long_flag;
	bool double_flag;
	uint16_t key_time;
	uint16_t double_time;
};

extern volatile struct keys key[KEY_NUMBER]; 

void key_scan(void);	
void KEY_Interupt_10ms_Scan(void);

#endif



