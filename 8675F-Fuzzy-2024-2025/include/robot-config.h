using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor l1;
extern motor l2;
extern motor l3;
extern motor r1;
extern motor r2;
extern motor r3;
extern motor rightintake;
extern motor leftintake;
//extern motor lift;
extern optical colorsensor;
extern inertial imu;
extern controller Controller1;
extern motor_group Left;
extern motor_group Right;
extern digital_out clamp;
extern digital_out backclamp;
extern rotation rotation_lift;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );