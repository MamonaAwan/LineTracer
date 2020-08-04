#include <reg51.h>
	sfr ldata= 0x90;
	sbit rs=P2^0;
	sbit rw=P2^1;
	sbit en=P2^2;
	sbit sw=P2^3;
	sbit r=P2^5;
	sbit w=P2^6;
	sbit intr=P2^7;
	sbit busy=P1^7;
unsigned char adc()
{
	unsigned char level;
	P3=0x0ff;
	intr=1;
	w=0;
	w=1;
 	while(intr==1);
	r=0;
	level=P3;
	r=1;
 	return level;
}
void MSDelay(unsigned char itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
	for(j=0;j<1275;j++);
	return;
}

void lcdready()
{
	busy =1;
	rs=0;
	rw=1;
	while(busy==1)
	{
		en=0;
		MSDelay(1);
		en=1;
	}
	return;
}
void lcdcmd(unsigned char value)
{
	lcdready();
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	MSDelay(1);
	en=0;
	return;
}
void lcddata(unsigned char value)
{
	lcdready();
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	MSDelay(1);
	en=0;
	return;
}
void main()
{	unsigned char h,z,a,b,c,d,e;
	unsigned char msg[]="rollno. 07,25,30";
	sw=1;
	lcdcmd(0x38);
	MSDelay(10);
	lcdcmd(0x0E);
	MSDelay(10);
	lcdcmd(0x80);
	MSDelay(10);
   	for(z=0;z<16;z++)
	{
		lcddata(msg[z]);
		MSDelay(10);
	}
	while (1)	
	{ 
		if (sw==0)
		{	unsigned char msg4[]="press switch";
			lcdcmd(0xC0);
			for(d=0;d<12;d++)
			{
				lcddata(msg4[d]);
				MSDelay(10);
			}
		}
		else
		{
			h=adc();
			if(h>=207 && h<=218)
			{	unsigned char msg1[]="blue color  ";
				lcdcmd(0xC0);
				for(a=0;a<12;a++)
				{
					lcddata(msg1[a]);
					MSDelay(10);
				}
			}
			else if(h>=220 && h<=236)
			{	unsigned char msg2[]="green color  ";
				lcdcmd(0xC0);
				for(b=0;b<12;b++)
				{
					lcddata(msg2[b]);
					MSDelay(10);
				}
			}
			else if (h>=188 && h<=199)
			{	unsigned char msg3[]="red color   ";
				lcdcmd(0xC0);
				for(c=0;c<12;c++)
				{
					lcddata(msg3[c]);
					MSDelay(10);
				}
			}
			else
			{
				unsigned char msg5[]="not in range";
				lcdcmd(0xC0);
				for(e=0;e<12;e++)
				{
					lcddata(msg5[e]);
					MSDelay(10);
				}
			}				
		}
	}
}	
 
