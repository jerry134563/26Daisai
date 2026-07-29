#ifndef __LINE_FOLLOWER_H
#define __LINE_FOLLOWER_H

#include "main.h"
#include "BSP_H.h"
#define black 1
#define white 0
#define tracking_num_8
#ifdef tracking_num_8

enum tracking1
{
    track_left1,track_left2,track_left3,track_left4,track_right4,track_right3,track_right2,track_right1
};

#endif 


#ifdef tracking_num_5

enum tracking2
{
    track_left1 = 3,track_left2,track_center,track_right2,track_right1
};

#endif 

uint8_t*read_Line_state(void);

#endif
