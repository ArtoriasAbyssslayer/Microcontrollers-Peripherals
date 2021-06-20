// TODO
// When changing the device in the project settings, this include has to be adjusted accordingly.
// Also make sure to adjust the heap and stack size in startup file.
#include <ARMCM0.h>

#include <Application.h>
#include <libredBlocks_sim_uvision.h>

extern void Platform_initSimulation( void );

void SysTick_Handler()
{
  rb_sim_tick();
}

void SysTick_control(u8 disable){ //u8 ~ uint8_t for other c language standards | reaches maximum value of 2^7
  if (disable){
    NVIC_DisableIRQ ( SysTick_IRQn ); // Disable a device specific interrupt;
  }
  else{
    NVIC_EnableIRQ ( SysTick_IRQn );// Enable a device specific interrupt;
  }
} 
//need SYSTEM_TICKS_PER_SEC value to define the clock
static const u32 SYSTEM_TICKS_PER_SEC = 50;

/**
 * Main routine of our simulator application. It sets up the single components,
 * associates them with each other and starts the application.
 */
int main()
{
  SystemCoreClock = 8000000UL;
  SysTick_Config( SystemCoreClock / SYSTEM_TICKS_PER_SEC );

  rb_sim_uvision_init( 0x30000000, 150, 150, &SysTick_control);
  Platform_initSimulation();
  rb_sim_initDone();

  Application_run();

  while (true);
}
