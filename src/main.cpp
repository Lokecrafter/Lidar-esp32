#include <Arduino.h>
#include"Encoder.h"
#include"Motor.h"

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

void setup() {
	leftEnc.begin(13, 12);
	rightEnc.begin(11, 10);
	attachInterrupt(13, updateLeft, CHANGE);
	attachInterrupt(11, updateRight, CHANGE);
	
	//Preinstantiated motorns inside Motor.h
	right.begin(6, 10, 11);
	left.begin(5, 9, 8);

	Serial.begin(115000);
}

void loop() {

}