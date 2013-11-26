 /*
 *        Interrupts.cpp        
 *
 *                Author: Mateusz Bobiñski, Szymon Kudzia
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

void SETUP_PWM() {
    TCCR0 |= (1 << CS00) | (0 << CS01) | (0 << CS02) | (1 << WGM01) | (1 << WGM00)| (1 << COM01) | (1 << COM00);
}


void SET_PWM(int ocr) {
    OCR0 = ocr;
}
