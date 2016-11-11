#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
volatile uint32_t i;
#define LED (1 << PB0)
#define LED_TOG PORTB ^= LED

int main(void) {
  DDRB |= LED;
  TCCR0B |= (1 << CS02) | (1 << CS00);//prescaler 1024
  TIMSK0 |= (1 << TOIE0);//przerwanie przy przepłnieniu timera0
  sei();
  return 0;
}

ISR(TIMER0_OVF_vect) {
  //co 0.01632sek.
  for (i = 0; i < 4096000; i++) {
    LED_TOG;
  }
}
