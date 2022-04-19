/*

	��c�ļ����ڶ���Ļ������в���
	���������Ļ�������ʱ����
	����ֻ��Ŀǰѡ��Ļ�����в���
	Ŀǰѡ��Ļ����ͨ����������������������֮һ
	
	Ȼ������ṩ����д��ȡ�����е�8λ���ݻ�1λ���ݵĽӿ�
	����Ǹ��»������ݵ���Ļ
*/

#include "oled_buffer.h"
#include "oled_config.h"
#include "oled_color.h"
#include "string.h"


//���建�� ��Ļ����������ʱ������
unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN]={0};	//��Ļ����
static _Bool _SelectedBuffer=SCREEN_BUFFER;						//��ǰѡ��Ļ�����

#define BUFFERSIZE  sizeof(ScreenBuffer)
extern void UpdateTempBuffer(void);
extern void UpdateScreenBuffer(void);
extern void UpdateScreenBuffer_PART(int x0,int y0,int x1,int y1);
///////////////////////////////////////////////////////////////////
//����ѡ�� ��Ļ����
void SetScreenBuffer(void)
{
	_SelectedBuffer=SCREEN_BUFFER;
}
//����ѡ�� ��ʱ����
void SetTempBuffer(void)
{
	_SelectedBuffer=TEMP_BUFFER;
}
//��ȡ����Ŀǰѡ��Ļ�����
unsigned char GetSelectedBuffer(void)
{
	return _SelectedBuffer;
}
//����:�����Ļ��������
void ClearScreenBuffer(unsigned char val)
{
	memset(ScreenBuffer,0,sizeof(ScreenBuffer));
}




///////////////////////////////////////////////////////////////////////////////////////////
//��ȡѡ��Ļ�������8λ����
unsigned char ReadByteBuffer(int page,int x)
{
	return ScreenBuffer[page][x];
}
//д���ȡѡ��Ļ�����8λ����
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

//���õ�ǰѡ��Ļ����� �� ĳһ���������
void SetPointBuffer(int x,int y,int value)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //������Χ
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
//��ȡ��ǰѡ��Ļ����� �� ĳһ�����ɫ
unsigned char GetPointBuffer(int x,int y)
{
	if(x>SCREEN_COLUMN-1 ||y>SCREEN_ROW-1)   //������Χ
		return 0;
	if(_SelectedBuffer)
		return (ScreenBuffer[y/SCREEN_PAGE_NUM][x]>>(y%SCREEN_PAGE_NUM))&0x01;
	else
		return 1;
}
//ˢ����Ļ��ʾ
void UpdateScreenDisplay(void)
{
	UpdateScreenBuffer();
}


void UpdateScreenDisplay_PART(int x0,int y0,int x1,int y1)
{
	UpdateScreenBuffer_PART(x0,y0,x1,y1);
}


