#include "stm32f10x.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
char stra[] = "Hessllo world";

extern const unsigned char BMP2[];
extern const unsigned char BMP1[];

int main()
{
	unsigned char i=0;
	initSysTick();
	I2C_Configuration();
	OLED_Init();									//屏幕初始化而且这个代码厂家给的
	delay_ms(2000);
	
	OLED_Fill(0xff);							//屏幕点亮
	delay_ms(2000);
	OLED_Fill(0x00);							//全屏熄灭
	delay_ms(2);
//	OLED_ShowStr(0,3,"Hello Wrold",1);
//	OLED_ShowStr(0,6,"He World",2);
//	OLED_ShowStr(29,3,"lingziyue",2);

  while(1)
	{
			
		for(i=0;i<3;i++)
		{
		 OLED_ShowCN( 36+i*16, 3, i );
		 

		}
//		OLED_DrawBMP(  0,  0,  128,  8,(unsigned char*)BMP2);
//		
//	

//		OLED_Fill(0x00);							//全屏熄灭
//		delay_ms(1);
//		OLED_DrawBMP(  0,  0,  128,  8,(unsigned char*)BMP1);

//	
//		OLED_Fill(0x00);							//全屏熄灭
//		delay_ms(1);

	}

}

