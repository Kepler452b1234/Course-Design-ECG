/*
	Copyright (c) [2019] [һֻ����Ե jiezhuo]
	[https://gitee.com/jiezhuonew/oledlib] is licensed under the Mulan PSL v1.
	You can use this software according to the terms and conditions of the Mulan PSL v1.
	You may obtain a copy of Mulan PSL v1 at:
		http://license.coscl.org.cn/MulanPSL
	THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
	PURPOSE.
	See the Mulan PSL v1 for more details.
	
	
	��c�ļ����ڻ�ͼ���ַ�����(�߼�����)
	(��Ҫ)�ɴ��Ϊ����
	�� �� ����
	�ٻ������ ���� ������ Բ ��Բ Բ�Ǿ���
	Ȼ���� ͼƬ �ַ� �ַ���
	����� ����
*/

#include "oled_draw.h"
#include "oled_buffer.h"
#include "oled_config.h"
#include "stdlib.h"
#include "math.h"
#include "oled_bmp.h"
#include "oled_font.h"


extern unsigned char ScreenBuffer[SCREEN_PAGE_NUM][SCREEN_COLUMN];
//��ͼ���
static int  _pointx=0;
static int 	_pointy=0;

////////////////////////////////////////////////////////////////////
//����4�������ǶԵ�ǰ�������� �����»��ƺ������� �û���ֱ��ʹ��
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
//����һ����
void DrawPixel(int x,int y)
{
	SetPointBuffer(x,y,GetDrawColor());
}
//�õ�ĳ�������ɫ
Type_color GetPixel(int x,int y)
{
	if(GetPointBuffer(x,y))
		return pix_white;
	else
		return pix_black;
}

