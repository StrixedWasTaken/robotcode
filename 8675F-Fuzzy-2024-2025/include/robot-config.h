using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor l1;
extern motor l2;
extern motor l3;
extern motor r1;
extern motor r2;
extern motor r3;
extern motor intake;
extern motor frontintake;
extern motor_group intakes;
extern rotation verticalOdom;
extern rotation horizontalOdom;
extern motor ladybrown;
extern rotation ladyLift;
extern optical colorsensor;
extern inertial imu;
extern controller Controller1;
extern motor_group Left;
extern motor_group Right;
extern digital_out backclamp;
extern digital_out intakelift;
extern digital_out doinker;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );