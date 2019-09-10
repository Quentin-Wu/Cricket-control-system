#include "pwm.h"
#include "pid.h"
#include "openmv.h"
#include "usart.h"	
#include "math.h"


float warebuf[8];
extern u8 openmv[7];

PIDTypedef PID_Struct;


void PID_Init(void)
{
	PID_Struct.Set_X = 0;
	PID_Struct.Set_Y = 0;
	
	PID_Struct.Kp = 0;
	PID_Struct.Kd = 0;
	PID_Struct.Ki = 0;
	
	PID_Struct.X_Ek	= 0;
	PID_Struct.X_Ek1 = 0;
	PID_Struct.Y_Ek = 0;
	PID_Struct.Y_Ek1 = 0;
	
	PID_Struct.PWM_X = PID_Struct.PWM_X_Middle;
	PID_Struct.PWM_Y = PID_Struct.PWM_Y_Middle;
}

void Set_Xpoint(int xpoint)
{
	PID_Struct.Set_X = xpoint;
	printf("Set_X = %d\n",PID_Struct.Set_X);
}

void Set_Ypoint(int ypoint)
{
	PID_Struct.Set_Y = ypoint;
	printf("Set_Y = %d\n",PID_Struct.Set_Y);
}

void Set_Kp(float kpp)
{
	PID_Struct.Kp = kpp;
	printf("Kp = %f\n", PID_Struct.Kp);
}

void Set_Kd(float kdd)
{
	PID_Struct.Kd = kdd;
	printf("Kd = %f\n", PID_Struct.Kd);
}



void PID_realize(void)
{	  
	if(openmv[2]==0 && openmv[3]==0) 
	{	
		PID_Struct.PWM_X = PID_Struct.PWM_X_Middle;
		PID_Struct.PWM_Y = PID_Struct.PWM_Y_Middle;
	}
	
	else
	{	
		PID_Struct.X_Ek = openmv[2]-PID_Struct.Set_X;	//小球x坐标
		PID_Struct.Y_Ek = PID_Struct.Set_Y-openmv[3];	//小球y坐标
				
		
		PID_Struct.PWM_X = PID_Struct.Kp*PID_Struct.X_Ek +PID_Struct.Kd*(PID_Struct.X_Ek-PID_Struct.X_Ek1) + PID_Struct.PWM_X_Middle;
		PID_Struct.PWM_Y = PID_Struct.Kp*PID_Struct.Y_Ek +PID_Struct.Kd*(PID_Struct.Y_Ek-PID_Struct.Y_Ek1) + PID_Struct.PWM_Y_Middle;
		
		PID_Struct.X_Ek1 = PID_Struct.X_Ek;
		PID_Struct.Y_Ek1 = PID_Struct.Y_Ek;
		
		if(fabs(PID_Struct.X_Ek)<3) PID_Struct.PWM_X=PID_Struct.PWM_X_Middle;
		if(fabs(PID_Struct.Y_Ek)<3) PID_Struct.PWM_Y=PID_Struct.PWM_Y_Middle;	
		
		if(PID_Struct.PWM_X>2000)		PID_Struct.PWM_X=2000;
		if(PID_Struct.PWM_X<700)		PID_Struct.PWM_X=700;
		
		if(PID_Struct.PWM_Y>2000)		PID_Struct.PWM_Y=2000;
		if(PID_Struct.PWM_Y<700)		PID_Struct.PWM_Y=700;
	}
	
		TIM_SetCompare1(TIM14,PID_Struct.PWM_X);	 //更新PWM参数，改变输出占空比
		TIM_SetCompare1(TIM13,PID_Struct.PWM_Y);
	
		warebuf[0] = PID_Struct.PWM_X;
		warebuf[1] = PID_Struct.PWM_Y;
		warebuf[2] = openmv[2];
		warebuf[3] = openmv[3];
		vcan_sendware((uint8_t *)warebuf, sizeof(warebuf));
}



















