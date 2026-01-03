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
    imu.enableAccelerometer(50);
    imu.enableGyro(50);
    imu.enableMagnetometer(50);


    return true;
}

bool BNO085Accel::read()
{
    // Return false if no new sample is available yet
    if (!imu.dataAvailable())
        return false;

    // SparkFun accel outputs m/s^2
    double x = imu.getAccelX();
    double y = imu.getAccelY();
    double z = imu.getAccelZ();

    acc = Vector<3>(x, y, z);

    return true;
}

