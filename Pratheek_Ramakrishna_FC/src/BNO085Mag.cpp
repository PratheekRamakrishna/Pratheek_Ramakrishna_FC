#include "BNO085Mag.h"

BNO085Mag::BNO085Mag(const char *name, TwoWire &bus, uint8_t addr)
    : Mag(name),
      imu(-1),          // reset pin (use -1 unless wired)
      wire(&bus),
      address(addr)
{
}

bool BNO085Mag::init()
{
    // Ensure I2C bus is initialized
    wire->begin();

    // Initialize BNO085 over I2C
    if (!imu.begin_I2C(address, wire, 0))
    {
        LOGE("BNO085 Mag init failed (I2C addr: 0x%02X)", address);
        return false;
    }

    // Enable magnetometer reports (calibrated magnetic field)
    // 10000 us = 100 Hz
    if (!imu.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED, 10000))
    {
        LOGE("BNO085 enableReport(SH2_MAGNETIC_FIELD_CALIBRATED) failed");
        return false;
    }

    return true;
}

bool BNO085Mag::read()
{
    sh2_SensorValue_t v;

    if (!imu.getSensorEvent(&v))
        return false;

    if (v.sensorId != SH2_MAGNETIC_FIELD_CALIBRATED)
        return false;

    // BNO085 magnetometer output is in microtesla (µT)
    mag = Vector<3>(
        (double)v.un.magneticField.x,
        (double)v.un.magneticField.y,
        (double)v.un.magneticField.z
    );

    return true;
}
