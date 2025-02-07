#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

motor l1 = motor(PORT5, ratio6_1, true); 
motor l2 = motor(PORT3, ratio6_1, true);
motor l3 = motor(PORT1, ratio6_1, false);
motor r1 = motor(PORT4, ratio6_1, false);
motor r2 = motor(PORT8, ratio6_1, false);
motor r3 = motor(PORT7, ratio6_1, true);
inertial imu = inertial(PORT13);
motor intake = motor(PORT10, ratio6_1, false);
motor frontintake = motor(PORT6, ratio18_1, false);
motor_group intakes = motor_group(intake, frontintake);
optical colorsensor = optical(PORT20);
rotation ladyLift = rotation(PORT12, true);
motor ladybrown = motor(PORT16, ratio18_1, true);
controller Controller1 = controller(primary);
motor_group Left = motor_group(l1, l2, l3);
motor_group Right = motor_group(r1, r2, r3);
digital_out doinker = digital_out(Brain.ThreeWirePort.F);
digital_out intakelift = digital_out(Brain.ThreeWirePort.G);
digital_out backclamp = digital_out(Brain.ThreeWirePort.H);
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