#include "Servo.h"
#include <mbed.h>

#define Steering_ID 0

CAN can0(PA_11, PA_12);
CANMessage inMsg;

Servo rightServo(D4);
Servo leftServo(D3);

Timer timer;

// Prototypes
void enableDRS();
void disableDRS();

int main() {

  can0.frequency(250000);
  can0.mode(CAN::Normal);

  timer.reset();
  timer.start();

  disableDRS();

  while (1) {
    if (can0.read(inMsg)) {
      timer.stop();
      timer.reset();
      timer.start();

      if (inMsg.id == Steering_ID) {
        if (inMsg.data[0] == 12) { // 0x0C
          enableDRS();
        } else if (inMsg.data[0] == 13) { // 0x0D
          disableDRS();
        }
      }
    }

    // Bus connection broken
    if (timer.read() > 1) {
      disableDRS();
    }
  }
}

void enableDRS() {
  float val = 0.4;
  rightServo.write(1.0 - val);
  leftServo.write(val);
}

void disableDRS() {
  float val = 0.0;
  rightServo.write(1.0 - val);
  leftServo.write(val);
}