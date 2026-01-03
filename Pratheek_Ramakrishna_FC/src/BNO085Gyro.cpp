#include "BNO085Gyro.h"

BNO085Gyro::BNO085Gyro(const char *name, TwoWire &bus, uint8_t addr)
    : Gyro(name),
      wire(&bus),
      address(addr)
{
}

bool BNO085Gyro::init()
{
    // Ensure I2C bus is initialized
    wire->begin();

    // SparkFun API:
    // begin(deviceAddress, wirePort, intPin)
    // intPin = 255 => no interrupt pin
    if (!imu.begin(address, *wire, 255))
    {
        LOGE("BNO085 Gyro init failed (I2C addr: 0x%02X)", address);
        return false;
    }

    // SparkFun gyro enable
    // timeBetweenReports is in milliseconds
    // 10 ms => 100 Hz
    imu.enableGyro(50);

    return true;
}

bool BNO085Gyro::read()
{
    // SparkFun updates internal sensor values when new data arrives
    if (!imu.dataAvailable())
        return false;

    // SparkFun gyro outputs rad/s (library converts from Q format)
    Serial.println((double)imu.getGyroX());
    Serial.println((double)imu.getGyroY());
    Serial.println((double)imu.getGyroZ());
    angVel = Vector<3>(
        (double)imu.getGyroX(),
        (double)imu.getGyroY(),
        (double)imu.getGyroZ()
    );

    return true;
}
