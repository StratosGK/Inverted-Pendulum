/*
 * Motor Setup & Driving Code
 *    by Stratos Gkagkanis
 * Using Timer 1
 * Uno & Mega Compatible
 * Phase Correct PWM Mode 10
 *    2 PWM Pins
 *        UNO   -> OC1A = PIN 11 & OC1B = PIN 12
 *        MEGA  -> OC1A = PIN 9 & OC1B = PIN 10
 *    Both PWM Registers are Double Buffered (duty cycles can dynamically change without errors)
 *    TOP Register (ICR1) determines the Frequency. ICR1 is not double buffered so it should not change on the fly.
 * pcPWM Frequency Formula => Fclk / (2 * Prescaler * ICR1) -> 16MHz / (2 * Prescaler * ICR1)
 */
void PWMsetup(){
  //Clearing Registers
  TCCR1A = 0;
  TCCR1B = 0;
  ICR1 = 0;
  OCR1A = 0;
  OCR1B = 0;
  //pcPWM Mode 10 Setup
  TCCR1A = (1<<WGM11);    //pcPWM Mode 10
  TCCR1B = (1<<WGM13);
  ICR1 = 16000;           //500Hz = 16.000.000 / (2 * P * 16000)
  TCCR1B |= (1<<CS10);    //Prescaler = 1  & T1 START
  //From now on, T1 is running but with OCR1A & OCR1B being 0, both duty cycles are 0%.
}

void MotorControl(int pwmValue)
{
  if (pwmValue > 0)         //If the PWM Value is Positive then Clockwise rotation is selected.
  { 
    RIGHT(pwmValue);
  }
  else if (pwmValue < 0)    //If the PWM Value is Negative then AntiClockwise rotation is selected.
  {
    LEFT(-pwmValue);
  }
  else                  //If the PWM value is 0 the Motor will break.
  {
    BREAK();
  }  
}

void RIGHT(int pwmValue){       //Clockwise Rotation
  TCCR1A = (1<<WGM11);          //By clearing COM1XY bits, OC1A & OC1B pins wont produce any pulses and the DC becomes 0%
  digitalWrite(pinB, LOW);      //Disable AntiClockwise N Channel
  digitalWrite(pinD, HIGH);     //Enable Clockwise N Channel
  OCR1A = pwmValue;             //Load the value into the Capture Register for the duty cycle
  TCCR1A = (1<<COM1A1 | 1<<WGM11);  //By setting COM1A1, OC1A pin will produce pulses with a DC determined by the values in OCR1A and ICR1
}
void LEFT(int pwmValue){         //AntiClockwise Rotation
  TCCR1A = (1<<WGM11);           //By clearing COM1XY bits, OC1A & OC1B pins wont produce any pulses and the DC becomes 0%
  digitalWrite(pinD, LOW);       //Disable Clockwise N Channel
  digitalWrite(pinB, HIGH);      //Enable AntiClockwise N Channel
  OCR1B = pwmValue;              //Load the value into the Capture Register for the duty cycle
  TCCR1A = (1<<COM1B1 | 1<<WGM11);  //By setting COM1B1, OC1B pin will produce pulses with a DC determined by the values in OCR1B and ICR1
}
void COAST(){               //Coasting
  TCCR1A = (1<<WGM11);      //By clearing COM1XY bits, OC1A & OC1B pins wont produce any pulses and the DC becomes 0%
  digitalWrite(pinB, LOW);  //Disable AntiClockwise N Channel
  digitalWrite(pinD, LOW);  //Disable Clockwise N Channel
}
void BREAK(){               //BREAK
  TCCR1A = (1<<WGM11);      //By clearing COM1XY bits, OC1A & OC1B pins wont produce any pulses and the DC becomes 0%
  digitalWrite(pinB, HIGH); //Enable AntiClockwise N Channel
  digitalWrite(pinD, HIGH); //Enable Clockwise N Channel
}
