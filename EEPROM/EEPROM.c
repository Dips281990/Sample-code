#include<p18f4520.h>

#define sw1 PORTCbits.RC0
#define sw2 PORTCbits.RC1
#define led1 PORTCbits.RC2
#define led2 PORTCbits.RC3
#define led3 PORTCbits.RC4

unsigned char a[6]={'D','I','P','E','S','H'};
unsigned char i;


void delay();
void flash();

void delay()
{
unsigned int i,j;
for(i=0;i<100;i++)
{
for(j=0;j<150;j++);
}
}









void main()
{
	EEADR=0x22;
	EEDATA=0x53;
	EECON1bits.EEPGD=0;
EECON1bits.CFGS=0;
EECON1bits.WREN=1;
INTCONbits.GIE=0;
EECON2=0x55;
EECON2=0xAA;
EECON1bits.WR=1;
INTCONbits.GIE=1;
EECON1bits.WREN=0;
while(PIR2bits.EEIF==0);
PIR2bits.EEIF=0;

}





