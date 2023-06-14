#include "stm32f10x.h"
#include "delay.h"

void delay(uint16_t time)    // delay(1000)�ӳ�һ��
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
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		//����ʱ��Դ8��Ƶ
	SysTick->CTRL |=SysTick_CTRL_TICKINT_Msk;								//ʹ���ж�
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;								//����ʱ��
	SysTick->LOAD = 9;																			//��������һ����װ��ֵ
}




/**
*���ܣ�΢�뼶��ʱ����
*������xus:������ʱʱ�䣨��λ��΢�룩
*����ֵ:None
*/

void delay_us(u32 xus)
{
	SysTick->LOAD = 9* xus;																	//��9��Ϊlus,xus������ֵҪ*9
	SysTick->VAL = 0;																				//����������
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));		//�ȴ��������
}




/**
*���� ��΢�뼶��ʱ����
*���� ��xus ��������ʱʱ�䣨��λ��΢�룩
*����ֵ��None
*/

void delay_ms(u32 xms)
{
	SysTick->LOAD = 9000;																		//��9��Ϊ1us��1000��Ϊ1ms
	SysTick->VAL = 0;																				//����������
	while(xms--)
	{
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));	//�ȴ����μ������
	}
}














