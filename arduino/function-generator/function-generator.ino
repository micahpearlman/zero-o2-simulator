
// see: http://www.technoblogy.com/show?QVN
unsigned int Acc;
unsigned int Note = 80;//857; // Middle C

void setup() {
  // put your setup code here, to run once:
  // Enable 64 MHz PLL and use as source for Timer1
  PLLCSR = 1<<PCKE | 1<<PLLE;     

  // Set up Timer/Counter1 for PWM output
  TIMSK = 0;                     // Timer interrupts OFF
  TCCR1 = 1<<CS10;               // 1:1 prescale
  GTCCR = 1<<PWM1B | 2<<COM1B0;  // PWM B, clear on match

  pinMode(4, OUTPUT);            // Enable PWM output pin

  // Set up Timer/Counter0 for 20kHz interrupt to output samples.
  TCCR0A = 3<<WGM00;             // Fast PWM
  TCCR0B = 1<<WGM02 | 2<<CS00;   // 1/8 prescale
  TIMSK = 1<<OCIE0A;             // Enable compare match, disable overflow
  OCR0A = 49;                    // Divide by 400
  
  OCR1C = 255;  // set the frequency
}

void loop() {
  // put your main code here, to run repeatedly:

}
// triangle wave
ISR(TIMER0_COMPA_vect) {
  signed char Temp, Mask;
  Acc = Acc + Note;
  Temp = Acc >> 8;
  Mask = Temp >> 15;
  OCR1B = Temp ^ Mask;
}

/*
// sawtooth wav
ISR(TIMER0_COMPA_vect) {
  Acc = Acc + Note;
  OCR1B = Acc >> 8;
} 
*/
