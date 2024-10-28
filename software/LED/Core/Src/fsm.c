#include<stdio.h>
#include"fsm.h"

unsigned int cnt,state;

void fsm(){
    switch(state){
        case(WAIT_UP):
            cnt=0;
            if(KEY_LOW) state=CONFIRM_UP;
            break;
        case(CONFIRM_UP):
           if(cnt==5) state=TOGG;
           else if(KEY_HIGH) state=WAIT_UP;
           else cnt++;
            break;
        case(TOGG):
            LED_T;
            state=WAIT_DOWN;
            break;
        case(WAIT_DOWN):
            cnt=0;
            if(KEY_HIGH) state=CONFIRM_DOWN;
            break;
        case(CONFIRM_DOWN):
            if(cnt==5) state=WAIT_UP;
           else if(KEY_LOW) state=WAIT_DOWN;
           else cnt++;
            break;
        default:
            state=WAIT_UP;
        }

    }
