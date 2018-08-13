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

void zhixing(int v1,int v2 ){

	SetServoVelocity(13,v1);
	SetServoVelocity(14,-v1);
	SetServoVelocity(11,v2);
	SetServoVelocity(12,-v2);
	
}
void qiaoluo(void)
{
         SetServoPosition(1,434,300);
          SetServoPosition(2,421,300);
		  SetServoPosition(3,750,300);
		  _delay_ms(1000);
          SetServoPosition(1,434,300);
          SetServoPosition(2,563,300);
		  SetServoPosition(3,750,300);
		
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
	      SetServoPosition(7,451,300);
          SetServoPosition(8,565,300);
	      SetServoPosition(9,420,300);
	      SetServoPosition(10,555,300);
		  _delay_ms(1100);    
	      SetServoPosition(1,310,300);
          SetServoPosition(2,395,300);
		  SetServoPosition(3,668,300);
		  SetServoPosition(4,546,300);
		  SetServoPosition(5,644,300);
		  SetServoPosition(6,747,300);
	      _delay_ms(2000);
	
	while(1)
	{   
	    i=USART1_recieve();
		switch(i)
		{      
		    case '0': zhixing(600,615);   _delay_ms(70);zhixing(0,0);s=0;break;
			case '1': zhixing(-600,-610); _delay_ms(70);zhixing(0,0);s=0;break;
			case '2': zhixing(-500,500 );_delay_ms(70);zhixing(0,0);s=0;break;
			case '3': zhixing(500,-500 );_delay_ms(70);zhixing(0,0);s=0;break;
	        case '8':if(s==0){ rightping();} break;       //右手平举动作
		    case 'h':if(s==0){ leftping();} break;       //左手平举动作
		    case 'g':   f=f+1;  if (f%3==1){baoqiu1();s=1;}break;// g=g+1;  if (g%3==1)zou(); break;//leftxia();   break;//左手半下举
		    case 'c':   PORTC &= 0XDF; _delay_ms(1000); PORTC |= 0X20; break;//5
			case 'r':  PORTC &= 0XEF; _delay_ms(1000); PORTC |= 0X10;break;//4结束语音rightHand.Y < kneeRight.Y
		   // case '5':  w=w+1; if (w==1){ PORTC &= 0X7F;_delay_ms(1000);PORTC |= 0X80; wushu(); }break;   //7开始语音  //武术语音leftHand.Y < kneeLeft.Y
	        case 'j':if(s==0){ rightinit();} break;  //右手前伸
			case 't':qiaoluo() ;  break;//敲锣
			case 'k': g=g+1;  if (g%3==1)zou(); break;  // break;  右手半前伸
            case 'm':if(s==0){leftinit() ;}  break; //左手前伸
			case 'q':leftrightinit() ;   break;  //zuo手半前伸	
			case 'z': dun();zhixing(650,650 );   _delay_ms(4000);
			         zhixing(0,0 );break; // dunjiinit() ;	_delay_ms(1500); 
/*		SetServoPosition(1,441,300);
		SetServoPosition(2,430,300);
      	SetServoPosition(3,500,300); 
	    SetServoPosition(4,739,300);
		SetServoPosition(5,489,300);
		SetServoPosition(6,589,300);break;*/
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
	      SetServoPosition(1,566,300);
          SetServoPosition(2,421,300);
		  SetServoPosition(3,800,300);
		 
	  }
void   leftinit()                      //左手前伸  平常   
      {
	  	  SetServoPosition(4,459,300);
		  SetServoPosition(5,587,300);
		  SetServoPosition(6,559,300);
		
	  }
void   leftrightinit()                      //左右手前伸  平常    
      {
	      SetServoPosition(7,451,300);
          SetServoPosition(8,565,300);
	      SetServoPosition(9,420,300);
	      SetServoPosition(10,555,300);
		  _delay_ms(1100);    
	      SetServoPosition(1,310,300);
          SetServoPosition(2,421,300);
		  SetServoPosition(3,668,300);
		  SetServoPosition(4,546,300);
		  SetServoPosition(5,644,300);
		  SetServoPosition(6,747,300);
	      _delay_ms(2000);
	  } 
void  rightping()    //右手平举
     {
         SetServoPosition(1,597,300);
		 SetServoPosition(2,769,300);
		 SetServoPosition(3,469,100);
		 
	 }
 void  leftping()    //左手平举
     {
	     SetServoPosition(4,791,100);
    	 SetServoPosition(5,261,300);
		 SetServoPosition(6,562,300);
	 }
 void  leftrightping()    //左右手平举
     {
	     SetServoPosition(1,597,300);
		 SetServoPosition(2,769,300);
		 SetServoPosition(3,469,100);
		 SetServoPosition(4,791,100);
    	 SetServoPosition(5,261,300);
		 SetServoPosition(6,562,300);
	 }

 void  dun()
   {
   
	      SetServoPosition(1,566,300);
          SetServoPosition(2,308,300);
	      SetServoPosition(3,326,300);
	      SetServoPosition(4,927,300);
	      SetServoPosition(5,587,300);
		  SetServoPosition(6,559,300);

	      _delay_ms(1000);
   
   }
   void dunjiinit()
   {      SetServoPosition(7,525,300);
          SetServoPosition(8,510,300);
	      SetServoPosition(9,470,300);
	      SetServoPosition(10,506,300);
		  _delay_ms(500);
	
   }


void   zou()
	{
//		 SetServoPosition(2,608,300);
//		 SetServoPosition(3,778,300);
//		 SetServoPosition(4,488,300);
//  	 SetServoPosition(5,587,300);
//  	 SetServoPosition(6,549,300);
		 	   
		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
         _delay_ms(400);

    	 zhixing(300,300);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,366,300); 
	    SetServoPosition(4,687,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);//baizuoshou
		_delay_ms(400);

		SetServoPosition(7,441,300);
        SetServoPosition(8,587,300);
	    SetServoPosition(9,518,300);
	    SetServoPosition(10,469,300);//kuayoujiao
        _delay_ms(700);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
        _delay_ms(300);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,559,300); 
	    SetServoPosition(4,891,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);//baiyoushou
		_delay_ms(400);

		SetServoPosition(7,590,300); 
	    SetServoPosition(8,457,300);
		SetServoPosition(9,427,300);
		SetServoPosition(10,556,300);//kuazuojiao
        _delay_ms(700);

		/**************************************************************/

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
         _delay_ms(400);

    	 zhixing(300,300);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,366,300); 
	    SetServoPosition(4,687,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);//baizuoshou
		_delay_ms(400);

		SetServoPosition(7,441,300);
        SetServoPosition(8,587,300);
	    SetServoPosition(9,518,300);
	    SetServoPosition(10,469,300);//kuayoujiao
        _delay_ms(700);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
        _delay_ms(300);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,559,300); 
	    SetServoPosition(4,891,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);//baiyoushou
		_delay_ms(400);

		SetServoPosition(7,590,300); 
	    SetServoPosition(8,457,300);
		SetServoPosition(9,427,300);
		SetServoPosition(10,556,300);//kuazuojiao
        _delay_ms(700);

