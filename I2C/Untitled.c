#include<p18f4520.h>

#define SCL PORTCbits.RC3
#define SDA PORTCbits.RC4
#define SDA_dir TRISCbits.TRISC4
#define SCL_dir TRISCbits.TRISC3
#define _XTAL_FREQ 16000000
#define I2C_SPEED 100

unsigned char uartdata,readdata,sex;

void i2cinit(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
void i2c_sendack(void);
void i2c_sendnack(void);
int i2c_write(unsigned char data);
unsigned char i2c_read();
//void uart_init();
void i2cinit()
{
SCL_dir=1;
SDA_dir=1;
SSPADD  = ((_XTAL_FREQ/4000)/I2C_SPEED) - 1;
SSPSTAT = 0x80;		// Slew Rate control is disabled
	SSPCON1  = 0x28;

}


void i2c_start(void)
{
	SSPCON2bits.SEN = 1;			// Send start bit
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF=0;	// Clear the flag bit
}


// Function Purpose: I2C_ReStart sends start bit sequence
void i2c_restart(void)
{
	SSPCON2bits.RSEN = 1;			// Send Restart bit
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


//Function : I2C_Stop sends stop bit sequence
void i2c_stop(void)
{
	SSPCON2bits.PEN = 1;			// Send stop bit
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF = 0;			// Clear the flag bit
}



//Function : I2C_Send_ACK sends ACK bit sequence
void i2c_sendack(void)
{
	SSPCON2bits.ACKDT = 0;			// 0 means ACK
	SSPCON2bits.ACKEN = 1;			// Send ACKDT value
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


//Function : I2C_Send_NACK sends NACK bit sequence
void i2c_sendnack(void)
{
	SSPCON2bits.ACKDT = 1;			// 1 means NACK
	SSPCON2bits.ACKEN = 1;			// Send ACKDT value
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF = 0;			// Clear the flag bit
}


// Function Purpose: I2C_Write_Byte transfers one byte
int i2c_write(unsigned char data)
{
	SSPBUF = data;		// Send Byte value
	uartdata=SSPBUF;
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF = 0;			// Clear the flag bit

	return SSPCON2bits.ACKSTAT;		// Return ACK/NACK from slave
}

unsigned char i2c_read()
{
	SSPCON2bits.RCEN = 1;			// Enable reception of 8 bits
	while(PIR1bits.SSPIF==0);		// Wait for it to complete
//	PIR1bits.SSPIF = 0;			// Clear the flag bit
 
    return SSPBUF;		// Return received byte
}



void MCP7940_write(unsigned char address,unsigned char value)
{
i2c_start();
i2c_write(0xD0);
i2c_write(address);
i2c_write(value);
i2c_sendack();
i2c_stop();
}

unsigned char MCP7940_read(unsigned char daddress)
{
i2c_start();
i2c_write(0xD0);
i2c_write(daddress);
i2c_restart();
i2c_write(0xD1);
readdata=i2c_read();
i2c_sendack();
i2c_restart();
i2c_stop();
return readdata;
}

void main()
{
unsigned char readdata;
while(1)
//{
//i2cinit();
//i2c_start();
//i2c_write(0x22);
//readdata=i2c_read();
//i2c_sendack();
//i2c_stop();

MCP7940_write(0x00,0x01);
sex=MCP7940_read(0x00);

TXSTA=0X20;
SPBRG=15;
TXSTAbits.TXEN=1;
RCSTAbits.SPEN=1;
TXREG=uartdata;
while(PIR1bits.TXIF==0);

}
