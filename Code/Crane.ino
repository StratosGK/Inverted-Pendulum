/*
 * Crane Mode
 *    by Stratos Gkagkanis
 *    
 * During Crane Mode, a double PID is holding the Pendulum in a straight down position while
 * trying to keep the cart as close as possible to the middle of the railway.
 * Crane Mode is completed when the Pendulum's angle remains the same for 20 consecutive samples.
 */
void CraneMode(){
  T3Setup();
  i=20;
  do{
    if (T3Flag == true)  
    {
      T3Flag = false;
      Theta = (PendulumPulses * Pendrad);
      Position = MotorPulses / railwayPulses;
      PendulumPID.Compute();
      PlacePID.Compute();
      u = pend_U-cart_U;
      MotorControl(u);
      if (Thetaprev != Theta){
        Thetaprev = Theta;
        i = 20;
      }else{
        i--;
      }
    }
  }while(i>0);
  PendulumPulses = 0;
  MotorControl(0);
}

