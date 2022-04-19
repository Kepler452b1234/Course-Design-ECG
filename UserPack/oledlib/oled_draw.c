/*
	Copyright (c) [2019] [一只程序缘 jiezhuo]
	[https://gitee.com/jiezhuonew/oledlib] is licensed under the Mulan PSL v1.
	You can use this software according to the terms and conditions of the Mulan PSL v1.
	You may obtain a copy of Mulan PSL v1 at:
		http://license.coscl.org.cn/MulanPSL
	THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
	PURPOSE.
	See the Mulan PSL v1 for more details.
	
	
	此c文件用于画图和字符操作(高级操作)
	(主要)由打点为基础
	再 线 折线
	再画和填充 矩形 三角形 圆 椭圆 圆角矩形
	然后是 图片 字符 字符串
	最后是 汉字
*/

#include "oled_draw.h"
#include "oled_buffer.h"
#include "oled_config.h"
#include "stdlib.h"
#include "math.h"
#include "oled_bmp.h"
#include "oled_font.h"


extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
//画图光标
static int  _pointx=0;
static int 	_pointy=0;

////////////////////////////////////////////////////////////////////
//以下4个函数是对当前光标的设置 供以下绘制函数调用 用户不直接使用
void MoveTo(int x,int y)
{
	_pointx=x;
	_pointy=y;
}

TypeXY GetXY(void)
{
	
	TypeXY m;
	m.x=_pointx;
	m.y=_pointy;
	return m;
}
int GetX(void)
{
	return _pointx;
}
int GetY(void)
{
	return _pointy;
}
void LineTo(int x,int y)
{
	DrawLine(_pointx,_pointy,x,y);
	_pointx=x;
	_pointy=y;

}
///////////////////////////////////////////////////////////////////////////////////
//绘制一个点
void DrawPixel(int x,int y)
{
	SetPointBuffer(x,y,GetDrawColor());
}
//得到某个点的颜色
Type_color GetPixel(int x,int y)
{
	if(GetPointBuffer(x,y))
		return pix_white;
	else
		return pix_black;
}

////////////////////////////////////////////////////////////////////////////////////
////划线 
////参数:起点坐标 终点坐标
void DrawLine(int x1,int y1,int x2,int y2)
{
	
	unsigned short us; 
	unsigned short usX_Current, usY_Current;
	
	int lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int lIncrease_X, lIncrease_Y; 	

	lDelta_X = x2 - x1; //计算坐标增量 
	lDelta_Y = y2 - y1; 

	usX_Current = x1; 
	usY_Current = y1; 

	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; 			//设置单步正方向 
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;			//垂直线 
	else 
	{ 
		lIncrease_X = -1;			//设置单步反方向 
		lDelta_X = - lDelta_X;
	} 

	//Y轴的处理方式与上图X轴的处理方式同理
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;			//水平线 
	else 
	{
		lIncrease_Y = -1;
		lDelta_Y = - lDelta_Y;
	} 

	//选取不那么陡的方向依次画点
	if ( lDelta_X > lDelta_Y )
		lDistance = lDelta_X;
	else 
		lDistance = lDelta_Y; 

	//依次画点 进入缓存区 画好后再刷新缓冲区就好啦
	for ( us = 0; us <= lDistance + 1; us ++ )					//画线输出 
	{
		
		SetPointBuffer(usX_Current,usY_Current,GetDrawColor());	//画点 
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 

		if ( lError_X > lDistance ) 
		{
			lError_X -= lDistance; 
			usX_Current += lIncrease_X; 
		}  

		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			usY_Current += lIncrease_Y; 
		} 		
	}  
}

