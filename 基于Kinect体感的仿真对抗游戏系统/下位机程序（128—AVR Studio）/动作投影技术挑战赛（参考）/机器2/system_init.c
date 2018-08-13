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

	DDRF  = 0X00;		//PF����ADC0~ADC7
	PORTF = 0X00;		//��ֹ�ڲ�����
	ADMUX   = 0B01000000;  //REFS1:REFS0=01 AVCCΪ��׼��ѹ;ADLAR=1 �Ҷ���
	ADCSRA  = 0B10000110;  //ADEN=1 ADCʹ�ܣ�ADPS2:0=110 64��Ƶ
}


unsigned int Get_ADC(unsigned char ID)      //����ΪΪADͨ��ID��
{
	unsigned int temp = 0;
	ADMUX  =  0x40|ID;     //�˿�ѡ����Ҫ�����
		ADCSRA |= (1<<ADSC);       //��ʼת��
		while(!( ADCSRA  &  (1<<ADIF) ) ); //�ȴ�ת�����
		temp = ADCL+ADCH*256;
		ADCSRA |= (1<<ADIF);	   //��־λ���


	return temp;
}

/***************PWM��ʼ��**********************/
void PWM_init()
{	
	DDRC=0XFF;             //PB5,PB6  ��� ��Ӧ��OC1A,OC1B
	DDRB|=0X60;  
	TCCR1A = 0b10100010;
	TCCR1B = 0b00011010;
	TCCR1C=0X00;
	ICR1=300;             //���ıȶ�ֵ
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

void USART1_init()
{
	UCSR1A = 0X00;
	/*���ս����ж�ʹ�ܣ� �������뷢����ʹ��(1<<RXCIE0)|*/
	UCSR1B = 0B00011000;
	/* ����֡��ʽ: �첽����ֹ��żУ�飬1��ֹͣλ��8������λ*/
	UCSR1C = 0B00000110;
	/* ���ò�����Ϊ9600*/
	UBRR1L = 103;
}


void USART1_send(unsigned char data)
{
	/* �ȴ����ͻ�����Ϊ�� */
	while ( !( UCSR1A & (1<<UDRE)) ) ;
	/* �����ݷ��뻺��������������*/
	UDR1 = data;
}

unsigned char USART1_recieve()
{
	/* �ȴ���������*/
	while ( !(UCSR1A & (1<<RXC)) ) ;
	/* �ӻ������л�ȡ����������*/
	return UDR1;
}
void Init_Uart0(void)
{
	Init_Gpio();
    UCSR0A = 0x02;                  // ����Ϊ����ģʽ��Set to double velocity mode��                    // ��ʱ��Ƶ��Ϊ16Mʱ��������Ϊ1M // (Set main clock to 16M, baud rate to 1M)
	UBRR0H=0X00;
	UBRR0L=0X01;                    // �������뷢����ʹ�� // (Enable UART0��s receiver and transmitter)
    UCSR0B = (1<<RXEN)|(1<<TXEN);   // ����֡��ʽ: 8 ������λ, 1 ��ֹͣλ // (Set data frame:8 data bits,1 stop bit)�����ж�ʹ��
    UCSR0C = (3<<UCSZ0);            /* ���ö˿�״̬(Set port state) */
    DDRE &= ~_BV(PE0);              // ��ʼ��RX�˿�Ĭ�Ϸ���Ϊ���� // (Set default direction of RX to input mode)
	PORTE &= ~_BV(PE0);             // ��ʼ��RX�˿�Ĭ��״̬Ϊ���� // (Set default state of RX to tri-state)
	DDRE |= _BV(PE1);               // ��ʼ��TX�˿�Ĭ�Ϸ���Ϊ��� // (Set default direction of TX to output mode)
	PORTE |= _BV(PE1);              // ��ʼ��TX�˿�Ĭ��״̬Ϊ�ߵ�ƽ // (Set default state of RX to high state)
	DDRG |= _BV(PG3);               // ��ʼ��ʹ�ܶ˿�״̬����Ϊ��� // (Enable direction of Port A as output)
	PORTG &= ~_BV(PG3);             // ��ʼ��ʹ�ܶ˿�״̬ΪRX״̬ // (Set Port A state as same to RX)
	DDRG |= _BV(PG4);               // ��ʼ��ʹ�ܶ˿�״̬����Ϊ��� // (Set Port A state as same to RX)
    PORTG |= _BV(PG4);              // ��ʼ��ʹ�ܶ˿�״̬��ΪRX״̬ // (Set Port A state as same to RX)
}

void System_Init(void)
{


 
    Init_Uart0();
    USART1_init();

 


 }