///////////////////////////////////////////////////////////////////////////////

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
         _delay_ms(400);

    	 zhixing(300,300);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,366,300); 
	    SetServoPosition(4,687,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);//baizuoshou
		_delay_ms(400);

		SetServoPosition(7,441,300);
        SetServoPosition(8,587,300);
	    SetServoPosition(9,518,300);
	    SetServoPosition(10,469,300);//kuayoujiao
        _delay_ms(700);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
        _delay_ms(300);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,559,300); 
	    SetServoPosition(4,891,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);//baiyoushou
		_delay_ms(400);

		SetServoPosition(7,590,300); 
	    SetServoPosition(8,457,300);
		SetServoPosition(9,427,300);
		SetServoPosition(10,556,300);//kuazuojiao
        _delay_ms(700);

		SetServoPosition(1,542,300);
		SetServoPosition(2,529,300);
      	SetServoPosition(3,456,300); 
	    SetServoPosition(4,795,300);
		SetServoPosition(5,481,300);
		SetServoPosition(6,590,300);
	    SetServoPosition(7,537,300); 
	    SetServoPosition(8,492,300);
		SetServoPosition(9,498,300);
		SetServoPosition(10,489,300);//zhanzhi
        _delay_ms(300);
		zhixing(0,0);


	}
void  baoqiu1()    
     {  
	
	    SetServoPosition(3,775,300);
		SetServoPosition(4,471,300);
		 _delay_ms(2000); 
        
		 SetServoPosition(1,492,300);
		 SetServoPosition(2,411,300);
		 SetServoPosition(3,748,300);
		 SetServoPosition(4,503,300);
	   	 SetServoPosition(5,612,300);
	   	 SetServoPosition(6,628,300);
	      _delay_ms(2000); 

         SetServoPosition(1,434,300);
		 SetServoPosition(2,367,300);
		 SetServoPosition(3,873,300);
		 SetServoPosition(4,379,300);
	   	 SetServoPosition(5,619,300);
	   	 SetServoPosition(6,673,300);
	     _delay_ms(1500);

		 //SetServoPosition(7,390,300);
	
		 //SetServoPosition(9,480,300);
		
		 //_delay_ms(1000);

       }


   
zuo(void)
{
    SetServoPosition(9,912,300);
 	SetServoPosition(10,86,300);
	SetServoPosition(11,78,300);
 	SetServoPosition(12,945,300);
	_delay_ms(700);

}


