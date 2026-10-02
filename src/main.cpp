/////////////////////////////////////////////// SETUP ///////////////////////////////////////////////

//calls in libraries
#include <Arduino.h>
#include <PID_v1.h>


//define input pin and output pin(s)
#define PIN_INPUT 6
#define PIN_OUTPUT_FORWARD 9
#define PIN_OUTPUT_BACKWARD 10


//define variables
double Setpoint, Input, Output;

//specify links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


//main setup
void setup()
{
  //initialize the input variables
  Input = analogRead(PIN_INPUT);
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}


/////////////////////////////////////////////// MAIN CODE ///////////////////////////////////////////////

//main function
void loop()
{
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  analogWrite(PIN_OUTPUT_FORWARD, Output);

  // analogWrite(9, 255); //motor (pin 9) full speed
  // delay(1000);
  // analogWrite(9, 127); //motor (pin 9) half speed
  // delay(1000);
  // analogWrite(9, 50); 
  // delay(1000);
  // analogWrite(10, 255); //reverse motor (pin 10) full speed
  // delay(1000);
}

