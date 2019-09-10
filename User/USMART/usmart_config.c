#include "usmart.h"
#include "usmart_str.h"
////////////////////////////用户配置区///////////////////////////////////////////////
//这下面要包含所用到的函数所申明的头文件(用户自己添加) 
#include "delay.h"		
#include "pwm.h"
#include "pid.h"

extern void switch_mode(int mmode);
extern void mode_12_switch(int A, int B, int C, int D);
//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//如果使能了读写操作
//	(void*)read_addr,"u32 read_addr(u32 addr)",
//	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	 
//	(void*)TIM_SetCompare1,"void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1)",
		(void*)TIM_X_Set, "void TIM_X_Set(uint16_t Compare1)",
		(void*)TIM_Y_Set, "void TIM_Y_Set(uint16_t Compare1)",
		(void*)Set_Xpoint,"void Set_Xpoint(int xpoint)",
		(void*)Set_Ypoint,"void Set_Ypoint(int ypoint)",
		(void*)Set_Kp,		"void Set_Kp(float kpp)",
		(void*)Set_Kd,		"void Set_Kd(float kdd)",
		(void*)switch_mode,"void switch_mode(int mmode)",
		(void*)mode_12_switch, "void mode_12_switch(int A, int B, int C, int D)",
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//函数控制管理器初始化
//得到各个受控函数的名字
//得到函数总数量
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//函数数量
	0,	  	//参数数量
	0,	 	//函数ID
	1,		//参数显示类型,0,10进制;1,16进制
	0,		//参数类型.bitx:,0,数字;1,字符串	    
	0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
	0,		//函数的参数,需要PARM_LEN个0初始化
};   



















