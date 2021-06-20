#include <Application.h>
#include <Platform.h>
#include <stdbool.h>

static unsigned char ledValue = false;
static unsigned char doBlink = true;

static void onPushButtonChangedCbk(){
  if (Platform_PushButton_getValue()){
    if (doBlink){
      //if blinking it sets led on 
      ledValue = true;
      doBlink = false; 
    }
    else{
      if (ledValue){
        // if ledOn then turn off led
        ledValue = false;
      }
      else{
        //if ledOff then make led blink again 
        doBlink = true;    
      }
    }
    Platform_Led_setValue( ledValue );
  }
}

/*  
  
  INITIAL THOUGHT OF MAKING DELAY.

static int msTicks;
void Tick_Handler(void) {
      msTicks++;
}
void Delay (int dlyTicks) {
      int curTicks;
      curTicks = msTicks;
      while ((msTicks - curTicks) < dlyTicks) { __nop(); }
}

static void onSystemTick(){
	msTicks = 0;
	while(doBlink){
		Tick_Handler();
		ledValue = !ledValue;
		Platform_Led_setValue( ledValue );
		Delay(50);
		msTicks = 0;
	}
}
*/

static void onSystemTick(){
static unsigned int msTicks = 0;
  if (doBlink){
    if (msTicks%150 == 0){
      msTicks = 0; //to make sure that is blinking for ever!!! (until we hit the button)
      ledValue = !ledValue; //togle led value.
      Platform_Led_setValue( ledValue );
    }
    ++msTicks;
  }else{
    msTicks = 0;
  }
}


void Application_run()
{
  Platform_Led_setValue( ledValue );
  Platform_PushButton_setIsrCallback(onPushButtonChangedCbk);
  Platform_PushButton_enableInterrupt();
  Platform_registerSystickCallback(onSystemTick);
  while( 1 );
}

  
