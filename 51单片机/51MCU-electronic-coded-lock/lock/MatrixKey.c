#include <REGX52.H>
#include "Delay1ms.h"
#define key P1


/**
 * @brief 先行扫描，再列扫描
 */
unsigned char MatrixKey(){
	unsigned char keyValue[16] = {1,2,3,'A',
								  4,5,6,'B',
								  7,8,9,'C',
								'*',0,'#','D'};
    unsigned char num = 100;
    key = 0xF0;
    if(key != 0xF0){
        Delay1ms(10);   //延时抖消
        if(key != 0xF0){    //check again
			key = 0xF0;
            switch(key)   //先确定行
             {
                case 0x70: num=1;  break;   //第一行
                case 0xb0: num=5;  break;   //第二行
                case 0xd0: num=9;  break;   //第三行
                case 0xe0: num=13; break;   //第四行
             }
             key = 0x0F;     //对应IO口拉高，以便检测
             switch(key)   //再确定列
             {
                case 0x07: num=num+0;while(key != 0x0F){}; break;   //第一列
                case 0x0b: num=num+1;while(key != 0x0F){}; break;   //第二列
                case 0x0d: num=num+2;while(key != 0x0F){}; break;   //第三列
                case 0x0e: num=num+3;while(key != 0x0F){}; break;   //第四列
             }
        }
    }
    
	if(num == 100)
		return 100;
	else
		return keyValue[num-1];
}