#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
//	 

//STM32F103o?D?��?��y3��
//?ao����y��?��?��y3��
/********** mcudev.taobao.com 3??��  ********/


//��1��?SysTick��???����??��y?�꨺????��3��??DD1������
//�㨹����delay_us,delay_ms

// 	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
