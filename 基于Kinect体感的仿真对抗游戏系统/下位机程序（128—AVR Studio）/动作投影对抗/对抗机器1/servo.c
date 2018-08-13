#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "system_init.h"              //������ϵͳ��ʼ���йغ���

void SendUart0Byte(unsigned char data)
 {
       while ( !( UCSR0A & (1<<UDRE)) );   // �ȴ����ͻ�����Ϊ�� // waiting for finishing sending all datas in the Transmit Buffer
	   UDR0 = data;                       /* �����ݷ��뻺��������������*/

 }

void SetServoLimit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit)
 {

     unsigned short int temp_ccw = 0; // ��ʱ�ٶȣ����ڽ��з����б� // (temp velocity to judge the direction)
     unsigned short int temp_cw = 0;
     unsigned char temp_ccw_h = 0; // ����������hλ // (h bits to be sended)
     unsigned char temp_ccw_l = 0; // ����������lλ // (l bits to be sended)
     unsigned char temp_cw_h = 0;
     unsigned char temp_cw_l = 0;
	   unsigned char temp_sum = 0; // У��ͼĴ���� // (temp variable to save checksum)

	 if (ccw_limit > 1023)
	       {
		      temp_ccw = 1023; // �����ٶ�ֵ�ڿ��÷�Χ�� // (limit the velocity to 0-1023)
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
     temp_ccw_l = (unsigned char)temp_ccw; // ��16bit���ݲ�Ϊ2��8bit���� // (split 16 bits to 2 bytes)
	 temp_cw_h = (unsigned char)(temp_cw >> 8);
	 temp_cw_l = (unsigned char)temp_cw; // ��16bit���ݲ�Ϊ2��8bit���� // (split 16 bits to 2 bytes)
	 PORTG &= ~_BV(PG4);
	 PORTG |= _BV(PG3); // ʹ���ߴ�����������״̬ // (Set the bus to host transmit state)
	 UCSR0A |= (1<<TXC0); // ���UART0д��ɱ�־ // (Clear written flag of UART0)
	 SendUart0Byte(0xFF); // ������������0xFF // (Send the start byte 0xff)
	 SendUart0Byte(0xFF); // ������������0xFF // (Send the start byte 0xff)
	 SendUart0Byte(id); // ����id // (Send the servo��s ID)
	 SendUart0Byte(7); // �������ݳ���Ϊ��������+2����������Ϊ3 // (Send the length of frame)
	 SendUart0Byte(0x03); // ��������Ϊ��WRITE DATA�� // (Send command ��WRITE DATA��)
	 SendUart0Byte(0x06); // ������ƼĴ����׵�ַ // (Send the start address of control rigister)
	 SendUart0Byte(temp_cw_l); // ����˳ʱ��λ�����Ƶ�λ
	 SendUart0Byte(temp_cw_h); // ����˳ʱ��λ�����Ƹ�λ //(Send the high byte of clockwise position limit)
	 SendUart0Byte(temp_ccw_l); // ������ʱ��λ�����Ƶ�λ // (Send the low byte of counterclockwise position limit)
	 SendUart0Byte(temp_ccw_h); // ������ʱ��λ�����Ƹ�λ // (Send the low byte of counterclockwise position limit)
	 temp_sum = id + 7 + 0x03 + 0x06 + temp_cw_l + temp_cw_h + temp_ccw_l + temp_ccw_h;
	 temp_sum = ~temp_sum; // ����У��� // (Calculate the checksum)
	 SendUart0Byte(temp_sum); // ����У��� // (Send checksum)
	 while ( !( UCSR0A & (1<<TXC0)) ); // �ȴ��������

	 PORTG |= _BV(PG4);

	 PORTG &= ~_BV(PG3);  // ʹ���ߴ�����������״̬ // (Set the UART bus to host receiving state)
	 _delay_ms(2);        //����ɺ����߻ᱻ�ӻ�ռ�ã�����Ӧ�����ݣ����Խ�����ʱ
					               // (The bus will be overrode by slave after finishing sending
								   // to receive the answer, so here delays 2 ms.)

}





void SetServoPosition(unsigned char id, unsigned short int position, unsigned short int velocity)
{

   unsigned short int temp_velocity = 0; // ��ʱ�ٶȣ����ڽ��з����б� // (temp velocity to judge the direction)
   unsigned short int temp_position = 0;
   unsigned char temp_velocity_h = 0; // ����������hλ // (h bits to be sended)
   unsigned char temp_velocity_l = 0; // ����������lλ // (l bits to be sended)
   unsigned char temp_position_h = 0;
   unsigned char temp_position_l = 0;
   unsigned char temp_sum = 0; // У��ͼĴ���� // (temp variable to save checksum)
   if (velocity > 1023)
   {
    temp_velocity = 1023; // �����ٶ�ֵ�ڿ��÷�Χ�� // (limit the velocity to 0-1023)
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

   temp_velocity_h = (unsigned char)(temp_velocity >> 8); // ��16bit���ݲ�Ϊ2��8bit���� // (split 16 bits to 2 bytes)
   temp_velocity_l = (unsigned char)temp_velocity;
   temp_position_h = (unsigned char)(temp_position >> 8); // ��16bit���ݲ�Ϊ2��8bit���� // (split 16 bits to 2 bytes)
   temp_position_l = (unsigned char)temp_position;
   PORTG &= ~_BV(PG4);
   	 PORTG |= _BV(PG3); // ʹ���ߴ�����������״̬ // (Set the bus to host transmit state)
   UCSR0A |= (1<<TXC0); // ���UART0д��ɱ�־ // (Clear written flag of UART0)
   SendUart0Byte(0xFF); // ������������0xFF // (Send the start byte 0xff)
   SendUart0Byte(0xFF); SendUart0Byte(id); // ����id // (Send the servo��s ID)
   SendUart0Byte(7); // �������ݳ���Ϊ��������+2����������Ϊ3 // (Send the length of frame)
   SendUart0Byte(0x03); // ��������Ϊ��WRITE DATA�� // (Send command ��WRITE DATA��)
   SendUart0Byte(0x1E); // ������ƼĴ����׵�ַ // (Send the start address of control register)
   SendUart0Byte(temp_position_l); // �����ٶ����ݵ�λ // (Send the low byte of velocity)
   SendUart0Byte(temp_position_h); // �����ٶ����ݸ�λ // (Send the high byte of velocity)
   SendUart0Byte(temp_velocity_l); //����λ�õ��ֽ� // (Send the low byte of position)
   SendUart0Byte(temp_velocity_h); // ����λ�ø��ֽ� // (Send the high byte of position)
   temp_sum = id + 7 + 0x03 + 0x1E + temp_position_l + temp_position_h + temp_velocity_l + temp_velocity_h;
   temp_sum = ~temp_sum; // ����У���
   SendUart0Byte(temp_sum); // ����У��� (Send the checksum)
   while ( !( UCSR0A & (1<<TXC0)) ) // �ȴ��������
   {
                 // (Waiting for finishing sending)
   ;
   }
   PORTG |= _BV(PG4);

  	 PORTG &= ~_BV(PG3);  // ʹ���ߴ�����������״̬ // (Set the UART bus to host receiving state)
   _delay_ms(2); // ������ɺ����߻ᱻ�ӻ�ռ�ã�����Ӧ�����ݣ����Խ�����ʱ
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
    PORTG |= _BV(PG3); // ʹ���ߴ�����������״̬ 

    UCSR0A |= (1<<TXC0); // ���UART0д��ɱ�־ 
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
	
	 while ( !( UCSR0A & (1<<TXC0)) ) // �ȴ�������� 
{ 
; 
} 
PORTG &=~_BV(PG3);
PORTG |=_BV(PG4); // ʹ���ߴ�����������״̬ 
_delay_ms(2);
}
void Action()
{
	unsigned char temp_sum=0;
    PORTG &= ~_BV(PG4); 
    PORTG |= _BV(PG3); // ʹ���ߴ�����������״̬ 

    UCSR0A |= (1<<TXC0); // ���UART0д��ɱ�־ 	
	SendUart0Byte(0xFF);
	SendUart0Byte(0xFF);
	SendUart0Byte(0xFE);
	SendUart0Byte(2);
	SendUart0Byte(0x05);
	temp_sum=0xFE + 0x02 + 0x05;
	temp_sum=~temp_sum;
	SendUart0Byte(temp_sum);
	
	 while ( !( UCSR0A & (1<<TXC0)) ) // �ȴ�������� 
{ 
; 
} 
PORTG &=~_BV(PG3);
PORTG |=_BV(PG4); // ʹ���ߴ�����������״̬ 
_delay_ms(2);
}


void SetServoVelocity(unsigned char id, signed short int velocity)
{
     unsigned char temp_sign = 0; // ��ʱ���ţ����ڽ��з����б� // (temp variable to judge the direction)
	 unsigned short int temp_velocity = 0; // ��ʱ�ٶȣ����ڽ��з����б� // (temp velocity to judge the direction)
	 unsigned char temp_value_h = 0; // ����������hλ // (h bits to send)
	 unsigned char temp_value_l = 0; // ����������lλ // (l bits to send)
	 unsigned char temp_sum = 0; // У��ͼĴ���� // (temp variable to save checksum)
	 if (velocity < 0)
	 { temp_velocity = -velocity; // ���Ϊ��������ȡ����ֵ // (if negative, get the absolute value)
	 temp_sign = 1; // ���ø������ű�־ // (Set negative flag)
	 }
	 else
	 {
	 temp_velocity = velocity;
	 temp_sign = 0; // �����������ű�־
	 }

	 if (temp_velocity > 1023)
	 {
	 temp_velocity = 1023; // �����ٶ�ֵ�ڿ��÷�Χ�� // (Limit the velocity to 0-1023)
	 } // ����bit10Ϊ����λ����ʱtemp_velocity���Ǵ����͵��ٶ�������
	 // (Set bit0 as direction bit, then temp_velocity is the data to be sended)
	 temp_velocity |= (temp_sign << 10); temp_value_h = (unsigned char)(temp_velocity >> 8); // ��16bit���ݲ�Ϊ2��8bit����
	 // (Split the 16 bits to 2 bytes)
	 temp_value_l = (unsigned char)temp_velocity;
	 PORTG &= ~_BV(PG4);
	 	 PORTG |= _BV(PG3); // ʹ���ߴ�����������״̬ // (Set the bus to host transmit state)
	 UCSR0A |= (1<<TXC0); // ���UART0д��ɱ�־ // (Clear written flag of UART0)
	 SendUart0Byte(0xFF); // ������������0xFF // (Send the start byte 0xFF)
	 SendUart0Byte(0xFF); // ������������0xFF // (Send the start byte 0xFF)
	 SendUart0Byte(id); // ����id // (Send the servo��s ID)
	 SendUart0Byte(5); // �������ݳ���Ϊ��������+2����������Ϊ3 // (Send the length of frame)
	 SendUart0Byte(0x03); // ��������Ϊ��WRITE DATA�� // (Send command ��WRITE DATA��)
	 SendUart0Byte(0x20); // ������ƼĴ����׵�ַ // (Send the start address of control register)
	 SendUart0Byte(temp_value_l); // �����ٶ����ݵ�λ // (Send the low byte of velocity)
	 SendUart0Byte(temp_value_h); // �����ٶ����ݸ�λ // (Send the high byte of velocity)
	 temp_sum = id + 5 + 0x03 + 0x20 + temp_value_l + temp_value_h; temp_sum = ~temp_sum; // ����У��� // (Calculate the checksum)
	 SendUart0Byte(temp_sum); // ����У��� // (Send the checksum)
	 while ( !( UCSR0A & (1<<TXC0)) ) // �ȴ��������
	        {   ;}           // (Waiting for finishing sending)

	 PORTG |= _BV(PG4);

		 PORTG &= ~_BV(PG3);  // ʹ���ߴ�����������״̬ // (Set the UART bus to host receiving state)
	 _delay_ms(2);      // ������ɺ����߻ᱻ�ӻ�ռ�ã�����Ӧ�����ݣ����Խ�����ʱ
	 }
