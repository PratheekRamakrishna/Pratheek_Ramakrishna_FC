#ifndef BNO085MAG_H
#define BNO085MAG_H

#include <SparkFun_BNO080_Arduino_Library.h>
#include <Wire.h>
#include <Sensors/Mag/Mag.h>

using namespace astra;

class BNO085Mag : public Mag
{
public:
    BNO085Mag(const char *name = "BNO085Mag",
              TwoWire &bus = Wire,
              uint8_t addr = BNO080_DEFAULT_ADDRESS);

    bool init() override;
    bool read() override;

private:
    BNO080 imu;        // SparkFun BNO080 driver
    TwoWire *wire;     // I2C bus
    uint8_t address;   // I2C address
};

#endif // BNO085MAG_H
