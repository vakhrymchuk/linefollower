#pragma once

void ADC_setup() {
    cli();
    DIDR0 = 0x3F;       // digital inputs disabled
    ADMUX = 0x40;       // measuring on ADC3, use the internal 1.1 reference
    ADCSRA = 0xAC;      // AD-converter on, interrupt enabled, prescaler = 16
    ADCSRB = 0x40;      // AD channels MUX on, free running mode
    bitSet(ADCSRA, 6);  // Start the conversion by setting bit 6 (=ADSC) in ADCSRA
    sei();              // set interrupt flag
}

volatile unsigned short analogValue;

unsigned short analogReadInterrupt(byte pin) {
    if (pin > A0) return 0;
    return analogValue;
}

/*** Interrupt routine ADC ready ***/
ISR(ADC_vect) {
    analogValue = ADCW;
}

#define analogRead(pin) analogReadInterrupt(pin)
