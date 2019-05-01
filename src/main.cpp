#include "Servo.h"
#include <mbed.h>

#define Steering_ID 0

CAN can0(D10, D2); // CAN bus pins

CANMessage inMsg;

Servo rightUpper(A5);
Servo rightLower(A6);
Servo leftUpper(A1);
Servo leftLower(A2);

void enableDRS();
void disableDRS();

DigitalOut led(LED1);

int main() {
  can0.frequency(250000);
  can0.mode(CAN::Normal);
  while (1) {
    if (can0.read(inMsg)) {
      led = !led;
      if (inMsg.id == Steering_ID) {
        if (inMsg.data[0] == 12) {
          enableDRS();
        } else if (inMsg.data[0] == 13) {
          disableDRS();
        }
      }
    }
  }
}

void enableDRS() {
  int upperAngle = 60;
  int lowerAngle = 40;

  rightUpper.position(upperAngle);
  leftUpper.position(180 - upperAngle);

  rightLower.position(lowerAngle);
  leftLower.position(180 - lowerAngle);
}

void disableDRS() {
  int upperAngle = 30;
  int lowerAngle = 22;

  rightUpper.position(upperAngle);
  leftUpper.position(180 - upperAngle);

  rightLower.position(lowerAngle);
  leftLower.position(180 - lowerAngle);
}