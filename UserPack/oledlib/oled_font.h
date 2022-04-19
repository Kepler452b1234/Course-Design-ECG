#ifndef OLED_FONT_H
#define OLED_FONT_H

typedef enum 
{
	TEXT_BK_NULL=0,
	TEXT_BK_NOT_NULL,
}Type_textbk;

struct Cn16CharTypeDef                	// ������ģ���ݽṹ 
{
	unsigned char  Index[2];            // ������������,һ������ռ�����ֽ�	
	unsigned char  Msk[32];             // ����������(16*16��32������) 
};

#define NUM_OFCHINESE	8
extern const unsigned char font5x7[];
extern const unsigned char F8X16[];
extern struct Cn16CharTypeDef const CN16CHAR[NUM_OFCHINESE];



//����:��������ı���ģʽ 0Ϊ͸����1Ϊ������
void SetTextBkMode(Type_textbk value);
//����:��ȡ����ı���ģʽ 0Ϊ͸����1Ϊ������
Type_textbk GetTextBkMode(void);

unsigned char GetFontSize(void);
void SetFontSize(unsigned char value);
#endif

