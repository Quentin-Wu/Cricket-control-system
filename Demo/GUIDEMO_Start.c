#include "Dialog.h"
#include "usart.h"

/*********************************************************************
*
* Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_BUTTON_2 (GUI_ID_USER + 0x03)
#define ID_BUTTON_3 (GUI_ID_USER + 0x04)
#define ID_BUTTON_4 (GUI_ID_USER + 0x05)
#define ID_BUTTON_5 (GUI_ID_USER + 0x06)
#define ID_BUTTON_6 (GUI_ID_USER + 0x07)
#define ID_BUTTON_7 (GUI_ID_USER + 0x08)
#define ID_BUTTON_8 (GUI_ID_USER + 0x09)


#define ID_TEXT_0 (GUI_ID_USER + 0x10)
#define ID_TEXT_1 (GUI_ID_USER + 0x11)
#define ID_TEXT_2 (GUI_ID_USER + 0x12)
#define ID_TEXT_3 (GUI_ID_USER + 0x13)

#define ID_DROPDOWN_0 (GUI_ID_USER + 0x14)
#define ID_DROPDOWN_1 (GUI_ID_USER + 0x15)
#define ID_DROPDOWN_2 (GUI_ID_USER + 0x16)
#define ID_DROPDOWN_3 (GUI_ID_USER + 0x17)

//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 10)


__IO u8 set_a=0;
__IO u8 set_b=0;
__IO u8 set_c=0;
__IO u8 set_d=0;
__IO u8 set_a1=0;
__IO u8 set_b1=0;
__IO u8 set_c1=0;
__IO u8 set_d1=0;

extern __IO int mode;
extern __IO u16 xxxx;
extern __IO u16 yyyy;
extern GUI_CONST_STORAGE GUI_BITMAP bm2;
extern GUI_CONST_STORAGE GUI_BITMAP bm3;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontneirong55;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontxitong160;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontgun182;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontrenwu84;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontrewu55;


//主界面	
static const GUI_WIDGET_CREATE_INFO _aDialogCreate0[] = {
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 83, 514, 317, 98, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "滚", ID_TEXT_0, 87,  57,  173, 182, 0, 0x64, 0 },
		{ TEXT_CreateIndirect, "球", ID_TEXT_1, 230, 138, 140, 147, 0, 0x64, 0 },
		{ TEXT_CreateIndirect, "系", ID_TEXT_2, 120, 238, 140, 147, 0, 0x64, 0 },
		{ TEXT_CreateIndirect, "统", ID_TEXT_3, 230, 338, 140, 147, 0, 0x64, 0 },
    };
//任务界面
static const GUI_WIDGET_CREATE_INFO _aDialogCreate1[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "任务一", ID_BUTTON_0, 140, 171, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "任务二", ID_BUTTON_1, 140, 236, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "任务三", ID_BUTTON_2, 140, 301, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "任务四", ID_BUTTON_3, 140, 366, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "发挥一", ID_BUTTON_4, 140, 431, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "发挥二", ID_BUTTON_5, 140, 496, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "发挥三", ID_BUTTON_6, 140, 561, 200, 55, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "发挥四", ID_BUTTON_7, 140, 626, 200, 55, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "", ID_BUTTON_8, 414, 784, 66, 66, 0, 0x0, 0 },
    };

//任务一		
static const GUI_WIDGET_CREATE_INFO _aDialogCreate2[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "任务一", ID_TEXT_0, 0, 0, 480, 96, 0, 0x64, 0 },
		{ TEXT_CreateIndirect, "    小球放在区域 2 ，\n控制小球在区域内停\n留不少于 5 秒。", ID_TEXT_1,       		0, 120, 480, 480, 0, 0x64, 0 },
 };

//任务二
static const GUI_WIDGET_CREATE_INFO _aDialogCreate3[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "任务二", ID_TEXT_0, 0, 0, 480, 96, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "    在15秒内，控制小\n球从区域 1 进入区域\n 5 ，在区域 5 停留不\n少于 2 秒。", ID_TEXT_1,       		0, 120, 480, 480, 0, 0x64, 0 },
  };
//任务三
static const GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "任务三", ID_TEXT_0, 																								0, 0, 480, 96, 0, 0x64, 0 },
		{ TEXT_CreateIndirect, "    控制小球从区域 1 \n进入区域 4 ，在区域\n 4 停留不少于 2 秒，\n进入区域 5 ，小球在\n区域 5 停留不少于 2 \n秒，总时间不超过20 \n秒。",ID_TEXT_1,				0, 120, 480, 600,0,0x64,0},
   };
//任务四
static const GUI_WIDGET_CREATE_INFO _aDialogCreate5[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "任务四", ID_TEXT_0, 0, 0, 480, 96, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "    在30秒内，控制小\n球从区域 1 进区域 9 \n在区域 9 停留不少于\n 2 秒。",ID_TEXT_1,						0, 120,480, 480, 0, 0x64, 0},
};
//发挥一
static const GUI_WIDGET_CREATE_INFO _aDialogCreate6[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "发挥一", ID_TEXT_0, 0, 0, 480, 850, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
		{ TEXT_CreateIndirect, "    在40秒内，控制小\n球从区域 1 出发，进\n入区域 2 ，区域 6 ，\n停在区域 9 ，停留不\n少于 2 秒。", ID_TEXT_1, 		0, 120,480, 480, 0, 0x64, 0 },
};
//发挥二
static const GUI_WIDGET_CREATE_INFO _aDialogCreate7[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "发挥二", ID_TEXT_0, 0, 0, 480, 850, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "A", ID_BUTTON_1,  20, 430, 80, 66, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "B", ID_BUTTON_2, 140, 430, 80, 66, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "C", ID_BUTTON_3, 260, 430, 80, 66, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "D", ID_BUTTON_4, 380, 430, 80, 66, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "ok", ID_BUTTON_5, 20, 784, 66, 66, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "    在 40 秒内，控制\n小球从区域 A 进入区\n域 B ，区域 C ，停在\n区域 D 。",ID_TEXT_1,0,120,480,480,0,0x64,0},
		{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0,  20, 496, 80, 220, 0, 0x0, 0 },
		{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_1, 140, 496, 80, 220, 0, 0x0, 0 },
		{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_2, 260, 496, 80, 220, 0, 0x0, 0 },
		{ DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_3, 380, 496, 80, 220, 0, 0x0, 0 },
};
//发挥三
static const GUI_WIDGET_CREATE_INFO _aDialogCreate8[] = {
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "发挥三", ID_TEXT_0, 0, 0, 480, 850, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "    小球从区域 4 出发\n，绕区域 5 做圆周运\n动，运动不少于 3 周\n，停在区域 9 ，不少\n于 2 秒。",ID_TEXT_1,0,120,480,480,0,0x64,0},
		};
//发挥四
static const GUI_WIDGET_CREATE_INFO _aDialogCreate9[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "发挥四", ID_TEXT_0, 0, 0, 480, 850, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "激光随动", ID_BUTTON_0, 135, 226, 210, 100, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "液晶控制", ID_BUTTON_1, 135, 526, 210, 100, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "", ID_BUTTON_2, 414, 784, 66, 66, 0, 0x0, 0 },
    };
//激光
static const GUI_WIDGET_CREATE_INFO _aDialogCreate10[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "激光随动", ID_TEXT_0, 0, 0, 480, 850, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
    };		
//液晶屏控制
static const GUI_WIDGET_CREATE_INFO _aDialogCreate11[] = { 
		{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 852, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "液晶控制", ID_TEXT_0, 0, 0, 480, 96, 0, 0x64, 0 },
    { BUTTON_CreateIndirect, "", ID_BUTTON_0, 414, 784, 66, 66, 0, 0x0, 0 },
    };				

		
//函数声明
static void _cbDialog1(WM_MESSAGE * pMsg);
static void _cbDialog2(WM_MESSAGE * pMsg);
static void _cbDialog3(WM_MESSAGE * pMsg);
static void _cbDialog4(WM_MESSAGE * pMsg);
static void _cbDialog5(WM_MESSAGE * pMsg);
static void _cbDialog6(WM_MESSAGE * pMsg);
static void _cbDialog7(WM_MESSAGE * pMsg);
static void _cbDialog8(WM_MESSAGE * pMsg);
static void _cbDialog9(WM_MESSAGE * pMsg);
static void _cbDialog10(WM_MESSAGE * pMsg);
static void _cbDialog11(WM_MESSAGE * pMsg);
//主界面
static void _cbDialog0(WM_MESSAGE * pMsg) { 
	
    WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
					  GUI_SelectLayer(0);
						GUI_DrawBitmap(&bm3,0,0);
				
				break;
		   	
        case WM_INIT_DIALOG:
       //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            BUTTON_SetBitmapEx(hItem,0,&bm2,0,0);
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
						TEXT_SetTextColor(hItem, GUI_BLACK);
            TEXT_SetFont(hItem,&GUI_Fontgun182);
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
						TEXT_SetTextColor(hItem, GUI_BLACK);
            TEXT_SetFont(hItem,&GUI_Fontxitong160);
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
						TEXT_SetTextColor(hItem, GUI_BLACK);
            TEXT_SetFont(hItem,&GUI_Fontxitong160);
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
						TEXT_SetTextColor(hItem, GUI_BLACK);
            TEXT_SetFont(hItem,&GUI_Fontxitong160);
				
						WM_InvalidateWindow(pMsg->hWin);						
        break;
				
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
			
            switch(Id) {
								//返回键
                case ID_BUTTON_0:
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED: 
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                 break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
}		
//任务界面
static void _cbDialog1(WM_MESSAGE * pMsg) { 
    WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {

        case WM_INIT_DIALOG:
						//初始化对话框
				    
						
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			    	BUTTON_SetFont(hItem,&GUI_Fontrewu55);
						BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,GUI_BLUE);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
						BUTTON_SetFont(hItem,&GUI_Fontrewu55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
						BUTTON_SetFont(hItem,&GUI_Fontrewu55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
					  BUTTON_SetFont(hItem,&GUI_Fontrewu55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
					  BUTTON_SetFont(hItem,&GUI_Fontrewu55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
						BUTTON_SetFont(hItem,&GUI_Fontrewu55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
						BUTTON_SetFont(hItem,&GUI_Fontrewu55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
						BUTTON_SetFont(hItem,&GUI_Fontrewu55);
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						WM_InvalidateWindow(pMsg->hWin);
          break;
						
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
						switch(Id){
							//任务一
							case ID_BUTTON_0: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate2, GUI_COUNTOF(_aDialogCreate2), _cbDialog2, WM_HBKWIN, 0, 0);
											break;
									}
							break;
							//任务二
							case ID_BUTTON_1: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate3, GUI_COUNTOF(_aDialogCreate3), _cbDialog3, WM_HBKWIN, 0, 0);
											break;
									}
							break;
							//任务三
							case ID_BUTTON_2: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbDialog4, WM_HBKWIN, 0, 0);
											break;
									}
							break;
							//任务四
							case ID_BUTTON_3: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), _cbDialog5, WM_HBKWIN, 0, 0);
											break;
									}
							break;
							//发挥一	
							case ID_BUTTON_4: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate6, GUI_COUNTOF(_aDialogCreate6), _cbDialog6, WM_HBKWIN, 0, 0);
											break;
									}
							break;
							//发挥二		
						  case ID_BUTTON_5: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate7, GUI_COUNTOF(_aDialogCreate7), _cbDialog7, WM_HBKWIN, 0, 0);
											break;
									}
							break;	
							//发挥三
							case ID_BUTTON_6: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate8, GUI_COUNTOF(_aDialogCreate8), _cbDialog8, WM_HBKWIN, 0, 0);
											break;
									}
							break;									
							//发挥四
							case ID_BUTTON_7: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate9, GUI_COUNTOF(_aDialogCreate9), _cbDialog9, WM_HBKWIN, 0, 0);
											break;
									}
							break;
									
							case ID_BUTTON_8: 
									switch(NCode) {
											case WM_NOTIFICATION_CLICKED:
											break;
											case WM_NOTIFICATION_RELEASED: 
											GUI_EndDialog(pMsg->hWin, 0);
											GUI_CreateDialogBox(_aDialogCreate0, GUI_COUNTOF(_aDialogCreate0), _cbDialog0, WM_HBKWIN, 0, 0);
											break;
									}
							break;
        }
        break;
				case WM_PAINT:
					GUI_DrawBitmap(&bm3,0,0);	
				break;	
        default:
            WM_DefaultProc(pMsg);
            
        break;
    }
}
//任务一
static void _cbDialog2(WM_MESSAGE * pMsg) { 
		
    WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {

			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
		   	
        case WM_INIT_DIALOG:
       //初始化对话框
            hItem = pMsg->hWin;
            FRAMEWIN_SetFont(hItem,&GUI_Fontneirong55);
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");

						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						//初始化文本框
//					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
//            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);				
        break;
				
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
			
            switch(Id) {
								//返回键
                case ID_BUTTON_0:
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED: 
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                 break;
             }
        break;
						 
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=1;
}
//任务二
static void _cbDialog3(WM_MESSAGE * pMsg) { 
		
    WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {			
			case WM_PAINT:
					GUI_DrawBitmap(&bm3,0,0);	
			break;
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
            FRAMEWIN_SetFont(hItem,&GUI_Fontneirong55);
						FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);		
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
//					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
//            TEXT_SetFont(hItem,&GUI_Fontneirong55);
//						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
//            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);	
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=2;
}
//任务三
static void _cbDialog4(WM_MESSAGE * pMsg) { 
    
		WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
//            BUTTON_SetBitmapEx(hItem,0,&bmbreak,0,0);
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);		
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
//					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
//            TEXT_SetFont(hItem,&GUI_Fontneirong55);
//						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
//            TEXT_SetFont(hItem,&GUI_Fontneirong55);
//						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
//            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);	
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=3;
}
//任务四
static void _cbDialog5(WM_MESSAGE * pMsg) { 
		
    WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
 //           BUTTON_SetBitmapEx(hItem,0,&bmbreak,0,0);
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);		
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);	
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=4;
}
//发挥一
static void _cbDialog6(WM_MESSAGE * pMsg) { 
		
    WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);		
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
			WM_DefaultProc(pMsg);
        break;
    }
		mode=5;
}
//发挥二
static void _cbDialog7(WM_MESSAGE * pMsg) { 
    
		WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
						BUTTON_SetFont(hItem,&GUI_Fontneirong55);
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
						BUTTON_SetFont(hItem,&GUI_Fontneirong55);
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
						BUTTON_SetFont(hItem,&GUI_Fontneirong55);
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
						BUTTON_SetFont(hItem,&GUI_Fontneirong55);
						hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "ok");
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);		
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
				
				  	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
						DROPDOWN_SetFont(hItem, &GUI_Fontneirong55);
						DROPDOWN_SetAutoScroll(hItem,1);
						DROPDOWN_SetScrollbarWidth(hItem,23);
						DROPDOWN_SetItemSpacing(hItem,3);
						DROPDOWN_SetTextAlign(hItem,GUI_TA_VCENTER);
						DROPDOWN_SetTextHeight(hItem,33);
						DROPDOWN_AddString(hItem,"1");
						DROPDOWN_AddString(hItem,"2");
						DROPDOWN_AddString(hItem,"3");
						DROPDOWN_AddString(hItem,"4");
						DROPDOWN_AddString(hItem,"5");
						DROPDOWN_AddString(hItem,"6");
						DROPDOWN_AddString(hItem,"7");
						DROPDOWN_AddString(hItem,"8");
						DROPDOWN_AddString(hItem,"9");

				  	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_1);
						DROPDOWN_SetFont(hItem, &GUI_Fontneirong55);
						DROPDOWN_SetAutoScroll(hItem,1);
						DROPDOWN_SetScrollbarWidth(hItem,23);
						DROPDOWN_SetItemSpacing(hItem,3);
						DROPDOWN_SetTextAlign(hItem,GUI_TA_VCENTER);
						DROPDOWN_SetTextHeight(hItem,33);
						DROPDOWN_AddString(hItem,"1");
						DROPDOWN_AddString(hItem,"2");
						DROPDOWN_AddString(hItem,"3");
						DROPDOWN_AddString(hItem,"4");
						DROPDOWN_AddString(hItem,"5");
						DROPDOWN_AddString(hItem,"6");
						DROPDOWN_AddString(hItem,"7");
						DROPDOWN_AddString(hItem,"8");
						DROPDOWN_AddString(hItem,"9");
						
				  	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_2);
						DROPDOWN_SetFont(hItem, &GUI_Fontneirong55);
						DROPDOWN_SetAutoScroll(hItem,1);
						DROPDOWN_SetScrollbarWidth(hItem,23);
						DROPDOWN_SetItemSpacing(hItem,3);
						DROPDOWN_SetTextAlign(hItem,GUI_TA_VCENTER);
						DROPDOWN_SetTextHeight(hItem,33);
						DROPDOWN_AddString(hItem,"1");
						DROPDOWN_AddString(hItem,"2");
						DROPDOWN_AddString(hItem,"3");
						DROPDOWN_AddString(hItem,"4");
						DROPDOWN_AddString(hItem,"5");
						DROPDOWN_AddString(hItem,"6");
						DROPDOWN_AddString(hItem,"7");
						DROPDOWN_AddString(hItem,"8");
						DROPDOWN_AddString(hItem,"9");
						
				  	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_3);
						DROPDOWN_SetFont(hItem, &GUI_Fontneirong55);
						DROPDOWN_SetAutoScroll(hItem,1);
						DROPDOWN_SetScrollbarWidth(hItem,23);
						DROPDOWN_SetItemSpacing(hItem,3);
						DROPDOWN_SetTextAlign(hItem,GUI_TA_VCENTER);
						DROPDOWN_SetTextHeight(hItem,33);
						DROPDOWN_AddString(hItem,"1");
						DROPDOWN_AddString(hItem,"2");
						DROPDOWN_AddString(hItem,"3");
						DROPDOWN_AddString(hItem,"4");
						DROPDOWN_AddString(hItem,"5");
						DROPDOWN_AddString(hItem,"6");
						DROPDOWN_AddString(hItem,"7");
						DROPDOWN_AddString(hItem,"8");
						DROPDOWN_AddString(hItem,"9");
						WM_InvalidateWindow(pMsg->hWin);
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                case ID_BUTTON_1: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
								case ID_BUTTON_2: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                case ID_BUTTON_3: 
										switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
								case ID_BUTTON_4: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
								case ID_BUTTON_5: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
													set_a1=set_a;
													set_b1=set_b;
													set_c1=set_c;
													set_d1=set_d;
                        break;
                    }
                    break;
								case ID_DROPDOWN_0:
										hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
										switch(DROPDOWN_GetSel(hItem)){
											case 0:
												set_a=1;
											break;
											case 1:
												set_a=2;
											break;							
											case 2:
												set_a=3;
											break;
											case 3:
												set_a=4;
											break;	
											case 4:
												set_a=5;
											break;
											case 5:
												set_a=6;
											break;		
											case 6:
												set_a=7;
											break;
											case 7:
												set_a=8;
											break;							
											case 8:
												set_a=9;
											break;
										}
								break;
																		
								case ID_DROPDOWN_1:
										hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_1);
										switch(DROPDOWN_GetSel(hItem)){
											case 0:
												set_b=1;
											break;
											case 1:
												set_b=2;
											break;							
											case 2:
												set_b=3;
											break;
											case 3:
												set_b=4;
											break;	
											case 4:
												set_b=5;
											break;
											case 5:
												set_b=6;
											break;		
											case 6:
												set_b=7;
											break;
											case 7:
												set_b=8;
											break;							
											case 8:
												set_b=9;
											break;
										}
								break;
										
								case ID_DROPDOWN_2:
										hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_2);
										switch(DROPDOWN_GetSel(hItem)){
											case 0:
												set_c=1;
											break;
											case 1:
												set_c=2;
											break;							
											case 2:
												set_c=3;
											break;
											case 3:
												set_c=4;
											break;	
											case 4:
												set_c=5;
											break;
											case 5:
												set_c=6;
											break;		
											case 6:
												set_c=7;
											break;
											case 7:
												set_c=8;
											break;							
											case 8:
												set_c=9;
											break;
										}
								break;
										
								case ID_DROPDOWN_3:
										hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_3);
										switch(DROPDOWN_GetSel(hItem)){
											case 0:
												set_d=1;
											break;
											case 1:
												set_d=2;
											break;							
											case 2:
												set_d=3;
											break;
											case 3:
												set_d=4;
											break;	
											case 4:
												set_d=5;
											break;
											case 5:
												set_d=6;
											break;		
											case 6:
												set_d=7;
											break;
											case 7:
												set_d=8;
											break;							
											case 8:
												set_d=9;
											break;
										}
								break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=6;
}
//发挥三
static void _cbDialog8(WM_MESSAGE * pMsg) { 
			
		WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
				
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
            TEXT_SetFont(hItem,&GUI_Fontrenwu84);		
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=7;
}
//发挥四
static void _cbDialog9(WM_MESSAGE * pMsg) { 
    
		WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            BUTTON_SetFont(hItem,&GUI_Fontneirong55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
            BUTTON_SetFont(hItem,&GUI_Fontneirong55);
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						WM_InvalidateWindow(pMsg->hWin);
				break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//激光
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate10, GUI_COUNTOF(_aDialogCreate10), _cbDialog10, WM_HBKWIN, 0, 0);
                        break;
										}
                    break;
                case ID_BUTTON_1: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate11, GUI_COUNTOF(_aDialogCreate11), _cbDialog11, WM_HBKWIN, 0, 0);
                        break;
										}
                    break;
               case ID_BUTTON_2: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
										}
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
		mode=8;
}
//激光
static void _cbDialog10(WM_MESSAGE * pMsg) { 
     WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
						TEXT_SetTextColor(hItem, GUI_RED);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
        break;
    }
}
//液晶屏
static void _cbDialog11(WM_MESSAGE * pMsg) { 
     WM_HWIN hItem;
    int NCode;
    int Id;
    switch (pMsg->MsgId) {
			
				case WM_PAINT:
						GUI_DrawBitmap(&bm3,0,0);	
						GUI_FillCircle( 25,211,25);
						GUI_FillCircle(240,211,25);
						GUI_FillCircle(455,211,25);
						GUI_FillCircle(25,426,25);
						GUI_FillCircle(240,426,25);
						GUI_FillCircle(455,426,25);
						GUI_FillCircle(25,641,25);
						GUI_FillCircle(240,641,25);
						GUI_FillCircle(455,641,25);
						GUI_DrawLine(25,211,455,211);
						GUI_DrawLine(25,426,455,426);
						GUI_DrawLine(25,641,455,641);
						GUI_DrawLine(25,211,25,641);
						GUI_DrawLine(240,211,240,641);
						GUI_DrawLine(455,211,455,641);
						GUI_DrawLine(25,211,455,641);
						GUI_DrawLine(455,211,25,641);
				break;
				
        case WM_INIT_DIALOG:
            //初始化对话框
            hItem = pMsg->hWin;
				    FRAMEWIN_SetTitleVis(hItem,0);
						//初始化按键
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
						BUTTON_SetFont(hItem, GUI_FONT_24_1);
						BUTTON_SetText(hItem, "break");
						//初始化文本框
					  hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
						TEXT_SetTextColor(hItem, GUI_RED);
            TEXT_SetFont(hItem,&GUI_Fontneirong55);
						WM_InvalidateWindow(pMsg->hWin);
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            switch(Id) {
								//返回键
                case ID_BUTTON_0: 
                    switch(NCode) {
                        case WM_NOTIFICATION_CLICKED:
                        break;
                        case WM_NOTIFICATION_RELEASED:
                        GUI_EndDialog(pMsg->hWin, 0);
												//返回主界面
                        GUI_CreateDialogBox(_aDialogCreate1, GUI_COUNTOF(_aDialogCreate1), _cbDialog1, WM_HBKWIN, 0, 0);
                        break;
                    }
                    break;
             }
        break;
        default:
						WM_DefaultProc(pMsg);
//						printf("%d    %d\n",xxxx,yyyy);
        break;
    }
}

//主界面创建（刚开始）
static WM_HWIN CreateFramewin1(void) { 
    WM_HWIN hWin;
    hWin = GUI_CreateDialogBox(_aDialogCreate0, GUI_COUNTOF(_aDialogCreate0), _cbDialog0, WM_HBKWIN, 0, 0);
    return hWin;
}




void MainTask(void) {

    GUI_Init();
		GUI_UC_SetEncodeUTF8();
    CreateFramewin1();
		WM_MULTIBUF_Enable(1);
//    while (1) {
//      GUI_Delay(100); 
//    }
}
