#ifndef __Parametors__
#define __Parametors__

#define MAIN_FREQ 2000  // Hz
#define PERIOD_US (int)((1.0f / MAIN_FREQ) * 1000000)

#define MAIN_SEND_FREQ 1000  // Hz
#define MAIN_SEND_PERIOD_US (int)((1.0f / MAIN_SEND_FREQ) * 1000000)
#define CAM_SEND_FREQ 1000  // Hz
#define CAM_SEND_PERIOD_US (int)((1.0f / CAM_SEND_FREQ) * 1000000)

#endif