
#include "vex.h"
#include "PD.h"
#include "functions.h"
#include "math.h"
#include <cmath>
using namespace vex;

competition Competition;
///////////////////////////

void pre_auton(void)
{
  int brainx = 1;
  vexcodeInit();
  ladyLift.resetPosition();
  imu.calibrate();
  //
  while (auto_started == false)
  {
    if (brainx != Brain.Screen.xPosition())
    {
      switch (current_auton_selection)
      {
      case 0:
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        Brain.Screen.setPenColor(black);
        Brain.Screen.setFont(monoXL);
        Brain.Screen.drawRectangle(10, 80, 140, 130, red);    // Red
        Brain.Screen.drawRectangle(170, 80, 140, 130, blue);  // Blue
        Brain.Screen.drawRectangle(330, 80, 140, 130, green); // Skills
        Brain.Screen.setPenColor(white);
        //
        Brain.Screen.setFillColor(red);
        Brain.Screen.printAt(50, 160, "Red");
        //
        Brain.Screen.setFillColor(blue);
        Brain.Screen.printAt(200, 160, "Blue");
        //
        Brain.Screen.setFillColor(green);
        Brain.Screen.printAt(340, 160, "Skills");
        Brain.Screen.setPenColor(orange);
        Brain.Screen.setFillColor(white);
        Brain.Screen.setFont(monoXXL);
        Brain.Screen.printAt(80, 50, "8675F Fuzzy");
        buttonMake(10, 150, 80, 210, 1);  // Red Side
        buttonMake(170, 310, 80, 210, 2); // Blue Side
        buttonMake(330, 470, 80, 210, 3); // Skills

        break;
      case 1: // Red Menu
        backButton();
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(monoM);
        //
        Brain.Screen.drawRectangle(20, 20, 180, 80, red); // Goal Rush 2 Ring
        Brain.Screen.printAt(24, 60, "Goal Rush 2 Ring");
        buttonMake(20, 200, 20, 100, 4);
        //
        Brain.Screen.drawRectangle(20, 130, 180, 80, red); // AUTON SLOT 2
        Brain.Screen.printAt(24, 175, "AUTON SLOT 2");
        buttonMake(20, 200, 130, 210, 5);
        //
        Brain.Screen.drawRectangle(230, 20, 180, 80, red); // AUTON SLOT 3
        Brain.Screen.printAt(236, 60, "AUTON SLOT 3");
        buttonMake(230, 410, 20, 100, 6);
        //
        Brain.Screen.drawRectangle(230, 130, 180, 80, red); // AUTON SLOT 4
        Brain.Screen.printAt(236, 175, "Neg 2 Ring AWP");
        buttonMake(230, 410, 130, 210, 7);
        break;

      case 2: // Blue Menu
        backButton();
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(monoM);
        Brain.Screen.setFillColor(blue);
        //
        Brain.Screen.drawRectangle(20, 20, 180, 80, blue); // Goal Rush 2 Ring
        Brain.Screen.printAt(24, 60, "Goal Rush 2 Ring");
        buttonMake(20, 200, 20, 100, 8);
        //
        Brain.Screen.drawRectangle(20, 130, 180, 80, blue); // AUTON SLOT 6
        Brain.Screen.printAt(24, 175, "AUTON SLOT 6");
        buttonMake(20, 200, 130, 210, 9);
        //
        Brain.Screen.drawRectangle(230, 20, 180, 80, blue); // AUTON SLOT 7
        Brain.Screen.printAt(236, 60, "AUTON SLOT 7");
        buttonMake(230, 410, 20, 100, 10);
        //
        Brain.Screen.drawRectangle(230, 130, 180, 80, blue); // AUTON SLOT 8
        Brain.Screen.printAt(236, 175, "AUTON SLOT 8");
        buttonMake(230, 410, 130, 210, 11);
        //
        break;

      case 3: // Skills
        backButton();
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        Brain.Screen.setFont(mono60);
        Brain.Screen.printAt(2, 100, "Skills");
        break;

      case 4: // AUTON SLOT 1 RED
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.printAt(2, 100, "Goal Rush 2 Ring");
        break;
      //
      case 5: // AUTON SLOT 2 RED
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.printAt(2, 100, "AUTON SLOT 2");
        break;
      //
      case 6: // AUTON SLOT 3 RED
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.printAt(2, 100, "AUTON SLOT 3");
        break;
      //
      case 7: // AUTON SLOT 4 RED
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.printAt(2, 100, "AUTON SLOT 4");
        break;
      //
      case 8: // AUTON SLOT 5 BLUE
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.printAt(2, 100, "Goal Rush 2 Ring");
        break;
      //
      case 9: // AUTON SLOT 6 BLUE
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.printAt(2, 100, "AUTON SLOT 6");
        break;
      //
      case 10: // AUTON SLOT 7 BLUE
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.printAt(2, 100, "AUTON SLOT 7");
        break;
      //
      case 11: // AUTON SLOT 8 BLUE
        Brain.Screen.drawRectangle(0, 0, 480, 270, white);
        backButton();
        Brain.Screen.setFont(mono30);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.printAt(2, 100, "AUTON SLOT 8");
        break;
        //
      }
    }
    brainx = Brain.Screen.xPosition();
    wait(250, msec);
  }
}

