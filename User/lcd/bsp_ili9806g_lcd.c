/**
  ******************************************************************************
  * @file    bsp_ili9806g_lcd.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ILI9806GҺ��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./lcd/bsp_ili9806g_lcd.h"
#include "./font/fonts.h"	

//����Һ��ɨ�跽����仯��XY���ؿ���
//����ILI9806G_GramScan�������÷���ʱ���Զ�����
uint16_t LCD_X_LENGTH = ILI9806G_MORE_PIXEL;
uint16_t LCD_Y_LENGTH = ILI9806G_LESS_PIXEL;

//Һ����ɨ��ģʽ����������Ҫ���ڷ���ѡ�������ļ������
//������ѡֵΪ0-7
//����ILI9806G_GramScan�������÷���ʱ���Զ�����
//LCD�ճ�ʼ�����ʱ��ʹ�ñ�Ĭ��ֵ
uint8_t LCD_SCAN_MODE =6;


static sFONT *LCD_Currentfonts = &Font16x32;  //Ӣ������
static uint16_t CurrentTextColor   = WHITE;//ǰ��ɫ
static uint16_t CurrentBackColor   = BLACK;//����ɫ

__inline void                 ILI9806G_Write_Cmd           ( uint16_t usCmd );
__inline void                 ILI9806G_Write_Data          ( uint16_t usData );
__inline uint16_t             ILI9806G_Read_Data           ( void );
static void                   ILI9806G_Delay               ( __IO uint32_t nCount );
static void                   ILI9806G_GPIO_Config         ( void );
static void                   ILI9806G_FSMC_Config         ( void );
static void                   ILI9806G_REG_Config          ( void );
static void                   ILI9806G_SetCursor           ( uint16_t usX, uint16_t usY );
static __inline void          ILI9806G_FillColor           ( uint32_t ulAmout_Point, uint16_t usColor );
static uint16_t               ILI9806G_Read_PixelData      ( void );


/**
  * @brief  ����ʱ����
  * @param  nCount ����ʱ����ֵ
  * @retval ��
  */	
static void Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}

/**
  * @brief  ��ILI9806Gд������
  * @param  usCmd :Ҫд���������Ĵ�����ַ��
  * @retval ��
  */	
__inline void ILI9806G_Write_Cmd ( uint16_t usCmd )
{
	* ( __IO uint16_t * ) ( FSMC_Addr_ILI9806G_CMD ) = usCmd;
	
}


/**
  * @brief  ��ILI9806Gд������
  * @param  usData :Ҫд�������
  * @retval ��
  */	
__inline void ILI9806G_Write_Data ( uint16_t usData )
{
	* ( __IO uint16_t * ) ( FSMC_Addr_ILI9806G_DATA ) = usData;
	
}


/**
  * @brief  ��ILI9806G��ȡ����
  * @param  ��
  * @retval ��ȡ��������
  */	
__inline uint16_t ILI9806G_Read_Data ( void )
{
	return ( * ( __IO uint16_t * ) ( FSMC_Addr_ILI9806G_DATA ) );
	
}


/**
  * @brief  ���� ILI9806G ����ʱ����
  * @param  nCount ����ʱ����ֵ
  * @retval ��
  */	
static void ILI9806G_Delay ( __IO uint32_t nCount )
{
  for ( ; nCount != 0; nCount -- );
	
}


/**
  * @brief  ��ʼ��ILI9806G��IO����
  * @param  ��
  * @retval ��
  */
