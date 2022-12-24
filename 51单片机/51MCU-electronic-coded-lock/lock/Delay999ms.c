#include <REGX52.H>
#include<INTRINS.h>


void Delay999ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	_nop_();
	i = 42;
	j = 252;
	k = 9;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}