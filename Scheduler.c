#include "Scheduler.h"
#include "lstd.h"
#include "Task.h"
/*==========================================================================*/
/*                           GLOBAL DATA                                    */
/*==========================================================================*/

unsigned int _S_MSP=0x20007ff8;
unsigned int _E_MSP;

unsigned int _S_PSP_TA;
unsigned int _E_PSP_TA;

unsigned int _S_PSP_TB;
unsigned int _E_PSP_TB;

unsigned int _S_PSP_TC;
unsigned int _E_PSP_TC;

 u8_t TASKA_flag=1;
 u8_t TASKB_flag=0;

 extern u32_t SystickCounter;
/*==========================================================================*/
/*                           OS FUNCTIONS                                   */
/*==========================================================================*/

void SwitchAccessLevel(enum CPUAccessLevel level){

    switch(level){

    /*clear bit 0*/
    case priviledged:
        __asm("     mrs r3, CONTROL");
        __asm("     lsr r3,r3,#0x1");
        __asm("     lsl r3,r3,#0x1");
        __asm("     msr CONTROL, r3");
        break;
   /*set bit 0*/
    case Unpriviledged:
        __asm("     mrs r3, CONTROL");
        __asm("     orr r3,r3,#0x1");
        __asm("     msr CONTROL,r3");
        break;
    }
}

 //SwitchAccessLevel(Unpriviledged);
//OS_Generate_Exception;
void MainOs(void){

   
    _E_MSP = _S_MSP -2048; 

     
    _S_PSP_TA = (_E_MSP - (8));
    
    
    _E_PSP_TA = _S_PSP_TA - TaskA_Stack_Size;

   
    _S_PSP_TB = _E_PSP_TA -8;
    
    
    _E_PSP_TB = _S_PSP_TB - TaskB_Stack_Size;
    
    
    _S_PSP_TC = _E_PSP_TB -8;
    
    
    _E_PSP_TC = _S_PSP_TC - TaskC_Stack_Size;


    while(1){

      
        if((SystickCounter%50)==0){
            OS_SET_PSP(_S_PSP_TA);
            OS_SWITCH_SP_to_PSP;
            SwitchAccessLevel(Unpriviledged);
            TaskA_RedLed();
            OS_Generate_Exception;
            OS_SWITCH_SP_to_MSP;
        }
        
        
           if((SystickCounter%100)==0){
            OS_SET_PSP(_S_PSP_TB);
            OS_SWITCH_SP_to_PSP;
             SwitchAccessLevel(Unpriviledged);
             TaskB_BlueLed();
             OS_Generate_Exception;
             OS_SWITCH_SP_to_MSP;
        }
        
            if((SystickCounter%150)==0){
             OS_SET_PSP(_S_PSP_TC);
             OS_SWITCH_SP_to_PSP;
             SwitchAccessLevel(Unpriviledged);
             TaskC_GreenLed();
              OS_Generate_Exception;
             OS_SWITCH_SP_to_MSP;
        }


    }

}

void SVCHandler(void){

    SwitchAccessLevel(priviledged);
}

