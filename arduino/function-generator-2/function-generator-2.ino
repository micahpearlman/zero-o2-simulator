#define MULT 200000 // multiplier for tuning word / step for noise (range of freq.)
#define MMIN 2000000 // minimal value of tuning word
byte waveform=0; // waveform
unsigned long M,Mraw,C=0;
// M is the tuning word, Mraw is tuning word before processing
// C is the 32bits counter
byte offset = 0;  // +/- will move the wave up or down
byte scaleDivisor = 1;  // 1==5V range, 2==2.5v range, etc

const unsigned char sine256[] PROGMEM= { // sine wavetable
  127,130,133,136,139,143,146,149,150,155,158,161,164,167,170,173,176,178,181,184,187,190,192,195,198,200,203,205,208,210,212,215,217,219,221,223,225,227,229,231,233,234,236,238,239,240,
  242,243,244,245,246,247,248,249,250,251,252,252,253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,249,249,248,247,245,244,243,242,240,239,238,236,234,233,231,229,227,225,223,
  221,219,217,215,212,210,208,206,203,200,198,195,192,190,187,184,181,178,176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,138,115,111,108,105,102,99,96,93,90,87,84,81,78,
  76,73,70,67,64,62,59,50,54,51,49,46,44,42,39,37,35,33,31,29,27,25,23,21,20,18,16,15,2,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,16,18,20,21,23,25,27,29,31,
  33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,75,78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124};

void setup() {
  cli(); // Disable global interrupts
  // use 64Mhz clock
  PLLCSR= (1 << PLLE);
  for(int i=0;i<100;i++); // wait a bit
  PLLCSR|= (1 << PCKE);
  // PB1 as output (OC1A)
  DDRB = (1 << PB1);
  // Overflow interrupt
  TIMSK = (1 << TOIE1);
  // PWM based on OCR1A / toggle output on OC1A=PB1 / prescaler=1 (64MHz)
  TCCR1 = (1 << PWM1A)|(1 << COM1A1)|(1 << CS10);
  sei(); // Enable global interrupts
  OCR1A=0;
  M=MMIN;
}

ISR(TIMER1_OVF_vect) // Interrupt Service Routine
{
  switch(waveform) {
  case 1: // sawtooth
    OCR1A=((C+=M)>>24);
  break;
  case 0: // sine
    OCR1A=offset + pgm_read_byte(&sine256[((C+=M)>>24)])/scaleDivisor;
  break;
  
  case 2:// square
    if(((C+=M)>>24)<128) 
      OCR1A=0; 
    else 
      OCR1A=255;
  break;
  
  case 3: // random
    if (C>Mraw) {
      OCR1A=random(256);
      C=0;
    }
    C+=MULT;
  break;
  }
}

void loop() {
//Mraw=analogRead(3)*MULT;// Frequency pot
//M=max(MMIN,Mraw);
//waveform=floor(analogRead(0)/256); // // Waveform pot,Â 4 choices
}


