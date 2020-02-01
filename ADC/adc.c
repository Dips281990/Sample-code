#include<p18f4520.h>


#define data1 LATD
#define rs LATBbits.LATB0
#define rw LATBbits.LATB1
#define en LATBbits.LATB2
#define input PORTAbits.RA0

void lcddata(unsigned int);
void lcdcmd(unsigned int);
void delay();
unsigned int j,a,b;
unsigned int  c,temp;
float temperature;
unsigned char data[4];
void main()
{
unsigned char name[10]="1234567890";
TRISD=0X00;
TRISB=0x00;
TRISAbits.TRISA0=0xFF;
en=0X00;
delay();
lcdcmd(0x38);
delay();
lcdcmd(0x0E);
delay();
lcdcmd(0x01);
delay();
lcdcmd(0x06);
delay();
lcdcmd(0x80);
delay();
ADCON0=0x01;
ADCON1=0x00;
ADCON2=0x85;

while(1)
{

delay();
ADCON0bits.GO=1;
while(ADCON0bits.DONE==1);
a=ADRESL;
b=ADRESH;
b=b<<8;
c=a|b;
temperature=c;
temperature=temperature/200;
//c=c/200;
//data[0]=c/1000;
//temp=c%1000;
//data[1]=temp/100;
//temp=temp%100;
//data[2]=temp/10;
//data[3]=temp%10;
lcdcmd(0x80);
lcddata(0x30+temperature);

//lcdcmd(0x80);
//lcddata(0x30+data[0]);
//delay();
//lcdcmd(0x81);
//lcddata(0x30+data[1]);
//delay();
//lcdcmd(0x82);
//lcddata(0x30+data[2]);
////
//delay();
//lcdcmd(0x83);
//lcddata(0x30+data[3]);
//
}
}





			

		





void lcdcmd(unsigned int value)
{
//	unsigned char lcmd;
	data1=value;
	rs=0;
	rw=0;
	en=1;
	delay();
	en=0;
}


void lcddata(unsigned int value)
{
//	unsigned char ldata;
	data1=value;
	rs=1;
	rw=0;
	en=1;
	delay();
	en=0;
}

void delay()
{
unsigned int i,j;
for(i=0;i<200;i++)
{
for(j=0;j<500;j++);
}
}



