#include <avr/io.h>                     //声明，头文件
#include <avr/iom128.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "system_init.h"                //定义与系统初始化有关函数
void     rightinit(void);               //函数声明
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
int      Duosu = 600;                   //舵机速度

  
int main(void)                         //主函数
{   
    PWM_init();                        //PWM初始化
	System_Init();                     //系统初始化
    DDRA=0XFF;
	DDRC=0XF0;
	//PORTC = 0XFF;
	unsigned char i,m;
	int l=200,r=200,a=100,b=100;
	cli();                                  //关总中断
	for(m=1;m<=6;m++)                       //设置6个舵机（1—6）工作模式为舵机模式
    SetServoLimit(m,0,1023);                 
	_delay_ms(30);  
	for(m=1;m<=6;m++)  
	SetServoLimit(m,0,1023);    
	_delay_ms(30);                                     
	leftrightinit();                        //左右手初始化（重复，保证信号传输准确性）
	_delay_ms(30);   
	leftrightinit();  
	_delay_ms(30);
	leftrightinit();             
	_delay_ms(50);
	while(1)                               //循环判断上位机发送的指令信号
	{   
		i=USART1_recieve();                //串口1接收上位机指令信号    
		switch(i)                          //判断
		{     
			case '0': move(120,120);   _delay_ms(70);move(0,0);break;          //电机
			case '1': move(-120,-120); _delay_ms(70);move(0,0);break;
			case '2': move(-120,120);  _delay_ms(60);move(0,0);break;
			case '3': move(120,-120);  _delay_ms(60);move(0,0);break;
			case '4': move(220,220);   _delay_ms(70);move(0,0);break;
			case 'p': move(-170,-170); _delay_ms(70);move(0,0);break;

		    
			case '9': rightinit(); break;    //右手初始化                        //舵机
			case '5': rightgao();  break;    //右手高举
			case 'j': rightqian(); break;    //右手前伸
            case 'a': rightgou();  break;    //右勾手
			case '7': rightxia();  break;    //右下
	    	
			case 'i': leftinit(); break;     //左手初始化
			case 'e': leftgao();  break;     //左手高举
			case 'm': leftqian(); break;     //左手前伸
			case 'b': leftgou();  break;     //左勾手
			case 'g': leftxia();  break;     //左下
			default : break;
		}
		USART1_send(i);  
	}	
}

void   leftrightinit()                      //左右手初始化     
      {
		SetServoPosition(1,323,Duosu);
		SetServoPosition(2,532,Duosu);
		SetServoPosition(3,314,Duosu);
		SetServoPosition(4,600,Duosu);
		SetServoPosition(5,441,Duosu);
		SetServoPosition(6,603,Duosu);
	  }

void   rightinit()                          //右手初始化     
      {
		SetServoPosition(4,600,Duosu);
		SetServoPosition(5,441,Duosu);
		SetServoPosition(6,603,Duosu);
	   }

void  rightgao()                            //右手高举
     {
	    SetServoPosition(4,852,Duosu);
	    SetServoPosition(5,503,Duosu);
		SetServoPosition(6,442,Duosu);
	  }


void  rightqian()                           //右手前伸
     {
	    SetServoPosition(4,747,Duosu);
		SetServoPosition(5,503,Duosu);
		SetServoPosition(6,442,Duosu);
	 }

void  rightgou()                            //右勾手
    {
	    SetServoPosition(4,747,Duosu);
		SetServoPosition(5,345,Duosu);
	    SetServoPosition(6,562,Duosu);
     }

void  rightxia()                           //右手下举
     {
        SetServoPosition(4,579,Duosu);
        SetServoPosition(5,503,Duosu);
	    SetServoPosition(6,442,Duosu);
	 }

void   leftinit()                          //左手初始化     
      { 
	    SetServoPosition(1,323,Duosu);
		SetServoPosition(2,532,Duosu);
		SetServoPosition(3,314,Duosu);
	   }

void  leftgao()                            //左手高举
     {
	    SetServoPosition(1,493,Duosu);
		SetServoPosition(2,536,Duosu);
	    SetServoPosition(3,29,Duosu);
      }

void   leftqian()                          //左手前伸
     {
	    SetServoPosition(1,493,Duosu);
		SetServoPosition(2,536,Duosu);
		SetServoPosition(3,134,Duosu);
	  }

void  leftgou()                            //左勾手
     {
	    SetServoPosition(1,339,Duosu);
		SetServoPosition(2,395,Duosu);
	    SetServoPosition(3,134,Duosu);
     }

void  leftxia()                            //左手下举
     {
	    SetServoPosition(1,493,Duosu);
		SetServoPosition(2,536,Duosu);
	    SetServoPosition(3,276,Duosu);
	 }

 










