#define r0 (1<<3)
#define r1 (1<<4)
#define r2 (1<<5)
#define r3 (1<<6)
#define c0 7
#define c1 8
#define c2 9
#define c3 10
unsigned int row_val;
unsigned int col_val;
unsigned char value=0;
void keypad_init(void){
PINSEL0 = 0x00000000;
IODIR0=r0|r1|r2|r3;
IOSET0=r0|r1|r2|r3;
while((((IOPIN0>>c0)&1)&&((IOPIN0>>c1)&1)&&((IOPIN0>>c2)&1)&&((IOPIN0>>c3)&1))==1){
	IOSET0 = r0|r1|r2|r3;
	IOCLR0=r0;
	if((((IOPIN0>>c0)&1)&&((IOPIN0>>c1)&1)&&((IOPIN0>>c2)&1)&&((IOPIN0>>c3)&1))==0){
	row_val=0;
	break;
}
IOSET0=r0|r1|r2|r3;
IOCLR0=r1;
if((((IOPIN0>>c0)&1)&&((IOPIN0>>c1)&1)&&((IOPIN0>>c2)&1)&&((IOPIN0>>c3)&1))==0){
	row_val=1;
	break;
}
IOSET0=r0|r1|r2|r3;
IOCLR0=r2;
if((((IOPIN0>>c0)&1)&&((IOPIN0>>c1)&1)&&((IOPIN0>>c2)&1)&&((IOPIN0>>c3)&1))==0){
	row_val=2;
	break;
}
IOSET0=r0|r1|r2|r3;
IOCLR0=r3;
if((((IOPIN0>>c0)&1)&&((IOPIN0>>c1)&1)&&((IOPIN0>>c2)&1)&&((IOPIN0>>c3)&1))==0){
	row_val=3;
	break;
}
}
if(((IOPIN0>>c0)&1)==0){
	col_val=0;
}
else if(((IOPIN0>>c1)&1)==0){
	col_val=1;
}
else if(((IOPIN0>>c2)&1)==0){
	col_val=2;
}
else if(((IOPIN0>>c3)&1)==0){
	col_val=3;
}	
while((((IOPIN0>>c0)&1)&&((IOPIN0>>c1)&1)&&((IOPIN0>>c2)&1)&&((IOPIN0>>c3)&1))==0);

}
