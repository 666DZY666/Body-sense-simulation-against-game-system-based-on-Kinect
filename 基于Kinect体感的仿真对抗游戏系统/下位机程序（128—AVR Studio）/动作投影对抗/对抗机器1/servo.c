#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "system_init.h"              //定义与系统初始化有关函数

void SendUart0Byte(unsigned char data)
 {
       while ( !( UCSR0A & (1<<UDRE)) );   // 等待发送缓冲器为空 // waiting for finishing sending all datas in the Transmit Buffer
	   UDR0 = data;                       /* 将数据放入缓冲器，发送数据*/

 }

void SetServoLimit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit)
 {

     unsigned short int temp_ccw = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
     unsigned short int temp_cw = 0;
     unsigned char temp_ccw_h = 0; // 待发送数据h位 // (h bits to be sended)
     unsigned char temp_ccw_l = 0; // 待发送数据l位 // (l bits to be sended)
     unsigned char temp_cw_h = 0;
     unsigned char temp_cw_l = 0;
	   unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)

	 if (ccw_limit > 1023)
	       {
		      temp_ccw = 1023; // 限制速度值在可用范围内 // (limit the velocity to 0-1023)
		   }
	 else
	     {
		  temp_ccw = ccw_limit;
		  }
	 if (cw_limit > 1023)
		   {
		    temp_cw = 1023;
		   }
     else
	    {
		 temp_cw = cw_limit;
	    }

     temp_ccw_h = (unsigned char)(temp_ccw >> 8);
     temp_ccw_l = (unsigned char)temp_ccw; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
	 temp_cw_h = (unsigned char)(temp_cw >> 8);
	 temp_cw_l = (unsigned char)temp_cw; // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
	 PORTG &= ~_BV(PG4);
	 PORTG |= _BV(PG3); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
	 UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 // (Clear written flag of UART0)
	 SendUart0Byte(0xFF); // 发送启动符号0xFF // (Send the start byte 0xff)
	 SendUart0Byte(0xFF); // 发送启动符号0xFF // (Send the start byte 0xff)
	 SendUart0Byte(id); // 发送id // (Send the servo’s ID)
	 SendUart0Byte(7); // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
	 SendUart0Byte(0x03); // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
	 SendUart0Byte(0x06); // 舵机控制寄存器首地址 // (Send the start address of control rigister)
	 SendUart0Byte(temp_cw_l); // 发送顺时针位置限制低位
	 SendUart0Byte(temp_cw_h); // 发送顺时针位置限制高位 //(Send the high byte of clockwise position limit)
	 SendUart0Byte(temp_ccw_l); // 发送逆时针位置限制低位 // (Send the low byte of counterclockwise position limit)
	 SendUart0Byte(temp_ccw_h); // 发送逆时针位置限制高位 // (Send the low byte of counterclockwise position limit)
	 temp_sum = id + 7 + 0x03 + 0x06 + temp_cw_l + temp_cw_h + temp_ccw_l + temp_ccw_h;
	 temp_sum = ~temp_sum; // 计算校验和 // (Calculate the checksum)
	 SendUart0Byte(temp_sum); // 发送校验和 // (Send checksum)
	 while ( !( UCSR0A & (1<<TXC0)) ); // 等待发送完成

	 PORTG |= _BV(PG4);

	 PORTG &= ~_BV(PG3);  // 使总线处于主机接收状态 // (Set the UART bus to host receiving state)
	 _delay_ms(2);        //送完成后，总线会被从机占用，反馈应答数据，所以进行延时
					               // (The bus will be overrode by slave after finishing sending
								   // to receive the answer, so here delays 2 ms.)

}





