#ifndef _START_TASK_H
#define _START_TASK_H
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


/* Task */
#include "controller_task.h"

/* function */

/*  根据创建的任务列举Task Handle */
enum TASK_LIST
{
    CONTROLLER_TASK,
    TASK_NUM,
};

void startTask(void);

#endif // !_START_TASK_H
