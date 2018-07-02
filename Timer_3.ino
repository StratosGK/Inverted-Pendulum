/*
 * Timer 3
 *    by Stratos Gkagkanis
 * 16bit Timer 3 is used to count the sampling period.
 */
void T3Setup(){
  TCNT3 = 0;
  TCCR3A = 0;
  TCCR3B = 0;
  ICR3 = 0;
  OCR3A = 0;
  OCR3B = 0;
  TIMSK3 = 0;
  TIFR3 = 0;
  
  TCCR3B = (1<<WGM32);    //Mode 4 => CTC, TOP = OCR1A
  
  OCR3A = 4999;                     //Compare Value for 20ms
  TIMSK3 = 2;                       //OCIEA = 1
  TCCR3B |= (1<<CS31 | 1<<CS30);    //Prescaler = 64, Time = 62.5ns * 64 * 5000 = 20ms.
  //T3 is now ON
}

ISR(TIMER3_COMPA_vect){
  T3Flag = true;
}

void T3Start(){
  TCCR3B |= (1<<CS31 | 1<<CS30);  //Prescaler = 64, Opote: xronos = 62.5ns * 64 * 5000 = 20ms.
}

void T3Stop(){
  TCCR3B = (1<<WGM32);
  TCNT3 = 0;
}

void T3Pause(){
   TCCR3B = (1<<WGM32);
}

