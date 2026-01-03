#include "BNO085Accel.h"

BNO085Accel::BNO085Accel(const char *name, TwoWire &bus, uint8_t addr)
    : Accel(name),
      wire(&bus),
      address(addr)
{
}

bool BNO085Accel::init()
{
    // Ensure I2C bus is initialized
    wire->begin();

    // SparkFun API:
    // begin(deviceAddress, wirePort, intPin)
    // intPin = 255 means "no interrupt pin"
    if (!imu.begin(address, *wire, 255))
    {
        LOGE("BNO085 Accel init failed (I2C addr: 0x%02X)", address);
        return false;
    }

    // SparkFun: timeBetweenReports is in milliseconds
    // 10 ms -> 100 Hz
    imu.enableAccelerometer(10);

    return true;
}

bool BNO085Accel::read()
{
    // SparkFun updates internal sensor values when new data arrives
    if (!imu.dataAvailable())
        return false;

    // SparkFun accel outputs m/s^2 (already converted from Q format)
    acc = Vector<3>(
        (double)imu.getAccelX(),
        (double)imu.getAccelY(),
        (double)imu.getAccelZ()
    );

    return true;
}
