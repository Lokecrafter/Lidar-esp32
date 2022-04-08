#ifndef MOTOR_H
#define MOTOR_H
#include<Arduino.h>

#define FREQ 5000
#define RESOLUTION 8

class Motor{
    private:
        int enable;
        int forward;
        int reverse;

        float speed; 
    public:
        Motor(){
           //Do nothing constructor 
        }
        //enablePin has to bee between 0-15 for PWM to work
        void begin(int enablePin, int forwardPin, int reversePin){
            enable = enablePin;
            forward = forwardPin;
            reverse = reversePin;
            pinMode(enablePin, OUTPUT);
            pinMode(forwardPin, OUTPUT);
            pinMode(reversePin, OUTPUT);

            ledcSetup(enable % 15, FREQ, RESOLUTION);
            ledcAttachPin(enable, enable % 15); //Enable is used as pin and channel
        }

        void setSpeed(float motorSpeed){
            speed = motorSpeed;

            if(motorSpeed == 0){
                ledcWrite(enable, 0);
            }
            else if(motorSpeed > 0){
                digitalWrite(forward, HIGH);
                digitalWrite(reverse, LOW);
            }
            else{
                digitalWrite(forward, LOW);
                digitalWrite(reverse, HIGH);
            }
            //PWM command for motor speed
            //ledcWrite(enable, 255 * abs(motorSpeed));
        }

        float getSpeed(){ return speed; }
};


float clamp(float val, float minVal, float maxVal){
    val = max(val, minVal);
    val = min(val, maxVal);

    return(val);
}

#endif