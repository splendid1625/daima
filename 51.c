#include "reg52.h"
#include "LCD1602.h"
#include "LCD1602.c"
#include "dht11.h"

#define uchar unsigned char
#define uint unsigned int
sbit beep=P1^7;


sbit keySet=P2^4;
sbit keyAdd=P2^5;
sbit keyDec=P2^6;

uchar flag;
uchar tempsetH=33,HumiSetH=79,tempsetL=27,HumiSetL=70;
uchar TH,RH;
void keyScan();
void delay(uint xms)
{
	uint i,j;
	for(i=0;i<xms;i++)
		for(j=0;j<121;j++);
}
void ui_main()
{
	Write_com(0x01); //ÇåÆÁ
	delay(2);
	WriteAddress(0x01);
	delay(2);
	Print("T:   t:27 t:33");
	WriteAddress(0x41);
	Print("R:   r:70 r:79");
}


void main()
{	
	bit tmp;
	
	
	unsigned char DHT[5];
	
	LcdInt();
	delay(5);
	ui_main();
	while(1)
	{		
		delay(200);
		keyScan();
		//if(flag==0)
		//{
			DHT_Start();
			tmp=DHT_ByteRead(&DHT);
		   if(tmp==1)
		   {
		    TH= DHT[2];
		     RH=DHT[0];
		   }
//			receive();//
			WriteAddress(0x03);
			 delay(5);
			WriteData(TH/10+0x30);
			 WriteAddress(0x04);
			 delay(5);
			WriteData(TH%10+0x30);
			  delay(5);
			WriteAddress(0x43);
			 delay(5);
			WriteData(RH/10+0x30);
			 WriteAddress(0x44);
			 delay(5);
			WriteData(RH%10+0x30);
//			delay(200);
			if((TH>tempsetH)||(TH<tempsetL)||(RH>HumiSetH)||(RH<HumiSetL))
			{			
					beep=0;
			}
			else
			{			
					beep=1;				
			}
	}
}
void keyScan()
{	
		if(keySet==0)
		{
			delay(5);
			if(keySet==0)
			{
				//beep=1;
				//led=1;
				flag++;
				if(flag==5)
					flag=0;
			}
			while(!keySet);
		}
		if(keyAdd==0)
		{
			delay(5);
			if(keyAdd==0)
			{
				switch(flag)
				{
					case 1:tempsetL++;WriteAddress(0x08);delay(5);WriteData(tempsetL/10+0x30);WriteAddress(0x09);delay(5);WriteData(tempsetL%10+0x30);break;												 
					case 2:tempsetH++;WriteAddress(0x0d);delay(5);WriteData(tempsetH/10+0x30);WriteAddress(0x0d);delay(5);WriteData(tempsetH%10+0x30);break;
					case 3:HumiSetL++;WriteAddress(0x48);delay(5);WriteData(HumiSetL/10+0x30);WriteAddress(0x49);delay(5);WriteData(HumiSetL%10+0x30);break;
					case 4:HumiSetH++;WriteAddress(0x4d);delay(5);WriteData(HumiSetH/10+0x30);WriteAddress(0x4d);delay(5);WriteData(HumiSetH%10+0x30);break;		
				}
			}
			while(!keyAdd);
		}
		if(keyDec==0)
		{
			delay(5);
			if(keyDec==0)
			{
				switch(flag)
				{
					case 1:tempsetL--;WriteAddress(0x08);delay(5);WriteData(tempsetL/10+0x30);WriteAddress(0x09);delay(5);WriteData(tempsetL%10+0x30);break;												 
					case 2:tempsetH--;WriteAddress(0x0d);delay(5);WriteData(tempsetH/10+0x30);WriteAddress(0x0d);delay(5);WriteData(tempsetH%10+0x30);break;
					case 3:HumiSetL--;WriteAddress(0x48);delay(5);WriteData(HumiSetL/10+0x30);WriteAddress(0x49);delay(5);WriteData(HumiSetL%10+0x30);break;
					case 4:HumiSetH--;WriteAddress(0x4d);delay(5);WriteData(HumiSetH/10+0x30);WriteAddress(0x4d);delay(5);WriteData(HumiSetH%10+0x30);break;
				}
			}
			while(!keyDec);
		}
}
