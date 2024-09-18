#include "stdio.h"
#include "pico/stdlib.h"
#include "debounce_sw1.h"
#include "debounce_sw2.h"



static enum DB_States {INIT,WAITPUSHL,WAITPUSHR,MissR,MissL} DB_State;

void FSM() { 

bool btn = debounce_sw2();
bool btn1 = debounce_sw1();

switch(DB_State) {
case INIT:
if......
else DB_State = WAITPUSHL;
break;

case WAITPUSHR
if(btn) {
DB_State = WAITPUSHL;
}
else
DB_State = MissR;
break;

case WAITPUSHL
if(btn1) {
DB_State = WAITPUSHR;
}
else 
DB State = MissL;
break;

case MissL
DB_State = INIT;
break;

case MissR 
DB_State = INIT;
break;
}
}
