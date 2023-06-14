#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "codetab.h"







void I2C_Configuration(void)
{
	
	I2C_InitTypeDef	I2C_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1,  ENABLE);
			
	
	//PB6--SCL;PB7--SDA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	I2C_DeInit(I2C1);

	I2C_InitStructure.I2C_Ack	= I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);


}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
	
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));		//检查I2C1总线是否繁忙
  
	I2C_GenerateSTART(I2C1,  ENABLE);								//开启I2C1	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)){}//EC5,主模式
	
  I2C_Send7bitAddress(I2C1,  OLED_ADDRESS,  I2C_Direction_Transmitter);//发送器件地址
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1, addr);			//寄存器地址
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	
	I2C_SendData(I2C1, data);			//发送数据
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));

	I2C_GenerateSTOP(I2C1,ENABLE);	//关闭I2C总线

}
//写命令
void WriteCmd(unsigned char I2C_Command)
{
	I2C_WriteByte(0x00,I2C_Command);
}
//写数据的
void WriteDat(unsigned char I2C_Data)
{
	I2C_WriteByte(0x40,I2C_Data);
}
//OLED屏幕初始化
void OLED_Init(void)
{
	delay_ms(100);
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
	
	
}


//设置起点坐标
void OLED_SetPos(unsigned char x,unsigned char y)
{
	WriteCmd(0xb0 +y);
	WriteCmd((x&0xf0)>>4|0x10);
	WriteCmd((x&0x0f)|0x01);

}
//全屏填充
void OLED_Fill(unsigned char Fill_Date)
{
	unsigned char m,n;
	for(m=0;m<9;m++)
	{
		WriteCmd(0xb0+m);
		WriteCmd(0x00);
		WriteCmd(0x10);
		
			for(n=0;n<128;n++)
			{
				WriteDat(Fill_Date);
			}
	}
}
 
//清屏函数
void OLED_CLS(void)
{
	OLED_Fill(0x00);
}

//OLED打开
void OLED_ON(void)
{
	WriteCmd(0x8d);		//打开电荷泵
	WriteCmd(0x14);		//开启电荷泵
	WriteCmd(0xaf);		//OLED唤醒
} 

//OLED关闭
void OLED_OFF(void)
{
	WriteCmd(0x8d);		//打开设置电荷泵
	WriteCmd(0x10);			//关闭电荷泵
	WriteCmd(0xae);			//关闭OLED
}

//显示字符串的函数
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[],unsigned TextSize)
{
	unsigned char c = 0,i = 0, j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')						//如果j不为空（还有字符）则通过下面的程序显示出，如果为空则不运行下面的程序
			{	
				c = ch[j] - 32;										
				if(x>126)											//如果X大于了126就把x变为0，并且y切换到下一行
				{
					x=0;
					y++;
				
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
				WriteDat(F6x8[c][i]);
				x+=6;					//这里的x+=6表示上一个字符的基础上加上6个像素
				j++;					//这里的j++表示ch[j]里面的下一个字符
			}
		}break;
		
		//第二种
		case 2:								
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x>120)
				{
					x=0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
				WriteDat(F8X16[c*16+i]);

				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
				WriteDat(F8X16[c*16+i+8]);
				x+=8;
				j++;
				
			}
			
		}
		
	}
}


//显示汉字
void OLED_ShowCN(unsigned char x,unsigned char y,unsigned char N)
{
		unsigned char wm=0;
		unsigned int addr = 32*N;
		OLED_SetPos(x,y);
		for(wm=0;wm<16;wm++)
  	{
			WriteDat(led[addr]);
			addr += 1;
			
	  }
		OLED_SetPos(x,y+1);
		for(wm=0;wm<16;wm++)
  	{
			WriteDat(led[addr]);
			addr += 1;
			
	  }

	
	
}

//显示图片
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;
	
	if(y1%8 == 0)
	
		y = y1/8;
	else
		y = y1/8+1;
	
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
		for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
		
	}
	


}






