static void ILI9806G_GPIO_Config ( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ��FSMC��Ӧ��Ӧ�ܽ�ʱ��*/
	RCC_AHB1PeriphClockCmd ( 	
													/*�����ź�*/
													ILI9806G_CS_CLK|ILI9806G_DC_CLK|ILI9806G_WR_CLK|
													ILI9806G_RD_CLK	|ILI9806G_BK_CLK|ILI9806G_RST_CLK|
													/*�����ź�*/
													ILI9806G_D0_CLK|ILI9806G_D1_CLK|	ILI9806G_D2_CLK | 
													ILI9806G_D3_CLK | ILI9806G_D4_CLK|ILI9806G_D5_CLK|
													ILI9806G_D6_CLK | ILI9806G_D7_CLK|ILI9806G_D8_CLK|
													ILI9806G_D9_CLK | ILI9806G_D10_CLK|ILI9806G_D11_CLK|
													ILI9806G_D12_CLK | ILI9806G_D13_CLK|ILI9806G_D14_CLK|
													ILI9806G_D15_CLK	, ENABLE );
		
	
	/* ����FSMC���Ӧ��������,FSMC-D0~D15 */	
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D0_PIN; 
    GPIO_Init(ILI9806G_D0_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D0_PORT,ILI9806G_D0_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D1_PIN; 
    GPIO_Init(ILI9806G_D1_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D1_PORT,ILI9806G_D1_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D2_PIN; 
    GPIO_Init(ILI9806G_D2_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D2_PORT,ILI9806G_D2_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D3_PIN; 
    GPIO_Init(ILI9806G_D3_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D3_PORT,ILI9806G_D3_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D4_PIN; 
    GPIO_Init(ILI9806G_D4_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D4_PORT,ILI9806G_D4_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D5_PIN; 
    GPIO_Init(ILI9806G_D5_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D5_PORT,ILI9806G_D5_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D6_PIN; 
    GPIO_Init(ILI9806G_D6_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D6_PORT,ILI9806G_D6_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D7_PIN; 
    GPIO_Init(ILI9806G_D7_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D7_PORT,ILI9806G_D7_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D8_PIN; 
    GPIO_Init(ILI9806G_D8_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D8_PORT,ILI9806G_D8_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D9_PIN; 
    GPIO_Init(ILI9806G_D9_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D9_PORT,ILI9806G_D9_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D10_PIN; 
    GPIO_Init(ILI9806G_D10_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D10_PORT,ILI9806G_D10_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D11_PIN; 
    GPIO_Init(ILI9806G_D11_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D11_PORT,ILI9806G_D11_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D12_PIN; 
    GPIO_Init(ILI9806G_D12_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D12_PORT,ILI9806G_D12_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D13_PIN; 
    GPIO_Init(ILI9806G_D13_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D13_PORT,ILI9806G_D13_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D14_PIN; 
    GPIO_Init(ILI9806G_D14_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D14_PORT,ILI9806G_D14_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_D15_PIN; 
    GPIO_Init(ILI9806G_D15_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_D15_PORT,ILI9806G_D15_PinSource,FSMC_AF);

	/* ����FSMC���Ӧ�Ŀ�����
	 * FSMC_NOE   :LCD-RD
	 * FSMC_NWE   :LCD-WR
	 * FSMC_NE1   :LCD-CS
	 * FSMC_A0    :LCD-DC
	 */
    GPIO_InitStructure.GPIO_Pin = ILI9806G_RD_PIN; 
    GPIO_Init(ILI9806G_RD_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_RD_PORT,ILI9806G_RD_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_WR_PIN; 
    GPIO_Init(ILI9806G_WR_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_WR_PORT,ILI9806G_WR_PinSource,FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = ILI9806G_CS_PIN; 
    GPIO_Init(ILI9806G_CS_PORT, &GPIO_InitStructure);   
    GPIO_PinAFConfig(ILI9806G_CS_PORT,ILI9806G_CS_PinSource,FSMC_AF);  

    GPIO_InitStructure.GPIO_Pin = ILI9806G_DC_PIN; 
    GPIO_Init(ILI9806G_DC_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(ILI9806G_DC_PORT,ILI9806G_DC_PinSource,FSMC_AF);
	

  /* ����LCD��λRST���ƹܽ�*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = ILI9806G_RST_PIN; 
	GPIO_Init ( ILI9806G_RST_PORT, & GPIO_InitStructure );
		
	/* ����LCD������ƹܽ�BK*/
	GPIO_InitStructure.GPIO_Pin = ILI9806G_BK_PIN; 
	GPIO_Init ( ILI9806G_BK_PORT, & GPIO_InitStructure );

}


 /**
  * @brief  LCD  FSMC ģʽ����
  * @param  ��
  * @retval ��
  */
static void ILI9806G_FSMC_Config ( void )
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 	
	
	/* ʹ��FSMCʱ��*/
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

	//��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK 5/168M=30ns
	readWriteTiming.FSMC_AddressSetupTime      = 0x04;	 //��ַ����ʱ��
	//���ݱ���ʱ�䣨DATAST��+ 1��HCLK = 12/168M=72ns	
	readWriteTiming.FSMC_DataSetupTime         = 0x0b;	 //���ݽ���ʱ��
	//ѡ����Ƶ�ģʽ
	//ģʽB,�첽NOR FLASHģʽ����ILI9806G��8080ʱ��ƥ��
	readWriteTiming.FSMC_AccessMode            = FSMC_AccessMode_B;	
	
	/*����������ģʽB�޹�*/
	//��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
	readWriteTiming.FSMC_AddressHoldTime       = 0x00;	 //��ַ����ʱ��
	//��������ת�����ڣ������ڸ���ģʽ��NOR����
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	//����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��
	readWriteTiming.FSMC_CLKDivision           = 0x00;
	//���ݱ���ʱ�䣬������ͬ���͵�NOR	
	readWriteTiming.FSMC_DataLatency           = 0x00;	

	
	FSMC_NORSRAMInitStructure.FSMC_Bank                  = FSMC_Bank1_NORSRAMx;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType            = FSMC_MemoryType_NOR;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode              = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode          = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &readWriteTiming;  
	
	FSMC_NORSRAMInit ( & FSMC_NORSRAMInitStructure ); 
	
	
	/* ʹ�� FSMC_Bank1_NORSRAM3 */
	FSMC_NORSRAMCmd ( FSMC_Bank1_NORSRAMx, ENABLE );  
		
		
}


/**
 * @brief  ��ʼ��ILI9806G�Ĵ���
 * @param  ��
 * @retval ��
 */
static void ILI9806G_REG_Config ( void )
{
	/* EXTC Command Set enable register */
		DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xFF);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0x98);
	ILI9806G_Write_Data(0x06);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBA);
	ILI9806G_Write_Data(0x60);  
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBC);
	ILI9806G_Write_Data(0x03);
	ILI9806G_Write_Data(0x0E);
	ILI9806G_Write_Data(0x61);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x1B);
	ILI9806G_Write_Data(0x10);
	ILI9806G_Write_Data(0x73);
	ILI9806G_Write_Data(0x63);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0xFF);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0xD5);
	ILI9806G_Write_Data(0xD0);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x40); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBD);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x23);
	ILI9806G_Write_Data(0x45);
	ILI9806G_Write_Data(0x67);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x23);
	ILI9806G_Write_Data(0x45);
	ILI9806G_Write_Data(0x67);  
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xBE);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x2D);
	ILI9806G_Write_Data(0xCB);
	ILI9806G_Write_Data(0xA2);
	ILI9806G_Write_Data(0x62);
	ILI9806G_Write_Data(0xF2);
	ILI9806G_Write_Data(0xE2);
	ILI9806G_Write_Data(0x22);
	ILI9806G_Write_Data(0x22);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xC7);
	ILI9806G_Write_Data(0x63); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xED);
	ILI9806G_Write_Data(0x7F);
	ILI9806G_Write_Data(0x0F);
	ILI9806G_Write_Data(0x00);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xC0);
	ILI9806G_Write_Data(0x03);
	ILI9806G_Write_Data(0x0B);
	ILI9806G_Write_Data(0x00);   
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xFC);
	ILI9806G_Write_Data(0x08); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xDF);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x20);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF3);
	ILI9806G_Write_Data(0x74);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF9);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0xFD);
	ILI9806G_Write_Data(0x80);
	ILI9806G_Write_Data(0x80);
	ILI9806G_Write_Data(0xC0);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xB4);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x02); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF7);
	ILI9806G_Write_Data(0x81);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xB1);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x13);
	ILI9806G_Write_Data(0x13); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xF2);
	ILI9806G_Write_Data(0xC0);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x40);
	ILI9806G_Write_Data(0x28);  
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xC1);
	ILI9806G_Write_Data(0x17);
	ILI9806G_Write_Data(0x75);
	ILI9806G_Write_Data(0x75);
	ILI9806G_Write_Data(0x20); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xE0);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x08);
	ILI9806G_Write_Data(0x0C);
	ILI9806G_Write_Data(0x0F);
	ILI9806G_Write_Data(0x15);
	ILI9806G_Write_Data(0x09);
	ILI9806G_Write_Data(0x07);
	ILI9806G_Write_Data(0x01);
	ILI9806G_Write_Data(0x06);
	ILI9806G_Write_Data(0x09);
	ILI9806G_Write_Data(0x16);
	ILI9806G_Write_Data(0x14);
	ILI9806G_Write_Data(0x3E);
	ILI9806G_Write_Data(0x3E);
	ILI9806G_Write_Data(0x00);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0xE1);
	ILI9806G_Write_Data(0x00);
	ILI9806G_Write_Data(0x09);
	ILI9806G_Write_Data(0x12);
	ILI9806G_Write_Data(0x12);
	ILI9806G_Write_Data(0x13);
	ILI9806G_Write_Data(0x1c);
	ILI9806G_Write_Data(0x07);
	ILI9806G_Write_Data(0x08);
	ILI9806G_Write_Data(0x05);
	ILI9806G_Write_Data(0x08);
	ILI9806G_Write_Data(0x03);
	ILI9806G_Write_Data(0x02);
	ILI9806G_Write_Data(0x04);
	ILI9806G_Write_Data(0x1E);
	ILI9806G_Write_Data(0x1B);
	ILI9806G_Write_Data(0x00);
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0x3A);
	ILI9806G_Write_Data(0x55); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0x35);
	ILI9806G_Write_Data(0x00); 
	DEBUG_DELAY();
	ILI9806G_Write_Cmd(0x11);
	DEBUG_DELAY() ;
	ILI9806G_Write_Cmd(0x29);	   
	DEBUG_DELAY()  ;
	
}


