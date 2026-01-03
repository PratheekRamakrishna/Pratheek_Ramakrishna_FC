#ifndef BNO085GYRO_H
#define BNO085GRYO_H

#include <SparkFun_BNO080_Arduino_Library.h>
#include <Wire.h>
#include <Sensors/Gyro/Gyro.h>

using namespace astra;

class BNO085Gyro : public Gyro
{
public:
    BNO085Gyro(const char *name = "BNO085Gyro", TwoWire &bus = Wire, uint8_t addr = BNO080_DEFAULT_ADDRESS);

    bool init() override;
    bool read() override;

private:
    BNO080 imu;
    TwoWire *wire;
    uint8_t address;
};

#endif // ICM20948GYRO_H