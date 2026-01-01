#include "BNO085Accel.h"

BNO085Accel::BNO085Accel(const char *name, TwoWire &bus, uint8_t addr)
    : Accel(name),
      imu(-1),              // reset pin (keep -1 unless you wired reset)
      wire(&bus),
      address(addr)
{
    // Adafruit_BNO08x doesn't have enableDebugging(Serial) like SparkFun libs.
    // If you want debug prints, you'd do it in your own code (Serial.println etc.).
}

bool BNO085Accel::init()
{
    // Make sure Wire is initialized
    wire->begin();

    // Adafruit API: begin_I2C(i2c_addr, TwoWire*, sensor_id)
    if (!imu.begin_I2C(address, wire, 0))
    {
        LOGE("BNO08x Accel init failed (I2C addr: 0x%02X)", address);
        return false;
    }

    // Enable accelerometer reports.
    // interval_us default in Adafruit is 10000 (100 Hz) if omitted;
    // pick what you want. Here: 100 Hz.
    if (!imu.enableReport(SH2_ACCELEROMETER, 10000))
    {
        LOGE("BNO08x enableReport(SH2_ACCELEROMETER) failed");
        return false;
    }

    return true;
}

bool BNO085Accel::read()
{
    sh2_SensorValue_t v;

    // getSensorEvent returns true when a new event is available
    if (!imu.getSensorEvent(&v))
        return false;

    // We only care about accel events (since multiple reports can be enabled)
    if (v.sensorId != SH2_ACCELEROMETER)
        return false;

    // Adafruit/SH2 accelerometer values are typically in m/s^2 already.
    // If your downstream expects m/s^2, assign directly:
    acc = Vector<3>(
        (double)v.un.accelerometer.x,
        (double)v.un.accelerometer.y,
        (double)v.un.accelerometer.z
    );

    // If you discover your values are in "g" instead (rare for SH2 accel),
    // convert like this instead:
    // acc = Vector<3>(
    //     (double)v.un.accelerometer.x * 9.80665,
    //     (double)v.un.accelerometer.y * 9.80665,
    //     (double)v.un.accelerometer.z * 9.80665
    // );

    return true;
}
