#include <Arduino.h>

#include"Encoder.h"
#include"Motor.h"
//#include<Wire.h>
//#include<LIDARLite.h>

Encoder leftEnc;
Encoder rightEnc;

//Interrupt ISPs for encoders
void IRAM_ATTR updateLeft(){
	leftEnc.lastCounter = leftEnc.counter;
	if (digitalRead(leftEnc.pinB) != digitalRead(leftEnc.pinA)) { 
		leftEnc.counter ++;
	} else {
		leftEnc.counter --;
	} 
}
void IRAM_ATTR updateRight(){
	rightEnc.lastCounter = rightEnc.counter;
	if (digitalRead(rightEnc.pinB) != digitalRead(rightEnc.pinA)) { 
		rightEnc.counter ++;
	} else {
		rightEnc.counter --;
	} 
}

void setup() {
	leftEnc.begin(34, 39);
	rightEnc.begin(36, 4);
	attachInterrupt(leftEnc.pinA, updateLeft, CHANGE);
	attachInterrupt(rightEnc.pinA, updateRight, CHANGE);

	//Preinstantiated motorns inside Motor.h
	right.begin(13, 12, 27);
	left.begin(33, 15, 32);
	Serial.begin(115200);
}

void loop() {
	Serial.println("Hello world!");
	delay(1000);
}