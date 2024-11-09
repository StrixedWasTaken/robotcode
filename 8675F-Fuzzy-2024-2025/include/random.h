    

// void arc(float target, float radius, float setspeed) {
//   timeout = 0;
//   settle = 0;
//   deriv = 0;
//   l2.resetPosition();
//   r2.resetPosition();
//   while (settle < 1) {
//     float ratio = (radius - l2.position(deg))/(radius + r2.position(deg));
//     error = (imu.rotation(deg)-target);
//     deriv = error - perro;
//     speed = (error * skp) + (deriv * skd);
//     if (speed > setspeed) { 
//       speed = setspeed;
//     } else if (speed < -setspeed) {
//       speed = -setspeed;
//     }
//     Brain.Screen.printAt(10, 120, " Drive Error: %2f", error);
//     Left.spin(fwd, error * ratio, volt);
//     Right.spin(fwd, error, volt);
//     timeout++;
//     perro = error;
//     if (error < 1 && error > -1) {
//       settle++;
//     }

//     if (timeout >= timeoutamt) {
//       settle++;
//     }
//     wait(10, msec);
//   }
//   Left.stop(hold);
//   Right.stop(hold);
// }

// int state=1;
// float drivespeed;
// void motortoggle() {
//   if (Controller1.ButtonA.pressing() && state==0) {
//     wait(10, msec);
//     state=1;

//   } else if (Controller1.ButtonA.pressing() && state==1) {
//     wait(10, msec);
//     state=0; 
//   }

//   if(state==1) {
//     drivespeed=1;
//   }
//   if(state==0) {
//     drivespeed=0.10;
//   }
// }








// bool red_team=true;
// bool blue_team=false;

// int ringcheck()
// {
//   colorsensor.setLightPower(75, pct);
//   colorsensor.setLight(ledState::on);
//   while (true)
//   {
//     if (colorsensor.hue() < 20)
//     {
//       wait(10, msec);
//       moto.spin(fwd, 50, pct);
//     }
//     else
//     {
//       moto.stop();
//     }
//     wait(10, msec);
//   }
// }

// bool limit_checker = false;

// int lift_limiter() {
//   while (true) {
//     if (rotation_lift.angle() >= 270) {
//       limit_checker = true;
//     } else {
//       limit_checker = false;
//     }
//       wait(10, msec);
//   }
// }
    // if (Controller1.ButtonL1.pressing())
    // {
    //   lift.spin(fwd, 15, pct);
    // } else if (Controller1.ButtonL2.pressing() && limit_checker == false) {
    //     lift.spin(reverse, 15, pct);
    //   if (limit_checker==true) {
    //     lift.stop();
    //   }
    //   } else {
    //     lift.stop();
    //   }