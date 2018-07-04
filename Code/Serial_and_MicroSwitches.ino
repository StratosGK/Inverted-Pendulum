/*
 * Micro Switches
 * The Micro Switches code checks if the cart has hit any of the two switches.
 * If it did, then the system stops in order to avoid hitting the sides of the structure.
 * 
 * Serial Event
 * Only for Matlab - Microcontroller Interface
 */
void MicroSwitches(){
  if( FlagR == true || FlagL == true ){
    detachInterrupt(digitalPinToInterrupt(encoderMA));
    detachInterrupt(digitalPinToInterrupt(encoderMB));
    detachInterrupt(digitalPinToInterrupt(encoderPA));
    detachInterrupt(digitalPinToInterrupt(encoderPB));
    while(1){
      if(FlagR == true){
        MotorControl(-16000);
        delay(300);
        MotorControl(0);
        FlagR = false;
      }else if(FlagL == true){
        MotorControl(16000);
        delay(300);
        MotorControl(0);
        FlagL = false;
      }
    }
  }
}

void serialEvent(){
  commandChar = Serial.read();
  switch (commandChar){
    case 'R':
      Serial.print(x3);
      Serial.print(',');
      Serial.print(u);
      Serial.print(',');
      Serial.println(x1);
      break;
    case 'T':
      break;
    case 'S': //Read SetPoint
      r = Serial.parseFloat();
      if(r>0.42){
        r = 0.42;
      }else if(r<-0.42){
        r = -0.42;
      }
      break;
    case 'P': //Read Kp
      break;

      }
}

