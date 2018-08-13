#include<avr/io.h>
#include<avr/iom128.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include "servo.h"
#include "system_init.h"              //定义与系统初始化有关函数
void   rightinit(void);
void   leftinit(void);
void   leftrightinit(void);
void   rightping(void);
void   leftping(void); 
void  leftrightping(void);
void  leftqian(void); 
void  rightqian(void); 
void  leftrightqian(void);
void  leftxia(void);
void  rightxia(void);
void  zuorightxia(void);
void dunjiinit(void);
void  dun (void);
void   zou(void);
void wushu(void);
void baoqiu1(void);

void zhixing(int v1,int v2 )
{

	SetServoVelocity(13,v1);
	SetServoVelocity(14,v1);
	SetServoVelocity(11,v2);
	SetServoVelocity(12,v2);
	
}
void qiaoluo(void)
{
         SetServoPosition(1,298,300);
         SetServoPosition(2,631,300);
		 SetServoPosition(3,778,300);
		  _delay_ms(1000);
          SetServoPosition(1,467,300);
          SetServoPosition(2,806,300);
		  SetServoPosition(3,770,300);
		
}

int main(void)
{   
    PWM_init(); 
	System_Init();
	DDRA=0XFF;
	PORTA =0XFF;
	DDRC=0XFF;
	PORTC =0XFF;
	unsigned char i,m;
	int s=0;
	 int f=0;
	 int g=0;
     int  w=0;
	int l=1,r=1;
	cli();                        //关总中断
	for(m=1;m<=10;m++)                       //我们用10个舵机，
    SetServoLimit(m,0,1023);           //设置舵机工作模式为舵机模式
	for(int n=11;n<=14;n++)                    //我们用4个舵机，ID:11-14
		SetServoLimit(n,0,0);                  //设置舵机工作模式为电机模式
    	_delay_ms(1000);
       dunjiinit();
          SetServoPosition(1,273,300);
          SetServoPosition(2,614,300);
		  SetServoPosition(3,668,300);
		  SetServoPosition(4,697,300);
		  SetServoPosition(5,601,300);
		  SetServoPosition(6,667,300);
	      _delay_ms(2000);
	
	while(1)
	{   
	    i=USART1_recieve();
		switch(i)
		{      
		     case '0': zhixing(580,-600 ); _delay_ms(70);zhixing(0,0);s=0;break;
			case '1': zhixing(-580,600 ); _delay_ms(70);zhixing(0,0);s=0;break;
			case '3': zhixing(500,500 );_delay_ms(70);zhixing(0,0);s=0;break;
			case '2': zhixing(-500,-500 );_delay_ms(70);zhixing(0,0);s=0;break;
	        case '8': if(s==0){rightping();} break;       //右手平举动作
		    case 'h': if(s==0){leftping();} break;       //左手平举动作
		    case 'g':   f=f+1;  if (f%3==1){baoqiu1();s=1;}break;// g=g+1;  if (g%3==1)zou(); break;//leftxia();   break;//左手半下举
		    case 'c':  PORTC &= 0XDF; _delay_ms(1000); PORTC|= 0X20; break;//5
			case 'r':  PORTC &= 0XEF; _delay_ms(1000); PORTC|= 0X10;break;//4结束语音rightHand.Y < kneeRight.Y
		    case '5':  w=w+1; if (w==1){ PORTC &= 0X7F;_delay_ms(1000);PORTC |= 0X80; wushu(); }break;   //7开始语音  //武术语音leftHand.Y < kneeLeft.Y
	        case 'j': if(s==0){rightinit() ;} break;  //右手前伸
			case 't':qiaoluo() ;  break;//qiaoluo
			case 'k': g=g+1;  if (g%3==1)zou(); break;  // break;  右手半前伸
            case 'm':leftinit() ;  break; //左手前伸
			case 'q':leftrightinit() ;   break;  //youjiaoqianshen	
			case 'z': dun();zhixing(600,-600 );   _delay_ms(4000);
			           zhixing(0,0 );  dunjiinit() ;	_delay_ms(1500);
					   break;
		            //SetServoPosition(7,691,300);
		           // SetServoPosition(8,598,300);   //鞠躬
			//case 'e': g=g+1;  if (g%3==1)zou(); break; //左手高举  break;
			//case '9': rightinit(); break; //右手初始化
		  // case 'f': f=f+1;  if (f%3==1){baoqiu1();}break; //左手半上举
			//	case 'i': leftinit();  break;//左手初始化
				//	case'p' : f=f+1;  if (f%10==1){dun(); baoqiu1();} break; //	case 'n': break; //左手半前伸
		 //  case '6': f=f+1;  if (f%3==1){baoqiu1();}break; //右手半上举	//	SetServoPosition(4,536,300);
		   // case '7':  w=w+1; if (w==1){ PORTC &= 0X7F;_delay_ms(1000);PORTC |= 0X80; wushu(); }break;    //武术语音 //rightxia();  break;右手半下举
		///	case 'l':break;  //右手半拥抱
			//	case 'n': break; //左手半前伸
				default : break;
		}
		
		USART1_send(i);  
	}	
}


