#ifndef BNO085ACCEL_H
#define BNO085ACCEL_H

#include <Adafruit_BNO08x.h>
#include <Wire.h>
#include <Sensors/Accel/Accel.h>

using namespace astra;

class BNO085Accel : public Accel
{
public:
    BNO085Accel(const char *name = "BNO085Accel", TwoWire &bus = Wire, uint8_t addr = BNO08x_I2CADDR_DEFAULT);
    bool init() override;
    bool read() override;

private:
    Adafruit_BNO08x imu;
    TwoWire *wire;
    uint8_t address;
};

#endif