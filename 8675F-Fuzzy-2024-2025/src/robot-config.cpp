#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor l1 = motor(PORT4, ratio6_1, true); 
motor l2 = motor(PORT11, ratio6_1, true);
motor l3 = motor(PORT18, ratio6_1, true);
motor r1 = motor(PORT17, ratio6_1, false);
motor r2 = motor(PORT20, ratio6_1, false);
motor r3 = motor(PORT12, ratio6_1, false);
motor leftintake = motor(PORT9, ratio6_1, false);
motor rightintake = motor(PORT2, ratio6_1, true); 
//motor lift = motor(PORT30, ratio6_1, false);
inertial imu = inertial(PORT16);
optical colorsensor = optical(PORT9);
controller Controller1 = controller(primary);
motor_group Left = motor_group(l1, l2, l3);
motor_group Right = motor_group(r1, r2, r3);
digital_out clamp = digital_out(Brain.ThreeWirePort.A);
digital_out backclamp = digital_out(Brain.ThreeWirePort.B);
//rotation rotation_lift = rotation(PORT18);
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}