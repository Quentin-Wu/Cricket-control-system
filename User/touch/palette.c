#include "./touch/palette.h"
#include "./touch/gt5xx.h"
#include "./lcd/bsp_ili9806g_lcd.h"
#include "control.h"

extern void switch_mode(int mmode);
extern void mode_12_switch(int A, int B, int C, int D);


Touch_Button button[BUTTON_NUM];
/*画笔参数*/
Brush_Style brush;





void Touch_Button_Init(void);
static void Draw_Button1(void *btn);
static void Draw_Button2(void *btn);
static void Draw_Button3(void *btn);
static void Draw_Button4(void *btn);
static void Draw_Button5(void *btn);
static void Draw_Button6(void *btn);
static void Draw_Button7(void *btn);
static void Draw_Button8(void *btn);
static void Command_Select_Task1(void *btn);
static void Command_Select_Task2(void *btn);
static void Command_Select_Task3(void *btn);
static void Command_Select_Task4(void *btn);
static void Command_Select_Task5(void *btn);
static void Command_Select_Task6(void *btn);
static void Command_Select_Task7(void *btn);
static void Command_Select_Task8(void *btn);


void Palette_Init(uint8_t LCD_Mode)
{
  
  uint8_t i;
	
	ILI9806G_GramScan ( LCD_Mode );

  /* 整屏清为白色 */
	LCD_SetBackColor(CL_WHITE);
  ILI9806G_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	

  
  /* 初始化按钮 */
  Touch_Button_Init();
  
  /* 描绘按钮 */
  for(i=0;i<BUTTON_NUM;i++)
  {
    button[i].draw_btn(&button[i]);
  }


}



void Touch_Button_Init(void)
{
  button[0].start_x = BUTTON_START_X;
  button[0].start_y = 0;
  button[0].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[0].end_y = COLOR_BLOCK_HEIGHT;
	button[0].para = CL_GREY1;
  button[0].touch_flag = 0;
  button[0].draw_btn = Draw_Button1 ; 
	button[0].btn_command =Command_Select_Task1;

  button[1].start_x = BUTTON_START_X;
  button[1].start_y = COLOR_BLOCK_HEIGHT;
  button[1].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[1].end_y = COLOR_BLOCK_HEIGHT*2;
  button[1].para = CL_GREY1;
  button[1].touch_flag = 0;  
  button[1].draw_btn = Draw_Button2 ;
  button[1].btn_command = Command_Select_Task2 ;
	
  button[2].start_x = BUTTON_START_X;
  button[2].start_y = COLOR_BLOCK_HEIGHT*2;
  button[2].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[2].end_y = COLOR_BLOCK_HEIGHT*3;
  button[2].para = CL_GREY1;
  button[2].touch_flag = 0;  
  button[2].draw_btn = Draw_Button3 ;
  button[2].btn_command = Command_Select_Task3 ;
	  
  button[3].start_x = BUTTON_START_X;
  button[3].start_y = COLOR_BLOCK_HEIGHT*3;
  button[3].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH ;
  button[3].end_y = COLOR_BLOCK_HEIGHT*4;
  button[3].para = CL_GREY1;
  button[3].touch_flag = 0;  
  button[3].draw_btn = Draw_Button4 ;
  button[3].btn_command = Command_Select_Task4 ;
  
  button[4].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[4].start_y = 0;
  button[4].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[4].end_y = COLOR_BLOCK_HEIGHT;
  button[4].para = CL_GREY1;
  button[4].touch_flag = 0;  
  button[4].draw_btn = Draw_Button5;
  button[4].btn_command = Command_Select_Task5;
	 
  button[5].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[5].start_y = COLOR_BLOCK_HEIGHT;
  button[5].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[5].end_y = COLOR_BLOCK_HEIGHT*2;
  button[5].para = CL_GREY1;
  button[5].touch_flag = 0;  
  button[5].draw_btn = Draw_Button6 ;
  button[5].btn_command = Command_Select_Task6 ;
  
  button[6].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[6].start_y = COLOR_BLOCK_HEIGHT*2;
  button[6].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[6].end_y = COLOR_BLOCK_HEIGHT*3;
  button[6].para = CL_GREY1;
  button[6].touch_flag = 0;  
  button[6].draw_btn = Draw_Button7 ;
  button[6].btn_command = Command_Select_Task7 ;
  
  button[7].start_x = BUTTON_START_X + COLOR_BLOCK_WIDTH;
  button[7].start_y = COLOR_BLOCK_HEIGHT*3;
  button[7].end_x = BUTTON_START_X+COLOR_BLOCK_WIDTH*2 ;
  button[7].end_y = COLOR_BLOCK_HEIGHT*4;
  button[7].para = CL_GREY1;
  button[7].touch_flag = 0;  
  button[7].draw_btn = Draw_Button8 ;
  button[7].btn_command = Command_Select_Task8 ;
	
}