/**
 * @brief  ILI9806G��ʼ�����������Ҫ�õ�lcd��һ��Ҫ�����������
 * @param  ��
 * @retval ��
 */
void ILI9806G_Init ( void )
{
	ILI9806G_GPIO_Config ();
	ILI9806G_FSMC_Config ();
	
	
	ILI9806G_Rst ();
	ILI9806G_REG_Config ();
	
	//����Ĭ��ɨ�跽������ 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����  
	ILI9806G_GramScan(LCD_SCAN_MODE);
    
    ILI9806G_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
    ILI9806G_BackLed_Control ( ENABLE );      //����LCD�����
}


/**
 * @brief  ILI9806G����LED����
 * @param  enumState �������Ƿ�ʹ�ܱ���LED
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg ENABLE :ʹ�ܱ���LED
  *     @arg DISABLE :���ñ���LED
 * @retval ��
 */
void ILI9806G_BackLed_Control ( FunctionalState enumState )
{
	if ( enumState )
		 GPIO_SetBits( ILI9806G_BK_PORT, ILI9806G_BK_PIN );	
	else
		 GPIO_ResetBits( ILI9806G_BK_PORT, ILI9806G_BK_PIN );
		
}



/**
 * @brief  ILI9806G ������λ
 * @param  ��
 * @retval ��
 */
