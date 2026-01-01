#include "BNO085Gyro.h"

BNO085Gyro::BNO085Gyro(const char *name, TwoWire &bus, uint8_t addr)
    : Gyro(name),
      imu(-1),          // reset pin (use -1 unless wired)
      wire(&bus),
      address(addr)
{
}

bool BNO085Gyro::init()
{
    // Ensure I2C bus is initialized
    wire->begin();

    // Initialize BNO085 over I2C (addr is typically 0x4A or 0x4B)
    if (!imu.begin_I2C(address, wire, 0))
    {
        LOGE("BNO085 Gyro init failed (I2C addr: 0x%02X)", address);
        return false;
    }

    // Enable gyro reports.
    // 10000 us = 100 Hz; adjust as needed.
    if (!imu.enableReport(SH2_GYROSCOPE_CALIBRATED, 10000))
    {
        LOGE("BNO085 enableReport(SH2_GYROSCOPE_CALIBRATED) failed");
        return false;
    }

    return true;
}

bool BNO085Gyro::read()
{
    sh2_SensorValue_t v;

    if (!imu.getSensorEvent(&v))
        return false;

    if (v.sensorId != SH2_GYROSCOPE_CALIBRATED)
        return false;

    // SH2 gyro is typically in rad/s already.
    // Keep as rad/s (same intent as your original, which output rad/s).
    angVel = Vector<3>(
        (double)v.un.gyroscope.x,
        (double)v.un.gyroscope.y,
        (double)v.un.gyroscope.z
    );

    // If you find your values are in deg/s (unlikely with SH2),
    // convert like this instead:
    // angVel = Vector<3>(
    //     (double)v.un.gyroscope.x * (M_PI / 180.0),
    //     (double)v.un.gyroscope.y * (M_PI / 180.0),
    //     (double)v.un.gyroscope.z * (M_PI / 180.0)
    // );

    return true;
}