////////////////////////////////////////////////////////////////////////////////////
////���� 
////����:������� �յ�����
void DrawLine(int x1,int y1,int x2,int y2)
{
	
	unsigned short us; 
	unsigned short usX_Current, usY_Current;
	
	int lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int lIncrease_X, lIncrease_Y; 	

	lDelta_X = x2 - x1; //������������ 
	lDelta_Y = y2 - y1; 

	usX_Current = x1; 
	usY_Current = y1; 

	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; 			//���õ��������� 
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;			//��ֱ�� 
	else 
	{ 
		lIncrease_X = -1;			//���õ��������� 
		lDelta_X = - lDelta_X;
	} 

	//Y��Ĵ���ʽ����ͼX��Ĵ���ʽͬ��
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;			//ˮƽ�� 
	else 
	{
		lIncrease_Y = -1;
		lDelta_Y = - lDelta_Y;
	} 

	//ѡȡ����ô���ķ������λ���
	if ( lDelta_X > lDelta_Y )
		lDistance = lDelta_X;
	else 
		lDistance = lDelta_Y; 

	//���λ��� ���뻺���� ���ú���ˢ�»������ͺ���
	for ( us = 0; us <= lDistance + 1; us ++ )					//������� 
	{
		
		SetPointBuffer(usX_Current,usY_Current,GetDrawColor());	//���� 
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

//���� 
//����:������� �յ�����
void DrawLine_2(int x1,int y1,int x2,int y2,int left,int top,int right,int bottom)
{
	
	unsigned short us; 
	unsigned short usX_Current, usY_Current;
	
	int lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int lIncrease_X, lIncrease_Y; 	

	lDelta_X = x2 - x1; //������������ 
	lDelta_Y = y2 - y1; 

	usX_Current = x1; 
	usY_Current = y1; 

	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; 			//���õ��������� 
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;			//��ֱ�� 
	else 
	{ 
		lIncrease_X = -1;			//���õ��������� 
		lDelta_X = - lDelta_X;
	} 

	//Y��Ĵ���ʽ����ͼX��Ĵ���ʽͬ��
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;			//ˮƽ�� 
	else 
	{
		lIncrease_Y = -1;
		lDelta_Y = - lDelta_Y;
	} 

	//ѡȡ����ô���ķ������λ���
	if ( lDelta_X > lDelta_Y )
		lDistance = lDelta_X;
	else 
		lDistance = lDelta_Y; 

	//���λ��� ���뻺���� ���ú���ˢ�»������ͺ���
	for ( us = 0; us <= lDistance + 1; us ++ )					//������� 
	{
		if(usY_Current>=top&&usY_Current<=bottom&&usY_Current>=top&&usY_Current<=bottom)
		SetPointBuffer(usX_Current,usY_Current,GetDrawColor());	//���� 
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
//���ٻ��� ר���ڻ���ƽ��ֱ���� ���Ч��
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
//���ٻ��� ר���ڻ���ƽ��ֱ���� ���Ч��
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
//�������� ��ʼ��ת�۵������ �ܵ����
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
//��һ������PCtoLCD2002������ѡ��[���� ����ʽ ����]
//�������x y ͼ��ȡģ���� ͼ����w h
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

//��һ������PCtoLCD2002������ѡ��[���� ����ʽ ����]�����������μ�[draw_api.h]
//�������x y ͼ��ȡģ���� ͼ����w h
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
//��ʾһ���ַ�
//��������ߴ缰ʹ���뿴SetFontSize()��ע��
//��size=0ʱ xΪ�ڼ��� yΪ�ڼ���
void DrawChar(int x, int y, unsigned char c)
{
	int i,j;
	unsigned char draw_background,bg,a,b,size,color;
	
	size=GetFontSize();		//����ߴ�
	color=GetDrawColor();	//������ɫ 1��0��
	bg=GetTextBkMode();		//д�ֵ�ʱ���ֵı�������ɫ 1��0��
	draw_background= bg = !color;	//��������ɫҪ��һ���ֲſ��õ�
	
	if(!size)//Ĭ���ַ���С
	{
		if((y>SCREEN_PAGE_NUM-2) || (x>SCREEN_COLUMN-8))
			return;
		c=c-' ';			//�õ�ƫ�ƺ��λ��
		for(i=0;i<8;i++)
			WriteByteBuffer(y,x+i,F8X16[c*16+i]);
		for(i=0;i<8;i++)
			WriteByteBuffer(y+1,x+i,F8X16[c*16+i+8]);
	}
	else//ʹ��ԭ�������ַ�
	{
		//�ж�һ���ַ������������Ƿ񳬳��߽緶Χ
		if ((x >= SCREEN_COLUMN) ||         // Clip right
		(y >= SCREEN_ROW) ||        		// Clip bottom
		((x + 5 * size - 1) < 0) ||   		// Clip left
		((y + 8 * size - 1) < 0)    		// Clip top
		)
			return;
		for (i=0; i<6; i++)
		{
			int line;
			//һ���ַ���font5x7����һ��6��char��ʾ
			//lineΪ����ַ��ĵ�ĳ������
			if (i == 5)
				line = 0x0;		//5*7���壬Ҳ����ֻ��5�����ݣ����Ե�6��д0				`								
			else
				line = pgm_read_byte(font5x7+(c*5)+i);		//���ǵ����оʹ��ֿ��ҳ���Ҫд�������
			
			for (j=0; j<8; j++)
			{
				unsigned char draw_color = (line & 0x1) ? color : bg;//Ŀǰ��Ҫ������ɫ��0 ���Ǳ���ɫ 1��������ɫ

				//��ͬ�Ŵ�С������ֻ�����������ķŴ��� ���Ҫע��
				//�����������1������ �Ŵ�����4������ �پ���9������ �ﵽ�����˵ķŴ�Ч��
				if (draw_color^draw_background) 		//����ĳ���򣬵�����ɫ�͵���ɫ��ͬʱ���д��
					for ( a = 0; a < size; a++ )		//Ƕ��for����������������飬���Ŵ����Ŵ��д�룬�Ŵ�����2������д����
						for ( b = 0; b < size; b++ )
							SetPointBuffer(x + (i * size) + a, y + (j * size) + b, draw_color);

				line >>= 1;
			}
		}
	}
}
//��ʾ�ַ��� ������ʾ�����ʾ�ַ�
void DrawString(int x, int y,char *str)
{
	unsigned char j=0,tempx=x,tempy=y;
	unsigned char size=GetFontSize();
	
	if(!size)//Ĭ������
	{
		while (str[j]!='\0')
		{
			DrawChar(x,y,str[j]);
			x+=8;
			if(x>SCREEN_PAGEDATA_NUM-8){x=0;y+=2;}
			j++;
		}
	}
	else//ʹ��ԭ�������ַ�
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
////��ʾ���� ���Ƕ����ʾ���ֵ��ַ�
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
//��ʾ����
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t *cn)
{      			    
	uint8_t j,wordNum;

	if((x > 7)||(y>128-16))
		return;
	
	while ( *cn != '\0')	 																	//��C�������ַ��������ԡ�\0����β
	{
		for (wordNum=0; wordNum<NUM_OFCHINESE; wordNum++)
		{
			if ((CN16CHAR[wordNum].Index[0] == *cn)&&(CN16CHAR[wordNum].Index[1] == *(cn+1)))   //��ѯҪд�������ֿ��е�λ��
			{
				for (j=0; j<32; j++) 															//дһ����
				{		
					if (j == 16)	 															//����16X16�õ�����Y���꣬�����ڵ���16ʱ���л�����
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
		cn += 2;																			//�˴�����һ���֣�������Ѱ�ҵڶ�����
	}
}


//ʹ�öԽǵ�������
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

//����Ļѡ��λ�þ�������
void Clear_Screen(int x0,int y0,int x1,int y1)
{
	for(int i=x0;i<=x1;i++)
		for(int j=y0;j<=y1;j++)
	  ScreenBuffer[j/SCREEN_PAGE_BIT][i] &= ~(1<<(j%SCREEN_PAGE_BIT));

}

//����Ļѡ��λ�þ���ȡ�����		һ��ҳһ��ҳ
void Reverse_Screen(int x0,int y0,int x1,int y1)
{
	for(int i=x0;i<=x1;i++)
		for(int j=y0;j<=y1;j=j+8)
	  ScreenBuffer[j/SCREEN_PAGE_BIT][i] = ~ScreenBuffer[j/SCREEN_PAGE_BIT][i];

}
//��һ����ͷ,flagΪ1�����ͷ���ϣ�
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


