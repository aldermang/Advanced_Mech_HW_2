/////////////////////////////////////////////// SETUP ///////////////////////////////////////////////

//calls in libraries
#include <Arduino.h>
#include <PID_v1.h>


//define input pin and output pin(s)
#define PIN_INPUT 6
#define PIN_OUTPUT_FORWARD 9
#define PIN_OUTPUT_BACKWARD 10


//PID controller setup
double Setpoint = 90.0; //target RPM value
double Input = 0.0; //measured value from encoder
double Output = 100.0; //PID calculates to controller

double Kp = 1.0; //2
double Ki = 0.0; //5
double Kd = 0.0; //1

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


//define variables
const int pulses_per_rev = 4; //4 holes in wheel
const int threshold = 300; //light(600)/dark(200) transition value for photoresistor

long pulseCount = 0;
long lastPulseCount = 0;

bool lastState = false;

unsigned long lastRPMTime = 0;


//main setup
void setup()
{
  Serial.begin(115200);
 
  //define input/output pins
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_OUTPUT_FORWARD, OUTPUT);

  myPID.SetOutputLimits(0,250); //limits for motor speed; max is 250
  myPID.SetMode(AUTOMATIC);

  lastRPMTime = millis();
}

/////////////////////////////////////////////// MAIN CODE ///////////////////////////////////////////////

//main function
void loop()
{
  //read photoresistor value
  int sensorValue = analogRead(PIN_INPUT);

  //convert sensor data to high/low
  bool currentState = (sensorValue > threshold);

  //count light/dark transitions
  if(currentState==true && lastState==false)
  {
    pulseCount = pulseCount + 1;

    //use for debugging purposes
    //Serial.print("Pulse Count = ");
    //Serial.println(pulseCount);
  }

  lastState = currentState;

  //update pulse count every 500 msec
  if(millis() - lastRPMTime >= 500) {
    long pulses = pulseCount - lastPulseCount;
    
    lastPulseCount = pulseCount;
   
    lastRPMTime = millis();

    //RPM calculation
    Input = (pulses * 120.0)/pulses_per_rev;

    //PID compute
    myPID.Compute();

    //use for debugging purposes
    //Serial.print("Pulses: ");
    //Serial.println(pulses);
    //Serial.print("RPM: ");
    //Serial.println(Input);
    //Serial.print("Output: ");
    //Serial.println(Output);

  }

  analogWrite(PIN_OUTPUT_FORWARD,(int)Output);

}
