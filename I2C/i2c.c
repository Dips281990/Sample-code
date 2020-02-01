#include<p18f4520.h>
#include<stdio.h>
//#include<i2c.h>

#pragma config OSC = INTIO67
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = OFF
#pragma config PBADEN = OFF
#pragma config STVREN = OFF
#pragma config LVP = OFF


#define SDA LATCbits.LATC4
#define SCL LATCbits.LATC3
#define SDA_dir TRISCbits.TRISC4
#define SCL_dir TRISCbits.TRISC3

void i2c_init();
void StartI2C();
void StopI2C();
void i2c_write(unsigned char data);

void i2c_init()
{
 				SSPSTATbits.SMP=0;          //Slew Rate Control bit
                SSPSTATbits.CKE=0;           //SMBus Select bit
                 
                SSPCON1bits.WCOL=0;     //Write Collision
                SSPCON1bits.SSPEN=1;     //Synchronous Serial Port Enable bit
                SSPCON1bits.SSPM3=1;    //1000 = I2C Firmware Controlled Master mode
                SSPCON1bits.SSPM2=0;
                SSPCON1bits.SSPM1=1;
                SSPCON1bits.SSPM0=1;
			
//				SSPADD=39;
                SSPCON2bits.ACKDT=0;     //Acknowledge Data bit
                SSPCON2bits.ACKEN=0;     //Acknowledge Sequence Enable bit
                SSPCON2bits.RCEN=0;       //Receive Enable bit
                SSPCON2bits.PEN=0;         //Stop Condition Enable bit
                SSPCON2bits.RSEN=0;      //Repeated Start Condition Enable bit
                SSPCON2bits.SEN=0;       //Start Condition Enable/Stretch Enable bit
                
}

void StartI2C()
{
    SSPCON2bits.SEN = 1;                           // initiate bus start condition
}

void StopI2C()
{
       SSPCON2bits.PEN = 1;                     // initiate bus stop condition
}      

void i2c_write(unsigned char data)
{
SSPBUF=data;
while(!SSPSTATbits.BF);
                                 // write single byte to SSPBUF
//            if (SSPCON1bits.WCOL==1)          // test if write collision occurred
//                       return ( -1 );                       // if WCOL bit is set return negative #
//            else
//            {
//                       while(! SSPSTATbits.BF );  // wait until write cycle is complete  
//               
//                       if ( PIR1bits.SSPIF )          // test for ACK condition received
//                                return ( -2 );
//                       else
//                                return ( 0 );              // if WCOL bit is not set return non-negative #
//            }
}
unsigned char ReadI2C()
{
          if( ((SSPCON1&0x0F)==0x08) || ((SSPCON1&0x0F)==0x0B) )       //master mode only
                SSPCON2bits.RCEN = 1;          // enable master for 1 byte reception
          while ( !SSPSTATbits.BF );             // wait until byte received 
          return ( SSPBUF );                         // return with read byte
}
void RestartI2C()
{
          SSPCON2bits.RSEN = 1;                    // initiate bus restart condition
}

void main()
{
while(1)
{
SDA_dir=0;
SCL_dir=1;
i2c_init();
//               
//                SSPSTATbits.SMP=0;          //Slew Rate Control bit
//                SSPSTATbits.CKE=0;           //SMBus Select bit
//                 
//                SSPCON1bits.WCOL=0;     //Write Collision
//                SSPCON1bits.SSPEN=1;     //Synchronous Serial Port Enable bit
//                SSPCON1bits.SSPM3=1;    //1000 = I2C Firmware Controlled Master mode
//                SSPCON1bits.SSPM2=0;
//                SSPCON1bits.SSPM1=1;
//                SSPCON1bits.SSPM0=1;
//
//                SSPCON2bits.ACKDT=0;     //Acknowledge Data bit
//                SSPCON2bits.ACKEN=0;     //Acknowledge Sequence Enable bit
//                SSPCON2bits.RCEN=0;       //Receive Enable bit
//                SSPCON2bits.PEN=0;         //Stop Condition Enable bit
//                SSPCON2bits.RSEN=0;      //Repeated Start Condition Enable bit
//                SSPCON2bits.SEN=0;       //Start Condition Enable/Stretch Enable bit
//	
//                     //Start Condition Enable/Stretch Enable bit
//                //SSPCON2=0x00;
                StartI2C();
				i2c_write(0xD0);
				i2c_write(0x40);
				ReadI2C();
				SSPCON2bits.ACKSTAT=0;
                
//                i2c_write(0x00);
//                
                StopI2C();
}

}



