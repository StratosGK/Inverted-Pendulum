/*
 * Interrupt Service Routines
 */
 
void IRQmA()
{
  if (digitalRead(encoderMA) == HIGH)
  {
    if (digitalRead(encoderMB) == LOW)
    {
      MotorPulses++;
    }
    else
    {
      MotorPulses--;  
    }
  }
  else 
  {
    if (digitalRead(encoderMB) == HIGH)
    {
      MotorPulses++;
    }
    else
    {
      MotorPulses--;
    }
  }
}

void IRQmB()
{
  if (digitalRead(encoderMB) == HIGH)
  {
    if (digitalRead(encoderMA) == HIGH)
    {
      MotorPulses++;
    }
    else
    {
      MotorPulses--;
    }
  }
  else
  {
    if (digitalRead(encoderMA) == LOW)
    {
      MotorPulses++;
    }
    else
    {
      MotorPulses--;
    }
  }
}

//PENDULUM SERVICE ROUTINES
void IRQpA()
{
  if (digitalRead(encoderPA) == HIGH)
  {
    if (digitalRead(encoderPB) == LOW)
    {
      PendulumPulses++;
      }
    else
    {
      PendulumPulses--;  
    }
  }
  else 
  {
    if (digitalRead(encoderPB) == HIGH)
    {
      PendulumPulses++;
      }
    else
    {
      PendulumPulses--;
      }
  }
}

void IRQpB()
{
  if (digitalRead(encoderPB) == HIGH)
  {
    if (digitalRead(encoderPA) == HIGH)
    {
      PendulumPulses++;
    }
    else
    {
      PendulumPulses--;
    }
  }
  else
  {
    if (digitalRead(encoderPA) == LOW)
    {
      PendulumPulses++;
    }
    else
    {
      PendulumPulses--;
    }
  }
}

void IRQtermaR()
{
  FlagR = true;
}

void IRQtermaL()
{
  FlagL = true;
}
