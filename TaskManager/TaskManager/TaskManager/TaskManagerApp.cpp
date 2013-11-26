/*
 * TaskManager.cpp
 *
 * Created: 2013-11-20 15:33:34
 *  Author: Mateusz Bobiñski, Szymon Kudzia
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "TaskManager.h"

bool isOn1 = false;
bool isOn2 = false;


void first() {
	if (!isOn1) {
		PORTA |= 0x01;
		isOn1 = true;
	} else {
		PORTA &= ~0x01;
		isOn1 = false;
	}		
}

void second() {
	if (!isOn2) {
		PORTA |= 0x02;
		isOn2 = true;
	} else {
		PORTA &= ~0x02;
		isOn2 = false;
	}
}

void lightAll() {
	PORTA = 0xFF;
}

void lightOffAll() {
	PORTA = 0x00;
}


int main(void)
{
	DDRA = 0xFF;
	
	addTask(first, 1000);
	addTask(second, 2000);
	addTask(lightAll, 5000, false);
	addTask(lightOffAll, 6000, false);
	
    schedule();
}