void ILI9806G_Rst ( void )
{			
	GPIO_ResetBits ( ILI9806G_RST_PORT, ILI9806G_RST_PIN );	 //�͵�ƽ��λ

	ILI9806G_Delay ( 0xAFF ); 					   

	GPIO_SetBits ( ILI9806G_RST_PORT, ILI9806G_RST_PIN );		 	 

	ILI9806G_Delay ( 0xAFF ); 	
	
}




/**
 * @brief  ����ILI9806G��GRAM��ɨ�跽�� 
 * @param  ucOption ��ѡ��GRAM��ɨ�跽�� 
 *     @arg 0-7 :������ѡֵΪ0-7��˸�����
 *
 *	����������0��3��5��6 ģʽ�ʺϴ���������ʾ���֣�
 *				���Ƽ�ʹ������ģʽ��ʾ����	����ģʽ��ʾ���ֻ��о���Ч��			
 *		
 *	����0��2��4��6 ģʽ��X��������Ϊ480��Y��������Ϊ854
 *	����1��3��5��7 ģʽ��X��������Ϊ854��Y��������Ϊ480
 *
 *	���� 6 ģʽΪ�󲿷�Һ�����̵�Ĭ����ʾ����
 *	���� 3 ģʽΪ����ͷ����ʹ�õķ���
 *	���� 0 ģʽΪBMPͼƬ��ʾ����ʹ�õķ���
 *
 * @retval ��
 * @note  ����ͼ����A��ʾ���ϣ�V��ʾ���£�<��ʾ����>��ʾ����
					X��ʾX�ᣬY��ʾY��

------------------------------------------------------------
ģʽ0��				.		ģʽ1��		.	ģʽ2��			.	ģʽ3��					
					A		.					A		.		A					.		A									
					|		.					|		.		|					.		|							
					Y		.					X		.		Y					.		X					
					0		.					1		.		2					.		3					
	<--- X0 o		.	<----Y1	o		.		o 2X--->  .		o 3Y--->	
------------------------------------------------------------	
ģʽ4��				.	ģʽ5��			.	ģʽ6��			.	ģʽ7��					
	<--- X4 o		.	<--- Y5 o		.		o 6X--->  .		o 7Y--->	
					4		.					5		.		6					.		7	
					Y		.					X		.		Y					.		X						
					|		.					|		.		|					.		|							
					V		.					V		.		V					.		V		
---------------------------------------------------------				
											 LCD��ʾ��
								|-----------------|
								|			����Logo		|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|									|
								|-----------------|
								��Ļ���棨��480����854��

 *******************************************************/
void ILI9806G_GramScan ( uint8_t ucOption )
{	
	//������飬ֻ������0-7
	if(ucOption >7 )
		return;
	
	//����ģʽ����LCD_SCAN_MODE��ֵ����Ҫ���ڴ�����ѡ��������
	LCD_SCAN_MODE = ucOption;
	
	//����ģʽ����XY��������ؿ���
	if(ucOption%2 == 0)	
	{
		//0 2 4 6ģʽ��X�������ؿ���Ϊ480��Y����Ϊ854
		LCD_X_LENGTH = ILI9806G_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9806G_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7ģʽ��X�������ؿ���Ϊ854��Y����Ϊ480
		LCD_X_LENGTH = ILI9806G_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9806G_LESS_PIXEL; 
	}

	//0x36��������ĸ�3λ����������GRAMɨ�跽��	
	ILI9806G_Write_Cmd ( 0x36 ); 
	ILI9806G_Write_Data (0x00 | (ucOption<<5));//����ucOption��ֵ����LCD��������0-7��ģʽ
	ILI9806G_Write_Cmd ( CMD_SetCoordinateX ); 
	ILI9806G_Write_Data ( 0x00 );		/* x ��ʼ�����8λ */
	ILI9806G_Write_Data ( 0x00 );		/* x ��ʼ�����8λ */
	ILI9806G_Write_Data ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x ���������8λ */	
	ILI9806G_Write_Data ( (LCD_X_LENGTH-1)&0xFF );				/* x ���������8λ */

	ILI9806G_Write_Cmd ( CMD_SetCoordinateY ); 
	ILI9806G_Write_Data ( 0x00 );		/* y ��ʼ�����8λ */
	ILI9806G_Write_Data ( 0x00 );		/* y ��ʼ�����8λ */
	ILI9806G_Write_Data ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y ���������8λ */	 
	ILI9806G_Write_Data ( (LCD_Y_LENGTH-1)&0xFF );				/* y ���������8λ */

	/* write gram start */
	ILI9806G_Write_Cmd ( CMD_SetPixel );	
}



