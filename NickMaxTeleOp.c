#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S3, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S3_C1_1,     fr,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,     br,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C2_1,     fl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C2_2,     bl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_1,     liftA,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     liftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_1,     sweeper,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     spinner,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    cubeLiftServoA,       tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    cubeLiftServoB,       tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Motor config

////////////////////////////////Current pchs teleop code 12/20/2013

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "ButtonsDefs.h"  //Buttons definitions

const float MAX_JOYSTICK = 128.0;//used to scale joystick vectors out of 1

void initializeRobot()//initialize
{
	return;
}

int scaleJoystick(int n){
	if(n < 20 && n > -20){
		return 0;
	}

	return (n / MAX_JOYSTICK)	*  100; //scale the joysticks out of 100 rather than 128
}

task raiseLowerLift(){
	while(true){
		if(joystick.joy2_TopHat == pov_north){
			motor[liftA] = 100;
			motor[liftB] = 100;
		}
		else if(joystick.joy2_TopHat == pov_south){
			motor[liftA] = -100;
			motor[liftB] = -100;
		}
		else{
			motor[liftA] = 0;
			motor[liftB] = 0;
		}
	}
}


task main()
{

	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	startTask(raiseLowerLift);

	while (true)
	{
		getJoystickSettings(joystick);

		//todo fix motor signs
		if(joystick.joy1_TopHat == pov_north){
			motor[fr] = 100;
			motor[fl] = 100;
			motor[br] = -100;
			motor[bl] = -100;
		}
		else if(joystick.joy1_TopHat == pov_south){
			motor[fr] = -100;
			motor[fl] = -100;
			motor[br] = 100;
			motor[bl] = 100;
		}
		else if(joystick.joy1_TopHat == pov_east){
			motor[fr] = 100;
			motor[fl] = 100;
			motor[br] = 100;
			motor[bl] = 100;
		}
		else if(joystick.joy1_TopHat == pov_west){
			motor[fr] = -100;
			motor[fl] = -100;
			motor[br] = -100;
			motor[bl] = -100;
		}
		else if(joystick.joy1_Buttons == button_right_trigger){
			motor[fr] = 100;
			motor[fl] = -100;
			motor[br] = -100;
			motor[bl] = 100;
		}
		else if(joystick.joy1_Buttons == button_left_trigger){
			motor[fr] = -100;
			motor[fl] = 100;
			motor[br] = 100;
			motor[bl] = -100;
		}
		else{
			motor[fr] = 0;
			motor[fl] = 0;
			motor[br] = 0;
			motor[bl] = 0;
		}

		if(joystick.joy1_Buttons == button_a){
			motor[spinner] = 100;
		}
		else if(joystick.joy1_Buttons == button_b){
			motor[spinner] = -100;
		}
		else{
			motor[spinner] = 0;
		}

		if(joystick.joy2_Buttons == button_a){
			motor[sweeper] = 50;
		}
		else if(joystick.joy2_Buttons == button_b){
			motor[sweeper] = -50;
			} else{
			motor[sweeper] = 0;
		}

		//if(ServoValue[cubeLiftServoB] + 1 < 62){
		if(joystick.joy2_TopHat == pov_east && ServoValue[cubeLiftServoB] > 101){
			servo[cubeLiftServoA] = ServoValue[cubeLiftServoA] + 1;
			servo[cubeLiftServoB] = ServoValue[cubeLiftServoB] - 1;
			wait1Msec(5);
		}
		if(joystick.joy2_TopHat == pov_west){
			servo[cubeLiftServoA] = ServoValue[cubeLiftServoA] - 1;
			servo[cubeLiftServoB] = ServoValue[cubeLiftServoB] + 1;
			wait1Msec(5);
		}
		//}
	}
}