//划线 
//参数:起点坐标 终点坐标
void DrawLine_2(int x1,int y1,int x2,int y2,int left,int top,int right,int bottom)
{
	
	unsigned short us; 
	unsigned short usX_Current, usY_Current;
	
	int lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int lIncrease_X, lIncrease_Y; 	

	lDelta_X = x2 - x1; //计算坐标增量 
	lDelta_Y = y2 - y1; 

	usX_Current = x1; 
	usY_Current = y1; 

	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; 			//设置单步正方向 
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;			//垂直线 
	else 
	{ 
		lIncrease_X = -1;			//设置单步反方向 
		lDelta_X = - lDelta_X;
	} 

	//Y轴的处理方式与上图X轴的处理方式同理
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;			//水平线 
	else 
	{
		lIncrease_Y = -1;
		lDelta_Y = - lDelta_Y;
	} 

	//选取不那么陡的方向依次画点
	if ( lDelta_X > lDelta_Y )
		lDistance = lDelta_X;
	else 
		lDistance = lDelta_Y; 

	//依次画点 进入缓存区 画好后再刷新缓冲区就好啦
	for ( us = 0; us <= lDistance + 1; us ++ )					//画线输出 
	{
		if(usY_Current>=top&&usY_Current<=bottom&&usY_Current>=top&&usY_Current<=bottom)
		SetPointBuffer(usX_Current,usY_Current,GetDrawColor());	//画点 
		lError_X += lDelta_X; 
		lError_Y += lDelta_Y; 

		if ( lError_X > lDistance ) 
		{
			lError_X -= lDistance; 
			usX_Current += lIncrease_X; 
		}  

		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			usY_Current += lIncrease_Y; 
		} 		
	}  
}
//快速划线 专用于画横平竖直的线 提高效率
void DrawFastHLine(int x, int y, unsigned char w)
{
	int end = x+w;
	int a;
	
	Type_color color =GetDrawColor();
	for ( a = MAX(0,x); a < MIN(end,SCREEN_COLUMN); a++)
	{
		SetPointBuffer(a,y,color);
	}
}
//快速划线 专用于画横平竖直的线 提高效率
void DrawFastVLine(int x, int y, unsigned char h)
{
	int end = y+h;
	int a;
	
	Type_color color =GetDrawColor();
	for (a = MAX(0,y); a < MIN(end,SCREEN_ROW); a++)
	{
		SetPointBuffer(x,a,color);
	}
}
//绘制折线 开始和转折点的坐标 总点个数
void DrawPolyLineTo(const TypeXY *points,int num)
{
	int i=0;
	MoveTo(points[0].x,points[0].y);
	for(i=1;i<num;i++)
	{
		LineTo(points[i].x,points[i].y);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//画一幅画，PCtoLCD2002参数请选择[阴码 列行式 逆向]
//起点坐标x y 图像取模数组 图像宽高w h
void DrawBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h)
{
	int iCol,a;
	int yOffset = abs(y) % 8;
	int sRow = y / 8;
	int rows = h/8;

	if(x+w < 0 || x > SCREEN_COLUMN-1 || y+h < 0 || y > SCREEN_ROW-1)
		return;
	if(y < 0)
	{
		sRow--;
		yOffset = 8 - yOffset;
	}

	if(h%8!=0) rows++;
	for(a = 0; a < rows; a++) 
	{
		int bRow = sRow + a;
		if(bRow > (SCREEN_ROW/8)-1) break;
		if(bRow > -2) 
		{
			for (iCol = 0; iCol<w; iCol++) 
			{
				if (iCol + x > (SCREEN_COLUMN-1)) break;
				if (iCol + x >= 0) 
				{
					if (bRow >= 0) 
					{
						if(GetDrawColor() == pix_white)
						{
							unsigned char temp = ReadByteBuffer(bRow,x + iCol);
							temp|=pgm_read_byte(bitmap+(a*w)+iCol) << yOffset;
							WriteByteBuffer(bRow,x + iCol,temp);
						}
						else if(GetDrawColor() == pix_black)
						{
							unsigned char temp = ReadByteBuffer(bRow,x + iCol);
							temp&=~(pgm_read_byte(bitmap+(a*w)+iCol) << yOffset);
							WriteByteBuffer(bRow,x + iCol,temp);
						}
						else
						{
							unsigned char temp = ReadByteBuffer(bRow,x + iCol);
							temp^=(pgm_read_byte(bitmap+(a*w)+iCol) << yOffset);
							WriteByteBuffer(bRow,x + iCol,temp);
						}
					}
					if (yOffset && bRow<(SCREEN_ROW/8)-1 && bRow > -2) 
					{
						if(GetDrawColor() == pix_white) 
						{
							unsigned char temp = ReadByteBuffer(bRow+1,x + iCol);
							temp|=pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
							WriteByteBuffer(bRow+1,x + iCol,temp);
						}
						else if (GetDrawColor() == pix_black)
						{
							unsigned char temp = ReadByteBuffer(bRow+1,x + iCol);
							temp&=~(pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset));
							WriteByteBuffer(bRow+1,x + iCol,temp);
						}
						else
						{
							unsigned char temp = ReadByteBuffer(bRow+1,x + iCol);
							temp^=pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
							WriteByteBuffer( bRow+1,x + iCol,temp);						
						}
					}
				}
			}
		}
	}
}