void autonomous(void)
{
  auto_started = true;
  if (auto_started == true)
  {
    Brain.Screen.clearScreen();
  }
  switch (current_auton_selection)
  {
  case 0:
  //Turn(90, 12);
  Drive(40, 12);
  Drive(-20, 12);
  Drive(10, 12);
  // imu.setHeading(180, deg);
  // dumbclamp();
  // Drive(-36, 5);
  // wait(300, msec);
  // REDS();
  // rTurn(-105, 8);
  // Drive(45, 8);
  // wait(100, msec);
  // rTurn(-180, 6);
  // wait(100, msec);
  // Drive(20, 6);
  // Drive(-20, 6);
  // wait(100, msec);
  // rTurn(-220, 7);
  // Drive(21, 6);
    break;

  case 1:

    break;

  case 2:

    break;

  case 3:

    break;

  case 4: // Goal Rush Positive (RED)
    doinker.set(true);
    frontintake.spin(fwd, 100, pct);
    maxDrive(47, 11, 5, 7);
    doinker.set(false);
    frontintake.stop();
    wait(300, msec);
    Drive(-15, 7);
    wait(50, msec);
    doinker.set(true);
    Drive(-10, 7);
    wait(50, msec);
    doinker.set(false);
    wait(50, msec);
    //relTurn(190, 6);
    wait(100, msec);
    dumbclamp();
    Drive(-26, 5);
    wait(200, msec);
    intake.spin(fwd, 100, pct);
    wait(3, sec);
    intakes.stop();
    //relTurn(55, 6);
    break;

  case 5: // AUTON SLOT 2

    break;

  case 6: // AUTON SLOT 3

    break;

  case 7: // AUTON SLOT 4

    break;

  case 8: // Goal Rush Positive (BLUE)
    doinker.set(true);
    frontintake.spin(fwd, 100, pct);
    maxDrive(47, 11, 5, 7);
    doinker.set(false);
    frontintake.stop();
    wait(200, msec);
    Drive(-15, 7);
    wait(50, msec);
    doinker.set(true);
    Drive(-10, 7);
    wait(50, msec);
    doinker.set(false);
    wait(50, msec);
    //relTurn(190, 6);
    wait(100, msec);
    dumbclamp();
    Drive(-25, 5);
    wait(200, msec);
    intake.spin(fwd, 100, pct);
    wait(300, msec);
    frontintake.spin(reverse, 100, pct);
    wait(100, msec);
    intakes.spin(fwd, 100, pct);
    wait(3, sec);
    intakes.stop();
    //relTurn(-45, 6);
    doinker.set(true);
    Drive(23, 5);
    break;

  case 9: // AUTON SLOT 6

    break;

  case 10: // AUTON SLOT 7

    break;

  case 11: // AUTON SLOT 8

    break;
  }
}



void usercontrol(void)
{
  thread blah(liftControlTask);
  // Set brake modes for all motors
  l1.setBrake(coast);
  l2.setBrake(coast);
  l3.setBrake(coast);
  r1.setBrake(coast);
  r2.setBrake(coast);
  r3.setBrake(coast);
  ladybrown.setBrake(brake);
  Controller1.ButtonB.pressed(clamptoggle);  // ButtonB action
  Controller1.ButtonY.pressed(doinkertoggle);  // ButtonY action
  disableColorSort();  // Disabling color sort

  while (true)
  {
    // Driving control
    int leftSpeed = Controller1.Axis3.position();
    int rightSpeed = Controller1.Axis2.position();
    Left.spin(fwd, leftSpeed, pct);
    Right.spin(fwd, rightSpeed, pct);

    // Intake control
    if (Controller1.ButtonR2.pressing()) {
      intakes.spin(fwd, 12, volt);
    }
    else if (Controller1.ButtonR1.pressing()) {
      intakes.spin(reverse, 12, volt);
    }
    else {
      intakes.stop(coast);
    }

    if (Controller1.ButtonLeft.pressing()) {
      macroState = true;
      firstState();
    }

    if (Controller1.ButtonRight.pressing()) {
      macroState = true;
      secondState();
    }

    // Manual control for stopping the macro (optional)
    if (Controller1.ButtonL1.pressing()) {
      ladybrown.spin(fwd, 8, volt);  // Spin motor in reverse
    }
    else if (Controller1.ButtonL2.pressing()) {
      ladybrown.spin(reverse, 8, volt);  // Spin motor forward
    } 
    else {
      ladybrown.stop(hold);  // Stop the motor if no button is pressed
    }

    wait(10, msec);  // Small delay to avoid overloading the loop
  }
}
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  massivething();
  if (auto_started == true)
  {
  }
  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}