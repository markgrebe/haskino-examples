#include "HaskinoRuntime.h"

void haskinoMain();
#define HASKINOMAIN_STACK_SIZE 100
byte haskinoMainTcb[sizeof(TCB) + HASKINOMAIN_STACK_SIZE];
void task2();
#define TASK2_STACK_SIZE 108
byte task2Tcb[sizeof(TCB) + TASK2_STACK_SIZE];
void task1();
#define TASK1_STACK_SIZE 116
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
    pinMode(13,1);
    while (1)
        {
        uint32_t bind2;

        takeSem(0);
        bind2 = 0;
        while (1)
            {
            if ((bind2 < 3))
                {
                digitalWrite(13,1);
                delayMilliseconds(125);
                digitalWrite(13,0);
                delayMilliseconds(125);
                bind2 = (bind2 + 1);
                }
            else
                {
                break;
                }
            }
        }
    taskComplete();
    }
void task2()
    {
    uint8_t bind0;

    bind0 = 0;
    while (1)
        {
        giveSem(0);
        debug((uint8_t *)showWord8(bind0));
        delayMilliseconds(2000);
        }
    taskComplete();
    }
void haskinoMain()
    {
    createTask(1, task1Tcb, TASK1_STACK_SIZE, task1);
    createTask(2, task2Tcb, TASK2_STACK_SIZE, task2);
    scheduleTask(1,1000);
    scheduleTask(2,1050);
    taskComplete();
    }
