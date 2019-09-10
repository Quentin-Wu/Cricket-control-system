
#include "stm32f4xx.h"
#include "GUI.h"
#include "usart.h"	
#include "./lcd/bsp_ili9806g_lcd.h"
#include "./systick/bsp_SysTick.h"
#include "./touch/gt5xx.h"
#include "GUIDEMO.h"
#include "pwm.h"
#include "openmv.h"
#include "pid.h"
#include "control.h"


extern __IO u8 set_a1;
extern __IO u8 set_b1;
extern __IO u8 set_c1;
extern __IO u8 set_d1;


extern PIDTypedef PID_Struct;
extern u8 openmv[7];
extern int mode_CNT, mode_13_TIME;

extern int mode_12_A,mode_12_B,mode_12_C,mode_12_D;
extern int mode_12_A_point,mode_12_B_point,mode_12_C_point,mode_12_D_point;  //只需更改这四个点对应的1.。。。。9 即可


int Aim[9][4]={																															/*******************/
	{204, 13 ,1370,1300 },{215, 111 ,1370,1320 },{213, 204 ,1370,1320},       /*	1		  2		 3	 */
	{113, 8  ,1350,1310 },{116, 112 ,1350,1320 },{119, 213 ,1320,1320},				/*	4			5		 6	 */
	{13 , 20 ,1290,1290 },{13 , 116 ,1293,1310 },{23 , 210 ,1292,1320}   			/*	7			8		 9	 */
};																																					/*******************/
		

//用来切换任务
__IO int mode=0;
void switch_mode(int mmode)
{
	mode = mmode;
	mode_CNT = 0;  			//粗略计时 用以切换任务中的不同子任务
	mode_13_TIME = 0;		//任务13 画圆的控制变量
	mode_12_A=0;mode_12_B=0;mode_12_C=0;mode_12_D=0;  //任务12 切换控制点
	mode_12_A_point=111;mode_12_B_point=111;mode_12_C_point=111;mode_12_D_point=111;  //控制A B C D 的点
	printf("mode = %d\n", mode);
}

//用来更改发挥部分设置的四个点的坐标
void mode_12_switch(int A, int B, int C, int D)
{
	mode_12_A_point = A;
	mode_12_B_point = B;
	mode_12_C_point = C;
	mode_12_D_point = D;
	printf("%d -> %d -> %d-> %d \n" ,A,B,C,D);
}
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main ( void )
{
	
	/*CRC和emWin没有关系，只是他们为了库的保护而做的，这样STemWin的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);  
	
	/* 初始化GUI */
	GUI_Init();	

	//初始化串口
	uart_init(115200);	
	
	//触摸初始化有使用串口输出调试信息，为确保正常，先初始化串口再初始化触摸
	GTP_Init_Panel();
	 
	/* 初始化定时器 */
	SysTick_Init();

	MainTask();
	 while(1)
	{

		switch(mode)
		{
			case 1: mode_1();  break;
			case 2: mode_2();  break;
			case 3: mode_3();  break;
			case 4: mode_4();  break;
			case 5: mode_11(); break;
			case 6: mode_12(); break;
			case 7: mode_13(); break;
			case 8: mode_14(); break;
			default:					 break;
		}
		GUI_Delay(100); 
//		printf("%d\n",mode);          //点击不同的任务mode不同的mode
//		printf("A=%d    ",set_a1);		//set_a1是发挥2 A设置完点击OK后的值，set_a是改了马上就变得值，B C D 同理
//		printf("B=%d    ",set_b1);		//液晶控制返回参数是xxxx yyyy 在GUIDEMO_Start.c的1211行
//		printf("C=%d    ",set_c1);		//（440,210）   (225,210)    (10,210)    
//		printf("D=%d    ",set_d1);		// (440,425)    (225,425)		 (10,425)
	}																	// (440,640)		(225,640)			(10,640)
}																		//每个点相聚215





/*********************************************END OF FILE**********************/

