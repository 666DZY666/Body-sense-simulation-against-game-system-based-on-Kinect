#include<avr/io.h>
#include<avr/iom128.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"system_init.h"
void Init_Gpio(void)
 {
     DDRE &= ~(_BV(PE5) | _BV(PE4));
	 PORTE |= (_BV(PE5) | _BV(PE4));
 }

void ADC_Init(void)
{

	DDRF  = 0X00;		//PF用于ADC0~ADC7
	PORTF = 0X00;		//禁止内部上拉
	ADMUX   = 0B01000000;  //REFS1:REFS0=01 AVCC为基准电压;ADLAR=1 右对齐
	ADCSRA  = 0B10000110;  //ADEN=1 ADC使能；ADPS2:0=110 64分频
}


unsigned int Get_ADC(unsigned char ID)      //参数为为AD通道ID号
{
	unsigned int temp = 0;
	ADMUX  =  0x40|ID;     //端口选择需要先清除
		ADCSRA |= (1<<ADSC);       //开始转换
		while(!( ADCSRA  &  (1<<ADIF) ) ); //等待转换完成
		temp = ADCL+ADCH*256;
		ADCSRA |= (1<<ADIF);	   //标志位清除


	return temp;
}

/***************PWM初始化**********************/
void PWM_init()
{	
	DDRC=0XFF;             //PB5,PB6  输出 对应于OC1A,OC1B
	DDRB|=0X60;  
	TCCR1A = 0b10100010;
	TCCR1B = 0b00011010;
	TCCR1C=0X00;
	ICR1=300;             //最大的比对值
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

void USART1_init()
{
	UCSR1A = 0X00;
	/*接收结束中断使能， 接收器与发送器使能(1<<RXCIE0)|*/
	UCSR1B = 0B00011000;
	/* 设置帧格式: 异步，禁止奇偶校验，1个停止位，8个数据位*/
	UCSR1C = 0B00000110;
	/* 设置波特率为9600*/
	UBRR1L = 103;
}


void USART1_send(unsigned char data)
{
	/* 等待发送缓冲器为空 */
	while ( !( UCSR1A & (1<<UDRE)) ) ;
	/* 将数据放入缓冲器，发送数据*/
	UDR1 = data;
}

unsigned char USART1_recieve()
{
	/* 等待接收数据*/
	while ( !(UCSR1A & (1<<RXC)) ) ;
	/* 从缓冲器中获取并返回数据*/
	return UDR1;
}
void Init_Uart0(void)
{
	Init_Gpio();
    UCSR0A = 0x02;                  // 设置为倍速模式（Set to double velocity mode）                    // 主时钟频率为16M时，波特率为1M // (Set main clock to 16M, baud rate to 1M)
	UBRR0H=0X00;
	UBRR0L=0X01;                    // 接收器与发送器使能 // (Enable UART0’s receiver and transmitter)
    UCSR0B = (1<<RXEN)|(1<<TXEN);   // 设置帧格式: 8 个数据位, 1 个停止位 // (Set data frame:8 data bits,1 stop bit)接收中断使能
    UCSR0C = (3<<UCSZ0);            /* 设置端口状态(Set port state) */
    DDRE &= ~_BV(PE0);              // 初始化RX端口默认方向为输入 // (Set default direction of RX to input mode)
	PORTE &= ~_BV(PE0);             // 初始化RX端口默认状态为高阻 // (Set default state of RX to tri-state)
	DDRE |= _BV(PE1);               // 初始化TX端口默认方向为输出 // (Set default direction of TX to output mode)
	PORTE |= _BV(PE1);              // 初始化TX端口默认状态为高电平 // (Set default state of RX to high state)
	DDRG |= _BV(PG3);               // 初始化使能端口状态方向为输出 // (Enable direction of Port A as output)
	PORTG &= ~_BV(PG3);             // 初始化使能端口状态为RX状态 // (Set Port A state as same to RX)
	DDRG |= _BV(PG4);               // 初始化使能端口状态方向为输出 // (Set Port A state as same to RX)
    PORTG |= _BV(PG4);              // 初始化使能端口状态方为RX状态 // (Set Port A state as same to RX)
}

void System_Init(void)
{


 
    Init_Uart0();
    USART1_init();

 


 }
