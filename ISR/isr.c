#include<p18f4520.h>

#define led PORTDbits.RD2

#define sw PORTCbits.RC0
unsigned char led_flag=0;
void isr(void);
void delay();





void isr(void)
{
if(INTCONbits.INT0IF==1)
{
unsigned int i;
for(i=0;i<4;i++)
{
led=1;
delay();
led=0;
}

INTCONbits.INT0IF=0;
}
}


















void main()
{

//TRISDbits.TRISD7=0;
TRISB=0xFF;
TRISC=0xFF;
TRISD=0x00;
INTCONbits.GIE=1;
INTCONbits.INT0IE=1;
INTCONbits.INT0IF=0;
INTCONbits.RBIF=0;
if(sw==0)
{
led=1;
}

}


void delay()
{
unsigned int a,b;
for(a=0;a<100;a++)
{
for(b=0;b<150;b++);
}
}
//void int0_isr(void)
//{
//led=1;
//INTCONbits.INT0IF=0;
//}
