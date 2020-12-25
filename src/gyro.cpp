#include "gyro.h"
#include <Arduino.h>
#include "MPU6050_6Axis_MotionApps_V6_12.h"
#include "Wire.h"
#include "mqtt.h"

#define READRATE 500

using namespace Gyro;

MPU6050 mpu;

bool dmpReady = false;
uint8_t fifoBuffer[64];

Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector

float ypr[3];

unsigned long Gyro::previousMillis = 0;

void Gyro::setup() {
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties

    mpu.initialize();
    // todo toto postelovat
//    mpu.setXGyroOffset(220);
//    mpu.setYGyroOffset(76);
//    mpu.setZGyroOffset(-85);
//    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    if (mpu.dmpInitialize() == 0) {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.setDMPEnabled(true);
        dmpReady = true;
    } else {
        Mqtt::publishLog("DMP Initialization failed");
    }
}

void Gyro::readAndPublish() {
    if (!dmpReady) return;

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > READRATE) {
        previousMillis = currentMillis;
        if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Mqtt::publishGyro(ypr[0] * 180 / M_PI, ypr[1] * 180 / M_PI, ypr[2] * 180 / M_PI);
        }
    }
}