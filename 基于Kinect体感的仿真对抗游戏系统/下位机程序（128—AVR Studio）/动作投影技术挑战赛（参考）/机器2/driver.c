#include<avr/io.h>
#include<util/delay.h>
#include"driver.h"

void PWM_Init(){
	
	DDRB|= (1<<PB5)|(1<<PB6);  //PB5,PB6对应OC1A，OC1B
	
	TCCR1A = 0b10100010;
	TCCR1B = 0b00011010;       //模式14,快速PWM模式，TOP=ICRn，8分频，16M

	ICR1 = 300;	   //最大比对值

}

void move(int l_speed,int r_speed)     //l_speed,r_speed的范围为-300 ~ +300
{                                        //当速度达到200~300时基本没有太大的变化
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
