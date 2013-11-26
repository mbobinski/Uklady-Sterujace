/*
 * TaskManager.cpp
 *
 * Created: 2013-11-20 15:41:12
 *  Author: Mateusz Bobiñski, Szymon Kudzia
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "TaskManager.h"

Task* tasks[MAX_TASK]; 
unsigned int tasks_count = 0;



ISR(TIMER0_COMP_vect) {
	for (int i = 0; i < tasks_count; ++i) {		
		if (tasks[i]->periodic) {
			if (--tasks[i]->toGo == 0) {
				tasks[i]->toGo = tasks[i]->interval;
				tasks[i]->ready++;
			}
		} else {
			if (tasks[i]->toGo > 0)
				--tasks[i]->toGo;
			else if (tasks[i]->toGo-- == 0)
				tasks[i]->ready++;
		}			
	}
}


void initKernel() {
	TIMSK |= (1 << OCIE0);
	TCCR0 |= (1 << CS00) | (1 << CS01) | (0 << CS02) | (1 << WGM01) | (1 << WGM00)| (1 << COM01) | (0 << COM00);
	OCR0 = 0xFA;
	
	
}

void schedule() {
	initKernel();
	
	sei();
	
	int task = 0;
	while (true) {
		if (tasks[task]->ready) {
			tasks[task]->ready--;
			tasks[task]->task();
			task = 0;
		} else if (task >= tasks_count) {
			task = 0;	
			continue;
		}			
		
		task++;	
	}
}

void addTask(TASK_POINTER task, uint16_t interval, bool periodic) {
	Task* t = (Task*)malloc(sizeof(Task));
	
	t->task = task;
	t->interval = interval;
	t->ready = 0;
	t->toGo = interval;
	t->periodic = periodic;
	
	tasks[tasks_count++] = t;
}