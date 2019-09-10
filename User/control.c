#include "control.h"
#include "pid.h"
#include "GUI.h"
#include "math.h"
#include "usart.h"


extern PIDTypedef PID_Struct;
extern u8 openmv[7];
extern int	Aim[9][4];
int mode_CNT = 0;

int mode_12_A,mode_12_B,mode_12_C,mode_12_D=0; //用来控制依次设置 A，B，C，D，
int mode_12_A_point,mode_12_B_point,mode_12_C_point,mode_12_D_point=111; //用来设置 A，B，C，D，

int mode_13_TIME = 0;
int mode_14_LAST_X = 116;
int mode_14_LAST_Y = 112;


//控制小球停留在区域2不少于5s
void mode_1(void)
{	
	PID_Struct.Kp = 6.6;
	PID_Struct.Kd = 100;
	PID_Struct.Set_X = Aim[1][0];
	PID_Struct.Set_Y = Aim[1][1];
	PID_Struct.PWM_X_Middle = Aim[1][2];
	PID_Struct.PWM_Y_Middle = Aim[1][3];
}

//15s内控制小球从区域1进入区域5停留不少于2s
void mode_2(void)
{
	PID_Struct.Kp = 6.6;
	PID_Struct.Kd = 100;
	
	if(mode_CNT < 4)        //小于4s
	{
		PID_Struct.Set_X = Aim[0][0];
		PID_Struct.Set_Y = Aim[0][1];
		PID_Struct.PWM_X_Middle = Aim[0][2];
		PID_Struct.PWM_Y_Middle = Aim[0][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT >=4)
	{
		PID_Struct.Set_X = Aim[4][0];
		PID_Struct.Set_Y = Aim[4][1];
		PID_Struct.PWM_X_Middle = Aim[4][2];
		PID_Struct.PWM_Y_Middle = Aim[4][3];
	}
}

// 1->4 ->5 停留2s 总时间不超过20s
void mode_3(void)
{
	PID_Struct.Kp = 6.6;
	PID_Struct.Kd = 100;
	
	if(mode_CNT<4)
	{
		PID_Struct.Set_X = Aim[0][0];
		PID_Struct.Set_Y = Aim[0][1];
		PID_Struct.PWM_X_Middle = Aim[0][2];
		PID_Struct.PWM_Y_Middle = Aim[0][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if( mode_CNT>=4 && mode_CNT<8)
	{
		PID_Struct.Set_X = Aim[3][0];
		PID_Struct.Set_Y = Aim[3][1];
		PID_Struct.PWM_X_Middle = Aim[3][2];
		PID_Struct.PWM_Y_Middle = Aim[3][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT>=8)
	{
		PID_Struct.Kp = 6.6;
		PID_Struct.Kd = 120;
		PID_Struct.Set_X = Aim[4][0];
		PID_Struct.Set_Y = Aim[4][1];
		PID_Struct.PWM_X_Middle = Aim[4][2];
		PID_Struct.PWM_Y_Middle = Aim[4][3];
	}
}

//30s 1->9
void mode_4(void)
{
	PID_Struct.Kp = 6.6;
	PID_Struct.Kd = 100;
	
	if(mode_CNT<4)
	{
		PID_Struct.Set_X = Aim[0][0];
		PID_Struct.Set_Y = Aim[0][1];
		PID_Struct.PWM_X_Middle = Aim[0][2];
		PID_Struct.PWM_Y_Middle = Aim[0][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT>=4)
	{
		PID_Struct.Set_X = Aim[8][0];
		PID_Struct.Set_Y = Aim[8][1];
		PID_Struct.PWM_X_Middle = Aim[8][2];
		PID_Struct.PWM_Y_Middle = Aim[8][3];
	}
}

//40s  1->2 ->6 ->9 
void mode_11(void)
{
	PID_Struct.Kp = 6.6;
	PID_Struct.Kd = 100;
	
	if(mode_CNT<4)
	{
		PID_Struct.Set_X = Aim[0][0];
		PID_Struct.Set_Y = Aim[0][1];
		PID_Struct.PWM_X_Middle = Aim[0][2];
		PID_Struct.PWM_Y_Middle = Aim[0][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT>=4 && mode_CNT<8)
	{
		PID_Struct.Set_X = Aim[1][0];
		PID_Struct.Set_Y = Aim[1][1];
		PID_Struct.PWM_X_Middle = Aim[1][2];
		PID_Struct.PWM_Y_Middle = Aim[1][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT>=8 && mode_CNT<12)
	{
		PID_Struct.Set_X = Aim[5][0];
		PID_Struct.Set_Y = Aim[5][1];
		PID_Struct.PWM_X_Middle = Aim[5][2];
		PID_Struct.PWM_Y_Middle = Aim[5][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT>=12)
	{
		PID_Struct.Set_X = Aim[8][0];
		PID_Struct.Set_Y = Aim[8][1];
		PID_Struct.PWM_X_Middle = Aim[8][2];
		PID_Struct.PWM_Y_Middle = Aim[8][3];
	}
}

//40s  A->B->C->D  
void mode_12(void)
{
		PID_Struct.Kp = 6.6;
		PID_Struct.Kd = 100;
	if(mode_12_A ==0 && mode_12_A_point!=111)
	{ 
		mode_12_A=1;
	}
	else if(mode_12_A==1 && mode_12_B==0 && mode_12_B_point!=111)
	{ 
		mode_12_B=1; 
	}
	else if(mode_12_B==1 && mode_12_C==0 && mode_12_C_point!=111)
	{  
		mode_12_C=1; 
	}
	else if(mode_12_C==1 && mode_12_D==0 && mode_12_D_point!=111)
	{ 
		mode_12_D=1; 
	}
	
	if(mode_12_A==1 && mode_12_B==1 && mode_12_C==1 && mode_12_D==1 && mode_CNT<4)
	{
		PID_Struct.Set_X = Aim[mode_12_A_point-1][0];
		PID_Struct.Set_Y = Aim[mode_12_A_point-1][1];
		PID_Struct.PWM_X_Middle = Aim[mode_12_A_point-1][2];
		PID_Struct.PWM_Y_Middle = Aim[mode_12_A_point-1][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_12_A==1 && mode_12_B==1 && mode_12_C==1 && mode_12_D==1 && mode_CNT>=4 && mode_CNT<8)
	{
		PID_Struct.Set_X = Aim[mode_12_B_point-1][0];
		PID_Struct.Set_Y = Aim[mode_12_B_point-1][1];
		PID_Struct.PWM_X_Middle = Aim[mode_12_B_point-1][2];
		PID_Struct.PWM_Y_Middle = Aim[mode_12_B_point-1][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_12_A==1 && mode_12_B==1 && mode_12_C==1 && mode_12_D==1 && mode_CNT>=8 && mode_CNT<12)
	{
		PID_Struct.Set_X = Aim[mode_12_C_point-1][0];
		PID_Struct.Set_Y = Aim[mode_12_C_point-1][1];
		PID_Struct.PWM_X_Middle = Aim[mode_12_C_point-1][2];
		PID_Struct.PWM_Y_Middle = Aim[mode_12_C_point-1][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_12_A==1 && mode_12_B==1 && mode_12_C==1 && mode_12_D==1 && mode_CNT>=12 )
	{
		PID_Struct.Set_X = Aim[mode_12_D_point-1][0];
		PID_Struct.Set_Y = Aim[mode_12_D_point-1][1];
		PID_Struct.PWM_X_Middle = Aim[mode_12_D_point-1][2];
		PID_Struct.PWM_Y_Middle = Aim[mode_12_D_point-1][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else 
	{
		PID_Struct.Set_X = Aim[1][0];
		PID_Struct.Set_Y = Aim[1][1];
		PID_Struct.PWM_X_Middle = Aim[1][2];
		PID_Struct.PWM_Y_Middle = Aim[1][3];
	}
}

//4_>> 5做圆周运动
void mode_13(void)
{
	PID_Struct.Kp = 6.6;
	PID_Struct.Kd = 100;
	
	if(mode_CNT<5)
	{	
		PID_Struct.Set_X = Aim[3][0] ;
		PID_Struct.Set_Y = Aim[3][1] ;
		PID_Struct.PWM_X_Middle = Aim[3][2];
		PID_Struct.PWM_Y_Middle = Aim[3][3];
		GUI_Delay(1000);
		mode_CNT++;
	}
	else if(mode_CNT>=5 && mode_13_TIME<280)
	{
		PID_Struct.Set_X = Aim[4][0] + 65*sin(mode_13_TIME/10 +3.4);
		PID_Struct.Set_Y = Aim[4][1] + 65*cos(mode_13_TIME/10 +3.4);
		GUI_Delay(50);
		mode_13_TIME++;
	}
	else if(mode_CNT>=5 && mode_13_TIME>=280)
	{
		PID_Struct.Set_X = Aim[8][0] ;
		PID_Struct.Set_Y = Aim[8][1] ;
		PID_Struct.PWM_X_Middle = Aim[8][2];
		PID_Struct.PWM_Y_Middle = Aim[8][3];
	}

}

//激光随动
void mode_14(void)
{
		PID_Struct.Kp = 5.6;
		PID_Struct.Kd = 100;
	
	if(openmv[4]!=0 && openmv[5]!=0)
	{
		PID_Struct.Set_X = openmv[4];
		PID_Struct.Set_Y = openmv[5];
		mode_14_LAST_X = openmv[4];
		mode_14_LAST_Y = openmv[5];
	}
	else if(openmv[4]==0 && openmv[5]==0)
	{
		PID_Struct.Set_X = mode_14_LAST_X;
		PID_Struct.Set_Y = mode_14_LAST_Y;
	}
}




