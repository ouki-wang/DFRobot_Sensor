/*!
 * @file DFRobot_Sensor.h
 * @brief 定义DFRobot_Sensor 类的基础结构
 * @n 这是一个虚拟的传感器，IIC地址不可改变,不对应任何实物，可以通过IIC和SPI口来控制它，假设它有下面这些功能
 * @n 向寄存器0里写入数据，点亮不同颜色的LED灯
 * @n 从寄存器1里读出数据，高四位表示光线强度，低四位表示声音强度
 * @n 从寄存器2 bit0里写入数据，写1表示正常模式，写0表示低功耗模式
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#ifndef __DFROBOT_SENSOR_H
#define __DFROBOT_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#define DFRobot_Sensor_ID 0x66

#define SENSOR_ADDR_LED    0
#define SENSOR_ADDR_DATA   1
#define SENSOR_ADDR_CONFIG 2

#define  COLOR_BLACK     0x0000      // 黑色    
#define  COLOR_NAVY      0x000F      // 深蓝色  
#define  COLOR_DGREEN    0x03E0      // 深绿色  
#define  COLOR_DCYAN     0x03EF      // 深青色  
#define  COLOR_PURPLE    0x780F      // 紫色  
#define  COLOR_MAROON    0x7800      // 深红色      
#define  COLOR_OLIVE     0x7BE0      // 橄榄绿      
#define  COLOR_LGRAY     0xC618      // 灰白色
#define  COLOR_DGRAY     0x7BEF      // 深灰色      
#define  COLOR_BLUE      0x001F      // 蓝色    
#define  COLOR_GREEN     0x07E0      // 绿色          
#define  COLOR_CYAN      0x07FF      // 青色  
#define  COLOR_RED       0xF800      // 红色       
#define  COLOR_MAGENTA   0xF81F      // 品红    
#define  COLOR_YELLOW    0xFFE0      // 黄色        
#define  COLOR_WHITE     0xFFFF      // 白色  

typedef struct {
  uint8_t   b: 5;
  uint8_t   g: 6;
  uint8_t   r: 5;
} __attribute__ ((packed)) sColor_t;

typedef struct {
  uint8_t   light: 4;
  uint8_t   sound: 4;
} __attribute__ ((packed)) sCombinedData_t;


typedef struct {
  uint8_t   lowpower: 1;
  uint8_t   highspeed: 1;
  uint8_t   reserved: 7;
} __attribute__ ((packed)) sMode_t;

typedef enum{
  eNormalPower = 0,
  eLowPower = 1,
}eLowPowerMode_t;

typedef enum{
  eNormalSpeed = 0<<1,
  eHighSpeed = 1<<1,
}eHighSpeedMode_t;

class DFRobot_Sensor
{
public:
  /**
   * @brief 构造函数
   * @param mode 构造设备时，可以指定它的默认工作模式
   */
  DFRobot_Sensor(uint8_t mode);

  /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败
   */
  int begin(void);
  
  /**
   * @brief 获取声音强度值
   * @return 返回声音强度，单位是DB
   */
  uint16_t getSoundStrength(void);

  /**
   * @brief 获取光线强度值
   * @return 返回光线强度，单位是流明
   */
  uint16_t getLightStrength(void);
  
    /**
   * @brief 切换模式
   * @return 返回0操作成功, 返回其他值操作失败
   */
  //uint8_t switchMode(sMode_t mode);
  uint8_t switchMode(uint8_t mode);
  /**
   * @brief 设置LED灯的颜色
     @note  设置颜色后，0.2秒后生效
   * @param r 红色通道颜色值，范围0-255
   * @param g 绿色通道颜色值，范围0-255
   * @param b 蓝色通道颜色值，范围0-255
   */
  void setLED(uint8_t r, uint8_t g, uint8_t b);
  /**
   * @brief 设置LED灯的颜色
     @note  设置颜色后，0.2秒后生效
   * @param color rgb565格式的颜色值
   */
  void setLED(uint16_t color);

  protected:
  /**
   * @brief 写寄存器函数，设计为虚函数，由派生类实现函数体
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   */
  virtual void writeReg(uint8_t reg, void* pBuf, size_t size) = 0;
  
  /**
   * @brief 读取寄存器函数，设计为虚函数，由派生类实现函数体
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  virtual uint8_t readReg(uint8_t reg, void* pBuf, size_t size) = 0;

private:
  uint8_t _r, _g, _b;
  uint8_t _mode;
};

class DFRobot_Sensor_IIC:public DFRobot_Sensor{
public:
  DFRobot_Sensor_IIC(TwoWire *pWire, uint8_t mode);
  /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败
   */
  int begin(void);
protected:
  /**
   * @brief 通过IIC总线写入寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
   virtual void writeReg(uint8_t reg, void* pBuf, size_t size);
  /**
   * @brief 通过IIC总线读取寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  virtual uint8_t readReg(uint8_t reg, void* pBuf, size_t size);

private:
  TwoWire *_pWire;
  uint8_t _deviceAddr;
};


class DFRobot_Sensor_SPI:public DFRobot_Sensor{
public:
  DFRobot_Sensor_SPI(SPIClass *spi, uint8_t csPin, uint8_t mode);
  /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败
   */
  int begin(void);
protected:
  /**
   * @brief 通过SPI总线写入寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  virtual void writeReg(uint8_t reg, void* pBuf, size_t size);
  /**
   * @brief 通过SPI总线读取寄存器值
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  virtual uint8_t readReg(uint8_t reg, void* pBuf, size_t size);

private:
  SPIClass *_pSpi;
  uint8_t _csPin;
};
#endif