void SetServoPosition(unsigned char id, unsigned short int position, unsigned short int velocity)
{

   unsigned short int temp_velocity = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
   unsigned short int temp_position = 0;
   unsigned char temp_velocity_h = 0; // 待发送数据h位 // (h bits to be sended)
   unsigned char temp_velocity_l = 0; // 待发送数据l位 // (l bits to be sended)
   unsigned char temp_position_h = 0;
   unsigned char temp_position_l = 0;
   unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)
   if (velocity > 1023)
   {
    temp_velocity = 1023; // 限制速度值在可用范围内 // (limit the velocity to 0-1023)
   }
   else
   {
   temp_velocity = velocity;
   }
   if (position > 1023)
   {
   temp_position = 1023;
   }
   else
   {
   temp_position = position;
   }

   temp_velocity_h = (unsigned char)(temp_velocity >> 8); // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
   temp_velocity_l = (unsigned char)temp_velocity;
   temp_position_h = (unsigned char)(temp_position >> 8); // 将16bit数据拆为2个8bit数据 // (split 16 bits to 2 bytes)
   temp_position_l = (unsigned char)temp_position;
   PORTG &= ~_BV(PG4);
   	 PORTG |= _BV(PG3); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
   UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 // (Clear written flag of UART0)
   SendUart0Byte(0xFF); // 发送启动符号0xFF // (Send the start byte 0xff)
   SendUart0Byte(0xFF); SendUart0Byte(id); // 发送id // (Send the servo’s ID)
   SendUart0Byte(7); // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
   SendUart0Byte(0x03); // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
   SendUart0Byte(0x1E); // 舵机控制寄存器首地址 // (Send the start address of control register)
   SendUart0Byte(temp_position_l); // 发送速度数据低位 // (Send the low byte of velocity)
   SendUart0Byte(temp_position_h); // 发送速度数据高位 // (Send the high byte of velocity)
   SendUart0Byte(temp_velocity_l); //发送位置低字节 // (Send the low byte of position)
   SendUart0Byte(temp_velocity_h); // 发送位置高字节 // (Send the high byte of position)
   temp_sum = id + 7 + 0x03 + 0x1E + temp_position_l + temp_position_h + temp_velocity_l + temp_velocity_h;
   temp_sum = ~temp_sum; // 计算校验和
   SendUart0Byte(temp_sum); // 发送校验和 (Send the checksum)
   while ( !( UCSR0A & (1<<TXC0)) ) // 等待发送完成
   {
                 // (Waiting for finishing sending)
   ;
   }
   PORTG |= _BV(PG4);

  	 PORTG &= ~_BV(PG3);  // 使总线处于主机接收状态 // (Set the UART bus to host receiving state)
   _delay_ms(2); // 发送完成后，总线会被从机占用，反馈应答数据，所以进行延时
                 // (The bus will be overrode by slave after finishing sending
				 // to receive the answer, so here delays 2 ms.)

}

void Action_write(unsigned char id,unsigned short int position,unsigned short int velocity)
{
	unsigned short int temp_velocity=0;
	unsigned short int temp_position=0;
	unsigned char temp_velocity_h=0;
	unsigned char temp_velocity_l=0;
	unsigned char temp_position_h=0;
	unsigned char temp_position_l=0;
	unsigned char temp_sum=0;	
	temp_velocity=velocity;
	temp_position=position;
	temp_velocity_h=(unsigned char)(temp_velocity>>8);
	temp_velocity_l=(unsigned char)temp_velocity;
	temp_position_h=(unsigned char)(temp_position>>8);
	temp_position_l=(unsigned char)temp_position;
	 PORTG &= ~_BV(PG4); 
    PORTG |= _BV(PG3); // 使总线处于主机发送状态 

    UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 
	SendUart0Byte(0xFF);
	SendUart0Byte(0xFF);
	SendUart0Byte(id);
	SendUart0Byte(7);
	SendUart0Byte(0x04);
	SendUart0Byte(0x1E);
	SendUart0Byte(temp_position_l);
	SendUart0Byte(temp_position_h);
	SendUart0Byte(temp_velocity_l);
	SendUart0Byte(temp_velocity_h);
	temp_sum=id+ 7 + 0x04 + 0x1e + temp_position_l + temp_position_h + temp_velocity_l + temp_velocity_h;
	temp_sum=~temp_sum;
	SendUart0Byte(temp_sum);
	
	 while ( !( UCSR0A & (1<<TXC0)) ) // 等待发送完成 
{ 
; 
} 
PORTG &=~_BV(PG3);
PORTG |=_BV(PG4); // 使总线处于主机接收状态 
_delay_ms(2);
}
void Action()
{
	unsigned char temp_sum=0;
    PORTG &= ~_BV(PG4); 
    PORTG |= _BV(PG3); // 使总线处于主机发送状态 

    UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 	
	SendUart0Byte(0xFF);
	SendUart0Byte(0xFF);
	SendUart0Byte(0xFE);
	SendUart0Byte(2);
	SendUart0Byte(0x05);
	temp_sum=0xFE + 0x02 + 0x05;
	temp_sum=~temp_sum;
	SendUart0Byte(temp_sum);
	
	 while ( !( UCSR0A & (1<<TXC0)) ) // 等待发送完成 
{ 
; 
} 
PORTG &=~_BV(PG3);
PORTG |=_BV(PG4); // 使总线处于主机接收状态 
_delay_ms(2);
}


