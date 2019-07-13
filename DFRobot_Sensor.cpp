/*!
 * @file DFRobot_Sensor.cpp
 * @brief 定义DFRobot_Sensor 类的基础结构，基础方法的实现
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#include <DFRobot_Sensor.h>
DFRobot_Sensor::DFRobot_Sensor(uint8_t mode):
  _mode(*((uint8_t*)&mode))
{
  
}

int DFRobot_Sensor::begin(void)
{
  writeReg(SENSOR_ADDR_CONFIG,&_mode,1);
  return 0;
}

uint16_t DFRobot_Sensor::getSoundStrength(void)
{
  sCombinedData_t data;
  readReg(SENSOR_ADDR_DATA, &data, sizeof(data));
  return data.sound << 6;
}

uint16_t DFRobot_Sensor::getLightStrength(void)
{
  sCombinedData_t data;
  readReg(SENSOR_ADDR_DATA, &data, sizeof(data));
  return data.light << 6;
}

void DFRobot_Sensor::setLED(uint8_t r, uint8_t g, uint8_t b)
{
  sColor_t data={.b=b>>3,.g=g>>2,.r=r>>3};
  writeReg(SENSOR_ADDR_LED, &data, sizeof(data));
}

void DFRobot_Sensor::setLED(uint16_t color)
{
  writeReg(SENSOR_ADDR_LED, &color, sizeof(color));
}

uint8_t DFRobot_Sensor::switchMode(uint8_t mode)
{
  writeReg(SENSOR_ADDR_CONFIG, &mode, sizeof(mode));
}

int DFRobot_Sensor_IIC::begin(void){
  Wire.begin();
  return DFRobot_Sensor::begin();
}

DFRobot_Sensor_IIC::DFRobot_Sensor_IIC(TwoWire *pWire, uint8_t mode)
  :DFRobot_Sensor(mode){
    _deviceAddr = DFRobot_Sensor_ID;
    _pWire = pWire;
}

void DFRobot_Sensor_IIC::writeReg(uint8_t reg, void* pBuf, size_t size)
{
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  for(uint16_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_Sensor_IIC::readReg(uint8_t reg, void* pBuf, size_t size)
{
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if( _pWire->endTransmission() != 0){
      return 0;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for(uint16_t i = 0; i < size; i++)
    _pBuf[i] = _pWire->read();
  _pWire->endTransmission();
  return size;
}

DFRobot_Sensor_SPI::DFRobot_Sensor_SPI(SPIClass *pSpi, uint8_t csPin, uint8_t mode)
  :DFRobot_Sensor(mode)
{
  _pSpi = pSpi;
  _csPin = csPin;
}

int DFRobot_Sensor_SPI::begin(void)
{
  pinMode(_csPin, OUTPUT);
  _pSpi->begin();
  DFRobot_Sensor::begin();
}

void DFRobot_Sensor_SPI::writeReg(uint8_t reg, void* pBuf, size_t size)
{
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_csPin, 0);
  _pSpi->transfer(reg);
  while(size--) {
    _pSpi->transfer(*_pBuf);
    _pBuf ++;
  }
  digitalWrite(_csPin, 1);
  SPI.endTransaction();
}

uint8_t DFRobot_Sensor_SPI::readReg(uint8_t reg, void* pBuf, size_t size)
{
  uint8_t * _pBuf = (uint8_t *)pBuf;
  size_t count = 0;
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_csPin, 0);
  _pSpi->transfer(reg);
  while(size--) {
    *_pBuf = SPI.transfer(0x00);
    _pBuf++;
    count++;
  }
  digitalWrite(_csPin, 1);
  _pSpi->endTransaction();
  return count;
}
