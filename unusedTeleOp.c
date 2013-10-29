#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     fl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     fr,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     bl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     br,            tmotorTetrix, openLoop)
#include "JoystickDriver.C"
#include "ButtonsDefs.h"

////We don't use this file

const int max_joystick = 128;
const int motor_max = 100;

typedef struct{
	int x1;
	int y1;
} ScaledJoystick;
ScaledJoystick scaled_joystick;

void drive(ScaledJoystick my_joystick);
void scaleJoystick(ScaledJoystick my_joystick);
float scale(int n, int premax, int postmax);
void rotate(bool clockwise);

task main(){
	while (true){
		getJoystickSettings(joystick);
		scaleJoystick(scaled_joystick);
		drive(scaled_joystick);
		if(joystick.joy1_Buttons == button_right_button){
			rotate(true);
		}
		else if(joystick.joy1_Buttons == button_left_button){
			rotate(false);
		}
		nxtDisplayCenteredTextLine(0, "%d", joystick.joy1_TopHat);
	}
}

void scaleJoystick(ScaledJoystick my_joystick){
	my_joystick.x1 = scale(joystick.joy1_x1, max_joystick, motor_max);
	my_joystick.y1 = scale(joystick.joy1_y1, max_joystick, motor_max);
}

void drive(ScaledJoystick my_joystick){
	motor[fr] = my_joystick.y1 - my_joystick.x1;
	motor[bl] = my_joystick.y1 - my_joystick.x1;
	motor[fl] = my_joystick.y1 + my_joystick.x1;
	motor[br] = my_joystick.y1 + my_joystick.x1;
}

float scale(int n, int premax, int postmax){
	return (n / premax) * postmax;
}

void rotate(bool clockwise){
		motor[fr] = (clockwise) ? -motor_max : motor_max;
		motor[bl] = (clockwise) ? motor_max : -motor_max;
		motor[fl] = (clockwise) ? motor_max : -motor_max;
		motor[br] = (clockwise) ? -motor_max : motor_max;
}
