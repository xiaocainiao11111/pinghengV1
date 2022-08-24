#ifndef __CONTROL_H 
#define __CONTROL_H 
#include "sys.h" 

int Vertical(float Med,float Angle,float gyro_x);
int Velocity(int encoder_motor);
int Turn(int gyro_Z);
void EXTI9_5_IRQHandler(void);
#endif

