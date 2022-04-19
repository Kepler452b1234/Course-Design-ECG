#include "user_calculate.h"
#include "math.h"


extern float pwmVal;
extern float magni;


float arr[128]={0};
/*the function is used to process a set of voltage data collected and find out the MAX and MIN values*/
void AD_calcuate(float *newdata,uint16_t *data,int len)
{
         
    for(int i=0;i<len;i++)
    {
	    newdata[i]=(float)  3.3*data[i]/4096;     //data processing equation 

	   }
	
    return;
}

//冒泡排序
void BubbleSort(float* a, int n)    
{
	int end = 0;
	float exchange;
	for (end = n - 1; end >= 0; end--)    
	{
		int flag = 0;//记录该趟冒泡排序是否进行过交换
		int i = 0;
		for (i = 0; i < end; i++)   //经过这个for循环可以选出这一次的最大值
		{
			if (a[i]>a[i + 1])
			{
				exchange=a[i];
				a[i]=a[i + 1];
				a[i + 1]=exchange;
				flag = 1;
			}
		}
		if (flag == 0)//该趟冒泡排序没有进行过交换，已有序
			break;
	}
}