//
//#include<p18f4520.h>
//#include<stdio.h>
//#include <i2c.h>
//
//#pragma config OSC = INTIO67
//#pragma config FCMEN = OFF
//#pragma config IESO = OFF
//#pragma config PWRT = OFF
//#pragma config BOREN = OFF
//#pragma config WDT = OFF
//#pragma config MCLRE = OFF
//#pragma config PBADEN = OFF
//#pragma config STVREN = OFF
//#pragma config LVP = OFF
//
//#define lcd PORTD
//#define sda TRISCbits.TRISC4
//#define scl TRISCbits.TRISC3
//
//#if defined (I2C_V1)
//#undef StartI2C
//
//#if defined (I2C_V1)
//#undef RestartI2C
//#if defined (I2C_V1)
//#undef StopI2C
//
//void cmd(unsigned char);
//void dat(unsigned char);
//
//void Delay_ms();
//void StartI2C();
//unsigned char Write(unsigned char);
//void RestartI2C();
//unsigned char ReadI2C();
//void StopI2C();
//
//void main()
//{
//                unsigned int sec,sec1,sec2,x[25],min,min1,min2,hour,hour1,hour2;
//                unsigned char i,j;
//                TRISD=0x00;
//                I2C_SCL = 1;
//                 I2C_SDA = 1;
//                cmd(0x01);
//                cmd(0x02);
//                cmd(0x28);
//                cmd(0x0C);
//                cmd(0x06);
//               
//                ADCON1=0x0F;
//                SSPSTAT &=0x3F;
//               
//                SSPSTATbits.SMP=0;          //Slew Rate Control bit
//                SSPSTATbits.CKE=0;           //SMBus Select bit
//                 
//                SSPCON1bits.WCOL=0;     //Write Collision
//                SSPCON1bits.SSPEN=1;     //Synchronous Serial Port Enable bit
//                SSPCON1bits.SSPM3=1;    //1000 = I2C Firmware Controlled Master mode
//                SSPCON1bits.SSPM2=0;
//                SSPCON1bits.SSPM1=1;
//                SSPCON1bits.SSPM0=1;
//
//                SSPCON2bits.ACKDT=0;     //Acknowledge Data bit
//                SSPCON2bits.ACKEN=0;     //Acknowledge Sequence Enable bit
//                SSPCON2bits.RCEN=0;       //Receive Enable bit
//                SSPCON2bits.PEN=0;         //Stop Condition Enable bit
//                SSPCON2bits.RSEN=0;      //Repeated Start Condition Enable bit
//                SSPCON2bits.SEN=0;       //Start Condition Enable/Stretch Enable bit
//                //SSPCON2=0x00;
//                StartI2C();
//                WriteI2C(0xD0);
//                WriteI2C(0x00);
//                WriteI2C(0x40);
//                StopI2C();
//                StartI2C();
//                WriteI2C(0xD0);
//                WriteI2C(0x01);
//                WriteI2C(0x40);
//                StopI2C();
//                StartI2C();
//                WriteI2C(0xD0);
//                WriteI2C(0x02);
//                WriteI2C(0x10);
//                StopI2C();
//                while(1)
//                {
//                                //Read second
//                                StartI2C();
//                                WriteI2C(0xD0);
//                                WriteI2C(0x00);
//                                RestartI2C();
//                                WriteI2C(0xD1);
//                                sec=ReadI2C();
//                                StopI2C();
//
//                                //Read minute
//                                StartI2C();
//                                WriteI2C(0xD0);
//                                WriteI2C(0x01);
//                                RestartI2C();
//                                WriteI2C(0xD1);
//                                min=ReadI2C();
//                                StopI2C();
//                               
//                                //Read hour
//                                StartI2C();
//                                WriteI2C(0xD0);
//                                WriteI2C(0x02);
//                                RestartI2C();
//                                WriteI2C(0xD1);
//                                hour=ReadI2C();
//                                StopI2C();
//
//                                hour1=(hour>>4);
//                                hour2=(hour & 0x0F);
//
//                                min1=(min>>4);
//                                min2=(min & 0x0F);
//
//                                sec1=(sec>>4);
//                                sec2=(sec & 0x0F);
//
//                                sprintf(x,"%d %d :",hour1,hour2);
//                                cmd(0x83);
//                                i=0;
//                                while(x[i]!='\0')
//                                {
//                                                dat(x[i]);
//                                                i++;
//                                }
//
//                                sprintf(x,"%d %d ",min1,min2);
//                                cmd(0x86);
//                                i=0;
//                                while(x[i]!='\0')
//                                {
//                                                dat(x[i]);
//                                                i++;
//                                }
//
//                                sprintf(x,"%d %d :",sec1,sec2);
//                                cmd(0x80);
//                                i=0;
//                                while(x[i]!='\0')
//                                {
//                                                dat(x[i]);
//                                                i++;
//                                }             
//                }
//}
//
//void StartI2C()
//{
//    SSPCON2bits.SEN = 1;                           // initiate bus start condition
//}
//
//unsigned char WriteI2C( unsigned char data_out )
//{
//            SSPBUF = data_out;                       // write single byte to SSPBUF
//            if (SSPCON1bits.WCOL==1)          // test if write collision occurred
//                       return ( -1 );                       // if WCOL bit is set return negative #
//            else
//            {
//                       while( SSPSTATbits.BF );  // wait until write cycle is complete  
//               
//                       if ( PIR1bits.SSPIF )          // test for ACK condition received
//                                return ( -2 );
//                       else
//                                return ( 0 );              // if WCOL bit is not set return non-negative #
//            }
//}
//
//void RestartI2C()
//{
//          SSPCON2bits.RSEN = 1;                    // initiate bus restart condition
//}
//
//unsigned char ReadI2C()
//{
//          if( ((SSPCON1&0x0F)==0x08) || ((SSPCON1&0x0F)==0x0B) )       //master mode only
//                SSPCON2bits.RCEN = 1;          // enable master for 1 byte reception
//          while ( !SSPSTATbits.BF );             // wait until byte received 
//          return ( SSPBUF );                         // return with read byte
//}
//
//void StopI2C()
//{
//       SSPCON2bits.PEN = 1;                     // initiate bus stop condition
//}             
//
//void cmd(unsigned char k)
//{
//        PORTD &=0x0F;
//        PORTD |=(k & (0xF0));
//        PORTD |=(2<<0);
//        Delay_ms();
//        PORTD=PORTD & 0xFC;
//        Delay_ms();
//
//        PORTD &=0x0F;
//        PORTD |=((k<<4) & (0xF0));
//        PORTD |=(2<<0);
//        Delay_ms();
//        PORTD=PORTD & 0xFC;
//        Delay_ms();
//}
//void dat(unsigned char k)
//{
//        PORTD &=0x0F;
//        PORTD |=(k & 0xF0);
//        PORTD |=(3<<0);
//        Delay_ms();
//        PORTD=PORTD & 0xFD;
//        Delay_ms();
//
//        PORTD &=0x0F;
//        PORTD |=((k<<4) & (0xF0));
//        PORTD |=(3<<0);
//        Delay_ms();
//        PORTD=PORTD & 0xFD;
//        Delay_ms();
//}
//
//void Delay_ms()
//{
//         unsigned int i;
//         for(i=0;i<40;i++);
//}
