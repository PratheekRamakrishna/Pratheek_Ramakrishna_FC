#ifndef BNO085GYRO_H
#define BNO085GRYO_H

#include <Adafruit_BNO08x.h>
#include <Wire.h>
#include <Sensors/Gyro/Gyro.h>

using namespace astra;

class BNO085Gyro : public Gyro
{
public:
    BNO085Gyro(const char *name = "BNO085Gyro", TwoWire &bus = Wire, uint8_t addr = BNO08x_I2CADDR_DEFAULT);

    bool init() override;
    bool read() override;

private:
    Adafruit_BNO08x imu;
    TwoWire *wire;
    uint8_t address;
};

#endif // ICM20948GYRO_H