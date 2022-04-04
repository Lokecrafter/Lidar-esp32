#ifndef ENCODEMOTORS_H
#define ENCODEMOTORS_H

#include <Arduino.h>
#include"Encoder.h"
#include"Motor.h"

#define STEPSERROR 20
#define MTRSPEEED 1


Encoder leftEnc;
Encoder rightEnc;
//Interrupt ISPs for encoders
void updateLeft(){
	leftEnc.lastCounter = leftEnc.counter;
	if (digitalRead(leftEnc.pinB) != digitalRead(leftEnc.pinA)) { 
		leftEnc.counter ++;
	} else {
		leftEnc.counter --;
	} 
}
void updateRight(){
	rightEnc.lastCounter = rightEnc.counter;
	if (digitalRead(rightEnc.pinB) != digitalRead(rightEnc.pinA)) { 
		rightEnc.counter ++;
	} else {
		rightEnc.counter --;
	} 
}


class EncodedMotors{
	private:

	public:
		void begin(){
			leftEnc.begin(13, 12);
			rightEnc.begin(11, 10);
			attachInterrupt(13, updateLeft, CHANGE);
			attachInterrupt(11, updateRight, CHANGE);
			
			//Preinstantiated motorns inside Motor.h
			right.begin(6, 10, 11);
			left.begin(5, 9, 8);
		}

		void driveSteps(int leftSteps, int rightSteps){
			int targetLeft = leftEnc.getDistance() + leftSteps;
			int targetRight = rightEnc.getDistance() + rightSteps;


			while(true){
				//Breaks while-loop if encodervalue is inside of an error threshold
				if(abs(targetLeft - leftEnc.getDistance()) < STEPSERROR &&  abs(targetRight - rightEnc.getDistance()) < STEPSERROR){
					break;
				}
				
				//Determines if left motor should move forward or backward
				if(abs(targetLeft - leftEnc.getDistance()) > STEPSERROR && targetLeft - leftEnc.getDistance() > 0){
					left.setSpeed(MTRSPEEED);
				}
				else if(abs(targetLeft - leftEnc.getDistance()) > STEPSERROR && targetLeft - leftEnc.getDistance() < 0){
					left.setSpeed(-MTRSPEEED);
				}
				
				//Determines if right motor should move forward or backward
				if(abs(targetRight - rightEnc.getDistance()) > STEPSERROR && targetRight - rightEnc.getDistance() > 0){
					right.setSpeed(MTRSPEEED);
				}
				else if(abs(targetRight - rightEnc.getDistance()) > STEPSERROR && targetRight - rightEnc.getDistance() < 0){
					right.setSpeed(-MTRSPEEED);
				}
			}
		}
};



#endif