/**
 * @brief  ��ILI9806G��ʾ���Ͽ���һ������
 * @param  usX �����ض�ɨ�跽���´��ڵ����X����
 * @param  usY �����ض�ɨ�跽���´��ڵ����Y����
 * @param  usWidth �����ڵĿ���
 * @param  usHeight �����ڵĸ߶�
 * @retval ��
 */
void ILI9806G_OpenWindow ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight )
{	
	ILI9806G_Write_Cmd ( CMD_SetCoordinateX ); 				 /* ����X���� */
	ILI9806G_Write_Data ( usX >> 8  );	 /* �ȸ�8λ��Ȼ���8λ */
	ILI9806G_Write_Data ( usX & 0xff  );	 /* ������ʼ��ͽ�����*/
	ILI9806G_Write_Data ( ( usX + usWidth - 1 ) >> 8  );
	ILI9806G_Write_Data ( ( usX + usWidth - 1 ) & 0xff  );

	ILI9806G_Write_Cmd ( CMD_SetCoordinateY ); 			     /* ����Y����*/
	ILI9806G_Write_Data ( usY >> 8  );
	ILI9806G_Write_Data ( usY & 0xff  );
	ILI9806G_Write_Data ( ( usY + usHeight - 1 ) >> 8 );
	ILI9806G_Write_Data ( ( usY + usHeight - 1) & 0xff );
	
}


/**
 * @brief  �趨ILI9806G�Ĺ������
 * @param  usX �����ض�ɨ�跽���¹���X����
 * @param  usY �����ض�ɨ�跽���¹���Y����
 * @retval ��
 */
static void ILI9806G_SetCursor ( uint16_t usX, uint16_t usY )	
{
	ILI9806G_OpenWindow ( usX, usY, 1, 1 );
}


/**
 * @brief  ��ILI9806G��ʾ������ĳһ��ɫ������ص�
 * @param  ulAmout_Point ��Ҫ�����ɫ�����ص������Ŀ
 * @param  usColor ����ɫ
 * @retval ��
 */
static __inline void ILI9806G_FillColor ( uint32_t ulAmout_Point, uint16_t usColor )
{
	uint32_t i = 0;
	
	
	/* memory write */
	ILI9806G_Write_Cmd ( CMD_SetPixel );	
		
	for ( i = 0; i < ulAmout_Point; i ++ )
		ILI9806G_Write_Data ( usColor );
		
	
}


/**
 * @brief  ��ILI9806G��ʾ����ĳһ������ĳ����ɫ��������
 * @param  usX �����ض�ɨ�跽���´��ڵ����X����
 * @param  usY �����ض�ɨ�跽���´��ڵ����Y����
 * @param  usWidth �����ڵĿ���
 * @param  usHeight �����ڵĸ߶�
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight )
{
	ILI9806G_OpenWindow ( usX, usY, usWidth, usHeight );

	ILI9806G_FillColor ( usWidth * usHeight, CurrentBackColor );		
	
}


/**
 * @brief  ��ILI9806G��ʾ����ĳһ����ĳ����ɫ�������
 * @param  usX �����ض�ɨ�跽���¸õ��X����
 * @param  usY �����ض�ɨ�跽���¸õ��Y����
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_SetPointPixel ( uint16_t usX, uint16_t usY )	
{	
	if ( ( usX < LCD_X_LENGTH ) && ( usY < LCD_Y_LENGTH ) )
  {
		ILI9806G_SetCursor ( usX, usY );
		
		ILI9806G_FillColor ( 1, CurrentTextColor );
	}
	
}


/**
 * @brief  ��ȡILI9806G GRAN ��һ����������
 * @param  ��
 * @retval ��������
 */
static uint16_t ILI9806G_Read_PixelData ( void )	
{	
	uint16_t usR=0, usG=0, usB=0 ;

	
	ILI9806G_Write_Cmd ( 0x2E );   /* ������ */
	
	usR = ILI9806G_Read_Data (); 	/*FIRST READ OUT DUMMY DATA*/
	
	usR = ILI9806G_Read_Data ();  	/*READ OUT RED DATA  */
	usB = ILI9806G_Read_Data ();  	/*READ OUT BLUE DATA*/
	usG = ILI9806G_Read_Data ();  	/*READ OUT GREEN DATA*/	
	
  return ( ( ( usR >> 11 ) << 11 ) | ( ( usG >> 10 ) << 5 ) | ( usB >> 11 ) );
	
}


