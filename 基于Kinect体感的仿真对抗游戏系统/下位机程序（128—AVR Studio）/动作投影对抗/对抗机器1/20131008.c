#include <avr/io.h>                     //������ͷ�ļ�
#include <avr/iom128.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "system_init.h"                //������ϵͳ��ʼ���йغ���
void     rightinit(void);               //��������
void     leftinit(void);
void     leftrightinit(void);
void     rightping(void);
void     leftping(void); 
void     leftrightping(void);
void     leftgao(void); 
void     rightgao(void); 
void     leftrightgao(void);
void     leftxia(void);
void     rightxia(void);
void     zuorightxia(void);
void     leftgou(void);
void     yougou(void);
int      Duosu = 600;                   //����ٶ�

  
int main(void)                         //������
{   
    PWM_init();                        //PWM��ʼ��
	System_Init();                     //ϵͳ��ʼ��
    DDRA=0XFF;
	DDRC=0XF0;
	//PORTC = 0XFF;
	unsigned char i,m;
	int l=200,r=200,a=100,b=100;
	cli();                                  //�����ж�
	for(m=1;m<=6;m++)                       //����6�������1��6������ģʽΪ���ģʽ
    SetServoLimit(m,0,1023);                 
	_delay_ms(30);  
	for(m=1;m<=6;m++)  
	SetServoLimit(m,0,1023);    
	_delay_ms(30);                                     
	leftrightinit();                        //�����ֳ�ʼ�����ظ�����֤�źŴ���׼ȷ�ԣ�
	_delay_ms(30);   
	leftrightinit();  
	_delay_ms(30);
	leftrightinit();             
	_delay_ms(50);
	while(1)                               //ѭ���ж���λ�����͵�ָ���ź�
	{   
		i=USART1_recieve();                //����1������λ��ָ���ź�    
		switch(i)                          //�ж�
		{     
			case '0': move(120,120);   _delay_ms(70);move(0,0);break;          //���
			case '1': move(-120,-120); _delay_ms(70);move(0,0);break;
			case '2': move(-120,120);  _delay_ms(60);move(0,0);break;
			case '3': move(120,-120);  _delay_ms(60);move(0,0);break;
			case '4': move(220,220);   _delay_ms(70);move(0,0);break;
			case 'p': move(-170,-170); _delay_ms(70);move(0,0);break;

		    
			case '9': rightinit(); break;    //���ֳ�ʼ��                        //���
			case '5': rightgao();  break;    //���ָ߾�
			case 'j': rightqian(); break;    //����ǰ��
            case 'a': rightgou();  break;    //�ҹ���
			case '7': rightxia();  break;    //����
	    	
			case 'i': leftinit(); break;     //���ֳ�ʼ��
			case 'e': leftgao();  break;     //���ָ߾�
			case 'm': leftqian(); break;     //����ǰ��
			case 'b': leftgou();  break;     //����
			case 'g': leftxia();  break;     //����
			default : break;
		}
		USART1_send(i);  
	}	
}

void   leftrightinit()                      //�����ֳ�ʼ��     
      {
		SetServoPosition(1,323,Duosu);
		SetServoPosition(2,532,Duosu);
		SetServoPosition(3,314,Duosu);
		SetServoPosition(4,600,Duosu);
		SetServoPosition(5,441,Duosu);
		SetServoPosition(6,603,Duosu);
	  }

void   rightinit()                          //���ֳ�ʼ��     
      {
		SetServoPosition(4,600,Duosu);
		SetServoPosition(5,441,Duosu);
		SetServoPosition(6,603,Duosu);
	   }

void  rightgao()                            //���ָ߾�
     {
	    SetServoPosition(4,852,Duosu);
	    SetServoPosition(5,503,Duosu);
		SetServoPosition(6,442,Duosu);
	  }


void  rightqian()                           //����ǰ��
     {
	    SetServoPosition(4,747,Duosu);
		SetServoPosition(5,503,Duosu);
		SetServoPosition(6,442,Duosu);
	 }

void  rightgou()                            //�ҹ���
    {
	    SetServoPosition(4,747,Duosu);
		SetServoPosition(5,345,Duosu);
	    SetServoPosition(6,562,Duosu);
     }

void  rightxia()                           //�����¾�
     {
        SetServoPosition(4,579,Duosu);
        SetServoPosition(5,503,Duosu);
	    SetServoPosition(6,442,Duosu);
	 }

void   leftinit()                          //���ֳ�ʼ��     
      { 
	    SetServoPosition(1,323,Duosu);
		SetServoPosition(2,532,Duosu);
		SetServoPosition(3,314,Duosu);
	   }

void  leftgao()                            //���ָ߾�
     {
	    SetServoPosition(1,493,Duosu);
		SetServoPosition(2,536,Duosu);
	    SetServoPosition(3,29,Duosu);
      }

void   leftqian()                          //����ǰ��
     {
	    SetServoPosition(1,493,Duosu);
		SetServoPosition(2,536,Duosu);
		SetServoPosition(3,134,Duosu);
	  }

void  leftgou()                            //����
     {
	    SetServoPosition(1,339,Duosu);
		SetServoPosition(2,395,Duosu);
	    SetServoPosition(3,134,Duosu);
     }

void  leftxia()                            //�����¾�
     {
	    SetServoPosition(1,493,Duosu);
		SetServoPosition(2,536,Duosu);
	    SetServoPosition(3,276,Duosu);
	 }

 










