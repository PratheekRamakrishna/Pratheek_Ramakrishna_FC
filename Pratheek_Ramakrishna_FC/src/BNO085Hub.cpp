#include "BNO085Hub.h"

BNO085Hub::BNO085Hub(TwoWire& bus, uint8_t addr, uint8_t intPin)
  : wire(&bus), address(addr), intPin(intPin) {}

bool BNO085Hub::init(uint16_t period_ms)
{
  wire->begin();
  wire->setClock(400000);

  if (!imu.begin(address, *wire, intPin))
    return false;

  // Enable all reports ONCE
  imu.enableAccelerometer(period_ms);
  imu.enableGyro(period_ms);
  imu.enableMagnetometer(period_ms);

  return true;
}

bool BNO085Hub::poll()
{
  if (!imu.dataAvailable())
    return false;

  // Read *everything* after the one dataAvailable()
  s.ax = imu.getAccelX(); s.ay = imu.getAccelY(); s.az = imu.getAccelZ();
  s.gx = imu.getGyroX();  s.gy = imu.getGyroY();  s.gz = imu.getGyroZ();
  s.mx = imu.getMagX();   s.my = imu.getMagY();   s.mz = imu.getMagZ();

  s.hasAccel = true; s.hasGyro = true; s.hasMag = true;
  return true;
}
