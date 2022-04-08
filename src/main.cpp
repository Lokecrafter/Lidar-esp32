#include <Arduino.h>

#include"EncodedMotors.h"
#include<Wire.h>
#include<LIDARLite.h>
#define HALLEFCT 21
#define OFFSETANGLE -1.1868239		//-68 deg

const int minLowHallTime = 30;

LIDARLite lidarLite;
int cal_cnt = 0; //Call count
bool sameRot = false; //Debounce hall efect sensor

unsigned long prevTime = 0;
unsigned long deltaTime = 0;




const int bufferSize = 1000;
int distBuffer[bufferSize];		//Distance in millimeters
float angleBuffer[bufferSize];	//Angles in radians
int storedValues = 0;



//HALLEFCT ISR
void IRAM_ATTR updateRevTime(){
	if(sameRot == true)	return;
	
	unsigned long currentTime = millis();
	sameRot = true;


	deltaTime = currentTime - prevTime;
	prevTime = currentTime;
}
//Lidar dataGrabber
void doReading(){
	int dist = 0;

	if(cal_cnt == 0){
    	dist = lidarLite.distance();
	}
	else{
		dist = lidarLite.distance(false);
	}

	unsigned long revolutionTime = millis() - prevTime;
	float revolutionPercentage = (float)revolutionTime / (float)deltaTime;

	//Store angle in radians
	angleBuffer[storedValues] = revolutionPercentage * 2 * PI - OFFSETANGLE;
	distBuffer[storedValues] = dist;




	//Increment bufferIndex
	storedValues++;
	if(storedValues >= bufferSize){
    	dist = lidarLite.distance();
		storedValues = 0;
		cal_cnt = 1;
	}
	//Increment reading counter
	cal_cnt++;
	cal_cnt = cal_cnt % 200;
}





void setup() {
	pinMode(HALLEFCT, INPUT);
	attachInterrupt(digitalPinToInterrupt(HALLEFCT), updateRevTime, FALLING);

	lidarLite.begin(0, true);
	lidarLite.write(0x02, 0x0d);
	lidarLite.write(0x04, 0x00000100);
	lidarLite.write(0x12, 0x03);

	beginEncodedMotors();
	Serial.begin(115200);
}


int loopCounter = 0;

void loop() {
	
	if(loopCounter > 100){
		Serial.print("L ");
		for (int i = 0; i < storedValues; i++)
		{
			Serial.print("(");
			Serial.print(angleBuffer[i]);
			Serial.print(",");
			Serial.print(distBuffer[i]);
			Serial.print(") ");
		}
		Serial.println("");
		storedValues = 0;
		loopCounter = 0;
		lidarLite.distance(); //Calibrate
	}

	doReading();
	
	//reset samerot
	if((millis() - prevTime) >= minLowHallTime){
		sameRot = false;
	}
/*
	unsigned long revolutionTime = millis() - prevTime;
	float revolutionPercentage = (float)revolutionTime / (float)deltaTime;

	Serial.println(revolutionPercentage * 360);
*/
	loopCounter++;
}