void   rightinit()                      //右手前伸  平常     
      { 
	      SetServoPosition(1,473,300);
          SetServoPosition(2,664,300);
		  SetServoPosition(3,794,300);
		 
	  }
void   leftinit()                      //左手前伸  平常   
      {
	  	  SetServoPosition(4,505,300);
		  SetServoPosition(5,573,300);
		  SetServoPosition(6,505,300);
		
	  }
void   leftrightinit()                      //左右手前伸  平常    
      {   SetServoPosition(7,445,300);
          SetServoPosition(8,359,300);
	      SetServoPosition(9,556,300);
	      SetServoPosition(10,640,300);
		  _delay_ms(1100);    
          SetServoPosition(1,273,300);
          SetServoPosition(2,614,300);
		  SetServoPosition(3,668,300);
		  SetServoPosition(4,697,300);
		  SetServoPosition(5,601,300);
		  SetServoPosition(6,667,300);
         _delay_ms(1500);
	  } 
void  rightping()    //右手平举
     {
         SetServoPosition(1,473,50);
		 SetServoPosition(2,971,350);
		 SetServoPosition(3,463,300);
		 
	 }
 void  leftping()    //左手平举
     {
	     SetServoPosition(4,818,300);
    	 SetServoPosition(5,243,350);
		 SetServoPosition(6,505,50);
	 }
 void  leftrightping()    //左右手平举
     {
         SetServoPosition(1,473,50);
		 SetServoPosition(2,971,350);
		 SetServoPosition(4,818,300);
    	 SetServoPosition(5,243,350);
		 SetServoPosition(6,505,50);
	 }

 void  dun()
   {
   
	      SetServoPosition(1,305,300);
          SetServoPosition(2,641,300);
		  SetServoPosition(3,307,300);
		  SetServoPosition(4,1024,300);
		  SetServoPosition(5,579,300);
		  SetServoPosition(6,656,300);
          _delay_ms(1500);
   
   }
   void dunjiinit()
   {     SetServoPosition(7,445,300);
          SetServoPosition(8,359,300);
	      SetServoPosition(9,556,300);
	      SetServoPosition(10,640,300);
		 _delay_ms(500);
	
   }


