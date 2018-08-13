#include<avr/io.h>
#include<util/delay.h>
#include"driver.h"

void PWM_Init(){
	
	DDRB|= (1<<PB5)|(1<<PB6);  //PB5,PB6��ӦOC1A��OC1B
	
	TCCR1A = 0b10100010;
	TCCR1B = 0b00011010;       //ģʽ14,����PWMģʽ��TOP=ICRn��8��Ƶ��16M

	ICR1 = 300;	   //���ȶ�ֵ

}

void move(int l_speed,int r_speed)     //l_speed,r_speed�ķ�ΧΪ-300 ~ +300
{                                        //���ٶȴﵽ200~300ʱ����û��̫��ı仯
    if(l_speed>=0&&r_speed>=0)
	{     
		PORTC |= 0X02;//PC1=1
		PORTC &= 0XFE;//PC0=0
	}
    else if(l_speed>0&&r_speed<0)
	{     
		PORTC |= 0x03; //PC0.1=1
		r_speed=0-r_speed;
	}
	else if(l_speed<0&&r_speed>0)
	{     
		PORTC &= 0xFC;//PC0.1=0
		l_speed=0-l_speed;
	}
	else
	{
		PORTC |= 0X01;//PC0=1
		PORTC &= 0XFD;//PC1=0
		r_speed=0-r_speed;l_speed=0-l_speed;
	}
	OCR1A = l_speed;
	OCR1B = r_speed;	
}
