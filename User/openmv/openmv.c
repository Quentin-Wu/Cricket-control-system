/****************

usart3

PB(10)  P5
PB(11)	P4

openmv[2] 小球x坐标
openmv[3] 小球y坐标

openmv[4] 激光x坐标
openmv[5] 激光y坐标


******************/


#include	"openmv.h"
#include "usart.h"	
#include "pid.h"

u8 openmv[7]={0};

void uart3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,ENABLE);//使能USART3时钟
	
		//串口3对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3   TX P5
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3   RX	P4
	
	
		//USART3端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10与GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB10，PB11
	
	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口3
	
  USART_Cmd(USART3, ENABLE);  //使能串口3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口3中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

}

void USART3_IRQHandler(void)
{
	static u8 data = 0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
	{		
		data = USART_ReceiveData(USART3);
		Openmv_Receive_Data(data);
	}
}	


void Openmv_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 state = 0;	
	static u8 bit_number=0;	
	if(state==0&&data==0xAD)	//第一位校验位0xAD
	{
		state=1;
		openmv[bit_number++]=data;
	}
	else if(state==1&&data==18)		//第二位校验位18
	{
		state=2;
		openmv[bit_number++]=data;
	}
	else if(state==2)		
	{
		openmv[bit_number++]=data;
		if(bit_number>=6)
		{
			state=3;
		}
	}
	else if(state==3)		//检测是否接受到结束标志
	{
		if(data == 0x5B)	//最后一位终止位0x5B
		{
					state = 0;
					openmv[bit_number++]=data;
					PID_realize();
		}
		else if(data != 0x5B)
		{
				 state = 0;
					bit_number=0;						
		}
	}    
	else
	{
		state = 0;
		bit_number=0;
	}
}





