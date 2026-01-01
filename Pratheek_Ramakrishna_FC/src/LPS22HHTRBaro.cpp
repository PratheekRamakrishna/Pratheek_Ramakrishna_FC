#include "LPS22HHTRBaro.h"

LPS22HHBarometer::LPS22HHBarometer(const char *name, TwoWire &bus, uint8_t addr)
    : Barometer(name),
      wire(&bus),
      address(addr),
      baro(&bus, addr)   // ST driver wants (TwoWire*, address)
{
}

bool LPS22HHBarometer::init()
{
    // Ensure I2C bus is up
    wire->begin();

    // Initialize the sensor
    if (baro.begin() != LPS22HH_OK)
    {
        LOGE("LPS22HH begin() failed (addr: 0x%02X)", address);
        return false;
    }

    // Power up / enable measurements
    if (baro.Enable() != LPS22HH_OK)
    {
        LOGE("LPS22HH Enable() failed");
        return false;
    }

    // Optional: set output data rate (Hz). Pick what fits your loop.
    // Common values: 1, 10, 25, 50, 75, 100, 200
    if (baro.SetOutputDataRate(25.0f) != LPS22HH_OK)
    {
        LOGE("LPS22HH SetOutputDataRate() failed");
        return false;
    }

    return true;
}

bool LPS22HHBarometer::read()
{
    float p_hpa = 0.0f;
    float t_c   = 0.0f;

    if (baro.GetPressure(&p_hpa) != LPS22HH_OK)
        return false;

    if (baro.GetTemperature(&t_c) != LPS22HH_OK)
        return false;

    // ---- Store into your Barometer base class fields here ----

    //
    // Typical conventions:
    //   pressure = (double)p_hpa;        // in hPa (mbar)
    //   temperature = (double)t_c;       // in °C
    //
    // Or if your stack wants Pascals:
    //   pressure = (double)p_hpa * 100.0;

    pressure = (double)p_hpa;        // <-- adjust if your Barometer base differs
    temp = (double)t_c;       // <-- adjust if your Barometer base differs

    return true;
}
