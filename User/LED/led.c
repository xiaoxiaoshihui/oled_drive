#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{
	  GPIO_InitTypeDef led_init;
	  //ʹ��APB2ʱ��GPIC    //rcc.h
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    
	  //�ṹ������ (��Ҫ����ǰ��)   //gpio.h
	  
	  led_init.GPIO_Mode  =GPIO_Mode_Out_PP; //�������
	  led_init.GPIO_Pin   =GPIO_Pin_13;
	  led_init.GPIO_Speed =GPIO_Speed_10MHz;
	  GPIO_Init(GPIOC,&led_init);
	
	
	
	
}


