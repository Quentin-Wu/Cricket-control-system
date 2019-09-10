#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f4xx.h"
#include <stdio.h>



void uart3_init(u32 bound);
void Openmv_Receive_Data(int16_t data);//接收Openmv传过来的数据



#endif




