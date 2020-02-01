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

void flash()
{
unsigned char j;
TBLPTR=0x400;
//for(j=0;j<7;j++)
//{
TABLAT='D';
_asm TBLWTPOSTINC _endasm
//}


TBLPTR=0x400;
EECON1bits.EEPGD=1;
EECON1bits.CFGS=0;
EECON1bits.WREN=1;
INTCONbits.GIE=0;
EECON2=0x55;
EECON2=0xAA;
EECON1bits.WR=1;
_asm NOP _endasm
INTCONbits.GIE=1;
EECON1bits.WREN=0;

}






void main()
{
TRISCbits.TRISC0=1;
TRISCbits.TRISC1=1;
TRISCbits.TRISC2=0;
TRISCbits.TRISC3=0;
TRISCbits.TRISC4=0;
led2=0;
led3=0;
while(1)
	{
	  if(sw1==0)
		{
		led1=1;
		}
	  if(sw2==0)
		{
			flash();
			if(TABLAT=='H')
				{
					led2=1;
					delay();
				}
			else if(TABLAT!='H')
				{
					led3=1;
				}
		}
	}
}