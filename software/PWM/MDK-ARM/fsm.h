#include "stm32f4xx_hal.h"
#define KEY0 HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7)==0
#define KEY1 HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7)==1
#define WAIT_UP 1
#define CONFIRM_UP 2
#define TOGG 3
#define WAIT_DOWN 4
#define CONFIRM_DOWN 5
void check(int state);
void fsm(void);

