#include "motors.h"

#include <Servo.h>

extern Servo Motor1,Motor2,Motor3,Motor4,Motor5,Motor6;

void Motors::RunMotors(Servo* Motor,int Gain)
{
  int x = 0;
    
    if(Gain > 2000)
    {
        x = 2000;                      // Actuator Limit Saturation 
    }
    if(Gain < 1000)
    {
        x = 1000;                      // Actuator Limit Saturation 
    }
    else
    {
        x = Gain;              
    }
    Motor->writeMicroseconds(x);       // write gain to motors
}

double Motors::AltitudeControl(double input,double sensorVal,double initial)
{
  double b = sensorVal - initial; // start from zero;
  double Setpoint;                // variable for altitute hold setpoint
                                  // checks commanded valuue, compare that with actual value and returns compensated value
   if( input > 1750)
   {
     b = b + 1.5;
     Setpoint = b;
   }
   else if( input > 1650 &&  input < 1750)
   {
     b = b + 1;
     Setpoint = b;
   }
   else if( input > 1550 &&  input < 1650)
   {
     b = b + 0.5;
     Setpoint = b;
   }
   else if( input < 1450 && input > 1350)
   {
     b = b - 0.5;
     Setpoint = b;
   }
   else if( input < 1350 && input > 1250)
   {
     b = b - 1;
     Setpoint = b;
   }
   else if( input < 1250)
   {
     b = b - 1.5;
     Setpoint = b;
   }
   else if( input > 1450 && input < 1550)
   {
     Setpoint = b;
   }
   return(Setpoint);
}

void Motors::MotorMix(Servo x, int y, int lower, int upper)
{ 
  if (y > upper)
  {
    y = upper;
  }
  else if(y < lower)     // set upper and lower motor limits as each motor is different
  {                      // lower limit = just when the motor starts moving
    y = lower;
  }
  else
  {
    y = y;
  }
  RunMotors(&x,y);
}

void Motors::FlightControl(double m1,double m2,double m3,double m4,double m5,double m6)
{    
  MotorMix(Motor1,m1,1300,2000); // Top Left
  MotorMix(Motor2,m2,1300,2000); // Bottom Left
  MotorMix(Motor3,m3,1300,2000); // Top Right
  MotorMix(Motor4,m4,1300,2000); // Bottom Right
  MotorMix(Motor5,m5,1300,2000); // Top Rear
  MotorMix(Motor6,m6,1300,2000); // Bottom Rear
}

void Motors::StartUp()
{
  RunMotors(&Motor1,1200);
  RunMotors(&Motor2,1200);
  RunMotors(&Motor3,1200);
  RunMotors(&Motor4,1200);          // run all motors at same velocity on start up
  RunMotors(&Motor5,1200);
  RunMotors(&Motor6,1200);
}

void Motors::FullStop()
{
  RunMotors(&Motor1,1000);
  RunMotors(&Motor2,1000);
  RunMotors(&Motor3,1000);          // stop all motors
  RunMotors(&Motor4,1000);
  RunMotors(&Motor5,1000);
  RunMotors(&Motor6,1000);
}