void   zou()
	{
	   
		SetServoPosition(1,454,300);
		SetServoPosition(2,747,300);
      	SetServoPosition(3,498,300); 
	    SetServoPosition(4,791,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,517,300);
	    SetServoPosition(7,573,300); 
	    SetServoPosition(8,478,300);
		SetServoPosition(9,440,300);
		SetServoPosition(10,547,300);//zhanzhi


         _delay_ms(400);
      	 zhixing(400,-400);

		SetServoPosition(1,454,300);
		SetServoPosition(2,713,300);
      	SetServoPosition(3,369,300); 
	    SetServoPosition(4,694,300);
		SetServoPosition(5,502,300);
		SetServoPosition(6,513,300);//baizuoshou
		_delay_ms(400);

		SetServoPosition(7,647,300);
        SetServoPosition(8,550,300);
	    SetServoPosition(9,510,300);
	    SetServoPosition(10,607,300);//kuayoujiao
        _delay_ms(700);

		SetServoPosition(1,454,300);
		SetServoPosition(2,747,300);
      	SetServoPosition(3,498,300); 
	    SetServoPosition(4,791,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,517,300);
	    SetServoPosition(7,573,300); 
	    SetServoPosition(8,478,300);
		SetServoPosition(9,440,300);
		SetServoPosition(10,547,300);//zhanzhi
        _delay_ms(300);


		SetServoPosition(1,454,300);
		SetServoPosition(2,727,300);
      	SetServoPosition(3,594,300); 
	    SetServoPosition(4,916,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,516,300);//baiyoushou
		_delay_ms(400);

		SetServoPosition(7,472,300); 
	    SetServoPosition(8,380,300);
		SetServoPosition(9,348,300);
		SetServoPosition(10,451,300);//kuazuojiao
        _delay_ms(700);
		//////////////////////////////////////////////////////
		SetServoPosition(1,454,300);
		SetServoPosition(2,747,300);
      	SetServoPosition(3,498,300); 
	    SetServoPosition(4,791,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,517,300);
	    SetServoPosition(7,573,300); 
	    SetServoPosition(8,478,300);
		SetServoPosition(9,440,300);
		SetServoPosition(10,547,300);//zhanzhi


         _delay_ms(400);
      	

		SetServoPosition(1,454,300);
		SetServoPosition(2,713,300);
      	SetServoPosition(3,369,300); 
	    SetServoPosition(4,694,300);
		SetServoPosition(5,502,300);
		SetServoPosition(6,513,300);//baizuoshou
		_delay_ms(400);

		SetServoPosition(7,647,300);
        SetServoPosition(8,550,300);
	    SetServoPosition(9,510,300);
	    SetServoPosition(10,607,300);//kuayoujiao
        _delay_ms(400);

		SetServoPosition(1,454,300);
		SetServoPosition(2,747,300);
      	SetServoPosition(3,498,300); 
	    SetServoPosition(4,791,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,517,300);
	    SetServoPosition(7,573,300); 
	    SetServoPosition(8,478,300);
		SetServoPosition(9,440,300);
		SetServoPosition(10,547,300);//zhanzhi
        _delay_ms(300);


		SetServoPosition(1,454,300);
		SetServoPosition(2,727,300);
      	SetServoPosition(3,594,300); 
	    SetServoPosition(4,916,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,516,300);//baiyoushou
		_delay_ms(400);

		SetServoPosition(7,472,300); 
	    SetServoPosition(8,380,300);
		SetServoPosition(9,348,300);
		SetServoPosition(10,451,300);//kuazuojiao
         _delay_ms(700);
/////////////////////////////////////////////////////////////////////////////////
		SetServoPosition(1,454,300);
		SetServoPosition(2,747,300);
      	SetServoPosition(3,498,300); 
	    SetServoPosition(4,791,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,517,300);
	    SetServoPosition(7,573,300); 
	    SetServoPosition(8,478,300);
		SetServoPosition(9,440,300);
		SetServoPosition(10,547,300);//zhanzhi


         _delay_ms(400);
      	

		SetServoPosition(1,454,300);
		SetServoPosition(2,713,300);
      	SetServoPosition(3,369,300); 
	    SetServoPosition(4,694,300);
		SetServoPosition(5,502,300);
		SetServoPosition(6,513,300);//baizuoshou
		_delay_ms(400);

		SetServoPosition(7,647,300);
        SetServoPosition(8,550,300);
	    SetServoPosition(9,510,300);
	    SetServoPosition(10,607,300);//kuayoujiao
        _delay_ms(400);

		zhixing(0,0);

		SetServoPosition(1,454,300);
		SetServoPosition(2,747,300);
      	SetServoPosition(3,498,300); 
	    SetServoPosition(4,791,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,517,300);
	    SetServoPosition(7,573,300); 
	    SetServoPosition(8,478,300);
		SetServoPosition(9,440,300);
		SetServoPosition(10,547,300);//zhanzhi


	}
void  baoqiu1()    
     {  
	
	    SetServoPosition(3,679,300);
		SetServoPosition(4,574,300);
		 _delay_ms(2000); 
        
		 SetServoPosition(1,330,300);
		 SetServoPosition(2,671,300);
		 SetServoPosition(3,789,300);
		 SetServoPosition(4,511,300);
	   	 SetServoPosition(5,556,300);
	   	 SetServoPosition(6,610,300);
	      _delay_ms(2000); 

         SetServoPosition(1,324,300);
		 SetServoPosition(2,612,300);
		 SetServoPosition(3,905,300);
		 SetServoPosition(4,422,300);
	   	 SetServoPosition(5,609,300);
	   	 SetServoPosition(6,594,300);
	     _delay_ms(1500);

          SetServoPosition(7,478,300);
	   	 SetServoPosition(9,523,300);
		 _delay_ms(1000);
	     



       }
wushu()
{
Servo_all(745,1020,502,854,337,671);
 Servo_all(309,853,517,792,135,251);
 Servo_all(473,963,516,791,217,466);
 Servo_all(186,656,815,480,257,462);
 Servo_all(434,566,691,632,457,463);//5
 Servo_all(469,804,703,603,670,461);
 Servo_all(470,957,510,482,555,787);
 Servo_all(470,794,676,624,648,515);
 Servo_all(229,611,649,563,601,737);
 Servo_all(462,559,697,638,407,487);
 Servo_all(462,680,673,531,562,488);
 Servo_all(462,681,780,652,563,488);
 Servo_all(222,638,755,659,567,759);
 Servo_all(358,990,510,800,210,614);
 Servo_all(205,640,791,478,556,477);
 Servo_all(488,943,794,209,555,477);
 Servo_all(205,640,791,476,556,477);
 Servo_all(305,656,898,399,563,633);
 _delay_ms(200);     
 Servo_all(305,657,718,601,563,633);
 _delay_ms(200);
 Servo_all(305,656,898,399,563,633);
 _delay_ms(200);
 Servo_all(305,657,718,601,563,633);
 _delay_ms(200);


}
zuo(void)
{
    SetServoPosition(9,912,300);
 	SetServoPosition(10,86,300);
	SetServoPosition(11,78,300);
 	SetServoPosition(12,945,300);
	_delay_ms(700);

}
