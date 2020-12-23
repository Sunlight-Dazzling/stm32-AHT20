#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
//��1��?IIC1 1��??M24C02,OLED,LM75AD,HT1382    PB6,PB7
 
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
 
//IO2������o����y	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //��?��?SDA 


//IIC?����D2������o����y
void IIC_Init(void);                //3?��??��IIC��?IO?��				 
void IIC_Start(void);				//����?��IIC?a��?D?o?
void IIC_Stop(void);	  			//����?��IIC����?1D?o?
void IIC_Send_Byte(u8 txd);			//IIC����?����???��??��
u8 IIC_Read_Byte(unsigned char ack);//IIC?����?��???��??��
u8 IIC_Wait_Ack(void); 				//IIC�̨���yACKD?o?
void IIC_Ack(void);					//IIC����?��ACKD?o?
void IIC_NAck(void);				//IIC2?����?��ACKD?o?
 
void IIC_WriteByte(uint16_t addr,uint8_t data,uint8_t device_addr);
uint16_t IIC_ReadByte(uint16_t addr,uint8_t device_addr,uint8_t ByteNumToRead);//??��??�¦�??����??��?t��??����?��a?����?��??����y  


void  read_AHT20_once(void);
void  reset_AHT20(void);
void  init_AHT20(void);	
void  startMeasure_AHT20(void);
void  read_AHT20(void);
uint8_t  Receive_ACK(void);
void  Send_ACK(void);
void  SendNot_Ack(void);
void I2C_WriteByte(uint8_t  input);
uint8_t I2C_ReadByte(void);	
void  set_AHT20sendOutData(void);
void  I2C_Start(void);
void  I2C_Stop(void);
#endif

