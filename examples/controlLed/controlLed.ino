/*!
 * @file controlLed.ino
 * @brief 控制LED颜色值
 * @n 实验现象：板载LED灯每秒钟切换一次颜色
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/ouki-wang/DFRobot_Sensor
 */
#include <DFRobot_Sensor.h>
DFRobot_Sensor_IIC sensor(&Wire, eLowPower+eHighSpeed);

void setup(void)
{
  Serial.begin(115200);
  sensor.begin();
}

void loop(void)
{
  sensor.setLED(COLOR_PURPLE);
  delay(1000);
}
