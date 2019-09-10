
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
extern int mode_12_A_point,mode_12_B_point,mode_12_C_point,mode_12_D_point;  //ֻ��������ĸ����Ӧ��1.��������9 ����


int Aim[9][4]={																															/*******************/
	{204, 13 ,1370,1300 },{215, 111 ,1370,1320 },{213, 204 ,1370,1320},       /*	1		  2		 3	 */
	{113, 8  ,1350,1310 },{116, 112 ,1350,1320 },{119, 213 ,1320,1320},				/*	4			5		 6	 */
	{13 , 20 ,1290,1290 },{13 , 116 ,1293,1310 },{23 , 210 ,1292,1320}   			/*	7			8		 9	 */
};																																					/*******************/
		

//�����л�����
__IO int mode=0;
void switch_mode(int mmode)
{
	mode = mmode;
	mode_CNT = 0;  			//���Լ�ʱ �����л������еĲ�ͬ������
	mode_13_TIME = 0;		//����13 ��Բ�Ŀ��Ʊ���
	mode_12_A=0;mode_12_B=0;mode_12_C=0;mode_12_D=0;  //����12 �л����Ƶ�
	mode_12_A_point=111;mode_12_B_point=111;mode_12_C_point=111;mode_12_D_point=111;  //����A B C D �ĵ�
	printf("mode = %d\n", mode);
}

//�������ķ��Ӳ������õ��ĸ��������
void mode_12_switch(int A, int B, int C, int D)
{
	mode_12_A_point = A;
	mode_12_B_point = B;
	mode_12_C_point = C;
	mode_12_D_point = D;
	printf("%d -> %d -> %d-> %d \n" ,A,B,C,D);
}
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main ( void )
{
	
	/*CRC��emWinû�й�ϵ��ֻ������Ϊ�˿�ı��������ģ�����STemWin�Ŀ�ֻ������ST��оƬ���棬���оƬ���޷�ʹ�õġ� */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);  
	
	/* ��ʼ��GUI */
	GUI_Init();	

	//��ʼ������
	uart_init(115200);	
	
	//������ʼ����ʹ�ô������������Ϣ��Ϊȷ���������ȳ�ʼ�������ٳ�ʼ������
	GTP_Init_Panel();
	 
	/* ��ʼ����ʱ�� */
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
//		printf("%d\n",mode);          //�����ͬ������mode��ͬ��mode
//		printf("A=%d    ",set_a1);		//set_a1�Ƿ���2 A��������OK���ֵ��set_a�Ǹ������Ͼͱ��ֵ��B C D ͬ��
//		printf("B=%d    ",set_b1);		//Һ�����Ʒ��ز�����xxxx yyyy ��GUIDEMO_Start.c��1211��
//		printf("C=%d    ",set_c1);		//��440,210��   (225,210)    (10,210)    
//		printf("D=%d    ",set_d1);		// (440,425)    (225,425)		 (10,425)
	}																	// (440,640)		(225,640)			(10,640)
}																		//ÿ�������215





/*********************************************END OF FILE**********************/

