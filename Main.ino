/*
 * Digital Inverted Pendulum
 *    by Stratos Gkagkanis
 * 
 * You can a watch a video explaining the working principle here:
 * https://www.youtube.com/watch?v=ZlhQogjhdkM&t
 */
 
#include <PID_v1.h>
//H-Bridge Pins
const byte pinA = 11; //NPN | 2N3904 -> IRF9540 (P Channel Mosfet) | PWM
const byte pinB = 9;  //N Channel Mosfet | IRF540
const byte pinC = 12; //NPN | 2N3904 -> IRF9540 (P Channel Mosfet) | PWM
const byte pinD = 10; //N Channel Mosfet | IRF540

//Interrupt Pins    (MEGA2560 Interrupt Pins: 2, 3, 18, 19, 20, 21)
const byte encoderPA = 19;
const byte encoderPB = 18;
const byte encoderMA = 20;
const byte encoderMB = 21;
const byte termaR = 2;
const byte termaL = 3;

volatile boolean T3Flag = false;

//Serial Variables - Used only by the Matlab - MCU Interface
boolean serialFag = false;
char commandChar = 0;

//Micro Switches Variables
boolean FlagR = false;
boolean FlagL = false;

//State Space Variables
const float railwayPulses = 14979;  //The number of motor's encoder pulses for the complete railway
volatile double MotorPulses = 0;  //Initial motor's encoder pulses
volatile int PendulumPulses = 0;  //Initial pendulum's encoder pulses
double T = 0.02;    //Sampla rate (s)
const double Pendrad = (2*3.14159265)/(4*512);
double PendOffset = (2048/2) * Pendrad;
double u = 0.0;
double r = 0.0;
double x1 = 0.0;
double x1prev = 0.0;
double x2 = 0.0;
double x3 = 0.0;
double x3prev = 0.0;
double x4 = 0.0;

double Nbar = 214500.0;
double K1 = 214500.0;
double K2 = 68250.0;
double K3 = 546000.0;
double K4 = 50700.0;
double p1 = 0.5;

//Variables used to detect Angle and in Crane Mode
byte i = 250;
int minPu = 0;
int maxPu = 0;

//PID Variables - Used by Crane Mode
double Theta = 0;
double Thetaprev = 0;
double Position = 0;
double ThetaSP = 0;
double CartSP = 0;

double pend_U = 0;
double cart_U = 0;
float pend_KP = 35000;
float pend_KI = 1000;
float pend_KD = 6000;
float cart_KP = 15000;
float cart_KI = 2000;
float cart_KD = 3500;
int sampleRate = 20; //Sample rate (ms)

PID PendulumPID(&Theta, &pend_U, &ThetaSP, pend_KP, pend_KI, pend_KD, DIRECT);
PID PlacePID(&Position, &cart_U, &CartSP, cart_KP, cart_KI, cart_KD, DIRECT);

void setup() {
  Serial.begin (115200);
  
  pinMode(pinA, OUTPUT);
  digitalWrite(pinA, LOW);
  pinMode(pinC, OUTPUT);
  digitalWrite(pinC, LOW);
  pinMode(pinB, OUTPUT);
  digitalWrite(pinB, LOW);
  pinMode(pinD, OUTPUT);
  digitalWrite(pinD, LOW);
  pinMode(encoderMA, INPUT_PULLUP);
  pinMode(encoderMB, INPUT_PULLUP);
  pinMode(encoderPA, INPUT_PULLUP);
  pinMode(encoderPB, INPUT_PULLUP);
  pinMode(termaR, INPUT_PULLUP);
  pinMode(termaL, INPUT_PULLUP);
  PWMsetup();
  
  PendulumPID.SetMode(AUTOMATIC);
  PendulumPID.SetSampleTime(sampleRate);
  PendulumPID.SetOutputLimits(-16000,16000);
  PlacePID.SetMode(AUTOMATIC);
  PlacePID.SetSampleTime(sampleRate);
  PlacePID.SetOutputLimits(-16000,16000);
  attachInterrupt(digitalPinToInterrupt(encoderMA), IRQmA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderMB), IRQmB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPA), IRQpA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPB), IRQpB, CHANGE);

//For Matlab - MCU Interface
//  Serial.println("Connected");
//  while (commandChar != 'A')
//    {
//      serialEvent();
//    }
    
  DetectAngle();
  DetectCenter();
  CraneMode();
  SwingUp();
  T3Setup();
  
//  Serial.println('A');      //For Matlab - MCU Interface
  
  attachInterrupt(digitalPinToInterrupt(termaR), IRQtermaR, RISING);  //Μέχρι να γίνει σωστή δουλειά με τα τερματικά
  attachInterrupt(digitalPinToInterrupt(termaL), IRQtermaL, RISING);  //αυτές οι 2 εντολές δημιουργούν πρόβλημα, οπότε ας μείνουν σχόλια.

}

void loop() {
  if (T3Flag == true)   //If a sampling period has passed the flag will be true and the new control signal must be calculated
  {
    T3Flag = false;
    InvertedPendulum(); //Calculates and applies the new control signal
  }
  MicroSwitches();        //Checks whether cart has hit any of the two terminals
}
