#ifndef __DC_MOTOR_H
#define __DC_MOTOR_H
#include "BSP_H.h"
void dc_motor_on(int16_t speedL,int16_t speedR);
void dc_motorL_brake(void);
void dc_motorR_brake(void);

#endif
