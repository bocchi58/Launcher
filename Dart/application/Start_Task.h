#ifndef _START_TASK_H
#define _START_TASK_H
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


/* Task */
#include "controller_task.h"

/* function */

/*  ���ݴ����������о�Task Handle */
enum TASK_LIST
{
    CONTROLLER_TASK,
    TASK_NUM,
};

void startTask(void);

#endif // !_START_TASK_H
