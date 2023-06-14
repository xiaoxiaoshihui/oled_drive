#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{
	  GPIO_InitTypeDef led_init;
	  //使能APB2时钟GPIC    //rcc.h
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    
	  //结构体配置 (需要放在前面)   //gpio.h
	  
	  led_init.GPIO_Mode  =GPIO_Mode_Out_PP; //推挽输出
	  led_init.GPIO_Pin   =GPIO_Pin_13;
	  led_init.GPIO_Speed =GPIO_Speed_10MHz;
	  GPIO_Init(GPIOC,&led_init);
	
	
	
	
}


