/*
 * TaskManager.h
 *
 * Created: 2013-11-20 15:34:59
 *  Author: Kudzia Bobiñski, Szymon Kudzia
 */ 


#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#define MAX_TASK 255


typedef void (*TASK_POINTER)(void);

struct Task {
	TASK_POINTER task;
	uint8_t ready;
	uint16_t toGo;
	uint16_t interval;
	bool periodic;
};


void initKernel(void);
void schedule(void);
void addTask(TASK_POINTER task, uint16_t interval, bool periodic = true);



#endif /* TASKMANAGER_H_ */