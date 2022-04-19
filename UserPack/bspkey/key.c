#include "key.h"


extern uint8_t key1_state ;	//按键1的状态
extern uint8_t key2_state ;	//按键2的状态
extern uint8_t key3_state ;	//按键3的状态
extern uint8_t key4_state ;	//按键4的状态



//按键处理函数
void GetKeyFlag(void)
{
	//按键按下标志位置1，松开的时候标志位置零
	if(KEY1 == 0)
	{
		key1_state=1;
	}
	
	if(KEY2 == 0)
	{
		key2_state=1;
	}
	
	if(KEY3 == 0)
	{
		key3_state=1;
	}
	
	if(KEY4 == 0)
	{
		key4_state=1;
	}	
		
}	


