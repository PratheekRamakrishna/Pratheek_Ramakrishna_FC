#include <Arduino.h>
#include <AstraRocket.h>
#include <Sensors/GPS/MAX_M10S.h>
#include "LPS22HHTRBaro.h"
#include "BNO085Accel.h"
#include "BNO085Gyro.h"
#include "BNO085Mag.h"

using namespace astra_rocket;

// Pick the correct BNO085 I2C addr for YOUR board:
// Common: 0x4A (default), sometimes 0x4B
static constexpr uint8_t BNO085_ADDR = 0x4A;

// LPS22HH typical I2C addrs depend on SA0; library defines LPS22HH_I2C_ADD_H / _L.
// Most boards use one of those (often 0x5D or 0x5C depending on the defines).
// If you're unsure, start with the library default and/or run an I2C scan.
static constexpr uint8_t LPS22HH_ADDR = LPS22HH_I2C_ADD_H;

AstraRocketConfig config = AstraRocketConfig()
    .withGPS(new MAX_M10S)
    .withBarometer(new LPS22HHBarometer("LPS22HH", Wire, LPS22HH_ADDR))
    .withAccel(new BNO085Accel("BNO085Accel", Wire, BNO085_ADDR))
    .withGyro(new BNO085Gyro("BNO085Gyro", Wire, BNO085_ADDR))
    .withMag(new BNO085Mag("BNO085Mag", Wire, BNO085_ADDR))
    .withSensorStatusLEDPin(32)
    .withGPSStatusLEDPin(31)
    .withFlightLogRate(5)
    .withPreflightLogRate(5);

AstraRocket rocket(config);

void setup()
{
  Serial.begin(115200);
  delay(2000);

  if (!rocket.init())
  {
    LOGE("ASTRA FAILED TO INIT");
  }
}

void loop()
{
  rocket.update();
}
