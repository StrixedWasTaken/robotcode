#include "vex.h"
#include "math.h"
#include <cmath>
using namespace vex;

#define RATIO 1.0;
#define TO_INCH ((M_PI*2.75)/360)
double travelled;
double radians;
double previousmovement;
double heading_reading;
double circumference = (2.0 * M_PI * 1.375); // Circumference of the wheel
double begin_heading = 0;      //  Here so I can flip my coordinate plane for more understandable motions
double x = 0;
double y = 0;
int odom() 
{
  previousmovement = 0;
  l2.resetPosition();
  r2.resetPosition();
  while (true)
  {

    heading_reading = fmod((360 - imu.heading(deg)) + heading_reading, 360); // to wrap the angle if it is over 360 or under 0

    double actualencoder = l2.position(deg) + r2.position(deg) / 2; // average of our middle motors

    radians = heading_reading * (M_PI/180); // converts to radians

    double currentmovement = (actualencoder / 360) * circumference * RATIO; // degree to distance so odom can work properly

    travelled = currentmovement - previousmovement; // stores tbe amount of travelling the robot has done

    x += travelled * cos(radians); // tracks the chnage in movement of the x value
 
    y += travelled * sin(radians); // tracks the change in movement of the y value

    previousmovement = currentmovement;

    Brain.Screen.printAt(10, 100, "X: %2f", x);
    Brain.Screen.printAt(10, 120, "Y: %2f", y);
    Brain.Screen.printAt(10, 140, "Heading: %2f", imu.heading(deg));
    wait(10, msec);
  }
}
//linear
double const kp = 0.185;
double const ki = 0;
double const kd = 0.01;
//turning
double const tkp = 0.2;
double const tki = 0;
double const tkd = 0;
//swing
double const skp = 0;
double const ski = 0;
double const skd = 0;
double error;
double perro;
double deriv;
double integral;
double timeout;
double settle;
double speed;
double timeoutamt = 800;

void Drive(float target, float setspeed)
{
  timeout = 0;
  settle = 0;
  l2.resetPosition();
  r2.resetPosition();
  while (settle < 2)
 {
    float tm = l2.position(deg) + r2.position(deg) / 2;
    error = (target-tm);
    deriv = error - perro;
    integral = error + integral;
    if (error > 20) {
      integral=0;
    }
    speed = (error * kp) + (integral * ki) + (deriv * kd);
    if (speed > setspeed)
    {
      speed = setspeed;
    }
    else if (speed < -setspeed)
    {
      speed = -setspeed;
    }
    Brain.Screen.printAt(10, 120, " Drive Error: %2f", error);
    Left.spin(fwd, speed, volt);
    Right.spin(fwd, speed, volt);
    timeout++;
    perro = error;
    if (error < 3 && error > -1)
    {
      settle++;
    }

    if (timeout >= timeoutamt)
    {
      settle++;
    }
    wait(10, msec);
  }
  Left.stop(coast);
  Right.stop(coast);
}

void Turn(float target, float setspeed)
{
  timeout = 0;
  settle = 0;
  while (settle < 2)
  {
    error = (target - imu.heading(deg));
    if (fabs(error) >= 180)
    {
      error = -fabs(error) / error * 360 - fabs(error);
    }
    deriv = error - perro;
    integral = error + integral;
    if (error > 20) {
      integral=0;
    }
    speed = (error * tkp) + (integral * tki) + (deriv * tkd);
    if (speed > setspeed)
    {
      speed = setspeed;
    }
    else if (speed < -setspeed)
    {
      speed = -setspeed;
    }
       Brain.Screen.printAt(75, 100, "Heading: %2f", imu.heading(deg));
      Brain.Screen.printAt(75, 120, " Heading Error: %2f", error);
    Left.spin(fwd, speed, volt);
    Right.spin(reverse, speed, volt);
    timeout++;
    perro = error;
    if (fabs(error) < 2.25)
    {
      settle++;
    }

    if (timeout >= timeoutamt)
    {
      settle++;
    }
    wait(10, msec);
  }
  Left.stop(brake);
  Right.stop(brake);
}

void rightSwing(float target, float setspeed)
{
  timeout = 0;
  settle = 0;
  while (settle < 2)
  {
    error = (target - imu.rotation(deg));
    deriv = error - perro;
    speed = (error * skp) + (integral * ski) + (deriv * skd);
    if (speed > setspeed)
    {
      speed = setspeed;
    }
    else if (speed < -setspeed)
    {
      speed = -setspeed;
    }
    Right.spin(fwd, speed, volt);
    timeout++;
    perro = error;
    if (fabs(error) < 1)
    {
      settle++;
    }

    if (timeout >= timeoutamt)
    {
      settle++;
    }
    wait(10, msec);
  }
  Left.stop(hold);
  Right.stop(hold);
}

void leftSwing(float target, float setspeed)
{
  timeout = 0;
  settle = 0;
  while (settle < 2)
  {
    error = (target - imu.rotation(deg));
    deriv = error - perro;
    speed = (error * skp) + (integral * ski) + (deriv * skd);
    if (speed > setspeed)
    {
      speed = setspeed;
    }
    else if (speed < -setspeed)
    {
      speed = -setspeed;
    }
    Left.spin(fwd, speed, volt);
    timeout++;
    perro = error;
    if (fabs(error) < 1)
    {
      settle++;
    }

    if (timeout >= timeoutamt)
    {
      settle++;
    }
    wait(10, msec);
  }
  Left.stop(hold);
  Right.stop(hold);
}