
#include "GPTM_config.h"
#include "GPIO.h"
#include "GPIO_config.h"
#include "lstd.h"
#include "GPTM.h"
#include "Task.h"




void TaskA_RedLed(void){
  
  GPIO_ToggleBitBandBits(Channel_1, PortF);
  
  int a=5;
  int b=5;
  int c=5;
  int d=5;
  int e=5;
  int f=5;
  CalculationFunction(a,b,c,d,e,f);
  

}


void TaskB_BlueLed(void){
  
   GPIO_ToggleBitBandBits(Channel_2, PortF);
   
  int a=5;
  int b=5;
  int c=5;
  int d=5;
  int e=5;
  int f=5;
  CalculationFunction(a,b,c,d,e,f);


}


void TaskC_GreenLed(void){
  
   GPIO_ToggleBitBandBits(Channel_3, PortF);
   
  int a=5;
  int b=5;
  int c=5;
  int d=5;
  int e=5;
  int f=5;
  CalculationFunction(a,b,c,d,e,f);


}

void CalculationFunction(int a, int b, int c ,int d , int e , int f ){
  int g=5;
  
  g=a+b-c/d;
  c++;
  
}



u8_t Button1_PressedFlag=0;
u8_t Button2_PressedFlag=0;

States_t Button1State;
States_t Button2State;

void TaskA_ReadButtonState(void){


        /**********************Check for button 1**********************/
            if( 0 == GPIO_ReadBitBandBits(Channel_4,PortF) ){

                 GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 170, milli_Sec);

                     if(0 == GPIO_ReadBitBandBits(Channel_4,PortF) ){
                     Button1_PressedFlag=1;
                     //GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
                 }

            }

            else{
                Button1_PressedFlag=0;
            }

            /**********************Check for button 2**********************/
            if( 0 == GPIO_ReadBitBandBits(Channel_0,PortF) ){

                 GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 170, milli_Sec);


                 if(0 == GPIO_ReadBitBandBits(Channel_0,PortF) ){
                     Button2_PressedFlag=1;

                     //GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 50, milli_Sec);
                 }

             }
            else{
                 Button2_PressedFlag=0;
             }

            GPTM_GenerateDelay(GPTM_Config_ArrPtrStruct[0], 150, milli_Sec);
}

void InitializeTasks(void){
    GPIO_ConfigureInputPin(&GPIO_ConfigurePin_PF4);
    GPIO_ConfigureInputPin(&GPIO_ConfigurePin_PF0);
    GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF1);
    GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF2);
    GPIO_ConfigureOutputPin(&GPIO_ConfigurePin_PF3);

    GPTM_InitializeDelayMode(GPIO_TimerAFSELConfig_ArrPtrStruct[0], GPTM_Config_ArrPtrStruct[0]);
    GPTM_InitializeDelayMode(GPIO_TimerAFSELConfig_ArrPtrStruct[1], GPTM_Config_ArrPtrStruct[1]);
}

void TaskB_SwitchStates(void){

   /* if(1 == Button1_PressedFlag){
        GPIO_WriteBitBandBits(Channel_1, PortF,OutputHigh);
    }
    else{
        GPIO_WriteBitBandBits(Channel_1, PortF,OutputLow);
    }

    if(1 == Button2_PressedFlag){
        GPIO_WriteBitBandBits(Channel_2, PortF,OutputHigh);
    }

    else{
         GPIO_WriteBitBandBits(Channel_2, PortF,OutputLow);
     }*/

    if(1 == Button1_PressedFlag){

        switch(Button1State){

        case WhiteLed_State:
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputHigh);
            Button1State=RedLed_State;
            break;

        case RedLed_State:
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputLow);
            Button1State=GreenLed_State;
            break;

        case GreenLed_State:
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputHigh);
            Button1State=BlueLed_State;
            break;

        case BlueLed_State:
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputLow);
            Button1State=WhiteLed_State;
            break;

        }
    }


    if(1 == Button2_PressedFlag){

        switch(Button2State){

        case WhiteLed_State:
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputHigh);
            Button2State=BlueLed_State;
            break;

        case BlueLed_State:
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputLow);
            Button2State=GreenLed_State;
            break;

        case GreenLed_State:
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputHigh);
            Button2State=RedLed_State;
            break;

        case RedLed_State:
            GPIO_WriteBitBandBits(Channel_3, PortF,OutputLow);
            GPIO_WriteBitBandBits(Channel_1, PortF,OutputHigh);
            GPIO_WriteBitBandBits(Channel_2, PortF,OutputLow);
            Button2State=WhiteLed_State;
            break;

        }
    }


}
