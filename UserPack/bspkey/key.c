#include "key.h"


extern uint8_t key1_state ;	//����1��״̬
extern uint8_t key2_state ;	//����2��״̬
extern uint8_t key3_state ;	//����3��״̬
extern uint8_t key4_state ;	//����4��״̬



//����������
void GetKeyFlag(void)
{
	//�������±�־λ��1���ɿ���ʱ���־λ����
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


