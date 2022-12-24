#include <REGX52.H>
#include "Delay1ms.h"
#include "Delay999ms.h"
#include "LCD1602.h"
#include "MatrixKey.h"
#include "INTRINS.h"
#include "string.h"

sbit beep = P3^0;
sbit led = P3^7;

//全局变量
unsigned char getkeyNum;
passWord[6] = {1,2,3,4,5,6};	//默认设置代码为123456
char pw[6];						//存储输入密码
char i = 1;						//存储显示输入密码位置
char m;							//定位重置密码的输入值
unsigned char resetNum ;		//接收重置时返回的键值
char open = 'f';				//标志是否开锁成功


//重置密码
void resetPW(unsigned char getkeyNum){
	if(getkeyNum == 'A'){
		LCD_ShowString(2,1,"RESET");
		LCD_ShowString(1,1,"      ");		
		i=1;		//重置显示位置
		m=0;
		while(1){
			
			//输入六次，若已经输入完成，显示SUCCESS
			if(m>=6){
				LCD_ShowString(2,1,"SUCCESS");
				Delay999ms();
				LCD_ShowString(2,1,"       ");
				LCD_ShowString(1,1,"       ");
				i=1;
				break;
			}
			resetNum = MatrixKey();
			//如果有按键输入
			if(resetNum != 100){
				//如果按下删除键'B'
				if(resetNum == 'B'){
					m--;
					LCD_ShowChar(1,m+1,' ');
					continue;
				}
					
				//输出按键值
				if(resetNum < 10 )
					LCD_ShowChar(1,m+1,resetNum+48);
				else
					LCD_ShowChar(1,m+1,resetNum);
			
				passWord[m] = resetNum; m++;	//修改密码
			}
		}
	}
}


void Timer0Init(){
	EA = 0;		   //关闭总中断
	ET0 = 1;	   //允许T0中断
	TMOD = 0x01;	//定时器模式，T0使用工作方式1
	TH0 = 0x18;    //该初值使隔段时间产生一次中断
	TL0 = 0xFC;
	TR0 = 1;		//打开T0定时器
} 

//打开蜂鸣器
void startBeep(){
	EA = 1;
}
//关闭蜂鸣器
void stopBeep(){
	EA = 0;
}

void Timer0() interrupt 1  {
	TH0 = 63628/256;    	//通过定时器控制蜂鸣器发声频率
	TL0 = 63628%256;
	beep=~beep;				//反复切换高低电平。 
}


void main(){	
	Timer0Init();
	LCD_Init();
	led = 0;	
	
    while(1){
        getkeyNum = MatrixKey();
		
		//如果有按键输入
        if(getkeyNum != 100){
			
			//输入密码成功后修改密码
			if(open == 't'){
				resetPW(getkeyNum);
				open = 'f';
				continue;
			}
			
			//如果按下删除键'B'
			if(getkeyNum == 'B'){
				i--;
				LCD_ShowChar(1,i,' ');
				continue;
			}
			
		
			if(i<=6){
				//输出按键值
				if(getkeyNum < 10 )
					LCD_ShowChar(1,i,getkeyNum+48);
				else
					LCD_ShowChar(1,i,getkeyNum);
				
				pw[i-1] = getkeyNum;		//存入按键值
				i++;
			}else{
			
				if(getkeyNum == 'D'){		//如果密码相等，显示开锁成功
					if(pw[0]==passWord[0]&& pw[1]==passWord[1]&& pw[2]==passWord[2]&& pw[3]==passWord[3]&& pw[4]==passWord[4] && pw[5]==passWord[5]){
						LCD_ShowString(2,1,"OPEN!");
						led = 1;			//点亮LED
						open = 't';	
						startBeep();		//打开蜂鸣器
						Delay999ms();
						stopBeep();			//关闭蜂鸣器
						led = 0;
						LCD_ShowString(2,1,"      "); 
						
					}
					//如果密码不符合，清空输入密码的显示屏
					else{
						LCD_ShowString(2,1,"Failed!");
						Delay999ms();
						LCD_ShowString(2,1,"       ");
					}
					//重置pw,重置输入密码显示位置
					LCD_ShowString(1,1,"      ");
					i=1;	
				}
				
			}
		}	
	}
}

