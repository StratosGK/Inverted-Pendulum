/*
 * Pendulum Swing Up
 *    by Stratos Gkagkanis
 * Swings up the pendulum from it's downward position.
 */
void SwingUp(){
  maxPu = -5000;
  minPu = 5000;
  do{
    MotorControl(6000);
    delay(125);
    MotorControl(0);
    do{
      if(PendulumPulses < minPu){
        minPu = PendulumPulses;
      }
      if(abs((PendulumPulses * Pendrad)) > 3 ){
        break;
      }
    }while(PendulumPulses > (minPu/2));

    if(abs((PendulumPulses * Pendrad)) > 3 ){
      break;
    }
    MotorControl(-6000);
    delay(150);
    MotorControl(0);
    do{
      if(PendulumPulses > maxPu){
        maxPu = PendulumPulses;
      }
       if(abs((PendulumPulses * Pendrad)) > 3 ){
       break;
      }
    }while(PendulumPulses < (maxPu/2));
    
    if(abs((PendulumPulses * Pendrad)) > 3 ){
      break;
    }
  }while(abs((PendulumPulses * Pendrad - PendOffset)) > 0.2 );
  if(PendulumPulses < 0){
    PendOffset = -PendOffset;
  }
}
