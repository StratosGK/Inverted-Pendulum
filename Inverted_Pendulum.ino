/*
 * Inverted Pendulum
 *    by Stratos Gkagkanis
 * It is essentially the code which balances the Pendulum in the upward position.
 * State Feedback Controller 
 */
void InvertedPendulum(){
    x1 = - MotorPulses / railwayPulses;
    //The following is a filter in order to move the cart slower when the position is off by more than 4cm.
    //otherwise, when the setpoint changes externally by more than 15cm, the cart moves too fast.
    if(x1>0.04){
      r=x1-0.04;
    }else if (x1<-0.04){
      r=x1+0.04;
    }
    
    x2 = (x1-x1prev) / T;
    x3 = (PendulumPulses * Pendrad) - PendOffset;
    x4 = (x3-x3prev) / T;
    u = -(Nbar*r -K1*x1 -K2*x2 -K3*x3 -K4*x4);     //Minus sign for cart direction
    u=u*p1;
    if(u>16000){
      u = 16000;
    }else if(u<-16000){
      u = -16000;
    }
    if(abs(x3)>0.4){
      u = 0;
    }
    MotorControl(u);
    x1prev = x1;
    x3prev = x3;
}