//画一幅画，PCtoLCD2002参数请选择[阴码 逐行式 逆向]，具体描述参见[draw_api.h]
//起点坐标x y 图像取模数组 图像宽高w h
void DrawXBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h)
{
  // no need to dar at all of we're offscreen
  int xi, yi, byteWidth = (w + 7) / 8;
  if (x + w < 0 || x > SCREEN_COLUMN - 1 || y + h < 0 || y > SCREEN_ROW - 1)
    return;
  for (yi = 0; yi < h; yi++) {
    for (xi = 0; xi < w; xi++ ) {
      if (pgm_read_byte(bitmap + yi * byteWidth + xi / 8) & (1 << (xi & 7))) {
        SetPointBuffer(x + xi, y + yi, GetDrawColor());
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//显示一个字符
//关于字体尺寸及使用请看SetFontSize()的注释
//当size=0时 x为第几行 y为第几列
void DrawChar(int x, int y, unsigned char c)
{
	int i,j;
	unsigned char draw_background,bg,a,b,size,color;
	
	size=GetFontSize();		//字体尺寸
	color=GetDrawColor();	//字体颜色 1白0黑
	bg=GetTextBkMode();		//写字的时候字的背景的颜色 1白0黑
	draw_background= bg = !color;	//这两个颜色要不一样字才看得到
	
	if(!size)//默认字符大小
	{
		if((y>SCREEN_PAGE_NUM-2) || (x>SCREEN_COLUMN-8))
			return;
		c=c-' ';			//得到偏移后的位置
		for(i=0;i<8;i++)
			WriteByteBuffer(y,x+i,F8X16[c*16+i]);
		for(i=0;i<8;i++)
			WriteByteBuffer(y+1,x+i,F8X16[c*16+i+8]);
	}
	else//使用原作粗体字符
	{
		//判断一个字符的上下左右是否超出边界范围
		if ((x >= SCREEN_COLUMN) ||         // Clip right
		(y >= SCREEN_ROW) ||        		// Clip bottom
		((x + 5 * size - 1) < 0) ||   		// Clip left
		((y + 8 * size - 1) < 0)    		// Clip top
		)
			return;
		for (i=0; i<6; i++)
		{
			int line;
			//一个字符在font5x7中由一行6个char表示
			//line为这个字符的第某行内容
			if (i == 5)
				line = 0x0;		//5*7字体，也就是只有5列数据，所以第6列写0				`								
			else
				line = pgm_read_byte(font5x7+(c*5)+i);		//不是第六列就从字库找出需要写入的数据
			
			for (j=0; j<8; j++)
			{
				unsigned char draw_color = (line & 0x1) ? color : bg;//目前需要填充的颜色是0 就是背景色 1就是字体色

				//不同号大小的字体只是最基础字体的放大倍数 这点要注意
				//比如基础字是1个像素 放大后就是4个像素 再就是9个像素 达到马赛克的放大效果
				if (draw_color^draw_background) 		//这里改成异或，当背景色和点颜色不同时候才写入
					for ( a = 0; a < size; a++ )		//嵌套for，就是依次填充数组，按放大倍数放大后写入，放大倍数是2就连着写两个
						for ( b = 0; b < size; b++ )
							SetPointBuffer(x + (i * size) + a, y + (j * size) + b, draw_color);

				line >>= 1;
			}
		}
	}
}
//显示字符串 就是显示多次显示字符
void DrawString(int x, int y,char *str)
{
	unsigned char j=0,tempx=x,tempy=y;
	unsigned char size=GetFontSize();
	
	if(!size)//默认字体
	{
		while (str[j]!='\0')
		{
			DrawChar(x,y,str[j]);
			x+=8;
			if(x>SCREEN_PAGEDATA_NUM-8){x=0;y+=2;}
			j++;
		}
	}
	else//使用原作粗体字符
	{
		while (str[j]!='\0')
		{
			if(str[j]=='\n')
			{
				tempy+=8*size;
				tempx=x;
				j++;
				continue;
			}
			DrawChar(tempx,tempy,str[j]);
			tempx+=size*6;
			j++;
		}
	}
}
////显示数字 就是多次显示数字的字符
//void DrawNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len)
//{         	
//	unsigned char t,temp;
//	unsigned char enshow=0;			
//	unsigned char size=GetFontSize();
//	
//	if(!size)
//	{
//		for(t=0;t<len;t++)
//		{
//			temp=(num/oled_pow(10,len-t-1))%10;
//			if(enshow==0&&t<(len-1))
//			{
//				if(temp==0)
//				{
//					DrawChar(x,y+8*t,' ');
//					continue;
//				}
//				else 
//					enshow=1; 
//			}
//			DrawChar(x,y+8*t,temp+'0'); 
//		}
//	}
//	else
//	{
//		for(t=0;t<len;t++)
//		{
//			temp=(num/oled_pow(10,len-t-1))%10;
//			if(enshow==0&&t<(len-1))
//			{
//				if(temp==0)
//				{
//					DrawChar(x+(size*6)*t,y,'0');
//					continue;
//				}else enshow=1; 	 
//			}
//		 DrawChar(x+(size*6)*t,y,temp+'0'); 
//		}
//	}
//} 
//////////////////////////////////////////////////////////////////////////////////////////////////
//显示汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t *cn)
{      			    
	uint8_t j,wordNum;

	if((x > 7)||(y>128-16))
		return;
	
	while ( *cn != '\0')	 																	//在C语言中字符串结束以‘\0’结尾
	{
		for (wordNum=0; wordNum<NUM_OFCHINESE; wordNum++)
		{
			if ((CN16CHAR[wordNum].Index[0] == *cn)&&(CN16CHAR[wordNum].Index[1] == *(cn+1)))   //查询要写的字在字库中的位置
			{
				for (j=0; j<32; j++) 															//写一个字
				{		
					if (j == 16)	 															//由于16X16用到两个Y坐标，当大于等于16时，切换坐标
					{
						x++;
					}			
					WriteByteBuffer(x,y+(j%16),CN16CHAR[wordNum].Msk[j]);
				}
				y += 16;
				x--;
				if(y > (128-16))
				{x += 2;y = 0;}
			}
		}
		cn += 2;																			//此处打完一个字，接下来寻找第二个字
	}
}


//使用对角点填充矩形
void DrawRect(int left,int top,int right,int bottom)
{
	DrawLine ( left, top, right, top );
	DrawLine ( left, bottom , right , bottom );
	DrawLine ( left, top, left, bottom );
	DrawLine ( right , top, right , bottom );	
}

void Draw_Dottedrect(int left,int top,int right,int bottom)
{
	DrawRect(left,top,right,bottom);
	for(int i=top;i<bottom;i=i+16)
		for(int j=left+2;j<right-2;j=j+8)
		{
			for(int a=-2;a<3;a++)
				DrawPixel ( j+a, i);
//			for(int b=-2;b<3;b++)
//				DrawPixel ( j, i+b);
		}
		

}

//对屏幕选中位置经行清屏
void Clear_Screen(int x0,int y0,int x1,int y1)
{
	for(int i=x0;i<=x1;i++)
		for(int j=y0;j<=y1;j++)
	  ScreenBuffer[j/SCREEN_PAGE_BIT][i] &= ~(1<<(j%SCREEN_PAGE_BIT));

}

//对屏幕选中位置经行取反填充		一大页一大页
void Reverse_Screen(int x0,int y0,int x1,int y1)
{
	for(int i=x0;i<=x1;i++)
		for(int j=y0;j<=y1;j=j+8)
	  ScreenBuffer[j/SCREEN_PAGE_BIT][i] = ~ScreenBuffer[j/SCREEN_PAGE_BIT][i];

}
//画一个箭头,flag为1代表箭头向上，
void Draw_Arrow(uint8_t x,uint8_t y,uint8_t flag)
{	

	if(flag)
	{
		for(uint8_t i=0;i<3;i++)
		DrawLine( x+2+i, y+3, x+2+i, y+8 );
		for(uint8_t i=0;i<3;i++)
		DrawLine( x+i, y+3-i, x+6-i, y+3-i);
	}
	else
	{
		for(uint8_t i=0;i<3;i++)
		DrawLine( x+2+i, y, x+2+i, y+5 );
		for(uint8_t i=0;i<3;i++)
		DrawLine( x+i, y+5+i, x+6-i, y+5+i);
	}
	
}


