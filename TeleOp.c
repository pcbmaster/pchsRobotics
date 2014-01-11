#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     fr,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     br,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     fl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     bl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     liftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     blockLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     sweeperMotor,  tmotorTetrix, openLoop, reversed)
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


task main()
{

	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

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
		else if(joystick.joy1_Buttons == button_left_trigger){
			motor[fr] = 100;
			motor[fl] = -100;
			motor[br] = -100;
			motor[bl] = 100;
		}
		else if(joystick.joy1_Buttons == button_right_trigger){
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

		if(joystick.joy1_Buttons == button_y){
			motor[liftA] = 100;
			motor[liftB] = 100;
		}
		else if(joystick.joy1_Buttons == button_a){
			motor[liftA] = -100;
			motor[liftB] = -100;
		}
		else{
			motor[liftA] = 0;
			motor[liftB] = 0;
		}

		//if(ServoValue[cubeLiftServoB] + 1 < 62){
			if(joystick.joy1_Buttons == button_x){
				servo[cubeLiftServoA] = ServoValue[cubeLiftServoA] + 1;
				servo[cubeLiftServoB] = ServoValue[cubeLiftServoB] - 1;
				wait1Msec(5);
			}
			else if(joystick.joy1_Buttons == button_b){
				servo[cubeLiftServoA] = ServoValue[cubeLiftServoA] - 1;
				servo[cubeLiftServoB] = ServoValue[cubeLiftServoB] + 1;
				wait1Msec(5);
			}
		//}
		nxtDisplayCenteredBigTextLine(0, "%d", ServoValue[cubeLiftServoA]);
		nxtDisplayCenteredBigTextLine(1, "%d", ServoValue[cubeLiftServoB]);
	}
}
