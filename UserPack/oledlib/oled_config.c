#include "oled_config.h"
/* ��Ļ�����ļ����� */
#include "oled_driver.h"

extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
unsigned int OledTimeMs=0;												//ʱ���׼

//��ʼ��ͼ�ο⣬�뽫Ӳ����ʼ����Ϣ�������
void DriverInit(void)
{
	
	OLED_Init();			//��ʼ������oled
}

//��ScreenBuffer��Ļ�����������ʾ����Ļ��
void UpdateScreenBuffer(void)
{
	OLED_FILL(ScreenBuffer[0]);
}

void UpdateScreenBuffer_PART(int x0,int y0,int x1,int y1)
{
	OLED_FILL_PART(ScreenBuffer[0], x0, y0, x1, y1);
}


//////////////////////////////////////////////////////////
//�뽫�˺�������1ms�ж��Ϊͼ���ṩʱ��
//ϵͳʱ���׼��Ҫ����FrameRateUpdateScreen()�й̶�֡��ˢ����Ļ
void OledTimeMsFunc(void)
{
	if(OledTimeMs != 0x00)
	{ 
		OledTimeMs--;
	}
}
//ͼ�ο���ͨ����ʱ���� ��Ҫ�û��Լ����� ������delay.c�е���
void DelayMs(int ms)
{
	HAL_Delay(ms);
}


