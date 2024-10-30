#include "fsm.h"
#include "tim.h"
unsigned int cnt,state=1,KEY_STATE;

void fsm(){
    switch(KEY_STATE){
        case(WAIT_UP):
            cnt=0;
            if(KEY0) KEY_STATE=CONFIRM_UP;
            break;
        case(CONFIRM_UP):
           if(cnt==5) KEY_STATE=TOGG;
           else if(KEY1) KEY_STATE=WAIT_UP;
           else cnt++;
            break;
        case(TOGG):
           switch(state){
						 case(1):
                
                     __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,1000);
                    state=2;
               
            break;
          case(2):
                     __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,5000);
                    state=3;
                
            break;
          case(3):
                    __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,9000);
                    state=4;
   
            break;
          case(4):
                   __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,0);
                   state=1;
            break;
            default:
            break;}
					 KEY_STATE=WAIT_DOWN;
						break;
        case(WAIT_DOWN):
            cnt=0;
            if(KEY1) KEY_STATE=CONFIRM_DOWN;
            break;
        case(CONFIRM_DOWN):
            if(cnt==5) KEY_STATE=WAIT_UP;
           else if(KEY0) KEY_STATE=WAIT_DOWN;
           else cnt++;
            break;
        default:
            KEY_STATE=WAIT_UP;
						break;
        }

    }

