#include "sys.h"
#include "usart.h"


//STM32F103o?D?��?��y3��
//?ao����y��?��?��y3��
/********** mcudev.taobao.com 3??��  ********/


// 	 
//��?1?��1��?ucos,?���㨹����????��?����???t?��?��.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ��1��?	  
#endif
//	 
//STM32?a�����?
//��??��13?��??��		   

// 	  
 

//
//?����?��???�䨲??,?��3?printfo����y,??2?D����a????use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//������??aD����a��??��3?o����y                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//?����?_sys_exit()��?����?a��1��?��??��?��?�꨺?    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//???����?fputco����y 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//?-?������?��,?����?����?��������?   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*��1��?microLib��?��?����*/
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
 
#if EN_USART1_RX   //��?1?��1?����??����?
//��??��1?D??��t??3��D��
//���騰a,?����?USARTx->SR?������?a?a??????��?�䨪?��   	
u8 USART_RX_BUF[USART_REC_LEN];     //?����??o3?,��?�䨮USART_REC_LEN??��??��.
//?����?���䨬?
//bit15��?	?����?����3������??
//bit14��?	?����?��?0x0d
//bit13~0��?	?����?��?��?��DD���??����y??
u16 USART_RX_STA=0;       //?����?���䨬?����??	  
  
void uart_init(u32 bound){
    //GPIO???������??
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//��1?��USART1��?GPIOA����?��
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//?�䨮?��?������?3?
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//????��?��?
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ????

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//?��??��??��??3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//������??��??3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ�����̨���1?��
	NVIC_Init(&NVIC_InitStructure);	//?��?Y???����?2?��y3?��??��VIC??��??��
  
   //USART 3?��??������??

	USART_InitStructure.USART_BaudRate = bound;//��?��?����???a9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��?3��?a8??��y?Y??��?
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//��???����?1??
	USART_InitStructure.USART_Parity = USART_Parity_No;//?T????D��?��??
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//?T��2?t��y?Y����????
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//��?����?�꨺?

    USART_Init(USART1, &USART_InitStructure); //3?��??����??��
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//?a???D??
    USART_Cmd(USART1, ENABLE);                    //��1?����??�� 

}



void USART1_IRQHandler(void)                	//��??��1?D??��t??3��D��
	{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//��?1?����?��?��??��y?����?��?,?��?�¨�a��1��?ucosII��?.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //?����??D??(?����?��?��?��y?Y��?D?��?0x0d 0x0a?��?2)
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//?����??����?��?��?��y?Y
		
		if((USART_RX_STA&0x8000)==0)//?����??�䨪��3��
			{
			if(USART_RX_STA&0x4000)//?����?��?��?0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//?����?�䨪?��,??D??a��?
				else USART_RX_STA|=0x8000;	//?����?����3����? 
				}
			else //?1??��?��?0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//?����?��y?Y�䨪?��,??D??a��??����?	  
					}		 
				}
			}   		 
     } 
#ifdef OS_TICKS_PER_SEC	 	//��?1?����?��?��??��y?����?��?,?��?�¨�a��1��?ucosII��?.
	OSIntExit();  											 
#endif
} 
#endif	

