#ifndef ENCODER_H
#define ENCODER_H

class Encoder{
	private:
		int pinA = 0;
		int pinB = 0;

		int lastCounter = 0;
		int counter = 0; 
		int aState;
		int aLastState;  

		void IRAM_ATTR update(){
			lastCounter = counter;
			if (digitalRead(pinB) != digitalRead(pinA)) { 
				counter ++;
			} else {
				counter --;
			} 
		}
	public:
		Encoder(int newPinA, int newPinB){
			pinA = newPinA;
			pinB = newPinB;


			pinMode (pinA,INPUT);
			pinMode (pinA,INPUT);

			// Reads the initial state of the outputA
			aLastState = digitalRead(pinA);   

			attachInterrupt(pinA, update, CHANGE);			
		}


		int getDistance(){
			return counter;
		}
		int getDerivative(){
			return counter - lastCounter;
		}
};
#endif