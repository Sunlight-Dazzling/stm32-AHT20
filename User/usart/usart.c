#include "sys.h"
#include "usart.h"


//STM32F103o?D?～?角y3足
//?ao‘那y～?㊣?角y3足
/********** mcudev.taobao.com 3??﹞  ********/


// 	 
//豕?1?那1車?ucos,?辰～邦角“????米?赤﹞???t?∩?谷.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 那1車?	  
#endif
//	 
//STM32?a﹞⊿～?
//∩??迆13?那??‘		   

// 	  
 

//
//?車豕?辰???∩迆??,?∫3?printfo‘那y,??2?D豕辰a????use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//㊣那℅??aD豕辰a米??∫3?o‘那y                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//?“辰?_sys_exit()辰?㊣邦?a那1車?～??¯?迆?㏒那?    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//???“辰?fputco‘那y 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//?-?﹞﹞⊿?赤,?㊣米?﹞⊿?赤赤那㊣?   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*那1車?microLib米?﹞?﹞“*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //豕?1?那1?邦芍??車那?
//∩??迆1?D??﹞t??3足D辰
//℅⊿辰a,?芍豕?USARTx->SR?邦㊣邦?a?a??????米?∩赤?車   	
u8 USART_RX_BUF[USART_REC_LEN];     //?車那??o3?,℅?∩車USART_REC_LEN??℅??迆.
//?車那?℅∩足?
//bit15㏒?	?車那?赤那3谷㊣那??
//bit14㏒?	?車那?米?0x0d
//bit13~0㏒?	?車那?米?米?車DD∫℅??迆那y??
u16 USART_RX_STA=0;       //?車那?℅∩足?㊣那??	  
  
void uart_init(u32 bound){
    //GPIO???迆谷豕??
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//那1?邦USART1㏒?GPIOA那㊣?車
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//?∩車?赤?赤足那?3?
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//????那?豕?
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ????

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//?角??車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//℅車車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ赤“米角那1?邦
	NVIC_Init(&NVIC_InitStructure);	//?迄?Y???“米?2?那y3?那??‘VIC??∩??¯
  
   //USART 3?那??‘谷豕??

	USART_InitStructure.USART_BaudRate = bound;//辰?～?谷豕???a9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//℅?3∟?a8??那y?Y??那?
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//辰???赤㏒?1??
	USART_InitStructure.USART_Parity = USART_Parity_No;//?T????D㏒?谷??
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//?T車2?t那y?Y芍¯????
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//那?﹞⊿?㏒那?

    USART_Init(USART1, &USART_InitStructure); //3?那??‘∩??迆
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//?a???D??
    USART_Cmd(USART1, ENABLE);                    //那1?邦∩??迆 

}



void USART1_IRQHandler(void)                	//∩??迆1?D??﹞t??3足D辰
	{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//豕?1?那㊣?車?迆??那y?“辰?芍?,?米?¯辰a那1車?ucosII芍?.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //?車那??D??(?車那?米?米?那y?Y㊣?D?那?0x0d 0x0a?芍?2)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//?芍豕??車那?米?米?那y?Y
		
		if((USART_RX_STA&0x8000)==0)//?車那??∩赤那3谷
			{
			if(USART_RX_STA&0x4000)//?車那?米?芍?0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//?車那?∩赤?車,??D??a那?
				else USART_RX_STA|=0x8000;	//?車那?赤那3谷芍? 
				}
			else //?1??那?米?0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//?車那?那y?Y∩赤?車,??D??a那??車那?	  
					}		 
				}
			}   		 
     } 
#ifdef OS_TICKS_PER_SEC	 	//豕?1?那㊣?車?迆??那y?“辰?芍?,?米?¯辰a那1車?ucosII芍?.
	OSIntExit();  											 
#endif
} 
#endif	

