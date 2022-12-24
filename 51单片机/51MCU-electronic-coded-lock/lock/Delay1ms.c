#include <REGX52.H>
#include<INTRINS.h>



void Delay1ms(char time)		//@11.0592MHz
{
	char t;
	for(t=0;t<time;t++){
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
	}
	
}
