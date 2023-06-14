#include "stm32f10x.h"
#include "delay.h"

void delay(uint16_t time)    // delay(1000)延迟一秒
{
  uint16_t i=0;
	while(time--)
	{
	  i=12000;
		while(i--);
		
	}

}


void initSysTick(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		//设置时钟源8分频
	SysTick->CTRL |=SysTick_CTRL_TICKINT_Msk;								//使能中断
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;								//开定时器
	SysTick->LOAD = 9;																			//随意设置一个重装载值
}




/**
*功能：微秒级延时函数
*参数：xus:具体延时时间（单位：微秒）
*返回值:None
*/

void delay_us(u32 xus)
{
	SysTick->LOAD = 9* xus;																	//计9次为lus,xus则重载值要*9
	SysTick->VAL = 0;																				//计数器归零
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));		//等待计数完成
}




/**
*功能 ：微秒级延时函数
*参数 ：xus ：具体延时时间（单位：微秒）
*返回值：None
*/

void delay_ms(u32 xms)
{
	SysTick->LOAD = 9000;																		//计9次为1us，1000次为1ms
	SysTick->VAL = 0;																				//计数器归零
	while(xms--)
	{
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));	//等待单次计数完成
	}
}














