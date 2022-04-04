#ifndef MOTOR_H
#define MOTOR_H
#include<Arduino.h>

#define FREQ 5000
#define RESOLUTION 8

class Motor{
    public:
        //enablePin has to bee between 0-15 for PWM to work
        void begin(byte enablePin, byte forwardPin, byte reversePin){
            enable = enablePin;
            forward = forwardPin;
            reverse = reversePin;
            pinMode(enable, OUTPUT);
            pinMode(forward, OUTPUT);
            pinMode(reverse, OUTPUT);

            ledcSetup(enable, FREQ, RESOLUTION);
            ledcAttachPin(enable, enable); //Enable is used as pin and channel
        }

        void setSpeed(float motorSpeed){
            speed = motorSpeed;

            if(motorSpeed == 0){
                ledcWrite(enable, 0);
                return;
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
            ledcWrite(enable, 255 * abs(motorSpeed));
        }

        float getSpeed(){ return speed; }
    private:
        byte enable;
        byte forward;
        byte reverse;

        float speed; 
};


float clamp(float val, float minVal, float maxVal){
    val = max(val, minVal);
    val = min(val, maxVal);

    return(val);
}





Motor right;
Motor left;
const float standardSpeedFactor = 1;
const float turnSpeedFactor = 1;
float speedFactor;


//Joystick driving with this function
void driveMotors(float joyX, float joyY){
    joyX = clamp(joyX, -1, 1);
    joyY = clamp(joyY, -1, 1);

    if(joyY < 0)  joyX = joyX * -1; //Handles steering so it feels natural by simulating how a car would steer when reversing

    float leftMotor = joyY + joyX;
    float rightMotor = joyY - joyX;

    leftMotor = clamp(leftMotor, -1, 1);
    rightMotor = clamp(rightMotor, -1, 1);

    if(joyX == 0){
        speedFactor = standardSpeedFactor;
    }
    else{
        speedFactor = turnSpeedFactor;
    }

    right.setSpeed(rightMotor * speedFactor);
    left.setSpeed(leftMotor * speedFactor);
}

#endif