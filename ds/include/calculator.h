/*******************************************************************************
* Programmer: Avihay
* calculator.h
* File: calculator header
* Date: ה' יונ 20 13:23:32 IDT 2019
*******************************************************************************/
#include "queue.h"
#include "stack.h"

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

queue_t *ShuntingYard(char *expression); 

double *CalcExpression(char *post_expression);

void EventLoop(void); 

#endif          /* calculator  */







