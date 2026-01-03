#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h"

static BNO080 myIMU;

void gyro_test_init()
{
    Serial.println();
    Serial.println("BNO080 Read Example");

    Wire.begin();

    if (!myIMU.begin())
    {
        Serial.println("BNO080 not detected");
        while (1);
    }

    Wire.setClock(400000); // 400 kHz I2C

    myIMU.enableGyro(50); // 50 ms update rate

    Serial.println("Gyro enabled");
    Serial.println("Output: x,y,z (rad/s)");
}

void gyro_test_loop()
{
    if (myIMU.dataAvailable())
    {
        Serial.print(myIMU.getGyroX(), 2);
        Serial.print(",");
        Serial.print(myIMU.getGyroY(), 2);
        Serial.print(",");
        Serial.println(myIMU.getGyroZ(), 2);

        Serial.print("AccX: ");
        Serial.print(myIMU.getAccelX(), 2);
        Serial.print(",");
        Serial.print("AccY: ");

        Serial.print(myIMU.getAccelY(), 2);
        Serial.print(",");
        
        Serial.print("AccZ: ");
        Serial.println(myIMU.getAccelZ(), 2);
    }
}
