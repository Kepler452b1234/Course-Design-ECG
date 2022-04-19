/*

	此c文件用于对屏幕数组进行操作
	数组包括屏幕缓冲和临时缓冲
	函数只会目前选择的缓冲进行操作
	目前选择的缓冲可通过函数设置上面两个缓冲之一
	
	然后就是提供读或写入取缓冲中的8位数据或1位数据的接口
	最后是更新缓冲数据到屏幕
*/

#include "oled_buffer.h"
#include "oled_config.h"
#include "oled_color.h"
#include "string.h"


//定义缓冲 屏幕缓冲区和临时缓冲区
unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN]={0};	//屏幕缓冲
static _Bool _SelectedBuffer=SCREEN_BUFFER;						//当前选择的缓冲区

#define BUFFERSIZE  sizeof(ScreenBuffer)
extern void UpdateTempBuffer(void);
extern void UpdateScreenBuffer(void);
extern void UpdateScreenBuffer_PART(int x0,int y0,int x1,int y1);
///////////////////////////////////////////////////////////////////
//设置选择 屏幕缓冲
void SetScreenBuffer(void)
{
	_SelectedBuffer=SCREEN_BUFFER;
}
//设置选择 临时缓冲
void SetTempBuffer(void)
{
	_SelectedBuffer=TEMP_BUFFER;
}
//获取程序目前选择的缓冲区
unsigned char GetSelectedBuffer(void)
{
	return _SelectedBuffer;
}
//功能:清除屏幕缓冲数据
void ClearScreenBuffer(unsigned char val)
{
	memset(ScreenBuffer,0,sizeof(ScreenBuffer));
}




///////////////////////////////////////////////////////////////////////////////////////////
//读取选择的缓冲区的8位数据
unsigned char ReadByteBuffer(int page,int x)
{
	return ScreenBuffer[page][x];
}
//写入读取选择的缓冲区8位数据
void WriteByteBuffer(int page,int x,unsigned char byte)
{
	if(_SelectedBuffer)
	{
		ScreenBuffer[page][x] =byte;
	}
	else
	{
	}
}

//设置当前选择的缓冲区 的 某一个点的亮灭
void SetPointBuffer(int x,int y,int value)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //超出范围
		return;
	if(_SelectedBuffer)
	{
		if(value)
			ScreenBuffer[y/SCREEN_PAGE_BIT][x] |= 1<<(y%SCREEN_PAGE_BIT);
		else
			ScreenBuffer[y/SCREEN_PAGE_BIT][x] &= ~(1<<(y%SCREEN_PAGE_BIT));	
	}
	else
	{
	}
}
//获取当前选择的缓冲区 的 某一点的颜色
unsigned char GetPointBuffer(int x,int y)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //超出范围
		return 0;
	if(_SelectedBuffer)
		return (ScreenBuffer[y/SCREEN_PAGE_NUM][x]>>(y%SCREEN_PAGE_NUM))&0x01;
	else
		return 1;
}
//刷新屏幕显示
void UpdateScreenDisplay(void)
{
	UpdateScreenBuffer();
}


void UpdateScreenDisplay_PART(int x0,int y0,int x1,int y1)
{
	UpdateScreenBuffer_PART(x0,y0,x1,y1);
}


