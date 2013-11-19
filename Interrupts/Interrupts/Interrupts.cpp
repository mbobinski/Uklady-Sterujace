 /*
 *	Interrupts.cpp	
 *
 *		Author: Szymon Kudzia, Mateusz Bobiñski
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect) {
    
}

ISR(TIMER0_COMP_vect) {

}

void SETUP_PWM() {
    TCCR0 |= (1 << CS00) | (0 << CS01) | (0 << CS02) | (1 << WGM01) | (1 << WGM00)| (1 << COM01) | (1 << COM00);
}


void SET_PWM(int ocr) {
    OCR0 = ocr;
}


void SETUP_TIMEOUT(int microseconds) {
    TIMSK |= (1 << OCIE0);
    TCCR0 |= (1 << CS00) | (0 << CS01) | (0 << CS02) | (1 << WGM01) | (1 << WGM00)| (1 << COM01) | (0 << COM00);
    OCR0 = 0x10 * microseconds;
}

int main(void)
{    

}
