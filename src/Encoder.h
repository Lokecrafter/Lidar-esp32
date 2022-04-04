#ifndef ENCODER_H
#define ENCODER_H
#include<Arduino.h>


class Encoder{
	public:
		int pinA = 0;
		int pinB = 0;

		int lastCounter = 0;
		int counter = 0; 
		void begin(int newPinA, int newPinB){
			pinA = newPinA;
			pinB = newPinB;


			pinMode(pinA,INPUT);
			pinMode(pinA,INPUT);		
		}

		int getDistance(){
			return counter;
		}
		int getDerivative(){
			return counter - lastCounter;
		}
};
#endif