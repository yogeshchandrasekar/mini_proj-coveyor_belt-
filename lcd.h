#include<LPC21XX.H>
#include"delay.h"
#define LCD_D (0xff<<16)
#define RS (1<<24)
#define E (1<<25)
void LCD_DATA(unsigned char );
void LCD_COMMAND(unsigned char );
void LCD_INIT(void);
void LCD_STRING(char * st);
void LCD_INT(unsigned int val);
void LCD_INIT(void)
{
PINSEL0=0X00;
IODIR1|=LCD_D|RS|E;
IOCLR1=LCD_D;
LCD_COMMAND(0X38);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
}
void LCD_COMMAND(unsigned char cmd)
{
IOCLR1=LCD_D;
IOSET1=(cmd<<16);
IOCLR1=RS;
IOSET1=E;
delay_ms(2);
IOCLR1=E;
}
void LCD_DATA(unsigned char d)
{
IOCLR1=LCD_D;
IOSET1=(d<<16);
IOSET1=RS;
IOSET1=E;
delay_ms(2);
IOCLR1=E;
}
void LCD_STRING(char * st){
	while(*st){
	LCD_DATA(*st++);
	}
}
void LCD_INT(unsigned int val){
	unsigned int arr[50];
	int j=0;
	while(val!=0){
		arr[j++]=val%10;
		val=val/10;
	}
	for(j--;j>=0;j--){
		LCD_DATA(arr[j]+48);
	}
}
