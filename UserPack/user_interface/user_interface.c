#include "user_interface.h"
#include "draw_api.h"
#include "tim.h"







static void Draw_Background(void)
{
	int i,j;
  DrawLine(0,0,128,0);
	DrawLine(0,0,0,63);;
	DrawLine(0,63,128,63);
	DrawLine(128,0,128,63);
	DrawLine(90,0,90,63);
  for(i=0;i<82;i=i+8)
	{
		for(j=0;j<63;j=j+8)
		{
		 DrawLine(i,j,i+4,j);
		}
	}
//	 for(j=0;j<63;j=j+8)
//	{
//		for(i=0;i<82;i=i+16)
//		 DrawLine(i,j,i,j+4);
//		
//	}
//	
	
	UpdateScreen();
}



void Wave_Background(void)
{
  Draw_Background();
	UpdateScreen();
}



void HeartWave_display(float arr[])
{
	  float brr[90];
	  int   i,display_trigger; 
//	for(int i=0;i<NPT;i++)
//	{
//		if(arr[i]<2.8&&arr[i]>2.2)
//		{
//			display_trigger = i;
//			break;
//		}
//	}
	for(i=1;i<91;i++)
	{
	 brr[i]=-(arr[i]/1.5*16+0.5)+49;
	}
	
	Clear_Screen(1,0,90,63);
	Draw_Background();
    for(int i=1;i<91;i++)
	{
		
		DrawLine(i,brr[i],i+1,brr[i+1]);        //Draw a curve of the collected voltage value
		//else;
	}
	UpdateScreen();

}

void HeartRate_Display(float bpm)
{
	
  float Fre;
	char Scale[5];
  DrawString(92,2,"Heart");
	DrawString(92,10,"Rate:");
	//printf("POS=%d \n",MaxFrePos);
	sprintf(Scale,"%dbmp",(int)bpm);
	
	Clear_Screen(92,20,128,30);
	DrawString(92,20,(Scale));
	UpdateScreen();
	
	Clear_Screen(92,20,128,30);

}



void HeartState_Display(int bmp)
{
	DrawString(92,32,"State:");
	if(bmp<=55)
	{
		Clear_Screen(92,42,128,58);
	  DrawString(92,42,"Slow");
	  UpdateScreen();
	}else if(bmp>55&&bmp<70)
	{
		Clear_Screen(92,42,128,58);
	  DrawString(92,42,"Health");
	  UpdateScreen();
	}else if(bmp<=160&&bmp>=70)
	{
		Clear_Screen(92,42,128,58);
	  DrawString(92,42,"Fast");
	  UpdateScreen();
	}else if(bmp>160)
	{
		Clear_Screen(92,42,128,58);
	  DrawString(92,42,"Error");
	  UpdateScreen();
	}
	Clear_Screen(92,42,128,58);
}




