#include "HaskinoRuntime.h"

void haskinoMain();
#define HASKINOMAIN_STACK_SIZE 100
byte haskinoMainTcb[sizeof(TCB) + HASKINOMAIN_STACK_SIZE];
void task3();
#define TASK3_STACK_SIZE 108
byte task3Tcb[sizeof(TCB) + TASK3_STACK_SIZE];
void task2();
#define TASK2_STACK_SIZE 108
byte task2Tcb[sizeof(TCB) + TASK2_STACK_SIZE];
void task1();
#define TASK1_STACK_SIZE 108
byte task1Tcb[sizeof(TCB) + TASK1_STACK_SIZE];

void setup()
    {
    haskinoMemInit();
    createTask(255, haskinoMainTcb, HASKINOMAIN_STACK_SIZE, haskinoMain);
    scheduleTask(255, 0);
    startScheduler();
    }

void loop()
    {
    }


void task1()
    {
    pinMode(6,1);
    while (1)
        {
        digitalWrite(6,1);
        delayMilliseconds(500);
        digitalWrite(6,0);
        delayMilliseconds(500);
        }
    taskComplete();
    }
void task2()
    {
    pinMode(7,1);
    while (1)
        {
        digitalWrite(7,1);
        delayMilliseconds(1000);
        digitalWrite(7,0);
        delayMilliseconds(1000);
        }
    taskComplete();
    }
void task3()
    {
    pinMode(8,1);
    while (1)
        {
        digitalWrite(8,1);
        delayMilliseconds(2000);
        digitalWrite(8,0);
        delayMilliseconds(2000);
        }
    taskComplete();
    }
void haskinoMain()
    {
    createTask(1, task1Tcb, TASK1_STACK_SIZE, task1);
    createTask(2, task2Tcb, TASK2_STACK_SIZE, task2);
    createTask(3, task3Tcb, TASK3_STACK_SIZE, task3);
    scheduleTask(1,1000);
    scheduleTask(2,2000);
    scheduleTask(3,4000);
    taskComplete();
    }
