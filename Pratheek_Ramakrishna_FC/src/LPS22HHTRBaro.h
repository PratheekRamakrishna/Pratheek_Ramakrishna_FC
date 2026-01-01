#ifndef LPS22HHBAROMETER_H
#define LPS22HHBAROMETER_H

#include <Wire.h>
#include <LPS22HHSensor.h>
#include <Sensors/Baro/Barometer.h>

using namespace astra;

class LPS22HHBarometer : public Barometer
{
public:
    LPS22HHBarometer(const char *name = "LPS22HHBarometer",
                     TwoWire &bus = Wire,
                     uint8_t addr = LPS22HH_I2C_ADD_H);

    bool init() override;
    bool read() override;

private:
    TwoWire *wire;
    uint8_t address;

    // ST driver object (constructed with (TwoWire*, address))
    LPS22HHSensor baro;
};

#endif // LPS22HHBAROMETER_H
