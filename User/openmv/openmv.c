/****************

usart3

PB(10)  P5
PB(11)	P4

openmv[2] С��x����
openmv[3] С��y����

openmv[4] ����x����
openmv[5] ����y����


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

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,ENABLE);//ʹ��USART3ʱ��
	
		//����3��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3   TX P5
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3   RX	P4
	
	
		//USART3�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11
	
	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

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


void Openmv_Receive_Data(int16_t data)//����Openmv������������
{
	static u8 state = 0;	
	static u8 bit_number=0;	
	if(state==0&&data==0xAD)	//��һλУ��λ0xAD
	{
		state=1;
		openmv[bit_number++]=data;
	}
	else if(state==1&&data==18)		//�ڶ�λУ��λ18
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
	else if(state==3)		//����Ƿ���ܵ�������־
	{
		if(data == 0x5B)	//���һλ��ֹλ0x5B
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





