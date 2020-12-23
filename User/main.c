#include "delay.h"
#include "usart.h"
#include "bsp_i2c.h"


int main(void)
{	
	delay_init();     //?車那㊣o‘那y3?那??‘	  
	uart_init(115200);	 //∩??迆3?那??‘?a115200
	IIC_Init();
		while(1)
	{
		printf("恲僅坁僅珆尨");
		read_AHT20_once();
		delay_ms(1500);
  }
}
