#ifndef BNO085ACCEL_H
#define BNO085ACCEL_H

#include <SparkFun_BNO080_Arduino_Library.h>
#include <Wire.h>
#include <Sensors/Accel/Accel.h>

using namespace astra;

class BNO085Accel : public Accel
{
public:
    BNO085Accel(
        const char *name = "BNO085Accel",
        TwoWire &bus = Wire,
        uint8_t addr = BNO080_DEFAULT_ADDRESS
    );

    bool init() override;
    bool read() override;

private:
    BNO080 imu;        // SparkFun IMU class
    TwoWire *wire;
    uint8_t address;
};

#endif
