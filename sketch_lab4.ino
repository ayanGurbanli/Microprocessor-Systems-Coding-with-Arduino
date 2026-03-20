#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t countdown = 0;


// external interrupt service routine for the button on d2
ISR(INT0_vect) {
    if (countdown == 0) {
        PORTB |= (1 << PB4);  // turn on the output pin 
        countdown = 10;       // set the countdown for 10 ticks
    }

}

// timer1 compare match interrupt service routine
ISR(TIMER1_COMPA_vect) {
    if (countdown > 0) {
        countdown--;        // decrease countdown by 1 every 1ms
        if (countdown == 0) {
            PORTB &= ~(1 << PB4); // turn off the output pin when time is up
        }
    }
}

void setup() {
 
    // set pin b4 as output and d2 as input
    DDRB |= (1 << PB4);
    DDRD &= ~(1 << PD2);

    // configure external interrupt to trigger on falling edge
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);

    // reset timer1 control registers
    TCCR1A = 0;
    TCCR1B = 0;
    // set compare value for 1ms timing (16mhz / 64 prescaler / 1000hz - 1)
    OCR1A = 249;
    // enable ctc (clear timer on compare match) mode
    TCCR1B |= (1 << WGM12);
    // set clock prescaler to 64
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // enable the timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts
    sei();
}

void loop() {
  //empty main loop
  //because everything is handled by interrupts
}