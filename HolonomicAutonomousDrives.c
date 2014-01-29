#pragma systemFile
#pragma once

void turnLeft(int time_ms){
	motor[fr] = 100;
	motor[fl] = 100;
	motor[br] = 100;
	motor[bl] = 100;
	wait1Msec(time_ms);
	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
}

void turnRight(int time_ms){
	motor[fr] = -100;
	motor[fl] = -100;
	motor[br] = -100;
	motor[bl] = -100;
	wait1Msec(time_ms);
	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
}

void driveForward(int time_ms){
	motor[fr] = 100;
	motor[fl] = 100;
	motor[br] = -100;
	motor[bl] = -100;
	wait1Msec(time_ms);
	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
}


void driveBackward(int time_ms){
	motor[fr] = -100;
	motor[fl] = -100;
	motor[br] = 100;
	motor[bl] = 100;
	wait1Msec(time_ms);
	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
}

void rotate(int time_ms, bool clockwise){
	if(clockwise){
		motor[fr] = 100;
		motor[fl] = -100;
		motor[br] = -100;
		motor[bl] = 100;
	}
	else{
		motor[fr] = -100;
		motor[fl] = 100;
		motor[br] = 100;
		motor[bl] = -100;
	}
	wait1Msec(time_ms);
	motor[fr] = 0;
	motor[fl] = 0;
	motor[br] = 0;
	motor[bl] = 0;
}
