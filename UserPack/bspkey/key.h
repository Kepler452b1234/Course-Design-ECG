#ifndef _KEY_H
#define _KEY_H

#include "main.h"




//¶ÁÈ¡°´¼üµÄ×´Ì¬
#define KEY1 HAL_GPIO_ReadPin(GPIOB,Key1_Pin)
#define KEY2 HAL_GPIO_ReadPin(GPIOB,Key2_Pin)
#define KEY3 HAL_GPIO_ReadPin(GPIOB,Key3_Pin)
#define KEY4 HAL_GPIO_ReadPin(GPIOB,Key4_Pin)



void GetKeyFlag(void);

#endif