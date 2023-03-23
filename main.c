
#include "Task.h"
#include "Scheduler.h"
#include "SystickTimer.h"

u32_t SystickCounter=0;

void ApplicationSystickCallBack(void){
  
  SystickCounter++;
}

int main()
{

  __asm("       CPSIE I");

  InitializeTasks();
  Systick_Initialization();
  Systick_RegisterCallbackFunction(ApplicationSystickCallBack);
  SysTickGenerateDelay_Interrupt(100, milli_Sec);

  
  MainOs();
  return 0;
}
