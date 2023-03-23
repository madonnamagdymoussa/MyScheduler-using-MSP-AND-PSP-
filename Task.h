/*
 * Task.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Dell
 */

#ifndef TASK_H_
#define TASK_H_

void TaskA_ReadButtonState(void);
void InitializeTasks(void);
void TaskB_SwitchStates(void);

void TaskA_RedLed(void);
void TaskB_BlueLed(void);
void TaskC_GreenLed(void);

typedef enum{

    WhiteLed_State,
    RedLed_State,
    GreenLed_State,
    BlueLed_State
}States_t;

void CalculationFunction(int a, int b, int c ,int d , int e , int f );
#endif /* TASK_H_ */
