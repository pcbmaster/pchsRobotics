#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     touchSensor,    sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     fr,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     fl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     bl,            tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     br,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     liftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     holder,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     flagspinner,   tmotorTetrix, openLoop)


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "ButtonsDefs.h"


void initializeRobot()
{
	bFloatDuringInactiveMotorPWM = false;
	return;
}


task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	int x, y;
	float speed = 0.75;

	while (true)
	{
		getJoystickSettings(joystick);



		if(joystick.joy1_Buttons == button_right_trigger){

			motor[fr] = -100*speed;
			motor[fl] = 100*speed;
			motor[bl] = 100*speed ;
			motor[br] = -100*speed;
		}

		else if(joystick.joy1_Buttons == button_left_trigger){

			motor[fr] = 100*speed;
			motor[fl] = -100*speed;
			motor[bl] = -100*speed ;
			motor[br] = 100*speed;
		}
		else{
			x = joystick.joy1_x1 / 128.0 * 100 * speed;
			y = joystick.joy1_y1 / 128.0 * 100 * speed;

			motor[fr] = -x + y;
			motor[fl] = x + y;
			motor[bl] = -x + y;
			motor[br] = x + y;
		}

		if(joystick.joy2_TopHat == pov_north && !SensorValue[touchSensor]){
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

		if(joystick.joy2_TopHat == pov_east){
			motor[holder] = 50;
		}

		else if(joystick.joy2_TopHat == pov_west){
			motor[holder] = -50;
		}
		else{
			motor[holder] = 0;

		}
		if(joystick.joy1_Buttons == button_left_button){
			speed = 0.25;
		}
		else if(joystick.joy1_Buttons == button_right_button){
			speed = 1.0;
		}
		else{
	speed = 0.75;
	}
	if(joystick.joy1_Buttons == button_a){
motor[flagspinner] = 100;

}
else if(joystick.joy1_Buttons == button_b){

motor[flagspinner] = -100;
	}
else{
motor[flagspinner] = 0;
 }
	}
}
