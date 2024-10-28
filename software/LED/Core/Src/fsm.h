#define WAIT_UP 1
#define CONFIRM_UP 2
#define TOGG 3
#define WAIT_DOWN 4
#define CONFIRM_DOWN 5
#include "stm32f4xx_hal.h"
#define LED_T HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_6)
#define KEY_HIGH HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_6) == 1
#define KEY_LOW HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_6)==0
void fsm();