void SetServoVelocity(unsigned char id, signed short int velocity)
{
     unsigned char temp_sign = 0; // 临时符号，用于进行方向判别 // (temp variable to judge the direction)
	 unsigned short int temp_velocity = 0; // 临时速度，用于进行方向判别 // (temp velocity to judge the direction)
	 unsigned char temp_value_h = 0; // 待发送数据h位 // (h bits to send)
	 unsigned char temp_value_l = 0; // 待发送数据l位 // (l bits to send)
	 unsigned char temp_sum = 0; // 校验和寄存变量 // (temp variable to save checksum)
	 if (velocity < 0)
	 { temp_velocity = -velocity; // 如果为负数，则取绝对值 // (if negative, get the absolute value)
	 temp_sign = 1; // 设置负数符号标志 // (Set negative flag)
	 }
	 else
	 {
	 temp_velocity = velocity;
	 temp_sign = 0; // 设置正数符号标志
	 }

	 if (temp_velocity > 1023)
	 {
	 temp_velocity = 1023; // 限制速度值在可用范围内 // (Limit the velocity to 0-1023)
	 } // 设置bit10为方向位，这时temp_velocity就是待发送的速度数据了
	 // (Set bit0 as direction bit, then temp_velocity is the data to be sended)
	 temp_velocity |= (temp_sign << 10); temp_value_h = (unsigned char)(temp_velocity >> 8); // 将16bit数据拆为2个8bit数据
	 // (Split the 16 bits to 2 bytes)
	 temp_value_l = (unsigned char)temp_velocity;
	 PORTG &= ~_BV(PG4);
	 	 PORTG |= _BV(PG3); // 使总线处于主机发送状态 // (Set the bus to host transmit state)
	 UCSR0A |= (1<<TXC0); // 清除UART0写完成标志 // (Clear written flag of UART0)
	 SendUart0Byte(0xFF); // 发送启动符号0xFF // (Send the start byte 0xFF)
	 SendUart0Byte(0xFF); // 发送启动符号0xFF // (Send the start byte 0xFF)
	 SendUart0Byte(id); // 发送id // (Send the servo’s ID)
	 SendUart0Byte(5); // 发送数据长度为参数长度+2，参数长度为3 // (Send the length of frame)
	 SendUart0Byte(0x03); // 命令数据为“WRITE DATA” // (Send command “WRITE DATA”)
	 SendUart0Byte(0x20); // 舵机控制寄存器首地址 // (Send the start address of control register)
	 SendUart0Byte(temp_value_l); // 发送速度数据低位 // (Send the low byte of velocity)
	 SendUart0Byte(temp_value_h); // 发送速度数据高位 // (Send the high byte of velocity)
	 temp_sum = id + 5 + 0x03 + 0x20 + temp_value_l + temp_value_h; temp_sum = ~temp_sum; // 计算校验和 // (Calculate the checksum)
	 SendUart0Byte(temp_sum); // 发送校验和 // (Send the checksum)
	 while ( !( UCSR0A & (1<<TXC0)) ) // 等待发送完成
	        {   ;}           // (Waiting for finishing sending)

	 PORTG |= _BV(PG4);

		 PORTG &= ~_BV(PG3);  // 使总线处于主机接收状态 // (Set the UART bus to host receiving state)
	 _delay_ms(2);      // 发送完成后，总线会被从机占用，反馈应答数据，所以进行延时
	 }