/**
 * @brief  ��ȡ ILI9806G ��ʾ����ĳһ����������������
 * @param  usX �����ض�ɨ�跽���¸õ��X����
 * @param  usY �����ض�ɨ�跽���¸õ��Y����
 * @retval ��������
 */
uint16_t ILI9806G_GetPointPixel ( uint16_t usX, uint16_t usY )
{ 
	uint16_t usPixelData;

	
	ILI9806G_SetCursor ( usX, usY );
	
	usPixelData = ILI9806G_Read_PixelData ();
	
	return usPixelData;
	
}


/**
 * @brief  �� ILI9806G ��ʾ����ʹ�� Bresenham �㷨���߶� 
 * @param  usX1 �����ض�ɨ�跽�����߶ε�һ���˵�X����
 * @param  usY1 �����ض�ɨ�跽�����߶ε�һ���˵�Y����
 * @param  usX2 �����ض�ɨ�跽�����߶ε���һ���˵�X����
 * @param  usY2 �����ض�ɨ�跽�����߶ε���һ���˵�Y����
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DrawLine ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 )
{
	uint16_t us; 
	uint16_t usX_Current, usY_Current;
	
	int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int32_t lIncrease_X, lIncrease_Y; 	
	
	
	lDelta_X = usX2 - usX1; //������������ 
	lDelta_Y = usY2 - usY1; 
	
	usX_Current = usX1; 
	usY_Current = usY1; 
	
	
	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; //���õ������� 
	
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;//��ֱ�� 
	
	else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 

	
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;//ˮƽ�� 
	
	else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 

	
	if (  lDelta_X > lDelta_Y )
		lDistance = lDelta_X; //ѡȡ�������������� 
	
	else 
		lDistance = lDelta_Y; 

	
	for ( us = 0; us <= lDistance + 1; us ++ )//������� 
	{  
		ILI9806G_SetPointPixel ( usX_Current, usY_Current );//���� 
		
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 
		
		if ( lError_X > lDistance ) 
		{ 
			lError_X -= lDistance; 
			usX_Current += lIncrease_X; 
		}  
		
		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			usY_Current += lIncrease_Y; 
		} 
		
	}  
	
	
}   


/**
 * @brief  �� ILI9806G ��ʾ���ϻ�һ������
 * @param  usX_Start �����ض�ɨ�跽���¾��ε���ʼ��X����
 * @param  usY_Start �����ض�ɨ�跽���¾��ε���ʼ��Y����
 * @param  usWidth�����εĿ��ȣ���λ�����أ�
 * @param  usHeight�����εĸ߶ȣ���λ�����أ�
 * @param  ucFilled ��ѡ���Ƿ����þ���
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg 0 :���ľ���
  *     @arg 1 :ʵ�ľ��� 
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DrawRectangle ( uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled )
{
	if ( ucFilled )
	{
		ILI9806G_OpenWindow ( usX_Start, usY_Start, usWidth, usHeight );
		ILI9806G_FillColor ( usWidth * usHeight ,CurrentTextColor);	
	}
	else
	{
		ILI9806G_DrawLine ( usX_Start, usY_Start, usX_Start + usWidth - 1, usY_Start );
		ILI9806G_DrawLine ( usX_Start, usY_Start + usHeight - 1, usX_Start + usWidth - 1, usY_Start + usHeight - 1 );
		ILI9806G_DrawLine ( usX_Start, usY_Start, usX_Start, usY_Start + usHeight - 1 );
		ILI9806G_DrawLine ( usX_Start + usWidth - 1, usY_Start, usX_Start + usWidth - 1, usY_Start + usHeight - 1 );		
	}

}


/**
 * @brief  �� ILI9806G ��ʾ����ʹ�� Bresenham �㷨��Բ
 * @param  usX_Center �����ض�ɨ�跽����Բ�ĵ�X����
 * @param  usY_Center �����ض�ɨ�跽����Բ�ĵ�Y����
 * @param  usRadius��Բ�İ뾶����λ�����أ�
 * @param  ucFilled ��ѡ���Ƿ�����Բ
  *   �ò���Ϊ����ֵ֮һ��
  *     @arg 0 :����Բ
  *     @arg 1 :ʵ��Բ
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DrawCircle ( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled )
{
	int16_t sCurrentX, sCurrentY;
	int16_t sError;
	
	
	sCurrentX = 0; sCurrentY = usRadius;	  
	
	sError = 3 - ( usRadius << 1 );     //�ж��¸���λ�õı�־
	
	
	while ( sCurrentX <= sCurrentY )
	{
		int16_t sCountY;
		
		
		if ( ucFilled ) 			
			for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ ) 
			{                      
				ILI9806G_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCountY );           //1���о����� 
				ILI9806G_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCountY );           //2       
				ILI9806G_SetPointPixel ( usX_Center - sCountY,   usY_Center + sCurrentX );           //3
				ILI9806G_SetPointPixel ( usX_Center - sCountY,   usY_Center - sCurrentX );           //4
				ILI9806G_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCountY );           //5    
        ILI9806G_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCountY );           //6
				ILI9806G_SetPointPixel ( usX_Center + sCountY,   usY_Center - sCurrentX );           //7 	
        ILI9806G_SetPointPixel ( usX_Center + sCountY,   usY_Center + sCurrentX );           //0				
			}
		
		else
		{          
			ILI9806G_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCurrentY );             //1���о�����
			ILI9806G_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCurrentY );             //2      
			ILI9806G_SetPointPixel ( usX_Center - sCurrentY, usY_Center + sCurrentX );             //3
			ILI9806G_SetPointPixel ( usX_Center - sCurrentY, usY_Center - sCurrentX );             //4
			ILI9806G_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCurrentY );             //5       
			ILI9806G_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCurrentY );             //6
			ILI9806G_SetPointPixel ( usX_Center + sCurrentY, usY_Center - sCurrentX );             //7 
			ILI9806G_SetPointPixel ( usX_Center + sCurrentY, usY_Center + sCurrentX );             //0
    }			
		
		
		sCurrentX ++;

		
		if ( sError < 0 ) 
			sError += 4 * sCurrentX + 6;	  
		
		else
		{
			sError += 10 + 4 * ( sCurrentX - sCurrentY );   
			sCurrentY --;
		} 	
		
		
	}
	
	
}

/**
 * @brief  �� ILI9806G ��ʾ������ʾһ��Ӣ���ַ�
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽���¸õ����ʼY����
 * @param  cChar ��Ҫ��ʾ��Ӣ���ַ�
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DispChar_EN ( uint16_t usX, uint16_t usY, const char cChar )
{
	uint8_t  byteCount, bitCount,fontLength;	
	uint16_t ucRelativePositon;
	uint8_t *Pfont;
	
	//��ascii���ƫ�ƣ���ģ��������ASCII����ǰ32����ͼ�η��ţ�
	ucRelativePositon = cChar - ' ';
	
	//ÿ����ģ���ֽ���
	fontLength = (LCD_Currentfonts->Width*LCD_Currentfonts->Height)/8;
		
	//��ģ�׵�ַ
	/*ascii���ƫ��ֵ����ÿ����ģ���ֽ����������ģ��ƫ��λ��*/
	Pfont = (uint8_t *)&LCD_Currentfonts->table[ucRelativePositon * fontLength];
	
	//������ʾ����
	ILI9806G_OpenWindow ( usX, usY, LCD_Currentfonts->Width, LCD_Currentfonts->Height);
	
	ILI9806G_Write_Cmd ( CMD_SetPixel );			

	//���ֽڶ�ȡ��ģ����
	//����ǰ��ֱ����������ʾ���ڣ���ʾ���ݻ��Զ�����
	for ( byteCount = 0; byteCount < fontLength; byteCount++ )
	{
			//һλһλ����Ҫ��ʾ����ɫ
			for ( bitCount = 0; bitCount < 8; bitCount++ )
			{
					if ( Pfont[byteCount] & (0x80>>bitCount) )
						ILI9806G_Write_Data ( CurrentTextColor );			
					else
						ILI9806G_Write_Data ( CurrentBackColor );
			}	
	}	
}


