#include "oled_config.h"
/* 屏幕驱动文件引用 */
#include "oled_driver.h"

extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
unsigned int OledTimeMs=0;												//时间基准

//初始化图形库，请将硬件初始化信息放入此中
void DriverInit(void)
{
	
	OLED_Init();			//初始化配置oled
}

//将ScreenBuffer屏幕缓存的内容显示到屏幕上
void UpdateScreenBuffer(void)
{
	OLED_FILL(ScreenBuffer[0]);
}

void UpdateScreenBuffer_PART(int x0,int y0,int x1,int y1)
{
	OLED_FILL_PART(ScreenBuffer[0], x0, y0, x1, y1);
}


//////////////////////////////////////////////////////////
//请将此函数放入1ms中断里，为图形提供时基
//系统时间基准主要用于FrameRateUpdateScreen()中固定帧率刷新屏幕
void OledTimeMsFunc(void)
{
	if(OledTimeMs != 0x00)
	{ 
		OledTimeMs--;
	}
}
//图形库普通的延时函数 需要用户自己配置 这里在delay.c中调用
void DelayMs(int ms)
{
	HAL_Delay(ms);
}