void Touch_Button_Down(uint16_t x,uint16_t y)
{
  uint8_t i;
  for(i=0;i<BUTTON_NUM;i++)
  {
    /* 触摸到了按钮 */
    if(x<=button[i].end_x && y<=button[i].end_y && y>=button[i].start_y && x>=button[i].start_x )
    {
      if(button[i].touch_flag == 0)     /*原本的状态为没有按下，则更新状态*/
      {
      button[i].touch_flag = 1;         /* 记录按下标志 */
      
      button[i].draw_btn(&button[i]);  /*重绘按钮*/
      }        
      
    }
    else if(button[i].touch_flag == 1) /* 触摸移出了按键的范围且之前有按下按钮 */
    {
      button[i].touch_flag = 0;         /* 清除按下标志，判断为误操作*/
      
      button[i].draw_btn(&button[i]);   /*重绘按钮*/
    }

  }

}

void Touch_Button_Up(uint16_t x,uint16_t y)
{
   uint8_t i; 
   for(i=0;i<BUTTON_NUM;i++)
   {
     /* 触笔在按钮区域释放 */
      if((x<button[i].end_x && x>button[i].start_x && y<button[i].end_y && y>button[i].start_y))
      {        
        button[i].touch_flag = 0;       /*释放触摸标志*/
        
        button[i].draw_btn(&button[i]); /*重绘按钮*/        
      
        button[i].btn_command(&button[i]);  /*执行按键的功能命令*/
        
        break;
      }
    }  

}


//任务1
static void Draw_Button1(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {

		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务1");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		LCD_SetColors(CL_RED,CL_WHITE);
		ILI9806G_DispString_EN_CH( ptr->start_x,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务1");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}
//任务2
static void Draw_Button2(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务2");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务2");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}

//任务3
static void Draw_Button3(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务3");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务3");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}
//任务4
static void Draw_Button4(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务4");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务4");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}

//任务5
static void Draw_Button5(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务5");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务5");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}
//任务6
static void Draw_Button6(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务6");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务6");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}

//任务7
static void Draw_Button7(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务7");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x ,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务7");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}
//任务8
static void Draw_Button8(void *btn)
{
  Touch_Button *ptr = (Touch_Button *)btn;
  
  /*释放按键*/
  if(ptr->touch_flag == 0)
  {
		/*背景为功能键相应的颜色*/
		LCD_SetColors(ptr->para,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetColors(CL_RED,CL_BUTTON_GREY);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x + (ptr->end_x - ptr->start_x - 32*2 )/2,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务8");
  }
  else  /*按键按下*/
  {
    /*白色背景*/
		LCD_SetColors(CL_WHITE,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
                      ptr->start_y,
                      ptr->end_x - ptr->start_x,
											ptr->end_y - ptr->start_y,1);
		LCD_SetFont(&Font16x32);
		ILI9806G_DispString_EN_CH( ptr->start_x + (ptr->end_x - ptr->start_x - 32*2 )/2,
														ptr->start_y+ ((ptr->end_y - ptr->start_y-32)/2),	
														"任务8");
  } 
    /*按钮边框*/
		LCD_SetColors(CL_BLUE4,CL_WHITE);
    ILI9806G_DrawRectangle(ptr->start_x,
									ptr->start_y,
									ptr->end_x - ptr->start_x,
									ptr->end_y - ptr->start_y,0);
  
}

static void Command_Select_Task1(void *btn)
{
		switch_mode(1);
				ILI9806G_DispString_EN_CH( 300,300,	
														"任务1");
}

static void Command_Select_Task2(void *btn)
{
		switch_mode(2);				ILI9806G_DispString_EN_CH( 300,300,	
														"任务2");
}
static void Command_Select_Task3(void *btn)
{
		switch_mode(3);				ILI9806G_DispString_EN_CH( 300,300,	
														"任务3");
}

static void Command_Select_Task4(void *btn)
{
		switch_mode(4);			ILI9806G_DispString_EN_CH( 300,300,	
														"任务4");
}
static void Command_Select_Task5(void *btn)
{
		switch_mode(5);				ILI9806G_DispString_EN_CH( 300,300,	
														"任务5");
}

static void Command_Select_Task6(void *btn)
{
		switch_mode(6);					ILI9806G_DispString_EN_CH( 300,300,	
														"任务6");
}
static void Command_Select_Task7(void *btn)
{
		switch_mode(7);				ILI9806G_DispString_EN_CH( 300,300,	
														"任务7");
}

static void Command_Select_Task8(void *btn)
{
		switch_mode(8);				ILI9806G_DispString_EN_CH( 300,300,	
														"任务8");
}  