/**
 * @brief  �� ILI9806G ��ʾ������ʾӢ���ַ���
 * @param  line �����ض�ɨ�跽�����ַ�������ʼY����
  *   ��������ʹ�ú�LINE(0)��LINE(1)�ȷ�ʽָ���������꣬
  *   ��LINE(x)����ݵ�ǰѡ�������������Y����ֵ��
	*		��ʾ������ʹ��LINE��ʱ����Ҫ��Ӣ���������ó�Font8x16
 * @param  pStr ��Ҫ��ʾ��Ӣ���ַ������׵�ַ
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DispStringLine_EN (  uint16_t line,  char * pStr )
{
	uint16_t usX = 0;
	
	while ( * pStr != '\0' )
	{
		if ( ( usX - ILI9806G_DispWindow_X_Star + LCD_Currentfonts->Width ) > LCD_X_LENGTH )
		{
			usX = ILI9806G_DispWindow_X_Star;
			line += LCD_Currentfonts->Height;
		}
		
		if ( ( line - ILI9806G_DispWindow_Y_Star + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = ILI9806G_DispWindow_X_Star;
			line = ILI9806G_DispWindow_Y_Star;
		}
		
		ILI9806G_DispChar_EN ( usX, line, * pStr);
		
		pStr ++;
		
		usX += LCD_Currentfonts->Width;
		
	}
	
}


/**
 * @brief  �� ILI9806G ��ʾ������ʾӢ���ַ���
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽�����ַ�����ʼY����
 * @param  pStr ��Ҫ��ʾ��Ӣ���ַ������׵�ַ
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DispString_EN ( 	uint16_t usX ,uint16_t usY,  char * pStr )
{
	while ( * pStr != '\0' )
	{
		if ( ( usX - ILI9806G_DispWindow_X_Star + LCD_Currentfonts->Width ) > LCD_X_LENGTH )
		{
			usX = ILI9806G_DispWindow_X_Star;
			usY += LCD_Currentfonts->Height;
		}
		
		if ( ( usY - ILI9806G_DispWindow_Y_Star + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = ILI9806G_DispWindow_X_Star;
			usY = ILI9806G_DispWindow_Y_Star;
		}
		
		ILI9806G_DispChar_EN ( usX, usY, * pStr);
		
		pStr ++;
		
		usX += LCD_Currentfonts->Width;
		
	}
	
}


/**
 * @brief  �� ILI9806G ��ʾ������ʾӢ���ַ���(��Y�᷽��)
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽�����ַ�����ʼY����
 * @param  pStr ��Ҫ��ʾ��Ӣ���ַ������׵�ַ
 * @note ��ʹ��LCD_SetBackColor��LCD_SetTextColor��LCD_SetColors����������ɫ
 * @retval ��
 */
