#ifndef BNO085MAG_H
#define BNO085MAG_H

#include <Adafruit_BNO08x.h>
#include <Wire.h>
#include <Sensors/Mag/Mag.h>

using namespace astra;

class BNO085Mag : public Mag
{
public:
    BNO085Mag(const char *name = "BNO085Mag", TwoWire &bus = Wire, uint8_t addr = BNO08x_I2CADDR_DEFAULT);

    bool init() override;
    bool read() override;

private:
    Adafruit_BNO08x imu;
    TwoWire *wire;
    uint8_t address;
};

#endif // BNO085MAG_H