#include "vex.h"
#include "math.h"
#include <cmath>
#include <iostream>
using namespace vex;
using std::cout;
using std::endl;
double error;
double derivative;
double previous_error;
double integral;
double timeout;
double final;
double output;
double finalError;
double driveOutput;
double turnOutput;
double headingError;
double maxTime = 800;
double leftPower;
double rightPower;
double currentPosition;
double tolerance = 1;
double time_settled;
double settle_tolerance = 250;

double degrees_to_inches(double angle_deg, double radius_in_inches)
{
  return (angle_deg / 360.0) * (2 * M_PI * radius_in_inches);
}

float reduce_negative_180_to_180(float angle) {
  while(!(angle >= -180 && angle < 180)) {
    if( angle < -180 ) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
  return(angle);
}


bool pidSettled()
{
  // Check if we've timed out
  if (timeout > maxTime && timeout != 0)
  {
    cout << "\033[31mTimeout exceeded.\033[0m" << endl; 
    return true;
  }

  // Check if the system has settled enough
  if (time_settled > settle_tolerance)
  {
    cout << "\033[32mSystem has settled.\033[0m" << endl; 
    return true;
  }

  return false;
}

void Drive(float target, float setspeed)
{
  timeout = 0;
  time_settled = 0;
  l2.resetPosition();
  r2.resetPosition();
  double kp = 0.35;
  double ki = 0.0035;
  double kd = 1.4;
  double integral_tolerance = 5;
  while (!pidSettled())
  {
    currentPosition = degrees_to_inches(l2.position(deg), 1.375) + degrees_to_inches(r2.position(deg), 1.375) / 2;

    error = (target - currentPosition);
    derivative = error - previous_error;
    if (fabs(error) < integral_tolerance)
    {
      integral += error;
    }

    output = (error * kp) + (integral * ki) + (derivative * kd);
    //output = (output > setspeed) ? setspeed : (output < -setspeed) ? -setspeed : output;

      cout << "\033[34mDrive Error: \033[0m" << error << endl;
    Left.spin(fwd, output, volt);
    Right.spin(fwd, output, volt);

    timeout++;
    previous_error = error;

    if (fabs(error) < 0.5)
    {
      time_settled += 10;
    }
    else
    {
      time_settled = 0;
    }

    wait(10, msec);
  }
  Left.stop(brake);
  Right.stop(brake);
}

void maxDrive(float target, float setspeed, float maxMidDrive, float newSpeed)
{
  timeout = 0;
  time_settled = 0;
  l2.resetPosition();
  r2.resetPosition();
  double kp = 0;
  double ki = 0;
  double kd = 0;
  double integral_tolerance = 5;
  while (!pidSettled)
  {
    currentPosition = degrees_to_inches(l2.position(deg), 1.375) + degrees_to_inches(r2.position(deg), 1.375) / 2;

    error = (target - currentPosition);
    derivative = error - previous_error;
    if (error < integral_tolerance)
    {
      integral += error;
    }
    if (maxMidDrive < error)
    {
      setspeed = newSpeed;
    }

    output = (error * kp) + (integral * ki) + (derivative * kd);
    output = (output > setspeed) ? setspeed : (output < -setspeed) ? -setspeed : output;

    Left.spin(fwd, output, volt);
    Right.spin(fwd, output, volt);

    timeout++;
    previous_error = error;

    if (fabs(error) < 0.5)
    {
      time_settled += 10;
    }
    else
    {
      time_settled = 0;
    }
    
    wait(10, msec);
  }
  Left.stop(brake);
  Right.stop(brake);
}

void Turn(float target, float setspeed)
{
  timeout = 0;
  time_settled = 0;
  double kp = 0.4;
  double ki = 0;
  double kd = 0;
  double integral_tolerance = 5;

  while (!pidSettled())
  {
    error = reduce_negative_180_to_180(target - imu.heading(deg));
    derivative = error - previous_error;
    if (error < integral_tolerance)
    {
      integral += error;
    }

    output = (error * kp) + (integral * ki) + (derivative * kd);

    Left.spin(fwd, output, volt);
    Right.spin(reverse, output, volt);
    timeout++;
    cout << "\033[34mTurn Error: \033[0m" << error << endl;
    previous_error = error;

    if (fabs(error) < 0.5)
    {
      time_settled += 10;
    }
    else
    {
      time_settled = 0;
    }
    wait(10, msec);
  }
  Left.stop(brake);
  Right.stop(brake);
  cout << "\033[34mTurn Error: \033[0m" << error << endl;
}

void driveHeading(float target, float targetHeading, float maxDrive, float maxTurn)
{
  timeout = 0;
  time_settled = 0;
  l2.resetPosition();
  r2.resetPosition();
  double tDerivative;
  double tIntegral;
  double tPrevious_error;
  double integral_tolerance = 5;
  double kp = 0;
  double ki = 0;
  double kd = 0;
  double tkp = 0;
  double tki = 0;
  double tkd = 0;
  while (!pidSettled)
  {
    // current position in inches
    currentPosition = degrees_to_inches(l2.position(deg), 1.375) + degrees_to_inches(r2.position(deg), 1.375) / 2;
    error = target - currentPosition;
    derivative = error - previous_error;
    if (error < integral_tolerance)
    {
      integral += error;
    }
    
    headingError = reduce_negative_180_to_180(target - imu.heading(deg));
    tDerivative = error - tPrevious_error;
    if(headingError < integral_tolerance) 
    {
      tIntegral += headingError;
    }

    driveOutput = (error * kp) + (integral * ki) + (derivative * kd);
    turnOutput = (headingError * tkp) + (tIntegral * tki) + (tDerivative * tkd);

    driveOutput = (output > maxDrive) ? maxDrive : (output < -maxDrive) ? -maxDrive : output;
    turnOutput = (output > maxTurn) ? maxTurn : (output < -maxTurn) ? -maxTurn : output;

    cout << "error: " << error << endl;
    cout << "heading error: " << headingError << endl;

    leftPower = driveOutput - turnOutput;
    rightPower = driveOutput + turnOutput;

    Left.spin(fwd, leftPower, volt);
    Right.spin(fwd, rightPower, volt);

    timeout++;

    previous_error = error;

    if (fabs(error) < 0.25)
    {
      time_settled += 10;
    }
    else
    {
      time_settled = 0;
    }
    wait(10, msec);
  }
  Left.stop(brake);
  Right.stop(brake);
}

// void rightSwing(float target, float setspeed)
// {
//   timeout = 0;
//   settle = 0;
//   while (!pidSettled)
//   {
//     error = (target - imu.rotation(deg));
//     output = compute(error, 0.2, 0, 0.27);
//     output = (output > setspeed) ? setspeed : (output < -setspeed) ? -setspeed : output;
//     Right.spin(fwd, output, volt);
//     timeout++;
//     if (fabs(error) < tolerance)
//     {
//       time_settled += 1;
//     }
//     else
//     {
//       time_settled = 0;
//     }

//     wait(10, msec);
//   }
//   Left.stop(coast);
//   Right.stop(coast);
// }

// void leftSwing(float target, float setspeed)
// {
//   timeout = 0;
//   settle = 0;
//   while (!pidSettled)
//   {
//     error = (target - imu.rotation(deg));
//     derivative = error - previous_error;
//     output = compute(error, 0.2, 0, 0.27);
//     output = (output > setspeed) ? setspeed : (output < -setspeed) ? -setspeed : output;
//     Left.spin(fwd, output, volt);
//     timeout++;
//     if (fabs(error) < tolerance)
//     {
//       time_settled += 1;
//     }
//     else
//     {
//       time_settled = 0;
//     }

//     wait(10, msec);
//   }
//   Left.stop(coast);
//   Right.stop(coast);
// }
