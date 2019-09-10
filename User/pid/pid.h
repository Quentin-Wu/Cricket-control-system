#ifndef __PID_H
#define __PID_H

#include "stm32f4xx.h"

typedef struct
{
	int Set_X;
	int Set_Y;
		
	float Kp;
	float Ki;
	float Kd;
	
	float X_Ek;
	float X_Ek1;
	float Y_Ek;
	float Y_Ek1;
	
	int PWM_X;
	int PWM_Y;
	
	int PWM_X_Middle; //舵机中值
	int PWM_Y_Middle; //舵机中值
	
}PIDTypedef;


void PID_realize (void);

void PID_Init(void);
void Set_Xpoint(int xpoint);
void Set_Ypoint(int ypoint);
void Set_Kp(float kpp);
void Set_Kd(float kdd);



#endif







