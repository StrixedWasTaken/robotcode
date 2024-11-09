
#include "PD.h"
#include "math.h"
#include "vex.h"
using namespace vex;

competition Competition;

/*
displays image onto the brain screen
*/
void freaky()
{
  while (true)
  {
    Brain.Screen.drawImageFromFile("freaky.png", 0, 0);
    wait(10, msec);
  }
}
/*
toggles the back clamp
*/
void lifttoggle()
{
  backclamp.set(!backclamp.value());
  wait(100, msec);
}
/*
toggles the clamp lift
*/
void backtoggle()
{
  clamp.set(!clamp.value());
  wait(100, msec);
}

int current_auton_selection = 0;
bool auto_started = false;

/*
pre autonomous that runs function before the match starts
*/
void pre_auton(void)
{
  vexcodeInit();
  imu.calibrate();
  // /*
  // auton selector thats selects an autonomous loop before the beginning on the match
  // */
  while (auto_started == false)
  {
    Brain.Screen.clearScreen();
    switch (current_auton_selection)
    {
    case 0:
      Brain.Screen.printAt(10, 20, "Auton 1");
      Brain.Screen.printAt(410, 210, "Next");
      break;
    case 1:
      Brain.Screen.printAt(10, 20, "Auton 2");
      Brain.Screen.printAt(410, 210, "Next");

      break;
    }
    if (Brain.Screen.pressing() && Brain.Screen.xPosition() > 350 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 170 && Brain.Screen.yPosition() < 270)
    {
      while (Brain.Screen.pressing())
      {
      }
      current_auton_selection++;
    }
    else if (current_auton_selection == 2)
    {
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}


/*
loop that runs the selected program during the autonomous time
*/
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
  /*
  Drives to the goal picks it up and intakes 1 ring to the right of the goal
  */

    backclamp.set(true);
    Drive(-2050, 3);
    wait(200, msec);
    backclamp.set(false);
    wait(200, msec);
    Turn(290, 8); //turns l
    wait(100, msec);
    Drive(1000, 8);
    wait(200, msec);
    leftintake.spin(fwd, 100, pct);
    rightintake.spin(fwd, 100, pct);
    Drive(450, 6);
    leftintake.stop(coast);
    rightintake.stop(coast);
    //  
    break;

  case 1:

    break;
  }
}

    /*
    Skills 
    puts ring on one alliance stake, grabs a goal puts on 4 rings, grabs another goal and then 
    fills it with 3 rings and drops it in the corner
    intake.spin(fwd, 50, pct);
    wait(1, sec);
    //
    alliance ring
    //
    intake.stop(coast);
    Turn(225, 10);
    backclamp.set(true);
    Drive(-900, 10);
    backclamp.set(false);
    clamp.set(true); // BACK LIFT
    //
    grabbing goal
    //
    Turn(90, 10);
    intake.spin(fwd, 100, pct);
    Drive(1000, 10);
    intake.stop(coast);
    Turn(0, 10);
    Turn(315, 10);
    intake.spin(fwd, 100, pct);
    Drive(750, 10);
    intake.stop(coast);
    Turn(270, 10);
    intake.spin(fwd, 100, pct);
    Drive(800, 10);
    intake.stop(coast);
    clamp.set(false);
    backclamp.set(true);
    //
    goal with 4 rings
    //
    Turn(245, 10);
    Drive(-1250, 10);
    backclamp.set(false);
    wait(100, msec);
    clamp.set(true);
    Turn(270, 10);
    intake.spin(fwd, 100, pct);
    Drive(500, 10);
    Turn(180, 10);
    Drive(500, 10);
    wait(200, msec);
    intake.stop(coast);
    Turn(90, 10);
    Drive(-1500, 10);
    wait(150, msec);
    backclamp.set(false);
    clamp.set(false);
    //
    last goal that is picked up, 2 rings on the goal 
    //



    */




/*
the loop that the control input runs through to make certain parts on the robot function with the press of a button
*/
void usercontrol(void)
{
  l1.setBrake(coast);
  l2.setBrake(coast);
  l3.setBrake(coast);
  r1.setBrake(coast);
  r2.setBrake(coast);
  r3.setBrake(coast);
  Controller1.ButtonDown.pressed(backtoggle);
  Controller1.ButtonB.pressed(lifttoggle);     
  // task checkin = task(lift_limiter);
  while (true)
  {
    Left.spin(fwd, (Controller1.Axis3.position(pct)), pct);
    Right.spin(fwd, (Controller1.Axis2.position(pct)), pct);

    if (Controller1.ButtonR2.pressing())
    {
      leftintake.spin(fwd, 100, pct);
      rightintake.spin(fwd, 100, pct);
    }
    else if (Controller1.ButtonR1.pressing())
    {
      leftintake.spin(reverse, 100, pct);
      rightintake.spin(reverse, 100, pct);
    }
    else
    {
      leftintake.stop(coast);
      rightintake.stop(coast);
    }
    wait(10, msec);
  }
}
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
 // Brain.Screen.drawImageFromFile("tedk.png", 0, 0); 
  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
