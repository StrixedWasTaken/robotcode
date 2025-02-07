#include "vex.h"

int current_auton_selection = 0;
bool auto_started = false;

/// PISTON TOGGLES
//////////////////////////////////////////////
void clamptoggle()
{
  backclamp.set(!backclamp.value());
  wait(100, msec);
}

void liftoggle()
{
  intakelift.set(!intakelift.value());
  wait(100, msec);
}

void doinkertoggle()
{
  doinker.set(!doinker.value());
}
//////////////////////////////////////////////

/// COLOR SORT
//////////////////////////////////////////////
bool touchy = true;

int blueSort()
{
  colorsensor.setLight(ledState::on);
  colorsensor.setLightPower(100, pct);
  while (touchy)
  {
    intakes.spin(fwd, 100, pct);
    if (colorsensor.hue() > 190)
    {
      wait(82.28, msec);
      intakes.stop(brake);
      wait(150, msec);
    }
    else if (colorsensor.hue() < 190)
    {
      intakes.spin(fwd, 100, pct);
    }
  }
  return 1;
}

int redSort()
{
  colorsensor.setLight(ledState::on);
  colorsensor.setLightPower(100, pct);
  while (touchy)
  {
    intake.spin(fwd, 100, pct);
    if (colorsensor.hue() > 10 && colorsensor.hue() < 25)
    {
      wait(82.335, msec);
      intakes.stop(brake);
      wait(300, msec);
    }
    else if (colorsensor.hue() > 25)
    {
      intakes.spin(fwd, 100, pct);
    } 
  }
  return 1;
}

void BLUES()
{
  task bluey = task(blueSort);
}

void REDS()
{
  task redy = task(redSort);
}
void disableColorSort()
{
  touchy = false;
}

/// DRIVE CLAMPING
//////////////////////////////////////////////
int dumbassclamp()
{
  wait(800, msec);
  backclamp.set(true);
  return 1;
}

int awpclamp()
{
  wait(1350, msec);
  backclamp.set(false);
  return 1;
}

void sillyclamp()
{
  task sdfn = task(awpclamp);
}

void dumbclamp()
{
  task efkl = task(dumbassclamp);
}

// LADY BROWN P LOOP//////////////////////////
//////////////////////////////////////////////

bool macroState = false;
const int numStates = 2;
int states[numStates] = {0, 85};
int currState = 0;
int target = 0;

void firstState() {
  currState = 0;
  if (currState == numStates) {
    currState = 0;
  }
  target = states[currState];
  wait(500, msec);
}

void secondState() {
  currState = 1;
  if (currState == numStates) {
    currState = 0;
  }
  target = states[currState];
  wait(500, msec);
}

void nextState() {
  currState += 1;
  if (currState == numStates) {
    currState = 0;
  }
  target = states[currState];
  wait(500, msec);
}

void liftControl() {
  if (macroState==true) {
  double lbKp = .17;
  double error = target - ladyLift.position(deg);
  double velocity = error * lbKp;
  if (velocity > 6) velocity = 6;
  cout << "lb error: " << error << endl;
  ladybrown.spin(fwd, velocity, volt);
  if (error < 2 && error >0.1) {
    ladybrown.stop(brake);
    macroState=false;
    }
  }
}

void liftControlTask() {
  while (true) {
    liftControl();  // Call the liftControl function to run continuously
    wait(10, msec);
  }
}

/// BUTTONS FOR AUTON SELECTOR
//////////////////////////////////////////////
void buttonMake(double xGreater, double xLess, double yGreater, double yLess, double autoselect)
{
  if (Brain.Screen.pressing() && Brain.Screen.xPosition() > xGreater && Brain.Screen.xPosition() < xLess && Brain.Screen.yPosition() > yGreater && Brain.Screen.yPosition() < yLess)
  {
    current_auton_selection = autoselect;
  }
}

void backButton()
{
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(430, 0, 50, 50);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(mono40);
  Brain.Screen.printAt(445, 36, "X");
  if (Brain.Screen.pressing() && Brain.Screen.xPosition() > 420 && Brain.Screen.xPosition() < 480 && Brain.Screen.yPosition() > 0 && Brain.Screen.yPosition() < 60)
  {
    current_auton_selection = 0;
  }
  wait(100, msec);
}
//////////////////////////////////////////////
//////////////////////////////////////////////

void massivething()
{
  while (true)
  {
    Brain.Screen.drawImageFromFile("massive.png", 0, 0);
    wait(10, msec);
  }
}