#ifndef ENCODEMOTORS_H
#define ENCODEMOTORS_H

#include <Arduino.h>
#include"Motor.h"

#define STEPSERROR 20
#define MTRSPEEED 1


#define LEFTA 34
#define LEFTB 39
#define RIGHTA 36
#define RIGHTB 4


Motor right;
Motor left;

volatile int leftCounter = 0;
volatile int rightCounter = 0;

//Interrupt ISPs for encoders
void IRAM_ATTR updateLeft(){
	if (digitalRead(LEFTB) != digitalRead(LEFTA)) { 
		leftCounter ++;
	} else {
		leftCounter --;
	} 
}
void IRAM_ATTR updateRight(){
	if (digitalRead(RIGHTB) != digitalRead(RIGHTA)) { 
		rightCounter ++;
	} else {
		rightCounter --;
	} 
}

void beginEncodedMotors(){
	pinMode(LEFTA, INPUT);
	pinMode(RIGHTA, INPUT);
	pinMode(LEFTB, INPUT);
	pinMode(RIGHTB, INPUT);
	right.begin(13, 12, 27);
	left.begin(33, 15, 32);
	attachInterrupt(digitalPinToInterrupt(LEFTA), updateLeft, CHANGE);
	attachInterrupt(digitalPinToInterrupt(RIGHTA), updateRight, CHANGE);
}



void driveSteps(int leftSteps, int rightSteps){
	int targetLeft = leftCounter + leftSteps;
	int targetRight = rightCounter + rightSteps;


	while(true){
		//Breaks while-loop if encodervalue is inside of an error threshold
		if(abs(targetLeft - leftCounter) < STEPSERROR &&  abs(targetRight - rightCounter) < STEPSERROR){
			break;
		}
		
		//Determines if left motor should move forward or backward
		if(abs(targetLeft - leftCounter) > STEPSERROR && targetLeft - leftCounter > 0){
			left.setSpeed(MTRSPEEED);
		}
		else if(abs(targetLeft - leftCounter) > STEPSERROR && targetLeft - leftCounter < 0){
			left.setSpeed(-MTRSPEEED);
		}
		
		//Determines if right motor should move forward or backward
		if(abs(targetRight - rightCounter) > STEPSERROR && targetRight - rightCounter > 0){
			right.setSpeed(MTRSPEEED);
		}
		else if(abs(targetRight - rightCounter) > STEPSERROR && targetRight - rightCounter < 0){
			right.setSpeed(-MTRSPEEED);
		}
	}
}



//Joystick driving with this function
void driveMotors(float joyX, float joyY){
    joyX = clamp(joyX, -1, 1);
    joyY = clamp(joyY, -1, 1);

    if(joyY < 0)  joyX = joyX * -1; //Handles steering so it feels natural by simulating how a car would steer when reversing

    float leftMotor = joyY + joyX;
    float rightMotor = joyY - joyX;

    leftMotor = clamp(leftMotor, -1, 1);
    rightMotor = clamp(rightMotor, -1, 1);


    right.setSpeed(rightMotor);
    left.setSpeed(leftMotor);
}



#endif