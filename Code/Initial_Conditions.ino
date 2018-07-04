/*
 * Detection Of Initial Conditions
 *    by Stratos Gkagkanis
 *    
 * "DetectAngle" routine observes the pendulum's swing in order to find the exact value of the pendulum's encoder for the straight down position.
 * It will come in use later during Crane Mode.
 * "DetectCenter" routine slowly moves the cart right until it hits the Right Micro Switch.
 * That's how the system knows the exact location of the cart before entering Crane Mode and attempting control in general.
  */
  
void DetectAngle(){
  T3Setup();
  do{
    while(T3Flag == false){}
    if (PendulumPulses > maxPu){
      maxPu = PendulumPulses;
      i = 190;
    }else if (PendulumPulses < minPu){
      minPu = PendulumPulses;
      i = 190;
    }
   i--;
   T3Flag = false;
  }while(i>0);
  ThetaSP = (maxPu - abs(minPu)) / 2 * Pendrad;  //Set Point for Crane Mode
}

void DetectCenter(){
  int tempSpeed = 1750;
  if (digitalRead(termaR) == LOW){
    while(digitalRead(termaR) == LOW)
    {
      MotorControl(tempSpeed);
      delay(5);
      MotorControl(0);
    }
  }
  if(digitalRead(termaR) == HIGH){
    tempSpeed = 1000;
    while(digitalRead(termaR) == HIGH){
      MotorControl(-tempSpeed);
      delay(5);
      MotorControl(0);
    }
  }
  MotorPulses = -6292;
  MotorControl(-5000);
  delay(100);
  MotorControl(0);
  delay(250);
}
