#ifndef OLED_DRAW_H
#define OLED_DRAW_H
#include "oled_basic.h"
#include "oled_color.h"
#include "stdint.h"
void DrawPixel(int x,int y);
void DrawLine(int x1,int y1,int x2,int y2);
void DrawLine_2(int x1,int y1,int x2,int y2,int left,int top,int right,int bottom);	
void DrawFastHLine(int x, int y, unsigned char w);
void DrawFastVLine(int x, int y, unsigned char h);
void DrawPolyLineTo(const TypeXY *points,int num);
void DrawBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);
void DrawXBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);//此函数具体注释请参照'draw_api.h'内
void DrawSlowBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);
void DrawChar(int x, int y, unsigned char c);
void DrawString(int x, int y,char *str);
void DrawNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len);
//void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t *cn);
void DrawRect(int left,int top,int right,int bottom);
void Clear_Screen(int x0,int y0,int x1,int y1);

void Draw_Dottedrect(int left,int top,int right,int bottom);
void Reverse_Screen(int x0,int y0,int x1,int y1);
void Draw_Arrow(uint8_t x,uint8_t y,uint8_t flag);

Type_color GetPixel(int x,int y);
int GetY(void);
int GetX(void);
TypeXY GetXY(void);
void MoveTo(int x,int y);
void LineTo(int x,int y);
#endif

