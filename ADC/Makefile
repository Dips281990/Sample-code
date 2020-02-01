# MPLAB IDE generated this makefile for use with GNU make.
# Project: adc.mcp
# Date: Sun Aug 09 15:00:35 2015

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

adc.cof : adc.o
	$(LD) /p18F4520 /l"C:\MCC18\lib" /k"C:\MCC18\bin\LKR" "adc.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"adc.cof" /M"adc.map" /W

adc.o : adc.c C:/MCC18/h/p18f4520.h
	$(CC) -p=18F4520 /i"C:\MCC18\h" "adc.c" -fo="adc.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "adc.o" "adc.cof" "adc.hex"