void ILI9806G_DispString_EN_YDir (	 uint16_t usX,uint16_t usY ,  char * pStr )
{	
	while ( * pStr != '\0' )
	{
		if ( ( usY - ILI9806G_DispWindow_Y_Star + LCD_Currentfonts->Height ) >LCD_Y_LENGTH  )
		{
			usY = ILI9806G_DispWindow_Y_Star;
			usX += LCD_Currentfonts->Width;
		}
		
		if ( ( usX - ILI9806G_DispWindow_X_Star + LCD_Currentfonts->Width ) >  LCD_X_LENGTH)
		{
			usX = ILI9806G_DispWindow_X_Star;
			usY = ILI9806G_DispWindow_Y_Star;
		}
		
		ILI9806G_DispChar_EN ( usX, usY, * pStr);
		
		pStr ++;
		
		usY += LCD_Currentfonts->Height;		
	}	
}


/**
  * @brief  ����Ӣ����������
  * @param  fonts: ָ��Ҫѡ�������
	*		����Ϊ����ֵ֮һ
  * 	@arg��Font24x32;
  * 	@arg��Font16x24;
  * 	@arg��Font8x16;
  * @retval None
  */
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}

/**
  * @brief  ��ȡ��ǰ��������
  * @param  None.
  * @retval ���ص�ǰ��������
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}


/**
  * @brief  ����LCD��ǰ��(����)��������ɫ,RGB565
  * @param  TextColor: ָ��ǰ��(����)��ɫ
  * @param  BackColor: ָ��������ɫ
  * @retval None
  */
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor) 
{
  CurrentTextColor = TextColor; 
  CurrentBackColor = BackColor;
}

/**
  * @brief  ��ȡLCD��ǰ��(����)��������ɫ,RGB565
  * @param  TextColor: �����洢ǰ��(����)��ɫ��ָ�����
  * @param  BackColor: �����洢������ɫ��ָ�����
  * @retval None
  */
void LCD_GetColors(uint16_t *TextColor, uint16_t *BackColor)
{
  *TextColor = CurrentTextColor;
  *BackColor = CurrentBackColor;
}

/**
  * @brief  ����LCD��ǰ��(����)��ɫ,RGB565
  * @param  Color: ָ��ǰ��(����)��ɫ 
  * @retval None
  */
void LCD_SetTextColor(uint16_t Color)
{
  CurrentTextColor = Color;
}

/**
  * @brief  ����LCD�ı�����ɫ,RGB565
  * @param  Color: ָ��������ɫ 
  * @retval None
  */
void LCD_SetBackColor(uint16_t Color)
{
  CurrentBackColor = Color;
}

/**
  * @brief  ���ĳ������
  * @param  Line: ָ��Ҫɾ������
  *   ��������ʹ�ú�LINE(0)��LINE(1)�ȷ�ʽָ��Ҫɾ�����У�
  *   ��LINE(x)����ݵ�ǰѡ�������������Y����ֵ����ɾ����ǰ����߶ȵĵ�x�С�
  * @retval None
  */
void ILI9806G_ClearLine(uint16_t Line)
{
  ILI9806G_Clear(0,Line,LCD_X_LENGTH,((sFONT *)LCD_GetFont())->Height);	/* ��������ʾȫ�� */

}
/*********************end of file*************************/


