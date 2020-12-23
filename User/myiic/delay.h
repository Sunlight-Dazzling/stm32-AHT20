#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"
//	 

//STM32F103o?D?¡ã?¨¤y3¨¬
//?ao¡¥¨ºy¡ã?¡À?¨¤y3¨¬
/********** mcudev.taobao.com 3??¡¤  ********/


//¨º1¨®?SysTick¦Ì???¨ª¡§??¨ºy?¡ê¨º????¨®3¨´??DD1¨¹¨¤¨ª
//¡ã¨¹¨¤¡§delay_us,delay_ms

// 	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
