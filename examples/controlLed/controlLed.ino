/*!
 * @file controlLed.ino
 * @brief 控制LED颜色值
 * @n 实验现象：板载LED灯每秒钟切换一次颜色
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#include <DFRobot_Sensor.h>
DFRobot_Sensor_IIC sensor(&Wire, sensor.eLowPower+sensor.eHighSpeed);
//DFRobot_Sensor_IIC sensor;//这样定义会使用默认参数，&Wire  eNomalPrecision+eNormalSpeed+eNormalPower

void setup(void)
{
  Serial.begin(115200);
  /*在这里一致等到芯片初始化完成才能退出*/
  while(sensor.begin() != 0){
    Serial.println("初始化芯片失败，请确认芯片连接是否正确");
    delay(1000);
  }
}

void loop(void)
{
  /*setLED函数用于点亮LED，可以直接指定颜色，如下参数都是可用的
  COLOR_RGB565_BLACK  COLOR_RGB565_NAVY  COLOR_RGB565_DGREEN  COLOR_RGB565_DCYAN   COLOR_RGB565_PURPLE
  COLOR_RGB565_MAROON COLOR_RGB565_OLIVE COLOR_RGB565_LGRAY   COLOR_RGB565_DGRAY   COLOR_RGB565_BLUE  
  COLOR_RGB565_GREEN  COLOR_RGB565_CYAN  COLOR_RGB565_RED     COLOR_RGB565_MAGENTA COLOR_RGB565_YELLOW      
  COLOR_RGB565_WHITE
  */
  sensor.setLED(COLOR_RGB565_PURPLE);
  delay(1000);
  sensor.setLED(COLOR_RGB565_YELLOW);
  delay(1000);
  
  /*setLED函数用于点亮LED，可以通过配置RGB分量，显示特定颜色
    r g b 分量的范围都是0-255
  */
  sensor.setLED(/*r=*/50, /*g=*/0,  /*b=*/0);
  delay(1000);
  sensor.setLED(0,  50, 0);
  delay(1000);
  sensor.setLED(0,  0,  50);
  delay(1000);
}