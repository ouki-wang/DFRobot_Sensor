# DFRobot_Sensor
这里写模块介绍介绍，做到读完这段，就能对模块有初步了解，让客户懂的用这个模块能干什么<br>

这里需要显示svg图，可以一张图片，可以多张图片
![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)

## DFRobot_Sensor Library for Arduino
---------------------------------------------------------

三两句话描述这个库的大概功能

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

这里填写当前Arduino软件库完成了哪些功能

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
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
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 


## History

- data 2019-6-25
- version V0.1


## Credits

Written by(ouki.wang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





