#include "BNO085Mag.h"

BNO085Mag::BNO085Mag(const char *name, TwoWire &bus, uint8_t addr)
    : Mag(name),
      wire(&bus),
      address(addr)
{
}

bool BNO085Mag::init()
{
    // Ensure I2C bus is initialized
    wire->begin();

    // SparkFun API:
    // begin(deviceAddress, wirePort, intPin)
    // intPin = 255 means "no interrupt pin"
    if (!imu.begin(address, *wire, 255))
    {
        LOGE("BNO085 Mag init failed (I2C addr: 0x%02X)", address);
        return false;
    }

    // SparkFun: enable magnetometer
    // timeBetweenReports is in milliseconds
    // 10 ms -> 100 Hz
    imu.enableMagnetometer(10);

    return true;
}

bool BNO085Mag::read()
{
    // SparkFun updates internal values when new data arrives
    if (!imu.dataAvailable())
        return false;

    // SparkFun magnetometer outputs microtesla (µT)
    mag = Vector<3>(
        (double)imu.getMagX(),
        (double)imu.getMagY(),
        (double)imu.getMagZ()
    );

    return true;
}
